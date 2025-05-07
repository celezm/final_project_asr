#!/bin/bash

echo "Pulsa una tecla: (a=arrival, e=exit, 1-7=real_destination, q=salir)"

while true; do
    read -n 1 key
    echo ""

    case "$key" in
        a)
            echo "Publicando 0 en 'arrival'"
            ros2 topic pub --once /arrival std_msgs/msg/Int32 '{data: 0}'
            ;;
        e)
            echo "Publicando 0 en 'exit'"
            ros2 topic pub --once /exit std_msgs/msg/Int32 '{data: 0}'
            ;;
        [1-7])
            echo "Publicando $key en '/real_destination'"
            ros2 topic pub --once /real_destination std_msgs/msg/Int32 "{data: $key}"
            ;;
        q)
            echo "Saliendo..."
            break
            ;;
        *)
            echo "Tecla no válida"
            ;;
    esac
done

