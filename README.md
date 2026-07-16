# rbf_mqb_evo_vehicle_interface

Autoware vehicle interface for the RBF MQB Evo platform. It bridges Autoware
control/status topics and the vehicle CAN bus (via SocketCAN), translating
Autoware command messages into CAN frames and CAN status frames back into
Autoware `/vehicle/status/*` topics.

The CAN layout is defined by the `vehicle_cmd_status_module_dbc` DBC; the
generated C packing/unpacking code lives under `include/can_interface/` and
`src/can_interface/`.

## Features
- Publishes vehicle status from CAN to Autoware: control mode, velocity,
  steering, gear, turn indicators, hazard lights, steering wheel.
- Subscribes to Autoware commands and emits CAN frames: longitudinal/lateral
  control, gear request, emergency, plus a periodic ROS2 life-signal heartbeat.
- CRC-8 (AUTOSAR) and alive-counter validation on incoming status frames.
- Diagnostics for CAN RX rate/integrity and Autoware command rate; command or
  CAN comm faults are reflected into the outgoing control frame.
- SocketCAN integration via the external `ros2_socketcan` bridge.

## Dependencies
- ROS 2 (Humble or later recommended)
- Autoware message packages: `autoware_control_msgs`, `autoware_vehicle_msgs`,
  `tier4_vehicle_msgs`
- Common ROS deps: `rclcpp`, `rclcpp_components`, `diagnostic_updater`,
  `diagnostic_msgs`, `can_msgs`
- SocketCAN bridge: `ros2_socketcan` (provides the `to_can_bus` / `/from_can_bus`
  topics) — only needed when talking to real hardware.

## Build
From your colcon workspace root:
```bash
source /opt/ros/$ROS_DISTRO/setup.bash
colcon build --packages-up-to rbf_mqb_evo_vehicle_interface
source install/setup.bash
```

## Launch
- `launch/rbf_mqb_evo_vehicle_interface.launch.xml` — the interface node alone
  (assumes a CAN bridge is already running).
- `launch/rbf_mqb_evo_vehicle_interface_all.launch.xml` — the interface plus the
  `ros2_socketcan` bridge, for real hardware.
- `launch/test_rx.launch.xml` — RX-only bench test: the interface plus
  `can_rx_test_publisher`, which injects synthetic status frames on
  `/from_can_bus`. No SocketCAN / hardware required.

Real hardware (bring the CAN interface up first):
```bash
sudo ip link set can0 up type can bitrate 500000
ros2 launch rbf_mqb_evo_vehicle_interface rbf_mqb_evo_vehicle_interface_all.launch.xml
```

Interface only (you run your own bridge):
```bash
ros2 launch rbf_mqb_evo_vehicle_interface rbf_mqb_evo_vehicle_interface.launch.xml
```

Bench test without hardware (observe `/vehicle/status/*`):
```bash
ros2 launch rbf_mqb_evo_vehicle_interface test_rx.launch.xml
ros2 topic echo /vehicle/status/velocity_status
```

## Node: `rbf_mqb_evo_vehicle_interface`
A single `rclcpp_components` node (executable
`rbf_mqb_evo_vehicle_interface_node`).

### Subscribes
- `/from_can_bus` (`can_msgs/msg/Frame`) — raw frames from the CAN bridge
- `/control/command/control_cmd` (`autoware_control_msgs/msg/Control`)
- `/control/command/gear_cmd` (`autoware_vehicle_msgs/msg/GearCommand`)
- `/control/command/emergency_cmd` (`tier4_vehicle_msgs/msg/VehicleEmergencyStamped`)

### Publishes
- `to_can_bus` (`can_msgs/msg/Frame`) — outgoing CAN frames
- `/vehicle/status/control_mode` (`autoware_vehicle_msgs/msg/ControlModeReport`)
- `/vehicle/status/velocity_status` (`autoware_vehicle_msgs/msg/VelocityReport`)
- `/vehicle/status/steering_status` (`autoware_vehicle_msgs/msg/SteeringReport`)
- `/vehicle/status/gear_status` (`autoware_vehicle_msgs/msg/GearReport`)
- `/vehicle/status/turn_indicators_status` (`autoware_vehicle_msgs/msg/TurnIndicatorsReport`)
- `/vehicle/status/hazard_lights_status` (`autoware_vehicle_msgs/msg/HazardLightsReport`)
- `/vehicle/status/steering_wheel_status` (`tier4_vehicle_msgs/msg/SteeringWheelStatusStamped`)

### CAN messages
- TX: `VCU_CTRL_CMD_SI` (speed, tire angle, gear request, autonomous-enable,
  emergency), `SAFE_STAT_ROS2_HEARTBEAT` (periodic life signal).
- RX: `VCU_STAT_MOTION_SI` (speed, tire/steer angle),
  `VCU_STAT_VEHICLE_STATE` (gear, turn/hazard/horn state, control mode).

### Diagnostics
- `CAN Status` — CAN RX rate plus per-message CRC / alive-counter / DLC errors.
- `Autoware Command Rate` — command reception rates vs expected.

> Note: autonomous-enable is not driven from a topic here; it is expected to be
> controlled externally (e.g. a physical button).

## Parameters
Provided via `config/rbf_mqb_evo_vehicle_interface.param.yaml`:

- `base_frame_id` (string, `"base_link"`): frame id used for velocity status.
- `expected_control_cmd_hz` (double, `33.0`): expected `control_cmd` rate.
- `expected_gear_cmd_hz` (double, `0.0`): expected `gear_cmd` rate (`0` disables the check).
- `expected_vehicle_emergency_cmd_hz` (double, `33.0`): expected `emergency_cmd` rate.
- `expected_vcu_stat_motion_hz` (double, `0.0`): expected `VCU_STAT_MOTION_SI` RX rate.
- `expected_vcu_stat_vehicle_state_hz` (double, `0.0`): expected `VCU_STAT_VEHICLE_STATE` RX rate.

A rate of `0.0` disables the rate check for that entry.

## Test publisher: `can_rx_test_publisher`
A standalone executable that publishes synthetic `VCU_STAT_MOTION_SI` and
`VCU_STAT_VEHICLE_STATE` frames on `/from_can_bus`, used by `test_rx.launch.xml`.
Parameters: `publish_topic`, `good_crc`, `good_alive`, `publish_rate_hz`,
`vehicle_state_rate_hz`.

## Development tips
- Use `rqt_graph` and `ros2 topic echo` to verify topics flow between Autoware
  and CAN.
- If the DBC changes, regenerate the C sources under `include/can_interface/`
  and `src/can_interface/` and rebuild.

## License
Apache License 2.0

## Maintainer
`yelaydin <elaydin@robeff.com>`
