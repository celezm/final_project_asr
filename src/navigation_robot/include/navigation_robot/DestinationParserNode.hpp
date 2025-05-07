// Copyright 2025 Adrián Manzanares, Claudia Élez, Nerea Chamorro, Carlos García
// Licensed under the MIT License
// Copyright 2024 Intelligent Robotics Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef NAVIGATION_ROBOT__DESTINATIONPARSERNODE_HPP_
#define NAVIGATION_ROBOT__DESTINATIONPARSERNODE_HPP_

#include <memory>

#include "std_msgs/msg/int32.hpp"

#include "rclcpp/rclcpp.hpp"

namespace navigation_robot
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

}  // namespace navigation_robot

#endif  // NAVIGATION_ROBOT__DESTINATIONPARSERNODE_HPP_
