# ESP32 FreeRTOS MQTT Node-RED

This project uses an ESP32 to send data using MQTT to a Node-RED dashboard.

## What it does

- Uses FreeRTOS tasks to handle different sensors
- Sends distance data from HC-SR04 every 5 seconds
- Sends LDR (light) sensor data every 10 seconds
- Uses MQTT (Mosquitto broker) for communication
- Visualizes the data on Node-RED dashboard

## Why this project

I wanted to learn:
- How to use FreeRTOS on ESP32
- How to send data using MQTT
- How to use Node-RED for real-time dashboards

## Tools and Tech Used

- ESP32
- Arduino IDE
- FreeRTOS (built-in support)
- Mosquitto MQTT broker (local)
- Node-RED (running on PC)

## How to Run

1. Connect ESP32 to WiFi
2. Start Mosquitto broker on your PC
3. Start Node-RED and open the dashboard
4. Flash the code to ESP32
5. You should see sensor values updating on Node-RED

## Note

Make sure your PC and ESP32 are on the same network when using local MQTT.
