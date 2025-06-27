# ESP32 FreeRTOS MQTT Node-RED

This project uses an ESP32 to send data using MQTT to a Node-RED dashboard.

# Node-RED flow
![image](https://github.com/user-attachments/assets/bffb3b80-3973-4d07-a9a0-f5792c5bebe0)

# Node-RED dashboard
![image](https://github.com/user-attachments/assets/fc96ed8b-ebfb-4cd3-b93a-7a26c0617dfe)

# Cicuit
![photo_6264872609615300504_y](https://github.com/user-attachments/assets/965b054c-7d14-41e2-a9b3-d838f6b8b9c7)


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
