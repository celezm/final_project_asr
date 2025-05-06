#include "server/ActionServer.hpp"
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <cmath>

using namespace std::chrono_literals;

namespace server
{
  ActionServer::ActionServer()
  : Node("nav2_action_server"), state_(State::DeCamino), current_times_(0), is_robot_inactive_(false)
  {
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

    // Reiniciar el temporizador de inactividad
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

  void ActionServer::handle_accepted(std::shared_ptr<rclcpp_action::ServerGoalHandle<muevete>> goal_handle)
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

    start_time_ = now();
    timer_ = create_wall_timer(1s, std::bind(&ActionServer::execute, this));

    // Reiniciar el temporizador de inactividad
    if (!inactivity_timer_) {
      inactivity_timer_ = create_wall_timer(1s, std::bind(&ActionServer::check_robot_inactivity, this));
    }
  }

  void ActionServer::execute()
  {
    // Crear un feedback para enviar
    auto feedback = std::make_shared<muevete::Feedback>();

    // Calcular el tiempo transcurrido en segundos
    double elapsed_time = (this->now() - start_time_).seconds();

    // Actualizar el feedback con el tiempo transcurrido
    feedback->progreso = elapsed_time;

    // Publicar el feedback con el tiempo
    goal_handle_->publish_feedback(feedback);

    // Si el goal está siendo cancelado, finalizar el proceso
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
          wait_start_time_ = now();
        }
        break;

      case State::Esperando:
        //RCLCPP_INFO(get_logger(), "Que tenga un buen dia.");
        if ((this->now() - wait_start_time_).seconds() >= 5.0) {
          // En vez de mostrar mensaje de inactividad, mostramos el de destino alcanzado
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
        //pose.pose.position.x = 5.13930082321167;
        //pose.pose.position.y = -4.029267311096191;
        //pose.pose.position.z = -0.001434326171875;

        pose.pose.position.x = 2.8022539698638402;
        pose.pose.position.y = -0.03692829086813365;
        pose.pose.position.z = 0.0;

        pose.pose.orientation.x = 0.0;
        pose.pose.orientation.y = 0.0;
        pose.pose.orientation.z = 0.9979735770390689;
        pose.pose.orientation.w = 0.06362970636303165;
        break;
      case 2:
        //pose.pose.position.x = 1.545987844467163;
        //pose.pose.position.y = -0.009981523267924786;
        //pose.pose.position.z = -0.001434326171875;
        pose.pose.position.x = 6.06500137752852;
        pose.pose.position.y = -5.931359334378828;
        pose.pose.position.z = 0.0;

        // Definir la orientación (este es un ejemplo, puedes calcularlo para tu puerta)
        pose.pose.orientation.x = 0.0;
        pose.pose.orientation.y = 0.0;
        pose.pose.orientation.z = 0.9985772772407213;
        pose.pose.orientation.w = 0.05332374122759517;
        break;
      case 3:
        pose.pose.position.x = 8.20947551727295;
        pose.pose.position.y = -13.45923137664795;
        pose.pose.position.z = -0.005340576171875;

        pose.pose.orientation.x = 0.0;
        pose.pose.orientation.y = 0.0;
        pose.pose.orientation.z = -0.08283026926814523;
        pose.pose.orientation.w = 0.9965636690613232;
        break;
      case 4:
        pose.pose.position.x = 20.560640335083008;
        pose.pose.position.y = -24.40395164489746;
        pose.pose.position.z = -0.001434326171875;

        pose.pose.orientation.x = 0.0;
        pose.pose.orientation.y = 0.0;
        pose.pose.orientation.z = -0.752787314110982;
        pose.pose.orientation.w = 0.6582638222730866;
        break;
      case 5:
        pose.pose.position.x =  26.64468002319336;
        pose.pose.position.y = -17.468358993530273;
        pose.pose.position.z = -0.005340576171875;

        pose.pose.orientation.x = 0.0;
        pose.pose.orientation.y = 0.0;
        pose.pose.orientation.z = -0.5311433974866508;
        pose.pose.orientation.w = -0.5311433974866508;
        break;
      default:
        pose.pose.position.x = 0.0;
        pose.pose.position.y = 0.0;
        pose.pose.position.z = 0.0;
        returning_ = true;
        break;
    }

    return pose;
  }

  void ActionServer::cmd_vel_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
  {
    if (std::abs(msg->linear.x) > 0.01 || std::abs(msg->angular.z) > 0.01) {
      last_cmd_vel_time_ = this->now();
      is_robot_inactive_ = false;

      // Reiniciar el temporizador de inactividad si el robot se mueve
      if (!inactivity_timer_) {
        inactivity_timer_ = create_wall_timer(1s, std::bind(&ActionServer::check_robot_inactivity, this));
      }

      inactivity_timer_->reset();
    }
  }

  void ActionServer::check_robot_inactivity()
  {
    //RCLCPP_INFO(get_logger(), "Ha llegado a su destino.");
    if ((this->now() - last_cmd_vel_time_).seconds() > 5.0) {
      RCLCPP_INFO(get_logger(), "Ha llegado a su destino.");
      is_robot_inactive_ = true;

      // Cambiar al estado 'Esperando' si el robot está inactivo
      state_ = State::Esperando;
      std_msgs::msg::Int32 arrival_msg;
      arrival_msg.data = 0;
      arrival_pub_->publish(arrival_msg);
      returning_ = false;

      wait_start_time_ = now();

      inactivity_timer_->cancel();
    }
  }
}  // namespace server
