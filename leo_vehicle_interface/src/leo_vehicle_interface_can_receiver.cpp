#include "leo_vehicle_interface/leo_vehicle_interface_can_receiver.hpp"

#include "leo_vehicle_interface/autoware_socketcan_bridge.hpp"

namespace leo_vehicle_interface
{
LeoVehicleInterfaceCanReceiver::LeoVehicleInterfaceCanReceiver(const rclcpp::NodeOptions & options)
: Node{"leo_vehicle_interface_can_receiver", options}, diag_updater_{this}
{
  // params
  can_recv_timeout_threshold_ = declare_parameter("can_recv_timeout_threshold_", 2.0);
  data_publish_rate_ = declare_parameter("data_publish_rate", 100);
  base_frame_id_ = declare_parameter("base_frame_id", "base_link");

  // subscriptions
  can_frame_sub_ = this->create_subscription<can_msgs::msg::Frame>(
    "/from_can_bus", 100,
    std::bind(&LeoVehicleInterfaceCanReceiver::can_receive_callback, this, std::placeholders::_1));

  // publishers
  control_mechanism_temps_pub_ =
    this->create_publisher<leo_vehicle_interface_msgs::msg::ControlMechanismTemps>(
      "leo_vehicle_interface/control_mechanism_temps", 10);
  control_mechanism_volts_pub_ =
    this->create_publisher<leo_vehicle_interface_msgs::msg::ControlMechanismVolts>(
      "leo_vehicle_interface/control_mechanism_volts", 10);
  dynamic_sensor_frame_pub_ =
    this->create_publisher<leo_vehicle_interface_msgs::msg::DynamicSensorFrame>(
      "leo_vehicle_interface/dynamic_sensor_frame", 10);
  motion_info_pub_ = this->create_publisher<leo_vehicle_interface_msgs::msg::MotionInfo>(
    "leo_vehicle_interface/motion_info", 10);
  motor_info_pub_ = this->create_publisher<leo_vehicle_interface_msgs::msg::MotorInfo>(
    "leo_vehicle_interface/motor_info", 10);
  throttle_module_status_pub_ =
    this->create_publisher<leo_vehicle_interface_msgs::msg::ThrottleModuleStatus>(
      "leo_vehicle_interface/throttle_module_status", 10);
  vehicle_errors_pub_ = this->create_publisher<leo_vehicle_interface_msgs::msg::VehicleErrors>(
    "leo_vehicle_interface/vehicle_errors", 10);
  vehicle_info_pub_ = this->create_publisher<leo_vehicle_interface_msgs::msg::VehicleInfo>(
    "leo_vehicle_interface/vehicle_info", 10);
  vehicle_signal_status_pub_ =
    this->create_publisher<leo_vehicle_interface_msgs::msg::VehicleSignalStatus>(
      "leo_vehicle_interface/vehicle_signal_status", 10);
  wheel_speeds_pub_ = this->create_publisher<leo_vehicle_interface_msgs::msg::WheelSpeeds>(
    "leo_vehicle_interface/wheel_speeds", 10);

  // flux pusblishers
  flux_bus_status_pub_ =
    this->create_publisher<flux_pds_msgs::msg::BusStatus>("flux/bus_status", 10);
  flux_channel_status_pub_ =
    this->create_publisher<flux_pds_msgs::msg::ChannelStatus>("flux/channel_status", 10);
  flux_channel_currents_pub_ =
    this->create_publisher<flux_pds_msgs::msg::ChannelCurrents>("flux/channel_currents", 10);
  flux_channel_consumptions_pub_ = this->create_publisher<flux_pds_msgs::msg::ChannelConsumptions>(
    "flux/channel_consumptions", 10);

  // autoware publishers
  control_mode_pub_ = create_publisher<autoware_vehicle_msgs::msg::ControlModeReport>(
    "/vehicle/status/control_mode", rclcpp::QoS{1});
  vehicle_twist_pub_ = create_publisher<autoware_vehicle_msgs::msg::VelocityReport>(
    "/vehicle/status/velocity_status", rclcpp::QoS{1});
  steering_status_pub_ = create_publisher<autoware_vehicle_msgs::msg::SteeringReport>(
    "/vehicle/status/steering_status", rclcpp::QoS{1});
  gear_status_pub_ = create_publisher<autoware_vehicle_msgs::msg::GearReport>(
    "/vehicle/status/gear_status", rclcpp::QoS{1});
  turn_indicators_status_pub_ = create_publisher<autoware_vehicle_msgs::msg::TurnIndicatorsReport>(
    "/vehicle/status/turn_indicators_status", rclcpp::QoS{1});
  hazard_lights_status_pub_ = create_publisher<autoware_vehicle_msgs::msg::HazardLightsReport>(
    "/vehicle/status/hazard_lights_status", rclcpp::QoS{1});
  steering_wheel_status_pub_ =
    create_publisher<tier4_vehicle_msgs::msg::SteeringWheelStatusStamped>(
      "/vehicle/status/steering_wheel_status", 1);
  actuation_status_pub_ = create_publisher<tier4_vehicle_msgs::msg::ActuationStatusStamped>(
    "/vehicle/status/actuation_status", rclcpp::QoS{1});

  diag_updater_.setHardwareID("leo_vehicle_interface_can_receiver");
  diag_updater_.add("CAN Status", this, &LeoVehicleInterfaceCanReceiver::diagnostic_callback);

  // timer
  const auto period_ns = rclcpp::Rate(data_publish_rate_).period();
  data_publish_timer_ = rclcpp::create_timer(
    this, get_clock(), period_ns,
    std::bind(&LeoVehicleInterfaceCanReceiver::data_publish_timer_callback, this));
}

void LeoVehicleInterfaceCanReceiver::data_publish_timer_callback(void)
{
  control_mode_pub_->publish(AutowareSocketcanBridge::convert_to_autoware_control_mode_report(
    autonomous_rx_.VEHICLE_SIGNAL_STATUS));

  vehicle_twist_pub_->publish(AutowareSocketcanBridge::convert_to_autoware_velocity_report(
    autonomous_rx_.VEHICLE_INFO, autonomous_rx_.VEHICLE_SIGNAL_STATUS, base_frame_id_));

  steering_status_pub_->publish(
    AutowareSocketcanBridge::convert_to_autoware_steering_report(autonomous_rx_.VEHICLE_INFO));

  gear_status_pub_->publish(AutowareSocketcanBridge::convert_to_autoware_gear_report(
    autonomous_rx_.VEHICLE_SIGNAL_STATUS));

  turn_indicators_status_pub_->publish(
    AutowareSocketcanBridge::convert_to_autoware_turn_indicators_report(
      autonomous_rx_.VEHICLE_SIGNAL_STATUS));

  hazard_lights_status_pub_->publish(
    AutowareSocketcanBridge::convert_to_autoware_hazard_light_report(
      autonomous_rx_.VEHICLE_SIGNAL_STATUS));

  steering_wheel_status_pub_->publish(
    AutowareSocketcanBridge::convert_to_tier4_steering_wheel_status(
      autonomous_rx_.VEHICLE_INFO));

  actuation_status_pub_->publish(AutowareSocketcanBridge::convert_to_tier4_actuation_status(
    autonomous_rx_.MOTION_INFO, "base_link"));
}

void LeoVehicleInterfaceCanReceiver::can_receive_callback(can_msgs::msg::Frame::SharedPtr msg)
{
  static uint8_t check_currents_id = 0;
  static uint8_t check_consumptions_id = 0;
  if (autonomous_Receive(
        &(LeoVehicleInterfaceCanReceiver::autonomous_rx_), msg->data.data(), msg->id,
        msg->dlc)) {
    switch (msg->id) {
      case CONTROL_MECHANISM_TEMPS_CANID:
        receive_time_control_mechanism_temps_ = msg->header.stamp;
        publish_control_mechanism_temps(autonomous_rx_.CONTROL_MECHANISM_TEMPS);
        break;
      case CONTROL_MECHANISM_VOLTS_CANID:
        receive_time_control_mechanism_volts_ = msg->header.stamp;
        publish_control_mechanism_volts(autonomous_rx_.CONTROL_MECHANISM_VOLTS);
        break;
      case DYNAMIC_SENSOR_FRAME_CANID:
        receive_time_dynamic_sensor_frame_ = msg->header.stamp;
        publish_dynamic_sensor_frame(autonomous_rx_.DYNAMIC_SENSOR_FRAME);
        break;
      case MOTION_INFO_CANID:
        receive_time_motion_info_ = msg->header.stamp;
        publish_motion_info(autonomous_rx_.MOTION_INFO);
        break;
      case MOTOR_INFO_CANID:
        receive_time_motor_info_ = msg->header.stamp;
        publish_motor_info(autonomous_rx_.MOTOR_INFO);
        break;
      case THROTTLE_MODULE_STATUS_CANID:
        receive_time_throttle_module_status_ = msg->header.stamp;
        publish_throttle_module_status(autonomous_rx_.THROTTLE_MODULE_STATUS);
        break;
      case VEHICLE_ERRORS_CANID:
        receive_time_vehicle_errors_ = msg->header.stamp;
        publish_vehicle_errors(autonomous_rx_.VEHICLE_ERRORS);
        break;
      case VEHICLE_INFO_CANID:
        receive_time_vehicle_info_ = msg->header.stamp;
        publish_vehicle_info(autonomous_rx_.VEHICLE_INFO);
        break;
      case VEHICLE_SIGNAL_STATUS_CANID:
        receive_time_vehicle_signal_status_ = msg->header.stamp;
        publish_vehicle_signal_status(autonomous_rx_.VEHICLE_SIGNAL_STATUS);
        break;
      case WHEEL_SPEEDS_CANID:
        receive_time_wheel_speeds_ = msg->header.stamp;
        publish_wheel_speeds(autonomous_rx_.WHEEL_SPEEDS);
        break;
      default:
        break;
    }
  }

  if (flux_Receive(
        &(LeoVehicleInterfaceCanReceiver::flux_rx_), msg->data.data(), msg->id, msg->dlc)) {
    switch (msg->id) {
      case CHANNEL_STATUS_MSG_CANID:
        publish_flux_channel_status(flux_rx_.CHANNEL_STATUS_MSG);
        break;
      case BUS_STATUS_MSG_CANID:
        publish_flux_bus_status(flux_rx_.BUS_STATUS_MSG);
        break;
      case CURRENTS_1_MSG_CANID:
        check_currents_id |= 1;
        break;
      case CURRENTS_2_MSG_CANID:
        check_currents_id |= 2;
        break;
      case CURRENTS_3_MSG_CANID:
        check_currents_id |= 4;

        if (check_currents_id == 7) {
          publish_flux_channel_currents(
            flux_rx_.CURRENTS_1_MSG, flux_rx_.CURRENTS_2_MSG, flux_rx_.CURRENTS_3_MSG);
          check_currents_id = 0;
        }
        break;

      case CONSUMPTION_1_MSG_CANID:
        check_consumptions_id |= 1;
        break;
      case CONSUMPTION_2_MSG_CANID:
        check_consumptions_id |= 2;
        break;
      case CONSUMPTION_3_MSG_CANID:
        check_consumptions_id |= 4;
        if (check_consumptions_id == 7) {
          publish_flux_channel_consumptions(
            flux_rx_.CONSUMPTION_1_MSG, flux_rx_.CONSUMPTION_2_MSG, flux_rx_.CONSUMPTION_3_MSG);
          check_consumptions_id = 0;
          break;
        }
    }
  }
}

void LeoVehicleInterfaceCanReceiver::publish_control_mechanism_temps(
  const CONTROL_MECHANISM_TEMPS_t & control_mechanism_temps)
{
  auto msg = leo_vehicle_interface_msgs::msg::ControlMechanismTemps();
  msg.stamp = this->now();
  msg.pcb_temp_0 = control_mechanism_temps.pcb_temp_0;
  msg.pcb_temp_1 = control_mechanism_temps.pcb_temp_1;

  control_mechanism_temps_pub_->publish(msg);
}

void LeoVehicleInterfaceCanReceiver::publish_control_mechanism_volts(
  const CONTROL_MECHANISM_VOLTS_t & control_mechanism_volts)
{
  auto msg = leo_vehicle_interface_msgs::msg::ControlMechanismVolts();
  msg.stamp = this->now();
  msg.kl30_protected_voltage = control_mechanism_volts.ecu_kl30_protectd_voltage_phys;
  msg.kl30_2_protected_voltage = control_mechanism_volts.ecu_kl30_2_protectd_voltage_phys;

  msg.gatevcu_5v8_fb_voltage = control_mechanism_volts.ecu_5v8_fb_voltage_phys;
  msg.gatevcu_5v_fb_voltage = control_mechanism_volts.ecu_5v_fb_voltage_phys;

  msg.gatevcu_5v_supply_voltage_0 = control_mechanism_volts.ecu_5v_supply_0_voltage_phys;
  msg.gatevcu_5v_supply_voltage_1 = control_mechanism_volts.ecu_5v_supply_1_voltage_phys;
  msg.gatevcu_5v_supply_voltage_2 = control_mechanism_volts.ecu_5v_supply_2_voltage_phys;
  msg.gatevcu_5v_supply_voltage_3 = control_mechanism_volts.ecu_5v_supply_3_voltage_phys;
  msg.gatevcu_5v_supply_voltage_4 = control_mechanism_volts.ecu_5v_supply_4_voltage_phys;

  control_mechanism_volts_pub_->publish(msg);
}

void LeoVehicleInterfaceCanReceiver::publish_dynamic_sensor_frame(
  const DYNAMIC_SENSOR_FRAME_t & dynamic_sensor_frame)
{
  auto msg = leo_vehicle_interface_msgs::msg::DynamicSensorFrame();
  msg.stamp = this->now();
  msg.esp_lateral_acc = dynamic_sensor_frame.esp_lateral_acceleration_phys;
  msg.esp_longitudinal_acc = dynamic_sensor_frame.esp_longitudinal_acceleration_phys;
  msg.esp_yaw_rate = dynamic_sensor_frame.esp_yaw_rate_phys;
  msg.pitch = dynamic_sensor_frame.pitch_phys;
  msg.vehicle_mass = dynamic_sensor_frame.vehicle_mass_phys;

  dynamic_sensor_frame_pub_->publish(msg);
}

void LeoVehicleInterfaceCanReceiver::publish_motion_info(const MOTION_INFO_t & motion_info)
{
  auto msg = leo_vehicle_interface_msgs::msg::MotionInfo();
  msg.stamp = this->now();
  msg.steering_intervention = motion_info.steering_intervention;
  msg.brake_intervention = motion_info.brake_intervention;
  msg.acc_pedal_intervention = motion_info.acc_pedal_intervention;
  msg.throttle = motion_info.throttle_phys;
  msg.brake = motion_info.brake;
  msg.esp_brake_pressure = motion_info.ESP_brake_pressure_phys;
  msg.driver_brake = motion_info.driver_brake;

  motion_info_pub_->publish(msg);
}

void LeoVehicleInterfaceCanReceiver::publish_motor_info(const MOTOR_INFO_t & motor_info)
{
  auto msg = leo_vehicle_interface_msgs::msg::MotorInfo();
  msg.stamp = this->now();
  msg.motor_oil_temp = motor_info.motor_oil_temp_phys;
  msg.motor_coolant_temp = motor_info.motor_coolant_temp_phys;
  msg.motor_torque_setpoint_filtered = motor_info.motor_torque_setpoint_filtered_phys;
  msg.motor_torque_setpoint_raw = motor_info.motor_torque_setpoint_raw_phys;
  msg.motor_torque_total = motor_info.motor_torque_total_phys;
  msg.motor_rpm = motor_info.motor_rpm_phys;

  motor_info_pub_->publish(msg);
}

void LeoVehicleInterfaceCanReceiver::publish_throttle_module_status(
  const THROTTLE_MODULE_STATUS_t & throttle_module_status)
{
  auto msg = leo_vehicle_interface_msgs::msg::ThrottleModuleStatus();
  msg.stamp = this->now();
  msg.status = throttle_module_status.status;
  msg.target_throttle = throttle_module_status.target_throttle;
  msg.current_throttle = throttle_module_status.current_throttle;
  msg.dac_voltage_1 = throttle_module_status.dac_voltage_1_phys;
  msg.dac_voltage_2 = throttle_module_status.dac_voltage_2_phys;
  msg.fb_current = throttle_module_status.fb_current;

  throttle_module_status_pub_->publish(msg);
}

void LeoVehicleInterfaceCanReceiver::publish_vehicle_errors(const VEHICLE_ERRORS_t & vehicle_errors)
{
  auto msg = leo_vehicle_interface_msgs::msg::VehicleErrors();
  msg.stamp = this->now();

  vehicle_errors_pub_->publish(msg);
}

void LeoVehicleInterfaceCanReceiver::publish_vehicle_info(const VEHICLE_INFO_t & vehicle_info)
{
  auto msg = leo_vehicle_interface_msgs::msg::VehicleInfo();
  msg.stamp = this->now();
  msg.vehicle_velocity = vehicle_info.vehicle_velocity_phys;
  msg.steering_wheel_angle = vehicle_info.steering_wheel_angle_phys;
  msg.steering_wheel_speed = vehicle_info.steering_wheel_speed_phys;
  msg.steering_wheel_torque = vehicle_info.steering_wheel_torque;
  msg.steering_tire_angle = vehicle_info.steering_tire_angle_phys;
  vehicle_info_pub_->publish(msg);
}

void LeoVehicleInterfaceCanReceiver::publish_vehicle_signal_status(
  const VEHICLE_SIGNAL_STATUS_t & vehicle_signal_status)
{
  auto msg = leo_vehicle_interface_msgs::msg::VehicleSignalStatus();
  msg.stamp = this->now();
  msg.fuel = vehicle_signal_status.fuel;
  msg.blinker = vehicle_signal_status.blinker;
  msg.gear = vehicle_signal_status.gear;
  msg.target_gear_level = vehicle_signal_status.target_gear_level;
  msg.handbrake = vehicle_signal_status.hand_brake;
  msg.mode = vehicle_signal_status.mode;
  vehicle_signal_status_pub_->publish(msg);
}

void LeoVehicleInterfaceCanReceiver::publish_wheel_speeds(const WHEEL_SPEEDS_t & wheel_speeds)
{
  auto msg = leo_vehicle_interface_msgs::msg::WheelSpeeds();
  msg.stamp = this->now();
  msg.esp_bl_wheel_speed = wheel_speeds.esp_bl_wheel_speed_phys;
  msg.esp_br_wheel_speed = wheel_speeds.esp_br_wheel_speed_phys;
  msg.esp_fl_wheel_speed = wheel_speeds.esp_fl_wheel_speed_phys;
  msg.esp_fr_wheel_speed = wheel_speeds.esp_fr_wheel_speed_phys;
  wheel_speeds_pub_->publish(msg);
}

void LeoVehicleInterfaceCanReceiver::publish_flux_bus_status(const BUS_STATUS_MSG_t & bus_status)
{
  auto msg = flux_pds_msgs::msg::BusStatus();
  msg.stamp = this->now();
  msg.bus_voltage = bus_status.bus_voltage_phys;
  msg.bus_current = bus_status.bus_current_phys;
  msg.bus_power = bus_status.bus_power_phys;
  msg.bus_consumption = bus_status.bus_consumption_phys;

  flux_bus_status_pub_->publish(msg);
}

void LeoVehicleInterfaceCanReceiver::publish_flux_channel_status(
  const CHANNEL_STATUS_MSG_t & channel_status)
{
  auto msg = flux_pds_msgs::msg::ChannelStatus();
  msg.stamp = this->now();

  msg.ch1_status = channel_status.ch1_stat;
  msg.ch2_status = channel_status.ch2_stat;
  msg.ch3_status = channel_status.ch3_stat;
  msg.ch4_status = channel_status.ch4_stat;
  msg.ch5_status = channel_status.ch5_stat;
  msg.ch6_status = channel_status.ch6_stat;
  msg.ch7_status = channel_status.ch7_stat;
  msg.ch8_status = channel_status.ch8_stat;
  msg.ch9_status = channel_status.ch9_stat;
  msg.ch10_status = channel_status.ch10_stat;
  msg.ch11_status = channel_status.ch11_stat;
  msg.ch12_status = channel_status.ch12_stat;

  flux_channel_status_pub_->publish(msg);
}

void LeoVehicleInterfaceCanReceiver::publish_flux_channel_consumptions(
  const CONSUMPTION_1_MSG_t & consumptions_1, const CONSUMPTION_2_MSG_t & consumptions_2,
  const CONSUMPTION_3_MSG_t & consumptions_3)
{
  auto msg = flux_pds_msgs::msg::ChannelConsumptions();
  msg.stamp = this->now();

  msg.ch1_consumption = consumptions_1.ch1_cons_phys;
  msg.ch2_consumption = consumptions_1.ch2_cons_phys;
  msg.ch3_consumption = consumptions_1.ch3_cons_phys;
  msg.ch4_consumption = consumptions_1.ch4_cons_phys;
  msg.ch5_consumption = consumptions_2.ch5_cons_phys;
  msg.ch6_consumption = consumptions_2.ch6_cons_phys;
  msg.ch7_consumption = consumptions_2.ch7_cons_phys;
  msg.ch8_consumption = consumptions_2.ch8_cons_phys;
  msg.ch9_consumption = consumptions_3.ch9_cons_phys;
  msg.ch10_consumption = consumptions_3.ch10_cons_phys;
  msg.ch11_consumption = consumptions_3.ch11_cons_phys;
  msg.ch12_consumption = consumptions_3.ch12_cons_phys;

  flux_channel_consumptions_pub_->publish(msg);
}

void LeoVehicleInterfaceCanReceiver::publish_flux_channel_currents(
  const CURRENTS_1_MSG_t & currents_1, const CURRENTS_2_MSG_t & currents_2,
  const CURRENTS_3_MSG_t & currents_3)
{
  auto msg = flux_pds_msgs::msg::ChannelCurrents();
  msg.stamp = this->now();

  msg.ch1_current = currents_1.ch1_current_phys;
  msg.ch2_current = currents_1.ch2_current_phys;
  msg.ch3_current = currents_1.ch3_current_phys;
  msg.ch4_current = currents_1.ch4_current_phys;
  msg.ch5_current = currents_2.ch5_current_phys;
  msg.ch6_current = currents_2.ch6_current_phys;
  msg.ch7_current = currents_2.ch7_current_phys;
  msg.ch8_current = currents_2.ch8_current_phys;
  msg.ch9_current = currents_3.ch9_current_phys;
  msg.ch10_current = currents_3.ch10_current_phys;
  msg.ch11_current = currents_3.ch11_current_phys;
  msg.ch12_current = currents_3.ch12_current_phys;

  flux_channel_currents_pub_->publish(msg);
}

void LeoVehicleInterfaceCanReceiver::diagnostic_callback(
  diagnostic_updater::DiagnosticStatusWrapper & stat)
{
  double time_since_last_control_mechanism_temps =
    this->now().seconds() - receive_time_control_mechanism_temps_.seconds();
  double time_since_last_control_mechanism_volts =
    this->now().seconds() - receive_time_control_mechanism_volts_.seconds();
  double time_since_last_dynamic_sensor_frame =
    this->now().seconds() - receive_time_dynamic_sensor_frame_.seconds();
  double time_since_last_motion_info = this->now().seconds() - receive_time_motion_info_.seconds();
  double time_since_last_motor_info = this->now().seconds() - receive_time_motor_info_.seconds();
  double time_since_last_throttle_module_status =
    this->now().seconds() - receive_time_throttle_module_status_.seconds();
  double time_since_last_vehicle_errors =
    this->now().seconds() - receive_time_vehicle_errors_.seconds();
  double time_since_last_vehicle_info =
    this->now().seconds() - receive_time_vehicle_info_.seconds();
  double time_since_last_vehicle_signal_status =
    this->now().seconds() - receive_time_vehicle_signal_status_.seconds();
  double time_since_last_wheel_speeds =
    this->now().seconds() - receive_time_wheel_speeds_.seconds();

  if (time_since_last_control_mechanism_temps > can_recv_timeout_threshold_) {
    stat.add("Control Mechanism Temps", "No data received");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Control Mechanism Temps timeout");
  } else {
    stat.add("Control Mechanism Temps", "OK");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Control Mechanism Temps OK");
  }

  if (time_since_last_control_mechanism_volts > can_recv_timeout_threshold_) {
    stat.add("Control Mechanism Volts", "No data received");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Control Mechanism Volts timeout");
  } else {
    stat.add("Control Mechanism Volts", "OK");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Control Mechanism Volts OK");
  }

  if (time_since_last_dynamic_sensor_frame > can_recv_timeout_threshold_) {
    stat.add("Dynamic Sensor Frame", "No data received");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Dynamic Sensor Frame timeout");
  } else {
    stat.add("Dynamic Sensor Frame", "OK");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Dynamic Sensor Frame OK");
  }

  if (time_since_last_motion_info > can_recv_timeout_threshold_) {
    stat.add("Motion Info", "No data received");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Motion Info timeout");
  } else {
    stat.add("Motion Info", "OK");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Motion Info OK");
  }

  if (time_since_last_motor_info > can_recv_timeout_threshold_) {
    stat.add("Motor Info", "No data received");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Motor Info timeout");
  } else {
    stat.add("Motor Info", "OK");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Motor Info OK");
  }

  if (time_since_last_throttle_module_status > can_recv_timeout_threshold_) {
    stat.add("Throttle Module Status", "No data received");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Throttle Module Status timeout");
  } else {
    stat.add("Throttle Module Status", "OK");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Throttle Module Status OK");
  }

  if (time_since_last_vehicle_errors > can_recv_timeout_threshold_) {
    stat.add("Vehicle Errors", "No data received");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Vehicle Errors timeout");
  } else {
    stat.add("Vehicle Errors", "OK");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Vehicle Errors OK");
  }

  if (time_since_last_vehicle_info > can_recv_timeout_threshold_) {
    stat.add("Vehicle Info", "No data received");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Vehicle Info timeout");
  } else {
    stat.add("Vehicle Info", "OK");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Vehicle Info OK");
  }

  if (time_since_last_vehicle_signal_status > can_recv_timeout_threshold_) {
    stat.add("Vehicle Signal Status", "No data received");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Vehicle Signal Status timeout");
  } else {
    stat.add("Vehicle Signal Status", "OK");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Vehicle Signal Status OK");
  }

  if (time_since_last_wheel_speeds > can_recv_timeout_threshold_) {
    stat.add("Wheel Speeds", "No data received");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Wheel Speeds timeout");
  } else {
    stat.add("Wheel Speeds", "OK");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Wheel Speeds OK");
  }
}
}  // namespace leo_vehicle_interface

#include <rclcpp_components/register_node_macro.hpp>

RCLCPP_COMPONENTS_REGISTER_NODE(leo_vehicle_interface::LeoVehicleInterfaceCanReceiver)
