cmake_minimum_required(VERSION 3.8)
project(nav_pruebas)

# Opciones de compilación
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Encuentra dependencias
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(message_filters REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(pcl_ros REQUIRED)

find_package(geometry_msgs REQUIRED)


find_package(OpenCV REQUIRED)

set(dependencies
  rclcpp
  sensor_msgs
  message_filters
  pcl_conversions
  pcl_ros
  geometry_msgs

)

include_directories(include)

# Crea la librería
add_library(${PROJECT_NAME} SHARED
  src/nav_pruebas/DestinationParserNode.cpp
)
ament_target_dependencies(${PROJECT_NAME} ${dependencies})


# Ejecutables

add_executable(destination_parser src/destination_parser.cpp)
ament_target_dependencies(destination_parser ${dependencies})
target_link_libraries(destination_parser ${PROJECT_NAME})


# Instalación
install(TARGETS
  ${PROJECT_NAME}
  destination_parser
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY DESTINATION share/${PROJECT_NAME})

# Testing
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)

  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)

  ament_lint_auto_find_test_dependencies()
endif()

# Exportaciones
ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(${dependencies})

ament_package()
