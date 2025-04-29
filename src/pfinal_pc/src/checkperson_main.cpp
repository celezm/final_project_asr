#include <string>
#include <memory>

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "behaviortree_cpp_v3/utils/shared_library.h"
#include "behaviortree_cpp_v3/loggers/bt_zmq_publisher.h"

#include "ament_index_cpp/get_package_share_directory.hpp"

#include "rclcpp/rclcpp.hpp"


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::Node::make_shared("node");

  BT::BehaviorTreeFactory factory;
  BT::SharedLibrary loader;

  factory.registerFromPlugin(loader.getOSName("pfinal_pc"));

  std::string pkgpath = ament_index_cpp::get_package_share_directory("pfinal_pc");
  std::string xml_file = pkgpath + "/bt_xml/btree.xml";

  auto blackboard = BT::Blackboard::create();
  blackboard->set("node", node);
  BT::Tree tree = factory.createTreeFromFile(xml_file, blackboard);

  auto publisher_zmq = std::make_shared<BT::PublisherZMQ>(tree, 10, 1666, 1667);

  rclcpp::Rate rate(10);

  bool finish = false;

  while (!finish && rclcpp::ok()) {

    BT::NodeStatus status = tree.rootNode()->executeTick();

    if (status == BT::NodeStatus::SUCCESS) {
        RCLCPP_INFO(node->get_logger(), "El árbol terminó con éxito.");
    } else if (status == BT::NodeStatus::FAILURE) {
        RCLCPP_ERROR(node->get_logger(), "El árbol falló.");
    } else if (status == BT::NodeStatus::RUNNING) {
        RCLCPP_INFO(node->get_logger(), "El árbol está ejecutándose.");
    }

    rclcpp::spin_some(node);
    rate.sleep();
}

  rclcpp::shutdown();
  return 0;
}
