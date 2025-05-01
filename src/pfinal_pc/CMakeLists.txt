cmake_minimum_required(VERSION 3.10)
project(pfinal_pc)

# Activar opciones de compilación si se usa GCC o Clang
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Buscar dependencias de ROS 2 y otros paquetes
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(vision_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(message_filters REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(PCL REQUIRED COMPONENTS common io)
find_package(behaviortree_cpp_v3 REQUIRED)

# Incluir directorios necesarios
include_directories(
  include
  ${PCL_INCLUDE_DIRS}
  include/pfinal_pc
)

# Crear la librería compartida del proyecto
add_library(${PROJECT_NAME} SHARED
  src/pfinal_pc/CheckPerson.cpp
  src/pfinal_pc/AskForDestinationNode.cpp
  src/pfinal_pc/WaitForRobotNode.cpp

)

# Vincular las dependencias necesarias para la librería
ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  vision_msgs
  sensor_msgs
  message_filters
  pcl_conversions
  behaviortree_cpp_v3
)

# Vincular las librerías de PCL necesarias
target_link_libraries(${PROJECT_NAME}
  ${PCL_LIBRARIES}
)

# Definir símbolos de compilación para la exportación del plugin
target_compile_definitions(${PROJECT_NAME} PRIVATE BT_PLUGIN_EXPORT)

# Instalar los archivos de la librería y encabezados
install(TARGETS ${PROJECT_NAME}
  DESTINATION lib
)

# Instalar los encabezados de tu proyecto
install(
  DIRECTORY include/
  DESTINATION include
)

# Instalar el directorio de los archivos XML para BehaviorTree
install(
  DIRECTORY bt_xml/
  DESTINATION share/${PROJECT_NAME}/bt_xml
)

# Ejecutable para ejecutar el árbol de comportamiento
add_executable(bt_runner src/checkperson_main.cpp)

# Dependencias del ejecutable
ament_target_dependencies(bt_runner
  rclcpp
  behaviortree_cpp_v3
  ament_index_cpp
)

# Vincular el ejecutable con la librería
target_link_libraries(bt_runner
  ${PROJECT_NAME}
)

# Instalar el ejecutable
install(TARGETS bt_runner
  DESTINATION lib/${PROJECT_NAME}
)

# Si estamos construyendo pruebas, habilitar linters (opcional)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # Saltar el linter de copyright si aún no has agregado un archivo de licencia
  set(ament_cmake_copyright_FOUND TRUE)
  # Saltar cpplint si no estás usando git
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# Finalizar el paquete para ament
ament_package()
