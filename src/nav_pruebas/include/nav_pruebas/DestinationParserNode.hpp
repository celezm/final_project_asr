#ifndef DESTINATION_PARSER_NODE__YOLODETECTIONNODE_HPP_
#define DESTINATION_PARSER_NODE__YOLODETECTIONNODE_HPP_

#include <memory>

#include "std_msgs/msg/int32.hpp"

#include "rclcpp/rclcpp.hpp"

namespace nav_pruebas
{

class DestinationParserNode : public rclcpp::Node
{
public:
  DestinationParserNode();

private:
  int dest_id_ = -1;
  void detection_callback(const std_msgs::msg::Int32::ConstSharedPtr & msg);

  bool start_receiving_ = false;
  bool end_receiving_ = false;

  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr destination_sub_;
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr destination_pub_;
};

}  // namespace nav_pruebas

#endif  // DESTINATION_PARSER_NODE__YOLODETECTIONNODE_HPP_
