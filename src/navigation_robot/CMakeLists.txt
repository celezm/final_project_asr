cmake_minimum_required(VERSION 3.8)
project(navigation_robot)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(nav2_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(interfaces_final REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(message_filters REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(pcl_ros REQUIRED)

set(dependencies
  rclcpp
  rclcpp_action
  nav2_msgs
  tf2_geometry_msgs
  std_msgs
  geometry_msgs
  interfaces_final
  sensor_msgs
  message_filters
  pcl_conversions
  pcl_ros
)

include_directories(include)

add_library(${PROJECT_NAME} SHARED
  src/navigation_robot/ActionClient.cpp
  src/navigation_robot/ActionServer.cpp
  src/navigation_robot/DestinationParserNode.cpp
)
ament_target_dependencies(${PROJECT_NAME} ${dependencies})

add_executable(client src/action_client_main.cpp)
ament_target_dependencies(client ${dependencies})
target_link_libraries(client ${PROJECT_NAME})

add_executable(server src/action_server_main.cpp)
ament_target_dependencies(server ${dependencies})
target_link_libraries(server ${PROJECT_NAME})

add_executable(destination_parser src/destination_parser.cpp)
ament_target_dependencies(destination_parser ${dependencies})
target_link_libraries(destination_parser ${PROJECT_NAME})


install(TARGETS
  ${PROJECT_NAME}
  client
  server
  destination_parser
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(include)
ament_export_dependencies(${dependencies})
ament_package()
