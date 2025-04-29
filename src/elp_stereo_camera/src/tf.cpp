#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <tf2/LinearMath/Quaternion.h>

class OdometryToCameraLinkBroadcaster : public rclcpp::Node
{
public:
    OdometryToCameraLinkBroadcaster() : Node("odom_to_camera_link_broadcaster")
    {
        // Crear el broadcaster de tf2
        tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);

        // Publicar la transformación entre odom y camera_link cada 0.1 segundos
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),
            std::bind(&OdometryToCameraLinkBroadcaster::publish_odom_to_camera_link, this));
    }

private:
    void publish_odom_to_camera_link()
    {
        geometry_msgs::msg::TransformStamped transformStamped;

        // Llenar la información de la transformación
        transformStamped.header.stamp = this->get_clock()->now();
        transformStamped.header.frame_id = "odom";  // Marco de referencia de origen
        transformStamped.child_frame_id = "camera_link";  // Marco de referencia de destino

        // Definir la transformación: posición y rotación
        transformStamped.transform.translation.x = 0.0;  // Desplazamiento en X (ajustar según tu sistema)
        transformStamped.transform.translation.y = 0.0;  // Desplazamiento en Y
        transformStamped.transform.translation.z = 0.0;  // Desplazamiento en Z

        tf2::Quaternion q;
        q.setRPY(M_PI / 2,0.0 , M_PI / 2);  // Orientación en Euler (roll=90º, pitch=90º, yaw=0º)
        transformStamped.transform.rotation.x = q.x();
        transformStamped.transform.rotation.y = q.y();
        transformStamped.transform.rotation.z = q.z();
        transformStamped.transform.rotation.w = q.w();

        // Publicar la transformación
        tf_broadcaster_->sendTransform(transformStamped);
    }

    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<OdometryToCameraLinkBroadcaster>());
    rclcpp::shutdown();
    return 0;
}
