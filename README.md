## robione_vehicle_interface

Vehicle interface for Robione facility robots that bridges Autoware control/status topics and a vehicle CAN bus via SocketCAN.

### Repository layout
- **Package `robione_vehicle_interface`**: ROS 2 components that translate Autoware messages to/from CAN frames and publish/subscribe relevant topics.
- **Package `robione_vehicle_interface_msgs`**: Custom message definitions used for debugging and introspection.

## Features
- Publishes vehicle status from CAN to Autoware topics: control mode, velocity, steering, gear, indicators, hazard lights, steering wheel status.
- Subscribes to Autoware commands and emits CAN frames: control, gear, indicators, hazard lights, emergency, plus a periodic life-signal.
- SocketCAN integration via the external `ros2_socketcan` bridge.
- Diagnostic status for message/CAN timeouts.

## Dependencies
- ROS 2 (Humble or later recommended)
- Autoware message packages: `autoware_vehicle_msgs`, `autoware_control_msgs`, `autoware_adapi_v1_msgs`, `tier4_vehicle_msgs`, `tier4_control_msgs`
- Common ROS deps: `rclcpp`, `rclcpp_components`, `diagnostic_updater`, `diagnostic_msgs`, `std_msgs`, `geometry_msgs`, `can_msgs`
- Robione/RobEff interfaces: `robione_vehicle_interface_msgs`, `robeff_msgs`
- SocketCAN bridge: `ros2_socketcan` (for `to_can_bus` and `/from_can_bus` topics)

Ensure these dependencies are available in your workspace or installed from your distribution.

## Build
1. Set up a ROS 2 workspace (e.g., `~/robione_ws`) and clone this repository into `src/`.
2. Source your ROS 2 setup: `source /opt/ros/$ROS_DISTRO/setup.bash`.
3. Build with colcon:
```bash
cd ~/robione_ws
colcon build --symlink-install --packages-up-to robione_vehicle_interface robione_vehicle_interface_msgs
source install/setup.bash
```

## Launch
There are two launch files in `robione_vehicle_interface`:

- `launch/robione_vehicle_interface.launch.xml`: starts the receiver and sender nodes.
- `launch/robione_vehicle_interface_all.launch.xml`: starts the interface above and includes the SocketCAN bridge from `ros2_socketcan`.

Example (including SocketCAN):
```bash
ros2 launch robione_vehicle_interface robione_vehicle_interface_all.launch.xml
```

If you already run your own SocketCAN bridge, use:
```bash
ros2 launch robione_vehicle_interface robione_vehicle_interface.launch.xml
```

### SocketCAN notes
- Bring your CAN interface up, for example: `sudo ip link set can0 up type can bitrate 500000` and `sudo ip link set up can0`.
- The `ros2_socketcan` launch typically exposes `to_can_bus` (publisher) and `/from_can_bus` (subscription) topics used by this package.

## Parameters
Parameters are provided via `config/robione_vehicle_interface.param.yaml` and loaded by both nodes.

- `base_frame_id` (string, default: `"base_link"`): Frame ID for velocity and related status.
- `can_recv_timeout_threshold` (double, seconds, default: `1.0`): Timeout for incoming CAN-derived status.
- `autoware_msg_timeout_threshold` (double, seconds, default: `1.0`): Timeout for Autoware command reception.
- `data_publish_rate` (int, Hz, default: `100`): Rate for publishing status topics.
- `can_data_send_rate` (int, Hz, default: `100`): Rate for sending CAN messages.
- `steering_angle_rate` (double, deg/s, default: `125.0`): Steering tire rotation rate used if unspecified in command.
- `vehicle_velocity_limit` (double, m/s, default: `4.2`): Velocity limit applied to outgoing motion commands.

Note: The code reads these parameters in each node at startup. Prefer changing the YAML rather than CLI for consistency.

## Nodes
This package provides two ROS 2 component nodes (registered with `rclcpp_components`):

### Node: `robione_vehicle_interface_can_receiver`
- Subscribes:
  - `/from_can_bus` (`can_msgs/msg/Frame`): Raw frames from SocketCAN bridge.
- Publishes (Autoware-compatible):
  - `/vehicle/status/control_mode` (`autoware_vehicle_msgs/msg/ControlModeReport`)
  - `/vehicle/status/velocity_status` (`autoware_vehicle_msgs/msg/VelocityReport`)
  - `/vehicle/status/steering_status` (`autoware_vehicle_msgs/msg/SteeringReport`)
  - `/vehicle/status/gear_status` (`autoware_vehicle_msgs/msg/GearReport`)
  - `/vehicle/status/turn_indicators_status` (`autoware_vehicle_msgs/msg/TurnIndicatorsReport`)
  - `/vehicle/status/hazard_lights_status` (`autoware_vehicle_msgs/msg/HazardLightsReport`)
  - `/vehicle/status/steering_wheel_status` (`tier4_vehicle_msgs/msg/SteeringWheelStatusStamped`)
- Publishes (debug/introspection):
  - `robione_vehicle_interface/vehicle_info` (`robione_vehicle_interface_msgs/msg/VehicleInfo`)
  - `robione_vehicle_interface/vehicle_status` (`robione_vehicle_interface_msgs/msg/VehicleStatus`)
- Diagnostics:
  - Reports timeouts for Vehicle Info and Vehicle Status reception.

### Node: `robione_vehicle_interface_can_sender`
- Subscribes (Autoware commands):
  - `/control/command/control_cmd` (`autoware_control_msgs/msg/Control`)
  - `/control/command/gear_cmd` (`autoware_vehicle_msgs/msg/GearCommand`)
  - `/control/command/turn_indicators_cmd` (`autoware_vehicle_msgs/msg/TurnIndicatorsCommand`)
  - `/control/command/hazard_lights_cmd` (`autoware_vehicle_msgs/msg/HazardLightsCommand`)
  - `/control/command/emergency_cmd` (`tier4_vehicle_msgs/msg/VehicleEmergencyStamped`)
  - `/api/ad_api_adapter/routing_state` (`autoware_adapi_v1_msgs/msg/RouteState`) for arrival events
  - `/api/ad_api_adapter/tablet_feedback` (`robeff_msgs/msg/TabletFeedback`) to clear arrival
  - `/api/sick/zone` (`robeff_msgs/msg/SickZone`) to restrict area detection
- Publishes:
  - `to_can_bus` (`can_msgs/msg/Frame`): Outgoing CAN frames to SocketCAN bridge
  - `/robione_vehicle_interface/vehicle_motion_cmd` (`robione_vehicle_interface_msgs/msg/VehicleMotionCommands`) for debug
  - `/robione_vehicle_interface/vehicle_cmd` (`robione_vehicle_interface_msgs/msg/VehicleCommands`) for debug
- Behavior:
  - Sends life-signal frames periodically.
  - Converts Autoware commands to CAN frames, including velocity, steering tire angle/rate, gear, indicators, hazard, emergency, horn (briefly after arrival), and safety override based on restricted area.
  - Diagnostics: flags timeout if control command not received within `autoware_msg_timeout_threshold`.

## Messages (from `robione_vehicle_interface_msgs`)
Custom messages used for debugging and introspection:
- `VehicleInfo.msg`, `VehicleStatus.msg`, `VehicleMotionCommands.msg`, `VehicleCommands.msg`.

## Development tips
- Use `rqt_graph` and `ros2 topic echo` to verify that topics flow between Autoware and CAN.
- If you change DBC or CAN layouts, update the C sources under `include/can_interface` and `src/can_interface/` accordingly and rebuild.

## License
Apache License 2.0

## Maintainer
`yelaydin <elaydin@robeff.com>`
