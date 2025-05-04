#include <memory>

#include "nav_pruebas/DestinationParserNode.hpp"

#include "rclcpp/rclcpp.hpp"

namespace nav_pruebas
{

using std::placeholders::_1;

DestinationParserNode::DestinationParserNode()
: Node("destination_parser_node")
{
  destination_sub_ = create_subscription<std_msgs::msg::Int32>(
    "/destination_topic", rclcpp::QoS(10),
    std::bind(&DestinationParserNode::detection_callback, this, std::placeholders::_1));

  destination_pub_ = create_publisher<std_msgs::msg::Int32>(
    "/real_destination", rclcpp::QoS(10));

}

void
DestinationParserNode::detection_callback(
  const std_msgs::msg::Int32::ConstSharedPtr & msg)
{

  if (msg->data == -1) {
    start_receiving_ = true;
    end_receiving_ = false;
  } else if (msg->data == 0) {
    start_receiving_ = false;
    end_receiving_ = true;
  }

  if (start_receiving_ && !end_receiving_) {

    if (msg->data != dest_id_) {
      dest_id_ = msg->data;
    }

  }

  if (end_receiving_) {
    std_msgs::msg::Int32 destination_msg;
    destination_msg.data = dest_id_;
    if (dest_id_ != -1) {
      destination_pub_->publish(destination_msg);
    }
    dest_id_ = -1;
    start_receiving_ = false;
    end_receiving_ = false;
  }


}

}// namespace nav_pruebas
