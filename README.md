# 🤖 final_project_arquitectura

![CI](https://github.com/amanza17/final_project_arquitectura/actions/workflows/ci.yml/badge.svg)

Final project for the **Computer Architecture** course (2024–2025).  
Built on **ROS 2 Jazzy**, this system allows a robot to detect a nearby person, initiate a dialogue, and autonomously guide them to the classroom where their chosen degree is taught using navigation and behavior trees.

---

## 🧠 What does this project do?

- 📷 Detects people nearby using an **ELP stereo camera** and 3D point cloud processing.
- 🧍‍♂️ Uses **YOLO** to detect people in the image.
- 🌐 Projects the 2D detection into a **3D point cloud** to estimate real-world distance.
- 💬 When a person approaches the "base", the robot **starts a dialogue** to ask which degree program they are interested in.
- 🧭 A **Kobuki robot** with **Nav2** autonomously navigates to the corresponding classroom.
- 🌳 A **Behavior Tree** orchestrates the whole flow: perception, dialogue, and navigation.

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
