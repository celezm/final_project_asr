#include "pfinal_pc/AskForDestinationNode.hpp"

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

AskForDestinationNode::AskForDestinationNode(
  const std::string & xml_tag_name,
  const BT::NodeConfiguration & conf)
: BT::SyncActionNode(xml_tag_name, conf)
{
  conf.blackboard->get("node", node_);
  
  publisher_ = node_->create_publisher<std_msgs::msg::Int32>("destination_topic", 10);

}

BT::NodeStatus
AskForDestinationNode::tick()
{

  // Los 10 destinos posibles
  std::vector<std::string> destinations = {
    "Teleco", "Aero", "Robótica", "Biomed", "Datos", "Arqui", "Paisajismo"};

  // Preguntar al usuario por un destino
  std::cout << "Por favor, elige un destino (1-7):\n";
  for (size_t i = 0; i < destinations.size(); ++i) {
      std::cout << i + 1 << ". " << destinations[i] << "\n";
  }

  int choice;
  std::cin >> choice;

  if (choice < 0 || choice > destinations.size()) {
      std::cout << "Destino inválido.\n";
      return BT::NodeStatus::FAILURE;
  }

  std_msgs::msg::Int32 msg;

  for (int i = 0; i < 5; ++i) {
    msg.data = -1;  // Publicar el índice como un número entero
    publisher_->publish(msg);
  }
  sleep(1);
  for (int i = 0; i < 5; ++i) {
    msg.data = choice;  // Publicar el índice como un número entero
    publisher_->publish(msg);
  }
  sleep(1);
  for (int i = 0; i < 5; ++i) {
    msg.data = 0;  // Publicar el índice como un número entero
    publisher_->publish(msg);
  }


  std::cout << "Has elegido: " << destinations[choice] << " (índice: " << choice << ")\n";

  return BT::NodeStatus::SUCCESS;
}


} // namespace pfinal_pc


/*
#include "behaviortree_cpp_v3/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<pfinal_pc::AskForDestinationNode>("AskForDestinationNode");
}*/
