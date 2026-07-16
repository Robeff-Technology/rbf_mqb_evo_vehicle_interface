cmake_minimum_required(VERSION 3.8)
project(rbf_mqb_evo_vehicle_interface)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(
        include
        include/can_interface
)

# find dependencies
find_package(ament_cmake_auto REQUIRED)
find_package(tier4_vehicle_msgs REQUIRED)
ament_auto_find_build_dependencies()

ament_auto_add_library(can_interface SHARED
        src/can_interface/vehicle_cmd_status_module_dbc.c
        src/can_interface/vehicle_cmd_status_module_dbc-binutil.c

)


ament_auto_add_library(rbf_mqb_evo_vehicle_interface SHARED
        src/rbf_mqb_evo_vehicle_interface.cpp
        src/serial_port.cpp
)

ament_target_dependencies(rbf_mqb_evo_vehicle_interface
        rclcpp
        diagnostic_updater
        tier4_vehicle_msgs
        autoware_vehicle_msgs
        autoware_internal_planning_msgs
)

target_link_libraries(rbf_mqb_evo_vehicle_interface can_interface)

ament_auto_add_executable(can_rx_test_publisher
        src/can_rx_test_publisher.cpp
)
target_link_libraries(can_rx_test_publisher can_interface)

rclcpp_components_register_node(rbf_mqb_evo_vehicle_interface
        PLUGIN "rbf_mqb_evo_vehicle_interface::RbfMqbEvoVehicleInterface"
        EXECUTABLE rbf_mqb_evo_vehicle_interface_node
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
