#include "robione_vehicle_interface/robione_vehicle_interface.hpp"

#include <algorithm>
#include <chrono>
#include <cstring>

namespace robione_vehicle_interface
{
RobioneVehicleInterface::RobioneVehicleInterface(const rclcpp::NodeOptions & options)
: Node{"robione_vehicle_interface", options},
  params_{this},
  scheduler_{100},  // 100 Hz base rate
  vcu_ctrl_cmd_si_builder_{},
  safe_stat_ros2_heartbeat_builder_{},
  serial_port_name_{params_.get<std::string>("serial_port")},
  diag_updater_{this},
  cmd_rate_monitor_{
    {"control_cmd", params_.get_or<double>("expected_control_cmd_hz", 33.0)},
    {"gear_cmd", params_.get_or<double>("expected_gear_cmd_hz", 0.0)},
    {"turn_indicators_cmd", params_.get_or<double>("expected_turn_indicators_cmd_hz", 0.0)},
    {"hazard_lights_cmd", params_.get_or<double>("expected_hazard_lights_cmd_hz", 0.0)},
    {"vehicle_emergency_cmd", params_.get_or<double>("expected_vehicle_emergency_cmd_hz", 33.0)}},
  can_rate_monitor_{
    {"vcu_stat_motion", params_.get_or<double>("expected_vcu_stat_motion_hz", 50.0)},
    {"vcu_stat_vehicle_state", params_.get_or<double>("expected_vcu_stat_vehicle_state_hz", 50.0)}}
{
  is_horn_on_route_ = params_.get_or<bool>("is_horn_on_route", true);
  horn_duration_ = rclcpp::Duration::from_seconds(params_.get_or<double>("horn_duration_s", 10.0));
  params_.print_loaded_parameters();
  diag_updater_.setHardwareID("robione_vehicle_interface");
  diag_updater_.add("Serial Status", this, &RobioneVehicleInterface::diagnostic_serial_callback);
  diag_updater_.add("CAN Status", this, &RobioneVehicleInterface::diagnostic_can_callback);
  diag_updater_.add(
    "Autoware Command Rate", this, &RobioneVehicleInterface::diagnostic_cmd_rate_callback);
  init_subscribers();
  init_publishers();

  vcu_stat_publisher_.configure(
    *this, control_mode_pub_, vehicle_twist_pub_, steering_status_pub_, gear_status_pub_,
    turn_indicators_status_pub_, hazard_lights_status_pub_, battery_status_pub_,
    steering_wheel_status_pub_, params_.get<std::string>("base_frame_id"),
    vehicle_status_pub_);

  rx_validators_.emplace(
    VCU_STAT_MOTION_SI_CANID,
    CanMsgParser::AliveCrcValidator(
      VCU_STAT_MOTION_SI_CANID, "VCU_STAT_MOTION_SI", VCU_STAT_MOTION_SI_DLC));
  rx_validators_.emplace(
    VCU_STAT_VEHICLE_STATE_CANID,
    CanMsgParser::AliveCrcValidator(
      VCU_STAT_VEHICLE_STATE_CANID, "VCU_STAT_VEHICLE_STATE", VCU_STAT_VEHICLE_STATE_DLC));

  if (!openSerialFromConfig()) {
    // Try to open serial port from parameters/config
    RCLCPP_WARN(this->get_logger(), "Could not open serial port from config");
  }

  // Register tasks
  scheduler_.add_task(20, [this]() { task_20ms(); });  // 50 Hz
  scheduler_.add_task(50, [this]() { task_50ms(); });  // 20 Hz

  // 100 Hz base timer
  timer_100Hz_ = this->create_wall_timer(std::chrono::milliseconds(10), [this]() {
    scheduler_.tick();  // Runs tasks internally
  });
}

void RobioneVehicleInterface::init_subscribers()
{
  // Rain mode
  rain_mode_sub_ = this->create_subscription<std_msgs::msg::Bool>(
    "/robione_vehicle_interface/rain_mode", rclcpp::QoS{1}.transient_local(),
    std::bind(&RobioneVehicleInterface::rain_mode_callback, this, std::placeholders::_1));

  // socketcan topics
  can_frame_sub_ = this->create_subscription<can_msgs::msg::Frame>(
    "/from_can_bus", 100,
    std::bind(&RobioneVehicleInterface::can_receive_callback, this, std::placeholders::_1));

  // Autoware command subscriptions
  control_cmd_sub_ = create_subscription<autoware_control_msgs::msg::Control>(
    "/control/command/control_cmd", rclcpp::QoS(10).reliable(),
    std::bind(&RobioneVehicleInterface::control_cmd_callback, this, std::placeholders::_1));

  gear_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::GearCommand>(
    "/control/command/gear_cmd", rclcpp::QoS(5).reliable(),
    std::bind(&RobioneVehicleInterface::gear_cmd_callback, this, std::placeholders::_1));

  turn_indicators_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::TurnIndicatorsCommand>(
    "/control/command/turn_indicators_cmd", rclcpp::QoS(5).reliable(),
    std::bind(&RobioneVehicleInterface::turn_indicators_cmd_callback, this, std::placeholders::_1));

  hazard_lights_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::HazardLightsCommand>(
    "/control/command/hazard_lights_cmd", rclcpp::QoS(5).reliable(),
    std::bind(&RobioneVehicleInterface::hazard_lights_cmd_callback, this, std::placeholders::_1));

  vehicle_emergency_cmd_sub_ =
    create_subscription<tier4_vehicle_msgs::msg::VehicleEmergencyStamped>(
      "/control/command/emergency_cmd", rclcpp::QoS(10).reliable(),
      std::bind(
        &RobioneVehicleInterface::vehicle_emergency_cmd_callback, this, std::placeholders::_1));

  RCLCPP_INFO(this->get_logger(), "Creating route state subscription to /api/routing/state");
  sub_route_state_ = this->create_subscription<autoware_adapi_v1_msgs::msg::RouteState>(
    "/api/routing/state",
    rclcpp::QoS(1).transient_local().reliable(),
    std::bind(&RobioneVehicleInterface::route_state_callback, this, std::placeholders::_1));
  RCLCPP_INFO(this->get_logger(), "Route state subscription created successfully");

  tablet_feedback_sub_ = this->create_subscription<robeff_msgs::msg::TabletFeedback>(
    "/api/ad_api_adapter/tablet_feedback", rclcpp::QoS{1},
    std::bind(&RobioneVehicleInterface::tablet_feedback_callback, this, std::placeholders::_1));

  sick_zone_sub_ = this->create_subscription<robeff_msgs::msg::SickZone>(
    "/api/sick/zone", rclcpp::QoS(1).transient_local().reliable(),
    std::bind(&RobioneVehicleInterface::sick_zone_callback, this, std::placeholders::_1));

  primitive_emergency_detector_sub_ = this->create_subscription<std_msgs::msg::Bool>(
    "/perception/primitive_emergency_detector/emergency", 10,
    std::bind(
      &RobioneVehicleInterface::primitive_emergency_detector_callback, this,
      std::placeholders::_1));
}

void RobioneVehicleInterface::init_publishers()
{
  // socketcan
  can_frame_pub_ = create_publisher<can_msgs::msg::Frame>("to_can_bus", rclcpp::QoS(500));
  // autoware
  control_mode_pub_ = create_publisher<autoware_vehicle_msgs::msg::ControlModeReport>(
    "/vehicle/status/control_mode", rclcpp::QoS(10).reliable());
  vehicle_twist_pub_ = create_publisher<autoware_vehicle_msgs::msg::VelocityReport>(
    "/vehicle/status/velocity_status", rclcpp::QoS(10).reliable());
  steering_status_pub_ = create_publisher<autoware_vehicle_msgs::msg::SteeringReport>(
    "/vehicle/status/steering_status", rclcpp::QoS(10).reliable());
  gear_status_pub_ = create_publisher<autoware_vehicle_msgs::msg::GearReport>(
    "/vehicle/status/gear_status", rclcpp::QoS(5).reliable());
  turn_indicators_status_pub_ = create_publisher<autoware_vehicle_msgs::msg::TurnIndicatorsReport>(
    "/vehicle/status/turn_indicators_status", rclcpp::QoS(5).reliable());
  hazard_lights_status_pub_ = create_publisher<autoware_vehicle_msgs::msg::HazardLightsReport>(
    "/vehicle/status/hazard_lights_status", rclcpp::QoS(5).reliable());
  battery_status_pub_ = create_publisher<tier4_vehicle_msgs::msg::BatteryStatus>(
    "/vehicle/status/battery_charge", rclcpp::QoS(5).reliable());
  steering_wheel_status_pub_ =
    create_publisher<tier4_vehicle_msgs::msg::SteeringWheelStatusStamped>(
      "/vehicle/status/steering_wheel_status", rclcpp::QoS(10).reliable());
  vehicle_status_pub_ = create_publisher<robeff_msgs::msg::VehicleStatus>(
    "/robione_vehicle_interface/vehicle_status", rclcpp::QoS(10).reliable());
}

bool RobioneVehicleInterface::openSerialFromConfig()
{
  return openSerial(serial_port_name_, 115200);
}

bool RobioneVehicleInterface::openSerial(const std::string & port, unsigned int baud)
{
  try {
    serial_port_.set_port_name(port.c_str());
    serial_port_.open();
    serial_port_.configure(baud);
    RCLCPP_INFO(this->get_logger(), "Opened serial port %s at %u baud", port.c_str(), baud);
    serial_is_open_ = true;
    return true;
  } catch (const SerialPortException & e) {
    RCLCPP_ERROR(this->get_logger(), "SerialPortException[%s]: %s", port.c_str(), e.what());
    serial_is_open_ = false;
    return false;
  } catch (const std::exception & e) {
    RCLCPP_ERROR(this->get_logger(), "Exception opening serial[%s]: %s", port.c_str(), e.what());
    serial_is_open_ = false;
    return false;
  }
}

void RobioneVehicleInterface::can_receive_callback(can_msgs::msg::Frame::SharedPtr msg)
{
  // DBC SIDE
  auto validator_it = rx_validators_.find(msg->id);
  if (validator_it != rx_validators_.end()) {
    const auto result = validator_it->second.validate(*msg);
    if (!result.ok()) {
      const auto reason = validator_it->second.format_message(result);
      RCLCPP_WARN_THROTTLE(
        this->get_logger(), *this->get_clock(), 2000, "CAN RX %s invalid (0x%X): %s",
        validator_it->second.name().c_str(), msg->id, reason.c_str());
      return;
    }
  }

  const auto rec_id =
    pc_vcu_Receive(&(RobioneVehicleInterface::pc_vcu_rx_), msg->data.data(), msg->id, msg->dlc);
  if (rec_id != 0U) {
    // Successfully parsed the CAN frame
    auto it = can_watchdog_.find(msg->id);
    if (it != can_watchdog_.end()) {
      it->second.last_rx = now();
      it->second.seen = true;
    }

    if (rec_id == VCU_STAT_MOTION_SI_CANID) {
      vcu_stat_publisher_.publish_motion(pc_vcu_rx_.VCU_STAT_MOTION_SI);
      can_rate_monitor_.update("vcu_stat_motion", now());
    } else if (rec_id == VCU_STAT_VEHICLE_STATE_CANID) {
      vcu_stat_publisher_.publish_vehicle_state(pc_vcu_rx_.VCU_STAT_VEHICLE_STATE);
      can_rate_monitor_.update("vcu_stat_vehicle_state", now());
    } else if (rec_id == SAFETY_MANAGER_STATUS_CANID) {
      vcu_stat_publisher_.update_safety_status(pc_vcu_rx_.SAFETY_MANAGER_STATUS);
    } else if (rec_id == DTC_ERROR_STATUS_CANID) {
      uint64_t raw = 0U;
      std::memcpy(&raw, msg->data.data(), std::min<size_t>(msg->dlc, sizeof(uint64_t)));
      vcu_stat_publisher_.update_dtc_status(raw);
    } else if (rec_id == DTC_ERROR_STATUS_1_CANID) {
      uint64_t raw = 0U;
      std::memcpy(&raw, msg->data.data(), std::min<size_t>(msg->dlc, sizeof(uint64_t)));
      vcu_stat_publisher_.update_dtc_status_1(raw);
    } else if (rec_id == MCU_MODULE_STATUS_CANID) {
      vcu_stat_publisher_.update_mcu_status(pc_vcu_rx_.MCU_MODULE_STATUS);
    }
  }

}

void RobioneVehicleInterface::control_cmd_callback(
  const autoware_control_msgs::msg::Control::SharedPtr msg)
{
  vcu_ctrl_cmd_si_builder_.set_vehicle_speed_ms_cmd(msg->longitudinal.velocity);
  vcu_ctrl_cmd_si_builder_.set_tire_angle_rad_cmd(msg->lateral.steering_tire_angle);
  cmd_rate_monitor_.update("control_cmd", now());
}

void RobioneVehicleInterface::gear_cmd_callback(
  const autoware_vehicle_msgs::msg::GearCommand::SharedPtr msg)
{
  // Gear Req seems to be published without any problem in autoware side
  vcu_ctrl_cmd_si_builder_.set_gear_req(
    static_cast<CanMsgBuilder::VcuCtrlCmdSi::GearReq>(msg->command));
  cmd_rate_monitor_.update("gear_cmd", now());
}

void RobioneVehicleInterface::turn_indicators_cmd_callback(
  const autoware_vehicle_msgs::msg::TurnIndicatorsCommand::SharedPtr msg)
{
  if (msg->command == autoware_vehicle_msgs::msg::TurnIndicatorsCommand::ENABLE_LEFT) {
    vcu_ctrl_cmd_si_builder_.set_turn_left(true);
    vcu_ctrl_cmd_si_builder_.set_turn_right(false);
  } else if (msg->command == autoware_vehicle_msgs::msg::TurnIndicatorsCommand::ENABLE_RIGHT) {
    vcu_ctrl_cmd_si_builder_.set_turn_left(false);
    vcu_ctrl_cmd_si_builder_.set_turn_right(true);
  } else {  // NONE
    vcu_ctrl_cmd_si_builder_.set_turn_left(false);
    vcu_ctrl_cmd_si_builder_.set_turn_right(false);
  }
  cmd_rate_monitor_.update("turn_indicators_cmd", now());
}

void RobioneVehicleInterface::hazard_lights_cmd_callback(
  const autoware_vehicle_msgs::msg::HazardLightsCommand::SharedPtr msg)
{
  vcu_ctrl_cmd_si_builder_.set_hazard(
    msg->command == autoware_vehicle_msgs::msg::HazardLightsCommand::ENABLE);
  cmd_rate_monitor_.update("hazard_lights_cmd", now());
}

void RobioneVehicleInterface::vehicle_emergency_cmd_callback(
  const tier4_vehicle_msgs::msg::VehicleEmergencyStamped::SharedPtr msg)
{
  emergency_from_vehicle_cmd_ = msg && msg->emergency;
  update_merged_emergency_state();
  cmd_rate_monitor_.update("vehicle_emergency_cmd", now());
}

void RobioneVehicleInterface::route_state_callback(
  const autoware_adapi_v1_msgs::msg::RouteState::ConstSharedPtr msg)
{
  if (msg->state == autoware_adapi_v1_msgs::msg::RouteState::SET) {
    is_route_set_triggered_ = true;
    is_route_set_ = true;
    RCLCPP_INFO(this->get_logger(), "Route state is SET");
  } else {
    is_route_set_triggered_ = false;
    is_route_set_ = false;
    RCLCPP_INFO(this->get_logger(), "Route state is not SET");
  }

  if (msg->state == autoware_adapi_v1_msgs::msg::RouteState::ARRIVED) {
    is_arrived_triggered_ = true;
  }
}

void RobioneVehicleInterface::tablet_feedback_callback(
  const robeff_msgs::msg::TabletFeedback::ConstSharedPtr msg)
{
  if (
    msg->event_type == robeff_msgs::msg::TabletFeedback::ROUTE_COMPLETED ||
    msg->event_type == robeff_msgs::msg::TabletFeedback::ROUTE_REJECTED || msg->event_type == 6) {
    is_arrived_triggered_ = false;
    horn_active_ = false;
    vcu_ctrl_cmd_si_builder_.set_horn(false);
  }
}

void RobioneVehicleInterface::sick_zone_callback(
  const robeff_msgs::msg::SickZone::ConstSharedPtr msg)
{
  is_sick_zone_deactivated_ = (msg && msg->state == robeff_msgs::msg::SickZone::DEACTIVATE);

  if (is_sick_zone_deactivated_ || rain_mode_) {
    vcu_ctrl_cmd_si_builder_.set_safety_disable(true);
  } else {
    vcu_ctrl_cmd_si_builder_.set_safety_disable(false);
  }

  update_merged_emergency_state();
}

void RobioneVehicleInterface::primitive_emergency_detector_callback(
  const std_msgs::msg::Bool::ConstSharedPtr msg)
{
  emergency_from_primitive_detector_raw_ = msg && msg->data;
  update_merged_emergency_state();
}

void RobioneVehicleInterface::update_merged_emergency_state()
{
  const bool emergency_from_primitive_detector =  
    emergency_from_primitive_detector_raw_ && !is_sick_zone_deactivated_;
  const bool merged_emergency = emergency_from_vehicle_cmd_ || emergency_from_primitive_detector;
  // Emergency is 1 even there is no emergency
  vcu_ctrl_cmd_si_builder_.set_emergency_active(merged_emergency);
}

// Rain mode callback
// This callback handles the rain mode setting for the vehicle interface.
// If a valid message is received, it updates the rain_mode_ variable
// and logs the change. If the message is null, it logs a warning.
// Rain mode only changes if the incoming value is different from the current state.
// else, it logs that the rain mode was already set.
void RobioneVehicleInterface::rain_mode_callback(const std_msgs::msg::Bool::SharedPtr msg)
{
  if (msg) {
    if (rain_mode_ != msg->data) {
      rain_mode_ = msg->data;
      RCLCPP_INFO(this->get_logger(), "Rain mode set to: %s", rain_mode_ ? "enabled" : "disabled");
    } 
  }
}

void RobioneVehicleInterface::diagnostic_serial_callback(
  diagnostic_updater::DiagnosticStatusWrapper & stat)
{
  if (serial_is_open_) {
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Serial port is open");
    stat.add("Serial port", serial_port_name_);
  } else {
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::WARN, "Serial port is not open");
    stat.add("Serial port", serial_port_name_);
  }
}

void RobioneVehicleInterface::diagnostic_can_callback(
  diagnostic_updater::DiagnosticStatusWrapper & stat)
{
  stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "CAN ok");

  auto can_generate_emergency = false;
  // skip_disabled=true makes 0.0 Hz params work like other monitors
  const auto can_rate_status = can_rate_monitor_.report(stat, now(), can_generate_emergency, false, true);
  
  if (can_rate_status != RateMonitor::Status::OK) {
    stat.mergeSummary(diagnostic_msgs::msg::DiagnosticStatus::WARN, "CAN RX rate issue");
    vcu_ctrl_cmd_si_builder_.set_can_comm_fault(true);
  } else {
    vcu_ctrl_cmd_si_builder_.set_can_comm_fault(false);
  }

  for (const auto & kv : rx_validators_) {
    const auto & validator = kv.second;
    const auto crc_errors = validator.crc_error_count();
    const auto alive_errors = validator.alive_error_count();
    const auto dlc_errors = validator.dlc_error_count();

    if (crc_errors > 0U || alive_errors > 0U || dlc_errors > 0U) {
      stat.mergeSummary(diagnostic_msgs::msg::DiagnosticStatus::WARN, "CAN RX errors");
    }

    const std::string label = validator.name() + std::string("_rx");
    stat.addf(
      label.c_str(), "frames=%u crc_err=%u alive_err=%u dlc_err=%u", validator.frame_count(),
      crc_errors, alive_errors, dlc_errors);
  }
}

void RobioneVehicleInterface::diagnostic_cmd_rate_callback(
  diagnostic_updater::DiagnosticStatusWrapper & stat)
{
  const bool any_seen = cmd_rate_monitor_.any_seen();
  

  // Autonomous enable is not getting updated even the is_route_set_triggered_ is true
  // No problem at autoware side
  if (is_route_set_)
  {
    vcu_ctrl_cmd_si_builder_.set_autonomous_enable(true);
  }
  else
  {
    vcu_ctrl_cmd_si_builder_.set_autonomous_enable(false);
  }

  if (!any_seen) {
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::WARN, "No commands received yet");
    vcu_ctrl_cmd_si_builder_.set_autoware_comm_fault(true);
    return;
  }

  auto generate_emergency = false;
  cmd_rate_monitor_.report(stat, now(), generate_emergency, true, true);
  vcu_ctrl_cmd_si_builder_.set_autoware_comm_fault(generate_emergency);
}

void RobioneVehicleInterface::task_20ms()
{
  if(is_route_set_triggered_ && is_horn_on_route_) {
    if (horn_duration_.nanoseconds() > 0) {
      horn_active_ = true;
      horn_end_time_ = now() + horn_duration_;
      vcu_ctrl_cmd_si_builder_.set_horn(true);
    } else {
      vcu_ctrl_cmd_si_builder_.set_horn(false);
    }
    is_route_set_triggered_ = false;
  }
  if (is_arrived_triggered_ && !horn_active_) {
    if (horn_duration_.nanoseconds() > 0) {
      horn_active_ = true;
      horn_end_time_ = now() + horn_duration_;
      vcu_ctrl_cmd_si_builder_.set_horn(true);
    } else {
      vcu_ctrl_cmd_si_builder_.set_horn(false);
    }
    is_arrived_triggered_ = false;
  }

  if (horn_active_ && now() >= horn_end_time_) {
    horn_active_ = false;
    vcu_ctrl_cmd_si_builder_.set_horn(false);
  }
  can_frame_pub_->publish(vcu_ctrl_cmd_si_builder_.build_can_frame());
}
void RobioneVehicleInterface::task_50ms()
{
  safe_stat_ros2_heartbeat_builder_.set_ros_time_from_now();
  can_frame_pub_->publish(safe_stat_ros2_heartbeat_builder_.build_can_frame());
  vcu_stat_publisher_.publish_vehicle_status();
}
};  // namespace robione_vehicle_interface
#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(robione_vehicle_interface::RobioneVehicleInterface)
