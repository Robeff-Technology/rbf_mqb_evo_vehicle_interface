#include "robione_vehicle_interface/robione_vehicle_interface_can_receiver.hpp"

#include "robione_vehicle_interface/autoware_socketcan_bridge.hpp"

namespace robione_vehicle_interface
{
RobioneVehicleInterfaceCanReceiver::RobioneVehicleInterfaceCanReceiver(const rclcpp::NodeOptions & options)
: Node{"robione_vehicle_interface_can_receiver", options}, diag_updater_{this}
{
  // params
  can_recv_timeout_threshold_ = declare_parameter("can_recv_timeout_threshold_", 2.0);
  data_publish_rate_ = declare_parameter("data_publish_rate", 100);
  base_frame_id_ = declare_parameter("base_frame_id", "base_link");

  // subscriptions
  can_frame_sub_ = this->create_subscription<can_msgs::msg::Frame>(
    "/from_can_bus", 100,
    std::bind(&RobioneVehicleInterfaceCanReceiver::can_receive_callback, this, std::placeholders::_1));

  // publishers
  vehicle_info_pub_ = this->create_publisher<robione_vehicle_interface_msgs::msg::VehicleInfo>(
    "robione_vehicle_interface/vehicle_info", 10);
  vehicle_status_pub_ =
    this->create_publisher<robione_vehicle_interface_msgs::msg::VehicleStatus>(
      "robione_vehicle_interface/vehicle_status", 10);

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
  // actuation_status_pub_ = create_publisher<tier4_vehicle_msgs::msg::ActuationStatusStamped>(
  //   "/vehicle/status/actuation_status", rclcpp::QoS{1});

  diag_updater_.setHardwareID("robione_vehicle_interface_can_receiver");
  diag_updater_.add("CAN Status", this, &RobioneVehicleInterfaceCanReceiver::diagnostic_callback);

  // timer
  const auto period_ns = rclcpp::Rate(data_publish_rate_).period();
  data_publish_timer_ = rclcpp::create_timer(
    this, get_clock(), period_ns,
    std::bind(&RobioneVehicleInterfaceCanReceiver::data_publish_timer_callback, this));
}

void RobioneVehicleInterfaceCanReceiver::data_publish_timer_callback(void)
{
  control_mode_pub_->publish(AutowareSocketcanBridge::convert_to_autoware_control_mode_report(
    vcu_rx_.VEHICLE_STATUS));

  vehicle_twist_pub_->publish(AutowareSocketcanBridge::convert_to_autoware_velocity_report(
    vcu_rx_.VEHICLE_INFO, vcu_rx_.VEHICLE_STATUS, base_frame_id_));

  steering_status_pub_->publish(
    AutowareSocketcanBridge::convert_to_autoware_steering_report(vcu_rx_.VEHICLE_INFO));

  gear_status_pub_->publish(AutowareSocketcanBridge::convert_to_autoware_gear_report(
    vcu_rx_.VEHICLE_STATUS));

  turn_indicators_status_pub_->publish(
    AutowareSocketcanBridge::convert_to_autoware_turn_indicators_report(
      vcu_rx_.VEHICLE_STATUS));

  hazard_lights_status_pub_->publish(
    AutowareSocketcanBridge::convert_to_autoware_hazard_light_report(
      vcu_rx_.VEHICLE_STATUS));

  steering_wheel_status_pub_->publish(
    AutowareSocketcanBridge::convert_to_tier4_steering_wheel_status(
      vcu_rx_.VEHICLE_INFO));
}

void RobioneVehicleInterfaceCanReceiver::can_receive_callback(can_msgs::msg::Frame::SharedPtr msg)
{
  if (vcu_Receive(
        &(RobioneVehicleInterfaceCanReceiver::vcu_rx_), msg->data.data(), msg->id,
        msg->dlc)) {
    switch (msg->id) {
      case VEHICLE_INFO_CANID:
        receive_time_vehicle_info_ = msg->header.stamp;
        publish_vehicle_info(vcu_rx_.VEHICLE_INFO);
        break;
      case VEHICLE_STATUS_CANID:
        receive_time_vehicle_status_ = msg->header.stamp;
        publish_vehicle_status(vcu_rx_.VEHICLE_STATUS);
        break;
      default:
        break;
    }
  }

}

void RobioneVehicleInterfaceCanReceiver::publish_vehicle_info(const VEHICLE_INFO_t & vehicle_info)
{
  auto msg = robione_vehicle_interface_msgs::msg::VehicleInfo();
  msg.stamp = this->now();
  msg.vehicle_velocity = vehicle_info.vehicle_velocity_phys;
  msg.steering_wheel_angle = vehicle_info.steering_wheel_angle_phys;
  msg.steering_wheel_speed = vehicle_info.steering_wheel_speed_phys;
  msg.steering_wheel_torque = vehicle_info.steering_wheel_torque;
  msg.steering_tire_angle = vehicle_info.steering_tire_angle_phys;
  vehicle_info_pub_->publish(msg);
}

void RobioneVehicleInterfaceCanReceiver::publish_vehicle_status(
  const VEHICLE_STATUS_t & vehicle_status)
{
  auto msg = robione_vehicle_interface_msgs::msg::VehicleStatus();
  msg.stamp = this->now();

  msg.battery_voltage = vehicle_status.battery_voltage;
  msg.battery_soc = vehicle_status.battery_soc;
  msg.blinker = vehicle_status.blinker;
  msg.headlight = vehicle_status.headlight;
  msg.gear = vehicle_status.gear;
  msg.mode = vehicle_status.mode;
  msg.handbrake = vehicle_status.hand_brake;
  vehicle_status_pub_->publish(msg);
}


void RobioneVehicleInterfaceCanReceiver::diagnostic_callback(
  diagnostic_updater::DiagnosticStatusWrapper & stat)
{
  double time_since_last_vehicle_info =
    this->now().seconds() - receive_time_vehicle_info_.seconds();
  double time_since_last_vehicle_status =
    this->now().seconds() - receive_time_vehicle_status_.seconds();

  if (time_since_last_vehicle_info > can_recv_timeout_threshold_) {
    stat.add("Vehicle Info", "TIMEOUT");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Vehicle Info timeout");
  } else {
    stat.add("Vehicle Info", "OK");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Vehicle Info OK");
  }

  if (time_since_last_vehicle_status > can_recv_timeout_threshold_) {
    stat.add("Vehicle Status", "TIMEOUT");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Vehicle Signal Status timeout");
  } else {
    stat.add("Vehicle Status", "OK");
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Vehicle Signal Status OK");
  }
}
}  // namespace robione_vehicle_interface

#include <rclcpp_components/register_node_macro.hpp>

RCLCPP_COMPONENTS_REGISTER_NODE(robione_vehicle_interface::RobioneVehicleInterfaceCanReceiver)
