#ifndef SERVER__ACTION_SERVER_HPP_
#define SERVER__ACTION_SERVER_HPP_

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "interfaces_final/action/muevete.hpp"

namespace server
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

    rclcpp_action::Server<muevete>::SharedPtr navigate_action_server_;
    std::shared_ptr<rclcpp_action::ServerGoalHandle<muevete>> goal_handle_;

    geometry_msgs::msg::PoseStamped target_pose_;
    geometry_msgs::msg::PoseStamped original_pose_;
    State state_;
    int current_times_;
    rclcpp::Time wait_start_time_;
    rclcpp::Time start_time_;

    muevete::Goal current_goal_;
    std::shared_ptr<rclcpp::TimerBase> timer_;
    std::shared_ptr<rclcpp::TimerBase> inactivity_timer_;

    rclcpp::Time last_cmd_vel_time_;
    bool is_robot_inactive_;
  };
}  // namespace server

#endif  // SERVER__ACTION_SERVER_HPP_
