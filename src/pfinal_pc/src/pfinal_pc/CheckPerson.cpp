#include "pfinal_pc/CheckPerson.hpp"

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

CheckPerson::CheckPerson(
  const std::string & xml_tag_name,
  const BT::NodeConfiguration & conf)
: BT::ConditionNode(xml_tag_name, conf)
{
  conf.blackboard->get("node", node_);

  detection_sub_ = node_->create_subscription<vision_msgs::msg::Detection3DArray>(
    "/detections_3d", 10, std::bind(&CheckPerson::detection_callback, this, _1));

  detected_before_ = false;

}

void
CheckPerson::detection_callback(const vision_msgs::msg::Detection3DArray::SharedPtr msg)
{
  last_detection_ = msg;
}

BT::NodeStatus
CheckPerson::tick()
{
  if (!last_detection_) {
    return BT::NodeStatus::FAILURE;
  }

  for (const auto & detection : last_detection_->detections) {
    for (const auto & result : detection.results) {
      if (result.hypothesis.class_id == "person") {
        auto pos = detection.bbox.center.position;

        if (std::isnan(pos.x) || std::isinf(pos.x)) {
          continue;
        }

        double distance = std::sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);

        if (distance < 1.0) {
          if (detected_before_) {
            RCLCPP_INFO(node_->get_logger(), "-----> Person detected");
            return BT::NodeStatus::SUCCESS;
          } else {
            detected_before_ = true;
          }
        }
      }
    }
  }

  RCLCPP_INFO(node_->get_logger(), "-----> Waiting 4 person");
  return BT::NodeStatus::FAILURE;
}

} // namespace pfinal_pc

#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<pfinal_pc::CheckPerson>("check_person");
}
