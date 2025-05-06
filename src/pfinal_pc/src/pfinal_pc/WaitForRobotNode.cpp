#include "pfinal_pc/WaitForRobotNode.hpp"

#include <string>
#include <iostream>
#include <memory>

#include "sensor_msgs/msg/point_cloud2.hpp"
#include "vision_msgs/msg/detection2_d_array.hpp"
#include "vision_msgs/msg/detection3_d_array.hpp"

#include "behaviortree_cpp_v3/behavior_tree.h"

#include "message_filters/subscriber.h"
#include "message_filters/sync_policies/approximate_time.h"

#include "pcl/point_types.h"
#include "pcl_conversions/pcl_conversions.h"
#include "pcl/point_types_conversion.h"

#include "rclcpp/rclcpp.hpp"

namespace pfinal_pc
{

using std::placeholders::_1;
using std::placeholders::_2;
using namespace std::chrono_literals;

WaitForRobotNode::WaitForRobotNode(
  const std::string & xml_tag_name,
  const BT::NodeConfiguration & conf)
: BT::ConditionNode(xml_tag_name, conf)
{
  conf.blackboard->get("node", node_);

  arrival_sub_ = node_->create_subscription<std_msgs::msg::Int32>(
    "/arrival", 10, std::bind(&WaitForRobotNode::arrival_callback, this, _1));

  exit_sub_ = node_->create_subscription<std_msgs::msg::Int32>(
      "/exit", 10, std::bind(&WaitForRobotNode::exit_callback, this, _1));
  exit_sub_.reset();

}

void
WaitForRobotNode::arrival_callback(const std_msgs::msg::Int32::SharedPtr msg)
{
  if (msg->data == 0) {
    std::cout << "El robot ha llegado.\n";

    if (once_) {
      arrival_sub_.reset();
      exit_sub_ = node_->create_subscription<std_msgs::msg::Int32>(
      "/exit", 10, std::bind(&WaitForRobotNode::exit_callback, this, _1));
      once_ = false;
      robot_arrived_ = true;
      return;
    }
    once_ = true;
  }
}

void
WaitForRobotNode::exit_callback(const std_msgs::msg::Int32::SharedPtr msg)
{
  if (msg->data == 0) {
    std::cout << "El robot ha salido al aula.\n";
    exit_sub_.reset();
    arrival_sub_ = node_->create_subscription<std_msgs::msg::Int32>(
      "/arrival", 10, std::bind(&WaitForRobotNode::arrival_callback, this, _1));
  }
}


BT::NodeStatus
WaitForRobotNode::tick()
{
  if (!robot_arrived_) {

    std::cout << "Esperando a que el robot llegue al destino...\n";
    return BT::NodeStatus::FAILURE;
  } else {
    std::cout << "El robot ha llegado al destino.\n";
    robot_arrived_ = false;  // Reset the flag for the next tick
    return BT::NodeStatus::SUCCESS;

  }
}


} // namespace pfinal_pc


/*
#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<pfinal_pc::WaitForRobotNode>("WaitForRobotNode");
}*/
