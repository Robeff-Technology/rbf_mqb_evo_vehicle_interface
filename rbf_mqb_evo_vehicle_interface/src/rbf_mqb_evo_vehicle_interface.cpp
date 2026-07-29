#include "rbf_mqb_evo_vehicle_interface/rbf_mqb_evo_vehicle_interface.hpp"

#include <chrono>

namespace rbf_mqb_evo_vehicle_interface
{
RbfMqbEvoVehicleInterface::RbfMqbEvoVehicleInterface(const rclcpp::NodeOptions & options)
: Node{"rbf_mqb_evo_vehicle_interface", options},
  params_{this},
  scheduler_{100},  // 100 Hz base rate
  vcu_ctrl_cmd_si_builder_{},
  safe_stat_ros2_heartbeat_builder_{},
  diag_updater_{this},
  cmd_rate_monitor_{
    {"control_cmd", params_.get_or<double>("expected_control_cmd_hz", 33.0)},
    {"gear_cmd", params_.get_or<double>("expected_gear_cmd_hz", 0.0)},
    {"vehicle_emergency_cmd", params_.get_or<double>("expected_vehicle_emergency_cmd_hz", 33.0)}},
  can_rate_monitor_{
    {"vcu_stat_motion", params_.get_or<double>("expected_vcu_stat_motion_hz", 50.0)},
    {"vcu_stat_vehicle_state", params_.get_or<double>("expected_vcu_stat_vehicle_state_hz", 50.0)}}
{
  vcu_ctrl_cmd_si_builder_.set_autonomous_enable(true);
  params_.print_loaded_parameters();
  diag_updater_.setHardwareID("rbf_mqb_evo_vehicle_interface");
  diag_updater_.add("CAN Status", this, &RbfMqbEvoVehicleInterface::diagnostic_can_callback);
  diag_updater_.add(
    "Autoware Command Rate", this, &RbfMqbEvoVehicleInterface::diagnostic_cmd_rate_callback);
  init_subscribers();
  init_publishers();
  init_services();

  vcu_stat_publisher_.configure(
    *this, control_mode_pub_, vehicle_twist_pub_, steering_status_pub_, gear_status_pub_,
    turn_indicators_status_pub_, hazard_lights_status_pub_,
    steering_wheel_status_pub_, params_.get<std::string>("base_frame_id"));

  rx_validators_.emplace(
    VCU_STAT_MOTION_SI_CANID,
    CanMsgParser::AliveCrcValidator(
      VCU_STAT_MOTION_SI_CANID, "VCU_STAT_MOTION_SI", VCU_STAT_MOTION_SI_DLC));
  rx_validators_.emplace(
    VCU_STAT_VEHICLE_STATE_CANID,
    CanMsgParser::AliveCrcValidator(
      VCU_STAT_VEHICLE_STATE_CANID, "VCU_STAT_VEHICLE_STATE", VCU_STAT_VEHICLE_STATE_DLC));

  // Register tasks
  scheduler_.add_task(20, [this]() { task_20ms(); });  // 50 Hz - VCU control command
  scheduler_.add_task(50, [this]() { task_50ms(); });  // 20 Hz - ROS2 heartbeat

  // 100 Hz base timer
  timer_100Hz_ = this->create_wall_timer(std::chrono::milliseconds(10), [this]() {
    scheduler_.tick();  // Runs tasks internally
  });
}

void RbfMqbEvoVehicleInterface::init_subscribers()
{
  // socketcan topics
  can_frame_sub_ = this->create_subscription<can_msgs::msg::Frame>(
    "/from_can_bus", 100,
    std::bind(&RbfMqbEvoVehicleInterface::can_receive_callback, this, std::placeholders::_1));

  // Autoware command subscriptions
  control_cmd_sub_ = create_subscription<autoware_control_msgs::msg::Control>(
    "/control/command/control_cmd", rclcpp::QoS(10).reliable(),
    std::bind(&RbfMqbEvoVehicleInterface::control_cmd_callback, this, std::placeholders::_1));

  gear_cmd_sub_ = create_subscription<autoware_vehicle_msgs::msg::GearCommand>(
    "/control/command/gear_cmd", rclcpp::QoS(5).reliable(),
    std::bind(&RbfMqbEvoVehicleInterface::gear_cmd_callback, this, std::placeholders::_1));

  vehicle_emergency_cmd_sub_ =
    create_subscription<tier4_vehicle_msgs::msg::VehicleEmergencyStamped>(
      "/control/command/emergency_cmd", rclcpp::QoS(10).reliable(),
      std::bind(
        &RbfMqbEvoVehicleInterface::vehicle_emergency_cmd_callback, this, std::placeholders::_1));

}

void RbfMqbEvoVehicleInterface::init_publishers()
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
  steering_wheel_status_pub_ =
    create_publisher<tier4_vehicle_msgs::msg::SteeringWheelStatusStamped>(
      "/vehicle/status/steering_wheel_status", rclcpp::QoS(10).reliable());
}

void RbfMqbEvoVehicleInterface::init_services()
{
  // Relative name so the service follows the node namespace
  clear_intervention_srv_ = create_service<std_srvs::srv::Trigger>(
    "clear_intervention",
    std::bind(
      &RbfMqbEvoVehicleInterface::clear_intervention_callback, this, std::placeholders::_1,
      std::placeholders::_2));
}

void RbfMqbEvoVehicleInterface::can_receive_callback(can_msgs::msg::Frame::SharedPtr msg)
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
    vehicle_cmd_status_module_dbc_Receive(&(RbfMqbEvoVehicleInterface::vehicle_cmd_status_module_dbc_rx_), msg->data.data(), msg->id, msg->dlc);
  if (rec_id != 0U) {
    // Successfully parsed the CAN frame
    auto it = can_watchdog_.find(msg->id);
    if (it != can_watchdog_.end()) {
      it->second.last_rx = now();
      it->second.seen = true;
    }

    if (rec_id == VCU_STAT_MOTION_SI_CANID) {
      vcu_stat_publisher_.publish_motion(vehicle_cmd_status_module_dbc_rx_.VCU_STAT_MOTION_SI);
      can_rate_monitor_.update("vcu_stat_motion", now());
    } else if (rec_id == VCU_STAT_VEHICLE_STATE_CANID) {
      vcu_stat_publisher_.publish_vehicle_state(vehicle_cmd_status_module_dbc_rx_.VCU_STAT_VEHICLE_STATE);
      can_rate_monitor_.update("vcu_stat_vehicle_state", now());
    }
  }

}

void RbfMqbEvoVehicleInterface::control_cmd_callback(
  const autoware_control_msgs::msg::Control::SharedPtr msg)
{
  vcu_ctrl_cmd_si_builder_.set_vehicle_speed_ms_cmd(msg->longitudinal.velocity);
  vcu_ctrl_cmd_si_builder_.set_tire_angle_rad_cmd(msg->lateral.steering_tire_angle);
  cmd_rate_monitor_.update("control_cmd", now());
}

void RbfMqbEvoVehicleInterface::gear_cmd_callback(
  const autoware_vehicle_msgs::msg::GearCommand::SharedPtr msg)
{
  // Gear Req seems to be published without any problem in autoware side
  vcu_ctrl_cmd_si_builder_.set_gear_req(
    static_cast<CanMsgBuilder::VcuCtrlCmdSi::GearReq>(msg->command));
  cmd_rate_monitor_.update("gear_cmd", now());
}

void RbfMqbEvoVehicleInterface::vehicle_emergency_cmd_callback(
  const tier4_vehicle_msgs::msg::VehicleEmergencyStamped::SharedPtr msg)
{
  vcu_ctrl_cmd_si_builder_.set_emergency_active(msg && msg->emergency);
  cmd_rate_monitor_.update("vehicle_emergency_cmd", now());
}

void RbfMqbEvoVehicleInterface::clear_intervention_callback(
  const std_srvs::srv::Trigger::Request::SharedPtr request,
  std_srvs::srv::Trigger::Response::SharedPtr response)
{
  (void)request;

  if (!can_frame_pub_) {
    response->success = false;
    response->message = "CAN publisher is not initialized";
    return;
  }

  if (can_frame_pub_->get_subscription_count() == 0U) {
    response->success = false;
    response->message = "No ros2_socketcan sender is connected to to_can_bus";
    return;
  }

  can_msgs::msg::Frame frame;
  frame.header.stamp = now();
  frame.header.frame_id = "can";

  frame.id = CLEAR_INTERVENTION_CMD_CANID;
  frame.dlc = CLEAR_INTERVENTION_CMD_DLC;
  frame.is_extended = true;
  frame.is_rtr = false;
  frame.is_error = false;
  frame.data.fill(0U);

  try {
    can_frame_pub_->publish(frame);
  } catch (const std::exception & exception) {
    response->success = false;
    response->message =
      std::string{"Failed to publish clear-intervention CAN frame: "} + exception.what();
    return;
  }

  RCLCPP_INFO(
    this->get_logger(), "Clear-intervention CAN frame (0x%X) published to to_can_bus",
    CLEAR_INTERVENTION_CMD_CANID);

  response->success = true;
  response->message = "Clear-intervention CAN frame published to to_can_bus";
}

void RbfMqbEvoVehicleInterface::diagnostic_can_callback(
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

void RbfMqbEvoVehicleInterface::diagnostic_cmd_rate_callback(
  diagnostic_updater::DiagnosticStatusWrapper & stat)
{
  const bool any_seen = cmd_rate_monitor_.any_seen();
  
  if (!any_seen) {
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::WARN, "No commands received yet");
    vcu_ctrl_cmd_si_builder_.set_autoware_comm_fault(true);
    return;
  }

  auto generate_emergency = false;
  cmd_rate_monitor_.report(stat, now(), generate_emergency, true, true);
  vcu_ctrl_cmd_si_builder_.set_autoware_comm_fault(generate_emergency);
}

void RbfMqbEvoVehicleInterface::task_20ms()
{
  // Send the current VCU control command (speed, tire angle, gear, emergency).
  // build_can_frame() applies CRC/alive-counter and any comm-fault override.
  can_frame_pub_->publish(vcu_ctrl_cmd_si_builder_.build_can_frame());
}

void RbfMqbEvoVehicleInterface::task_50ms()
{
  safe_stat_ros2_heartbeat_builder_.set_ros_time_from_now();
  can_frame_pub_->publish(safe_stat_ros2_heartbeat_builder_.build_can_frame());
}

};  // namespace rbf_mqb_evo_vehicle_interface
#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(rbf_mqb_evo_vehicle_interface::RbfMqbEvoVehicleInterface)
