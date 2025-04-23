#!/usr/bin/env python3

import sys
import subprocess

def main():
    # Parámetros de calibración
    chessboard_size = "9x6"       # Tamaño del tablero de ajedrez (9 esquinas horizontales x 6 verticales)
    square_size = "0.025"         # Tamaño de cada cuadrado en metros (ajusta al tamaño real de tu patrón)
    left_topic = "/left/image_raw"
    right_topic = "/right/image_raw"

    # Comando para ejecutar el calibrador de cámara estéreo
    cmd = [
        "ros2", "run", "camera_calibration", "cameracalibrator",
        "--size", chessboard_size,
        "--square", square_size,
        "--approximate", "0.1",
        "--no-service-check",
        "--stereo",
        "--topic", left_topic, right_topic
    ]

    print("Lanzando calibración estéreo...")
    print("Usando topics:")
    print(f"  - Izquierda: {left_topic}")
    print(f"  - Derecha:   {right_topic}")
    print("\nMueve el tablero frente a ambas cámaras y pulsa 'Calibrate' cuando haya suficientes capturas.")
    print("Luego pulsa 'Save'.")

    subprocess.run(cmd)

if __name__ == "__main__":
    main()
