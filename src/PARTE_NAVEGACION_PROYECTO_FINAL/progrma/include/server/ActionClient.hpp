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

#ifndef SERVER__ACTION_CLIENT_HPP
#define SERVER__ACTION_CLIENT_HPP

#include "interfaces_final/action/muevete.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

namespace server
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
  rclcpp_action::Client<muevete>::SharedPtr action_client_;
  bool finished_ {false};
  bool success_ {false};
};

}  // namespace server

#endif  // SERVER__ACTION_CLIENT_HPP
