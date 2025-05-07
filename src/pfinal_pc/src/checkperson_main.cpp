#include <string>
#include <memory>

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "behaviortree_cpp_v3/utils/shared_library.h"
#include "behaviortree_cpp_v3/loggers/bt_zmq_publisher.h"

#include "ament_index_cpp/get_package_share_directory.hpp"

#include "rclcpp/rclcpp.hpp"
#include "pfinal_pc/AskForDestinationNode.hpp"

#include "hri/dialog/speak.hpp"

#include "pfinal_pc/WaitForRobotNode.hpp"


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<rclcpp_cascade_lifecycle::CascadeLifecycleNode>("lfnode");
  auto basic_node = rclcpp::Node::make_shared("node");


  BT::BehaviorTreeFactory factory;
  BT::SharedLibrary loader;

  factory.registerNodeType<pfinal_pc::AskForDestinationNode>("AskForDestinationNode");
  factory.registerNodeType<pfinal_pc::WaitForRobotNode>("WaitForRobotNode");
  //factory.registerNodeType<dialog::Speak>("Speak");

  BT::NodeBuilder speak_builder = [](const std::string & name, const BT::NodeConfiguration & config) {
    return std::make_unique<dialog::Speak>(name, "say", config);
  };
  
  factory.registerBuilder<dialog::Speak>("Speak", speak_builder);
  

  factory.registerFromPlugin(loader.getOSName("pfinal_pc"));


  std::string pkgpath = ament_index_cpp::get_package_share_directory("pfinal_pc");
  std::string xml_file = pkgpath + "/bt_xml/btfinal.xml";

  auto blackboard = BT::Blackboard::create();
  blackboard->set("node", node);  // para Speak (espera CascadeLifecycleNode)
  blackboard->set("basic_node", basic_node);  // para nodos que usen rclcpp::Node

  
  BT::Tree tree = factory.createTreeFromFile(xml_file, blackboard);

  auto publisher_zmq = std::make_shared<BT::PublisherZMQ>(tree, 10, 1666, 1667);

  rclcpp::Rate rate(10);

  bool finish = false;

  while (!finish && rclcpp::ok()) {

    BT::NodeStatus status = tree.rootNode()->executeTick();

    if (status == BT::NodeStatus::SUCCESS) {
      RCLCPP_INFO(basic_node->get_logger(), "El árbol terminó con éxito.");
    } else if (status == BT::NodeStatus::FAILURE) {
      RCLCPP_ERROR(basic_node->get_logger(), "El árbol falló.");
    } else if (status == BT::NodeStatus::RUNNING) {
      RCLCPP_INFO(basic_node->get_logger(), "El árbol está ejecutándose.");
    }
    rclcpp::spin_some(node->get_node_base_interface());
    rclcpp::spin_some(basic_node);
    rate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
