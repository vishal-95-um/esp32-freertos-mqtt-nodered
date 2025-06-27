#include <WiFi.h>
#include <PubSubClient.h>

// Task and queue handles
TaskHandle_t connection, distance_handle, light_handle;
QueueHandle_t dataQueue;

// WiFi credentials
const char* ssid = "PocoC75";
const char* password = "whoareyou";

// Sensor pins
const int trig = 21;
const int echo = 32;
const int ldr = 33;

// MQTT setup
const char* mqtt_server = "192.168.192.184";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// struct to pass sensor data through queue
struct sensorData {
  String sensorName;
  float value;
};

void setup() {
  Serial.begin(115200);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(ldr, INPUT);

  // queue for sending data between tasks
  dataQueue = xQueueCreate(10, sizeof(sensorData));

  // connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());

  // MQTT setup
  client.setServer(mqtt_server, mqtt_port);

  // create tasks
  xTaskCreate(mqtt_connect, "Connection", 2000, NULL, 1, &connection);
  xTaskCreate(distance, "Distance", 2000, NULL, 1, &distance_handle);
  xTaskCreate(light, "Light", 2000, NULL, 1, &light_handle);
  xTaskCreate(send_data, "SENDING", 2000, NULL, 1, NULL);
}

// task to measure distance using HC-SR04
void distance(void *parameter) {
  TickType_t lastwakeTime = xTaskGetTickCount();
  while (true) {
    float distance = get_distance();
    sensorData data = {"HCSR04", distance};
    xQueueSend(dataQueue, &data, portMAX_DELAY);
    vTaskDelayUntil(&lastwakeTime, 5000 / portTICK_PERIOD_MS);
  }
}

// task to read LDR values
void light(void *parameter) {
  TickType_t lastwakeTime = xTaskGetTickCount();
  while (true) {
    float light_value = get_light();
    sensorData data = {"LDR", light_value};
    xQueueSend(dataQueue, &data, portMAX_DELAY);
    vTaskDelayUntil(&lastwakeTime, 10000 / portTICK_PERIOD_MS);
  }
}

// task to send data from queue to MQTT
void send_data(void *parameter) {
  sensorData data;
  char payload[16];
  while (true) {
    if (xQueueReceive(dataQueue, &data, portMAX_DELAY)) {
      dtostrf(data.value, 6, 2, payload);  // convert float to string
      if (data.sensorName == "HCSR04") {
        client.publish("obj1/distance", payload);
      } else if (data.sensorName == "LDR") {
        client.publish("room1/light", payload);
      }
    }
  }
}

// function to get distance from HC-SR04
float get_distance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH, 25000);  // timeout for safety
  return duration / 58.0;
}

// function to read LDR
float get_light() {
  return analogRead(ldr);
}

// task to keep MQTT connected
void mqtt_connect(void *parameter) {
  while (true) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

// reconnect if MQTT is disconnected
void reconnect() {
  while (!client.connected()) {
    Serial.println("Trying to connect to MQTT....");
    if (client.connect("ESP_Pub")) {
      Serial.println("MQTT connected successfully");
    } else {
      Serial.println("MQTT not connected, trying again in 2 seconds");
      Serial.print("MQTT state: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void loop() {
  // not used, all work done in tasks
}
