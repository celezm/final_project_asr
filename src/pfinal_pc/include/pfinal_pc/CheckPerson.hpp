#ifndef CHECK_PERSON_PF_HPP__
#define CHECK_PERSON_PF_HPP__

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

namespace pfinal_pc
{

class CheckPerson : public BT::ConditionNode
{

public:
  CheckPerson(
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

  rclcpp::Subscription<vision_msgs::msg::Detection3DArray>::SharedPtr detection_sub_;
  vision_msgs::msg::Detection3DArray::SharedPtr last_detection_;

  void detection_callback(const vision_msgs::msg::Detection3DArray::SharedPtr msg);

  bool detected_before_;

};

} // namespace pfinal_pc

#endif // CHECK_PERSON_PF_HPP__
