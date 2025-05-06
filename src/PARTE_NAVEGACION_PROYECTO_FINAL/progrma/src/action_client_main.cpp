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

#include <memory>
#include <iostream>
#include <cstdlib>  // Para std::atoi

#include "server/ActionClient.hpp"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);

  /*if (argc < 2) {
    std::cerr << "Se tiene que pasar al menos un número (del 1 al 5) como parámetro" << std::endl;
    rclcpp::shutdown();
    return 1;
  }

  // Convertir el argumento a int8
  int objetivo = std::atoi(argv[1]);
  if (objetivo < 1 || objetivo > 5) {
    std::cerr << "El número debe estar entre 1 y 5." << std::endl;
    rclcpp::shutdown();
    return 1;
  }*/

  auto node = std::make_shared<server::ActionClient>();
  //auto goal = server::ActionClient::muevete::Goal();
  node->wait_and_send_goal();

  // Asignar el objetivo recibido
  //goal.objetivo = static_cast<int8_t>(objetivo);

  //node->send_request(goal);

  rclcpp::Rate rate(10);
  while (rclcpp::ok() && !node->is_action_finished()) {
    rclcpp::spin_some(node);
    rate.sleep();
  }

  if (node->is_result_success()) {
    std::cout << "Result: Success" << std::endl;
  } else {
    std::cerr << "Result: Error" << std::endl;
  }

  rclcpp::shutdown();
  return 0;
}
