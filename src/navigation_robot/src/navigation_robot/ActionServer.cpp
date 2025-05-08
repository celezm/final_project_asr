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

#include "navigation_robot/ActionServer.hpp"
#include <cmath>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

namespace navigation_robot
{
ActionServer::ActionServer()
: Node("nav2_action_server", rclcpp::NodeOptions().clock_type(RCL_SYSTEM_TIME)),
  state_(State::DeCamino), current_times_(0), is_robot_inactive_(false)
{
  clock_ = std::make_shared<rclcpp::Clock>(RCL_SYSTEM_TIME);

  pub_goal_pose_ = create_publisher<geometry_msgs::msg::PoseStamped>("/goal_pose", 10);

  cmd_vel_sub_ = create_subscription<geometry_msgs::msg::Twist>(
      "/cmd_vel_nav", 10, std::bind(&ActionServer::cmd_vel_callback, this, std::placeholders::_1));

  exit_pub_ = create_publisher<std_msgs::msg::Int32>("/exit", 10);
  arrival_pub_ = create_publisher<std_msgs::msg::Int32>("/arrival", 10);
}

void ActionServer::start_server()
{
  navigate_action_server_ = rclcpp_action::create_server<muevete>(
      shared_from_this(),
      "muevete",
      std::bind(&ActionServer::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
      std::bind(&ActionServer::handle_cancel, this, std::placeholders::_1),
      std::bind(&ActionServer::handle_accepted, this, std::placeholders::_1));

  RCLCPP_INFO(get_logger(), "Action Server Ready.");
}

rclcpp_action::GoalResponse ActionServer::handle_goal(
  const rclcpp_action::GoalUUID & uuid,
  std::shared_ptr<const muevete::Goal> goal)
{
  (void)uuid;
  current_goal_ = *goal;

  RCLCPP_INFO(this->get_logger(), "Nuevo objetivo recibido: %d", current_goal_.objetivo);

  if (inactivity_timer_) {
    inactivity_timer_->cancel();
    inactivity_timer_ = nullptr;
  }

  return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse ActionServer::handle_cancel(
  const std::shared_ptr<rclcpp_action::ServerGoalHandle<muevete>> goal_handle)
{
  (void)goal_handle;
  RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
  timer_ = nullptr;
  return rclcpp_action::CancelResponse::ACCEPT;
}

void ActionServer::handle_accepted(
  std::shared_ptr<rclcpp_action::ServerGoalHandle<muevete>> goal_handle)
{
  goal_handle_ = goal_handle;
  state_ = State::DeCamino;
  current_times_ = 0;

  original_pose_ = get_target_pose(0);
  target_pose_ = get_target_pose(current_goal_.objetivo);
  pub_goal_pose_->publish(target_pose_);

  std_msgs::msg::Int32 exit_msg;
  exit_msg.data = 0;
  exit_pub_->publish(exit_msg);

  start_time_ = clock_->now();
  timer_ = create_wall_timer(1s, std::bind(&ActionServer::execute, this));

  if (!inactivity_timer_) {
    inactivity_timer_ = create_wall_timer(1s,
        std::bind(&ActionServer::check_robot_inactivity, this));
  }
}

void ActionServer::execute()
{
  auto feedback = std::make_shared<muevete::Feedback>();
  double elapsed_time = (clock_->now() - start_time_).seconds();
  feedback->progreso = elapsed_time;
  goal_handle_->publish_feedback(feedback);

  if (goal_handle_->is_canceling()) {
    auto result = std::make_shared<muevete::Result>();
    goal_handle_->canceled(result);
    timer_ = nullptr;
    return;
  }

  switch (state_) {
    case State::DeCamino:
      if (is_robot_inactive_) {
        RCLCPP_INFO(get_logger(), "Cambio a estado 'Esperando' por inactividad.");
        state_ = State::Esperando;
        wait_start_time_ = clock_->now();
      }
      break;

    case State::Esperando:
      if ((clock_->now() - wait_start_time_).seconds() >= 5.0) {
        RCLCPP_INFO(get_logger(), "Que tenga un buen dia.");
        pub_goal_pose_->publish(original_pose_);
        state_ = State::DeVuelta;
        current_times_ = 0;
      }
      break;

    case State::DeVuelta:
      if (elapsed_time >= 10.0) {
        auto result = std::make_shared<muevete::Result>();
        result->tiempo = elapsed_time;
        goal_handle_->succeed(result);
        RCLCPP_INFO(get_logger(), "Acción completada con éxito");
        timer_ = nullptr;
      }
      break;
  }
}

geometry_msgs::msg::PoseStamped ActionServer::get_target_pose(int8_t objetivo)
{
  geometry_msgs::msg::PoseStamped pose;
  pose.header.frame_id = "map";
  pose.pose.orientation.w = 1.0;

  switch (objetivo) {
    case 1:
      pose.pose.position.x = 2.8022539698638402;
      pose.pose.position.y = -0.03692829086813365;
      pose.pose.position.z = 0.0;
      pose.pose.orientation.z = 0.9979735770390689;
      pose.pose.orientation.w = 0.06362970636303165;
      break;
    case 2:
      pose.pose.position.x = 2.5262413231511873;
      pose.pose.position.y = -5.557544388255546;
      pose.pose.orientation.z = 0.9986985533156493;
      pose.pose.orientation.w = 0.05100195687646843;
      break;
    case 3:
      pose.pose.position.x = 6.354001422511894;
      pose.pose.position.y = -9.260028428042023;
      pose.pose.orientation.z = 0.9990618969271992;
      pose.pose.orientation.w = 0.043305035598953046;
      break;
    case 4:
      pose.pose.position.x = 4.342757226077335;
      pose.pose.position.y = -20.285307541090052;
      pose.pose.orientation.z = -0.7546133274416966;
      pose.pose.orientation.w = 0.6561697387470491;
      break;
    case 5:
      pose.pose.position.x = 8.37267236893634;
      pose.pose.position.y = -15.7874257693295;
      pose.pose.orientation.z = -0.7578510367606909;
      pose.pose.orientation.w = 0.6524276251667659;
      break;
    case 6:
      pose.pose.position.x = 8.483269894276182;
      pose.pose.position.y = -14.063548141799897;
      pose.pose.orientation.z = 0.6245611873656338;
      pose.pose.orientation.w = 0.7809758787801513;
      break;
    case 7:
      pose.pose.position.x = 20.857502775276778;
      pose.pose.position.y = -24.41759317978372;
      pose.pose.orientation.z = 0.9992327365563989;
      pose.pose.orientation.w = 0.039165523027406855;
      break;
    default:
      pose.pose.position.x = 0.0;
      pose.pose.position.y = 0.0;
      returning_ = true;
      break;
  }

  return pose;
}

void ActionServer::cmd_vel_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
{
  if (std::abs(msg->linear.x) > 0.01 || std::abs(msg->angular.z) > 0.01) {
    last_cmd_vel_time_ = clock_->now();
    is_robot_inactive_ = false;

    if (!inactivity_timer_) {
      inactivity_timer_ = create_wall_timer(1s,
          std::bind(&ActionServer::check_robot_inactivity, this));
    }

    inactivity_timer_->reset();
  }
}

void ActionServer::check_robot_inactivity()
{
  if ((clock_->now() - last_cmd_vel_time_).seconds() > 5.0) {
    RCLCPP_INFO(get_logger(), "Ha llegado a su destino.");
    is_robot_inactive_ = true;
    state_ = State::Esperando;

    std_msgs::msg::Int32 arrival_msg;
    arrival_msg.data = 0;
    arrival_pub_->publish(arrival_msg);
    returning_ = false;

    system("aplay /home/carlos/Desktop/2024_2025/SEGUNDO_CUATRI/ARQUI/ARQUITECTURA/asr_ws/src/final_project_arquitectura/src/navigation_robot/src/navigation_robot/p_45036753_703.wav");

    wait_start_time_ = clock_->now();
    inactivity_timer_->cancel();
  }
}
}  // namespace navigation_robot
