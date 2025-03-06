#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <PubSubClient.h>

// NTP client for timestamp
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 60000); // Adjust time zone (1-hour offset)
extern PubSubClient mqttclient;
const char* MQTT_STOPIC= "hasan_quentin";

// Function to send relay state in the specified JSON format
void sendRelayState(const String state) {
  DynamicJsonDocument doc(256);
  doc["node_name"] = "Hasan_Quentin";
  doc["sensor_type"] = "relay";
  doc["data"]["relay_state"] = state;
  doc["timestamp"] = timeClient.;

  String jsonPayload;
  serializeJsonPretty(doc, jsonPayload);

  Serial.println("\nJSON Payload to Server:");
  Serial.println(jsonPayload);

  if (mqttclient.publish(MQTT_STOPIC, jsonPayload.c_str())) {
    Serial.println("JSON published successfully.\n");
  } else {
    Serial.println("Failed to publish JSON.\n");
  }
}