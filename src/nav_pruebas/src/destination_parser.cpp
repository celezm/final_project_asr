#include <memory>

#include "nav_pruebas/DestinationParserNode.hpp"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node_detector = std::make_shared<nav_pruebas::DestinationParserNode>();

  rclcpp::spin(node_detector);

  rclcpp::shutdown();
  return 0;
}
