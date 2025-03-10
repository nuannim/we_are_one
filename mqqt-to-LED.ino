/*
 *
 * This Arduino UNO R4 code is made available for public use without any restriction
 *
 */

#include <WiFiS3.h>
#include <MQTTClient.h>
const int RED_PIN = 2;    // ขา Red
const int GREEN_PIN = 4;  // ขา Green
const int BLUE_PIN = 7; // blue
const int potPin = A0;
const char WIFI_SSID[] = "Max sareeroop";          // CHANGE TO YOUR WIFI SSID
const char WIFI_PASSWORD[] = "Minimax999157";  // CHANGE TO YOUR WIFI PASSWORD

const char MQTT_BROKER_ADRRESS[] = "mqtt-dashboard.com";  // CHANGE TO MQTT BROKER'S ADDRESS
const int MQTT_PORT = 1883;
const char MQTT_CLIENT_ID[] = "123123asdwqeasdwasdwedqwe";  // CHANGE IT AS YOU DESIRE
const char MQTT_USERNAME[] = "";                                            // CHANGE IT IF REQUIRED, empty if not required
const char MQTT_PASSWORD[] = "";                                            // CHANGE IT IF REQUIRED, empty if not required

// The MQTT topics that Arduino should publish/subscribe
const char PUBLISH_TOPIC[] = "phycom/66070121";    // CHANGE IT AS YOU DESIRE
const char SUBSCRIBE_TOPIC[] = "phycom/66070121";  // CHANGE IT AS YOU DESIRE

const int PUBLISH_INTERVAL = 1000;  // 60 seconds

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

unsigned long lastPublishTime = 0;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(9600);
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    Serial.print("Arduino UNO R4 - Attempting to connect to SSID: ");
    Serial.println(WIFI_SSID);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // wait 10 seconds for connection:
    delay(10000);
  }
  // print your board's IP address:
  Serial.print("IP Address: 192.168.101.186");
  Serial.println(WiFi.localIP());

  connectToMQTT();
}

void loop() {
  mqtt.loop();

  if (millis() - lastPublishTime > PUBLISH_INTERVAL) {
    sendToMQTT();
    lastPublishTime = millis();
  }
}

void connectToMQTT() {
  // Connect to the MQTT broker
  mqtt.begin(MQTT_BROKER_ADRRESS, MQTT_PORT, network);

  // Create a handler for incoming messages
  mqtt.onMessage(messageHandler);

  Serial.print("Arduino UNO R4 - Connecting to MQTT broker");

  while (!mqtt.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  if (!mqtt.connected()) {
    Serial.println("Arduino UNO R4 - MQTT broker Timeout!");
    return;
  }

  // Subscribe to a topic, the incoming messages are processed by messageHandler() function
  if (mqtt.subscribe(SUBSCRIBE_TOPIC))
    Serial.print("Arduino UNO R4 - Subscribed to the topic: ");
  else
    Serial.print("Arduino UNO R4 - Failed to subscribe to the topic: ");

  Serial.println(SUBSCRIBE_TOPIC);
  Serial.println("Arduino UNO R4 - MQTT broker Connected!");
}

void sendToMQTT() {

  // int val = millis();
  //int val = analogRead(A0);
  // int sensorValue = analogRead(A0); // อ่านค่าเซนเซอร์
  // float voltage = sensorValue * (5.0 / 1023.0); // แปลงค่า Analog เป็น Voltage
  // float temperatureC = voltage * 100;
  // // int potValue = analogRead(potPin);
  // String val_str = String(temparatureC);

  // Convert the string to a char array for MQTT publishing
  // char messageBuffer[10];
  // val_str.toCharArray(messageBuffer, 10);
  // // Publish the message to the MQTT topic
  // mqtt.publish(PUBLISH_TOPIC, messageBuffer);
  

  // // Print debug information to the Serial Monitor in one line
  // Serial.println("Arduino UNO R4 - sent to MQTT: topic: " + String(PUBLISH_TOPIC) + " | payload: " + String(messageBuffer));
}

// void sendToMQTT() {
//   // Check if there's data available to read from the Serial Monitor
//   if (Serial.available() > 0) {
//     // Read the input from the Serial Monitor as a string
//     String val_str = Serial.readStringUntil('\n');

//     // Convert the string to a char array for MQTT publishing
//     char messageBuffer[10];
//     val_str.toCharArray(messageBuffer, 10);

//     // Publish the message to the MQTT topic
//     mqtt.publish(PUBLISH_TOPIC, messageBuffer);

//     // Print debug information to the Serial Monitor in one line
//     Serial.println("Arduino UNO R4 - sent to MQTT: topic: " + String(PUBLISH_TOPIC) + " | payload: " + String(messageBuffer));
//   }
// }

void messageHandler(String &topic, String &payload) {
  Serial.println("Arduino UNO R4 - received from MQTT: topic: " + topic + " | payload: " + payload);
  int val = payload.toInt();


  if(val >= 36 && val <= 50){
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
  }
  else if(val >= 26 && val <= 35){
    digitalWrite(RED_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
  }
  else if(val >= 10 && val <= 25){
    digitalWrite(RED_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
  }
  // analogWrite(9, val);
  

  // You can process the incoming data , then control something
  /*
  process something
  */
}