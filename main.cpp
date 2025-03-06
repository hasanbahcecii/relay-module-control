#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "sendRelayState.hpp"
#include "mqtt.hpp"


// WiFi credentials
const char* ssid = "SSID";
const char* password = "Password";

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi connected!");

  // Configure MQTT
  mqttclient.setServer(MQTTSERVER, MQTTPORT);
  mqttclient.setCallback(mqttCallback);
  mqtt_Setup();

  // Start NTP client
  timeClient.begin();

  // Configure relay pin
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Default: relay OFF
}

void loop() {
  //Maintain MQTT connection
  mqtt_Setup();
  mqttclient.loop();
  timeClient.update(); // Update NTP timestamp
}