cmake_minimum_required(VERSION 3.8)
project(leo_vehicle_interface_msgs)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

rosidl_generate_interfaces(${PROJECT_NAME}
        "msg/WheelSpeeds.msg"
        "msg/VehicleSignalStatus.msg"
        "msg/VehicleInfo.msg"
        "msg/VehicleErrors.msg"
        "msg/VehicleCommand.msg"
        "msg/ThrottleModuleStatus.msg"
        "msg/MotorInfo.msg"
        "msg/MotionInfo.msg"
        "msg/LongitudinalCommand.msg"
        "msg/FrontWheelCommand.msg"
        "msg/DynamicSensorFrame.msg"
        "msg/ControlMechanismVolts.msg"
        "msg/ControlMechanismTemps.msg"
        DEPENDENCIES std_msgs
        ADD_LINTER_TESTS
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
