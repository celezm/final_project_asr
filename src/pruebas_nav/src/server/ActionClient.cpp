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

#include "server/ActionClient.hpp"

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

namespace server
{

using std::placeholders::_1;
using std::placeholders::_2;

ActionClient::ActionClient()
: Node("nav2_action_client")
{
  action_client_ = rclcpp_action::create_client<server::ActionClient::muevete>(
    this, "muevete");

  destination_sub_ = this->create_subscription<std_msgs::msg::Int32>(
    "/real_destination", 10,
    std::bind(&ActionClient::destination_callback, this, _1));
}

void ActionClient::destination_callback(const std_msgs::msg::Int32::SharedPtr msg)
{
  RCLCPP_INFO(this->get_logger(), "Destino recibido: %d", msg->data);
  destination_ = msg->data;
  destination_received_ = true;
}

void ActionClient::wait_and_send_goal()
{
  rclcpp::Rate rate(10);

  while (rclcpp::ok() && !destination_received_) {
    RCLCPP_INFO(this->get_logger(), "Esperando destino en /real_destination...");
    rclcpp::spin_some(this->get_node_base_interface());
    rate.sleep();
  }

  muevete::Goal goal;
  goal.objetivo = destination_;

  send_request(goal);
}

void
ActionClient::send_request(muevete::Goal goal)
{
  finished_ = false;
  success_ = false;

  if (!action_client_->wait_for_action_server()) {
    RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
    rclcpp::shutdown();
  }

  auto send_goal_options =
    rclcpp_action::Client<ActionClient::muevete>::SendGoalOptions();

  send_goal_options.goal_response_callback =
    std::bind(&ActionClient::goal_response_callback, this, _1);
  send_goal_options.feedback_callback =
    std::bind(&ActionClient::feedback_callback, this, _1, _2);
  send_goal_options.result_callback =
    std::bind(&ActionClient::result_callback, this, _1);

  action_client_->async_send_goal(goal, send_goal_options);
}

void
ActionClient::goal_response_callback(const goal::SharedPtr & goal_handle)
{
  if (!goal_handle) {
    RCLCPP_ERROR(get_logger(), "Goal was rejected by server");
  } else {
    RCLCPP_INFO(get_logger(), "Goal accepted by server, waiting for result");
  }
}

void
ActionClient::feedback_callback(
  goal::SharedPtr,
  std::shared_ptr<const muevete::Feedback> feedback)
{
  RCLCPP_INFO(
    get_logger(), "Feedback recibido: tiempo tardado = %f", feedback->progreso);
}

void
ActionClient::result_callback(const goal::WrappedResult & result)
{
  switch (result.code) {
    case rclcpp_action::ResultCode::SUCCEEDED:
      RCLCPP_INFO(get_logger(), "Goal achieved!!");
      break;
    case rclcpp_action::ResultCode::ABORTED:
      RCLCPP_ERROR(get_logger(), "Goal was aborted");
      return;
    case rclcpp_action::ResultCode::CANCELED:
      RCLCPP_ERROR(get_logger(), "Goal was canceled");
      return;
    default:
      RCLCPP_ERROR(get_logger(), "Unknown result code");
      return;
  }

  finished_ = true;
  success_ = result.code == rclcpp_action::ResultCode::SUCCEEDED;
}


}  // namespace server
