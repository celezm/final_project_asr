cmake_minimum_required(VERSION 3.8)
project(elp_stereo_camera)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(camera_info_manager REQUIRED)
find_package(PCL REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)





add_executable(stereo_camera_node src/stereo_camera_node.cpp)
ament_target_dependencies(stereo_camera_node
  rclcpp
  sensor_msgs
  cv_bridge
  OpenCV
  camera_info_manager)

add_executable(stereo_point_cloud_generator src/stereo_point_cloud_generator.cpp)
ament_target_dependencies(stereo_point_cloud_generator
  rclcpp
  sensor_msgs
  cv_bridge
  OpenCV
  PCL
  pcl_conversions
  camera_info_manager)

  add_executable(tf src/tf.cpp)
  ament_target_dependencies(tf
    rclcpp
    sensor_msgs
    cv_bridge
    OpenCV
    PCL
    tf2_ros
    geometry_msgs
    pcl_conversions
    camera_info_manager)


install(TARGETS
  stereo_camera_node
  DESTINATION lib/${PROJECT_NAME})


install(TARGETS
  stereo_point_cloud_generator
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS
  tf
  DESTINATION lib/${PROJECT_NAME})

# Install launch files
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}/
)

# Install configuration files
install(DIRECTORY config
  DESTINATION share/${PROJECT_NAME}/
)

# Install calibration files
install(DIRECTORY cam_params
  DESTINATION share/${PROJECT_NAME}/
)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

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
