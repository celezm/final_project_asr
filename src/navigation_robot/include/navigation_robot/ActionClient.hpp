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

#ifndef NAVIGATION_ROBOT__ACTIONCLIENT_HPP_
#define NAVIGATION_ROBOT__ACTIONCLIENT_HPP_

#include <memory>  // C++ standard header

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "std_msgs/msg/int32.hpp"

#include "interfaces_final/action/muevete.hpp"


namespace navigation_robot
{

class ActionClient : public rclcpp::Node
{
public:
  using muevete = interfaces_final::action::Muevete;
  using goal = rclcpp_action::ClientGoalHandle<muevete>;

  ActionClient();

  void send_request(muevete::Goal goal);

  bool is_action_finished() {return finished_;}
  bool is_result_success() {return success_;}

protected:
  virtual void goal_response_callback(const goal::SharedPtr & goal_handle);
  virtual void feedback_callback(
    goal::SharedPtr,
    const std::shared_ptr<const muevete::Feedback> feedback);
  virtual void result_callback(const goal::WrappedResult & result);

private:
  void destination_callback(const std_msgs::msg::Int32::SharedPtr msg);
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr destination_sub_;

  rclcpp_action::Client<muevete>::SharedPtr action_client_;

  bool finished_ {false};
  bool success_ {false};
};

}  // namespace navigation_robot

#endif  // NAVIGATION_ROBOT__ACTIONCLIENT_HPP_
