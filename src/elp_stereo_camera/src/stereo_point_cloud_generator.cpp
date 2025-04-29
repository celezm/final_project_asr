#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <cv_bridge/cv_bridge.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
// Incluir highgui para visualizar disparidad (opcional)
#include <opencv2/highgui.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <memory>

typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::msg::Image, sensor_msgs::msg::Image> ApproxSyncPolicy;

class StereoPointCloudGenerator : public rclcpp::Node
{
public:
    StereoPointCloudGenerator() : Node("stereo_point_cloud_generator_node"),
                                   left_info_ready_(false),
                                   right_info_ready_(false),
                                   baseline_(0.0),
                                   fx_(0.0),
                                   cx_(0.0),
                                   cy_(0.0)
    {
        RCLCPP_INFO(this->get_logger(), "Iniciando Stereo Point Cloud Generator (Color, Ajustes Densidad)...");

        // Parámetros del SGBM (ajustar experimentalmente)
        int minDisparity = 0;
        int numDisparities = 128;
        int blockSize = 5;
        int P1 = 8 * 3 * blockSize * blockSize;
        int P2 = 32 * 3 * blockSize * blockSize;
        int disp12MaxDiff = 1;
        int preFilterCap = 63;
        int uniquenessRatio = 5;
        int speckleWindowSize = 50;
        int speckleRange = 2;
        int mode = cv::StereoSGBM::MODE_SGBM_3WAY;

        // SOR Filter
        sor_mean_k_ = 50;
        sor_stddev_thresh_ = 1.0;

        // Frame ID
        point_cloud_frame_id_ = "camera_link"; 

        // Inicializar SGBM
        stereoSGBM_ = cv::StereoSGBM::create(
            minDisparity, numDisparities, blockSize, P1, P2, disp12MaxDiff,
            preFilterCap, uniquenessRatio, speckleWindowSize, speckleRange, mode);
        RCLCPP_INFO(this->get_logger(), "StereoSGBM params: numDisp=%d, blkSize=%d, uniqueRatio=%d, speckleWin=%d",
                    numDisparities, blockSize, uniquenessRatio, speckleWindowSize);

        // Suscriptores y Publicador
        left_camera_info_subscriber_ = this->create_subscription<sensor_msgs::msg::CameraInfo>(
            "/stereo/left/camera_info", 10,
            std::bind(&StereoPointCloudGenerator::left_camera_info_callback, this, std::placeholders::_1));
        right_camera_info_subscriber_ = this->create_subscription<sensor_msgs::msg::CameraInfo>(
            "/stereo/right/camera_info", 10,
            std::bind(&StereoPointCloudGenerator::right_camera_info_callback, this, std::placeholders::_1));
        left_image_sub_.subscribe(this, "/stereo/left/image_rect");
        right_image_sub_.subscribe(this, "/stereo/right/image_rect");
        sync_ = std::make_shared<message_filters::Synchronizer<ApproxSyncPolicy>>(
            ApproxSyncPolicy(10), left_image_sub_, right_image_sub_);
        sync_->registerCallback(std::bind(&StereoPointCloudGenerator::image_callback, this, std::placeholders::_1, std::placeholders::_2));
        point_cloud_publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("stereo/point_cloud_color", 10);

        RCLCPP_INFO(this->get_logger(), "Nodo listo. Publicando en '%s' con frame_id '%s'.",
                    point_cloud_publisher_->get_topic_name(), point_cloud_frame_id_.c_str());
    }

private:
    void left_camera_info_callback(const sensor_msgs::msg::CameraInfo::SharedPtr msg) {
        if (!left_info_ready_) {
            fx_ = msg->k[0]; cx_ = msg->k[2]; cy_ = msg->k[5];
            left_info_ready_ = true;
            RCLCPP_INFO_ONCE(this->get_logger(), "Info cámara izquierda OK (fx=%.2f, cx=%.2f, cy=%.2f).", fx_, cx_, cy_);
        }
    }
    void right_camera_info_callback(const sensor_msgs::msg::CameraInfo::SharedPtr msg) {
        if (!right_info_ready_) {
            double p_fx = msg->p[0]; double p_tx = msg->p[3];
            if (std::abs(p_fx) > 1e-6) {
                 baseline_ = -p_tx / p_fx;
                 right_info_ready_ = true;
                 RCLCPP_INFO_ONCE(this->get_logger(), "Info cámara derecha OK (baseline=%.4f m).", baseline_);
            } else {
                // Error, fx es 0
            }
        }
    }

    void image_callback(const sensor_msgs::msg::Image::ConstSharedPtr& left_msg,
                        const sensor_msgs::msg::Image::ConstSharedPtr& right_msg)
    {
        if (!left_info_ready_ || !right_info_ready_) { return; }

        cv_bridge::CvImagePtr left_cv_ptr_mono, right_cv_ptr_mono, left_cv_ptr_color;
        try {
            left_cv_ptr_color = cv_bridge::toCvCopy(left_msg, sensor_msgs::image_encodings::BGR8);
            left_cv_ptr_mono = cv_bridge::toCvCopy(left_msg, sensor_msgs::image_encodings::MONO8);
            right_cv_ptr_mono = cv_bridge::toCvCopy(right_msg, sensor_msgs::image_encodings::MONO8);
        } catch (const cv_bridge::Exception& e) {
            return;
        }

        // Calcular disparidad
        cv::Mat disparity_sgbm;
        stereoSGBM_->compute(left_cv_ptr_mono->image, right_cv_ptr_mono->image, disparity_sgbm);

        // Convertir disparidad a formato de 32F
        cv::Mat disparity;
        disparity_sgbm.convertTo(disparity, CV_32F, 1.0 / 16.0);

        // Generar Point Cloud con Color
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
        cloud->points.reserve(disparity.rows * disparity.cols);
        float min_disparity_threshold = 0.5;
        float max_depth_threshold = 15.0;
        const cv::Mat& left_color_image = left_cv_ptr_color->image;

        cloud->width = disparity.cols;
        cloud->height = disparity.rows;
        cloud->is_dense = false;
        cloud->points.resize(cloud->width * cloud->height);

        for (int i = 0; i < disparity.rows; ++i) {
            for (int j = 0; j < disparity.cols; ++j) {
                int idx = i * disparity.cols + j;
                float disp = disparity.at<float>(i, j);

                pcl::PointXYZRGB& point = cloud->points[idx];

                if (disp <= min_disparity_threshold) {
                    point.x = point.y = point.z = std::numeric_limits<float>::quiet_NaN();
                    point.r = point.g = point.b = 0;
                    continue;
                }

                float Zc = (baseline_ * fx_) / disp;
                if (Zc > max_depth_threshold || Zc <= 0) {
                    point.x = point.y = point.z = std::numeric_limits<float>::quiet_NaN();
                    point.r = point.g = point.b = 0;
                    continue;
                }

                float Xc = (j - cx_) * Zc / fx_; // La coordenada X se calcula normalmente
                float Yc = (i - cy_) * Zc / fx_; // Para Y se mantiene la fórmula
                point.x = Zc; // Movimiento hacia el eje X
                point.y = -Yc; // No se modifica Y
                point.z = -Xc; // La distancia Z se calcula correctamente

                const cv::Vec3b& color = left_color_image.at<cv::Vec3b>(i, j);
                point.b = color[0];
                point.g = color[1];
                point.r = color[2];
            }
        }

        // Filtrar nube de puntos (opcional)
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered = cloud;

        // Publicar Point Cloud
        if (!cloud_filtered->points.empty()) {
            sensor_msgs::msg::PointCloud2 output_cloud_msg;
            pcl::toROSMsg(*cloud_filtered, output_cloud_msg);
            output_cloud_msg.header.stamp = left_msg->header.stamp;
            output_cloud_msg.header.frame_id = point_cloud_frame_id_;
            point_cloud_publisher_->publish(output_cloud_msg);
        }
    }

    message_filters::Subscriber<sensor_msgs::msg::Image> left_image_sub_;
    message_filters::Subscriber<sensor_msgs::msg::Image> right_image_sub_;
    std::shared_ptr<message_filters::Synchronizer<ApproxSyncPolicy>> sync_;
    rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr left_camera_info_subscriber_;
    rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr right_camera_info_subscriber_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr point_cloud_publisher_;
    cv::Ptr<cv::StereoSGBM> stereoSGBM_;
    bool left_info_ready_, right_info_ready_;
    double baseline_, fx_, cx_, cy_, fy_;
    int sor_mean_k_;
    double sor_stddev_thresh_;
    std::string point_cloud_frame_id_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<StereoPointCloudGenerator>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
