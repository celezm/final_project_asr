import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():
    stereo_camera_launch = os.path.join(
        get_package_share_directory('elp_stereo_camera'),
        'launch',
        'final.camera.launch.py'
    )

    hri_launch = os.path.join(
        get_package_share_directory('hri_bt_nodes'),
        'launch',
        'hri_dependencies.launch.py'
    )

    return LaunchDescription([
        IncludeLaunchDescription(PythonLaunchDescriptionSource(stereo_camera_launch)),
        IncludeLaunchDescription(PythonLaunchDescriptionSource(hri_launch))
    ])
