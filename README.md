# 🤖 final_project_arquitectura

![Build](https://github.com/amanza17/final_project_arquitectura/actions/workflows/ci.yml/badge.svg?branch=main)
![Tests](https://github.com/amanza17/final_project_arquitectura/actions/workflows/test.yml/badge.svg?branch=main)
![Ubuntu 24.04](https://img.shields.io/badge/OS-Ubuntu%2024.04-orange)
![ROS 2 Jazzy](https://img.shields.io/badge/ROS%202-Jazzy-blue)


Final project for the 'Arquitectura Software para Robots' subject (2024–2025).  
Built on **ROS 2 Jazzy**, this system allows a robot to detect a nearby person, initiate a dialogue, and autonomously guide them to the position where their chosen degree is taught using navigation and behavior trees.

---

## 🧠 What does this project do?

- Detects people nearby using an **ELP stereo camera** and 3D point cloud processing.
- Uses **YOLO (v8)** to detect people in the image.
- Projects the 2D detection into a **3D point cloud** to estimate real-world distance.
- When a person approaches the "base" (less than 1 meter to the camera), the robot **starts a dialogue** to ask which degree program they are interested in.
- A **Kobuki robot** with **Nav2** autonomously navigates to the corresponding classroom or position, wait a few seconds, and returns to the base.
- A **Behavior Tree** orchestrates the flow of the main computer (the one with the camera): Detection, dialogue and communication.
- A **FSM** orchestrates the behaviour of the Kobuki Robot: Communication and autonomous navigation.

---

## 📁 Node Structure

```plaintext
elp_stereo_camera/
  └── stereo_camera_node         # Captures images and generates point cloud

yolo_detector/
  └── yolo_node                  # Detects people and publishes 2D coordinates

projection_node/
  └── detection_2d_to_3d         # Converts 2D detections into 3D coordinates

dialog_node/
  └── ask_destination_node       # Starts dialogue with the user

bt_nodes/
  └── main_tree                  # Main Behavior Tree

navigation/
  └── nav_goal_node              # Sends goals to Nav2 based on user input
```

## Group Members
