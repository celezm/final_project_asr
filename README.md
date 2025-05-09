# 🤖 final_project_arquitectura

![Build](https://github.com/amanza17/final_project_arquitectura/actions/workflows/ci.yml/badge.svg?branch=main)
![Tests](https://github.com/amanza17/final_project_arquitectura/actions/workflows/test.yml/badge.svg?branch=main)
[![License: MIT](https://img.shields.io/badge/License-MIT-purple.svg)](https://opensource.org/licenses/MIT)
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

## 📦 How to install our proyect

Tested on **Ubuntu 24.04** and **ROS 2 Jazzy**.

```bash
# Clone the repo inside your ROS 2 workspace
git clone https://github.com/Amanza17/final_project_arquitectura.git

# Install dependencies
cd ~/final_project_arquitectura
rosdep install --from-paths src --ignore-src -r -y
cs import src < src/hri/thirdparty.repos

# Build
colcon build --symlink-install

# Source
source install/setup.bash
```

---

## 📁 Project Structure

```plaintext
├── bt
│   └── pc.xml
├── LICENSE
├── README.md
├── src
│   ├── ThirdParty              # Dependencies for Kobuki
│   ├── depth_worker            # Transforms detections 2D to 3D
│   ├── elp_stereo_camera       # Drivers for 3D camera
│   ├── hri                     # Voice
│   ├── kobuki                  # Drivers for Kobuki
│   ├── navigation_robot        # Client and server for the navigation
│   ├── pfinal_pc               # Code for de main computer
│   ├── thirdparty              # Other dependencies
│   └── yolov8_ros              # Object detection
└── yolov8m.pt

```

---

## How to execute

### PC:
```bash
ros2 launch pfinal_pc final.launch.py
ros2 run pfinal_pc bt_runner
```

### Kobuki:
```bash
```

---

## 👥 Group Members

- Adrián Manzanares Romera: [Amanza17](https://github.com/amanza17)
- Carlos García Escolano: [CarlosDrag0n](https://github.com/CarlosDrag0n)
- Nerea Chamorro Sierra: [nereacsierra](https://github.com/nereacsierra)
- Claudia Élez Mencía: [celezm](https://github.com/celezm)

---

## 🎦 Multimedia

Behaviour of the main pc: [Click here!](https://youtu.be/WHoLtzbrBdE)
Video trying both parts: [Click here!](https://youtu.be/DCAXKv_venw)

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

