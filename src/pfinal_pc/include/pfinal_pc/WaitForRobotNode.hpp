#ifndef WAIR_FOR_ROBOT_NODE_HPP__
#define WAIR_FOR_ROBOT_NODE_HPP__

#include <string>
#include <memory>

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "sensor_msgs/msg/point_cloud2.hpp"
#include "vision_msgs/msg/detection2_d_array.hpp"
#include "vision_msgs/msg/detection3_d_array.hpp"

#include "message_filters/subscriber.h"
#include "message_filters/sync_policies/approximate_time.h"

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp" 


namespace pfinal_pc {

class WaitForRobotNode: public BT::ConditionNode
{

public:
  WaitForRobotNode(
    const std::string & xml_tag_name,
    const BT::NodeConfiguration & conf);
  
  // void halt() {}
  BT::NodeStatus tick();

  static BT::PortsList providedPorts()
  {
    return BT::PortsList({});
  }
private:
  rclcpp::Node::SharedPtr node_;
  bool robot_arrived_ = false;
  bool is_active_ = false;
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr arrival_sub_;
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr exit_sub_;


  void arrival_callback(const std_msgs::msg::Int32::SharedPtr msg);
  void exit_callback(const std_msgs::msg::Int32::SharedPtr msg);


};

} // namespace pfinal_pc

#endif // WAIR_FOR_ROBOT_NODE_HPP__