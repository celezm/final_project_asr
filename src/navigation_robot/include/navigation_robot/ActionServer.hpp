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

#ifndef NAVIGATION_ROBOT__ACTIONSERVER_HPP_
#define NAVIGATION_ROBOT__ACTIONSERVER_HPP_

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "std_msgs/msg/int32.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/twist.hpp"

#include "interfaces_final/action/muevete.hpp"

namespace navigation_robot
{
class ActionServer : public rclcpp::Node
{
public:
  using muevete = interfaces_final::action::Muevete;
  using goal = rclcpp_action::ServerGoalHandle<muevete>;

  ActionServer();
  void start_server();

private:
  enum class State { DeCamino, Esperando, DeVuelta };
  bool returning_ = false;

  rclcpp_action::GoalResponse handle_goal(
    const rclcpp_action::GoalUUID & uuid,
    std::shared_ptr<const muevete::Goal> goal);

  rclcpp_action::CancelResponse handle_cancel(
    const std::shared_ptr<rclcpp_action::ServerGoalHandle<muevete>> goal_handle);

  void handle_accepted(std::shared_ptr<rclcpp_action::ServerGoalHandle<muevete>> goal_handle);
  void execute();

  geometry_msgs::msg::PoseStamped get_target_pose(int8_t objetivo);
  void cmd_vel_callback(const geometry_msgs::msg::Twist::SharedPtr msg);
  void check_robot_inactivity();

  rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pub_goal_pose_;
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_sub_;
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr exit_pub_;
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr arrival_pub_;

  rclcpp_action::Server<muevete>::SharedPtr navigate_action_server_;
  std::shared_ptr<rclcpp_action::ServerGoalHandle<muevete>> goal_handle_;

  geometry_msgs::msg::PoseStamped target_pose_;
  geometry_msgs::msg::PoseStamped original_pose_;
  State state_;
  int current_times_;

  rclcpp::Time wait_start_time_;
  rclcpp::Time start_time_;
  rclcpp::Time last_cmd_vel_time_;

  std::shared_ptr<rclcpp::TimerBase> timer_;
  std::shared_ptr<rclcpp::TimerBase> inactivity_timer_;

  muevete::Goal current_goal_;
  bool is_robot_inactive_;

  // Reloj explícito del sistema
  rclcpp::Clock::SharedPtr clock_;
};
}  // namespace navigation_robot

#endif  // NAVIGATION_ROBOT__ACTIONSERVER_HPP_
