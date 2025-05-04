import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():
    stereo_camera_launch = os.path.join(
        get_package_share_directory('elp_stereo_camera'),
        'launch',
        'stereo_camera_launch.py'
    )

    yolo_launch = os.path.join(
        get_package_share_directory('yolo_bringup'),
        'launch',
        'yolo.final.launch.py'
    )

    detection3d_launch = os.path.join(
        get_package_share_directory('depth_worker'),
        'launch',
        'detection3d_yolo.launch.py'
    )

    return LaunchDescription([
        IncludeLaunchDescription(PythonLaunchDescriptionSource(stereo_camera_launch)),
        IncludeLaunchDescription(PythonLaunchDescriptionSource(yolo_launch)),
        IncludeLaunchDescription(PythonLaunchDescriptionSource(detection3d_launch))
    ])
