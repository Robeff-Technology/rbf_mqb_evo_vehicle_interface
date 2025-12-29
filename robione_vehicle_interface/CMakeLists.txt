cmake_minimum_required(VERSION 3.8)
project(robione_vehicle_interface)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(
        include
        include/can_interface
)

# find dependencies
find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

ament_auto_add_library(can_interface SHARED
        src/can_interface/vcu.c
        src/can_interface/vcu-binutil.c

)


ament_auto_add_library(robione_vehicle_interface_can_recv SHARED
        src/robione_vehicle_interface_can_receiver.cpp
        src/autoware_socketcan_bridge.cpp
)

ament_auto_add_library(robione_vehicle_interface_can_sender SHARED
        src/robione_vehicle_interface_can_sender.cpp
        src/autoware_socketcan_bridge.cpp
        src/serial_port.cpp
        src/ultrasonic.cpp
)

target_link_libraries(robione_vehicle_interface_can_recv can_interface)
target_link_libraries(robione_vehicle_interface_can_sender can_interface)

rclcpp_components_register_node(robione_vehicle_interface_can_recv
        PLUGIN "robione_vehicle_interface::RobioneVehicleInterfaceCanReceiver"
        EXECUTABLE robione_vehicle_interface_recv_node
)

rclcpp_components_register_node(robione_vehicle_interface_can_sender
        PLUGIN "robione_vehicle_interface::RobioneVehicleInterfaceCanSender"
        EXECUTABLE robione_vehicle_interface_sender_node
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

ament_auto_package(
        INSTALL_TO_SHARE
        launch
        config
)
