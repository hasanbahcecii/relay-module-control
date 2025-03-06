
#include <PubSubClient.h>
#include <ESP8266WiFi.h> 
#include <ArduinoJson.h>

// MQTT broker credentials
const char* MQTTSERVER = "192.111.111.11";
const int MQTTPORT = 1883;
char* MQTT_RTOPIC = "relay_control";
const char* USERNAME = "iot";
const char* PASSWORD = "password";


// WiFi and MQTT clients
WiFiClient wifiClient;
PubSubClient mqttclient(wifiClient);

// Relay pin
const int relayPin = D1;


// Callback function for MQTT messages
void mqttCallback(char* topic, byte* payload, unsigned int length) {
 Serial.print("\nMessage arrived on topic: ");
 Serial.println(topic);

 String message;
 for (unsigned int i = 0; i < length; i++) {
   message += (char)payload[i];
 }
 Serial.print("Message: ");
 Serial.println(message+'\n');

 if (String(topic) == MQTT_RTOPIC) {
   //DynamicJsonDocument doc(256);
   //DeserializationError error = deserializeJson(doc, message);

   //if (!error) {
     //int g_command = doc["command"];
     int g_command = message.toInt();
     String relay_state = g_command ? "on" : "off";
    if (g_command==1) {
      Serial.println("new command received: Turning relay ON");
      digitalWrite(relayPin, LOW); // Relay ON
    } else if (g_command==-1) { // a text input convert to 0 so we use -1
      relay_state = "off";
      Serial.println("new command received: Turning relay OFF");
      digitalWrite(relayPin, HIGH); // Relay OFF
    }
    else Serial.println("wrong command received:"+g_command);
    
    sendRelayState(relay_state);
    
  //  } else {
    //  Serial.print("Deserialization failed: ");
    //  Serial.println(error.c_str()+'\n');
  //  }
 }
}


  void mqtt_Setup(){
  bool i = false;
  const char* ID ="quentin_hasan";
  const bool CLEAN_SESSION=false;
  const int QOS=1;
  const bool WILL_RETAIN= true;
  const char* LWTTOPIC = "status/relay";
  const char* LWTMESSAGE = "disconnected";

  while (!mqttclient.connected()) {
  if (!i) { Serial.print("Connecting to MQTT...");  i=true;}
   if (mqttclient.connect(ID,USERNAME,PASSWORD,LWTTOPIC, QOS, WILL_RETAIN, LWTMESSAGE,CLEAN_SESSION)) {
     Serial.println("\nConnected to MQTT");
   } else {
     Serial.print(".");
     delay(1000);
   }
  }
  mqttclient.subscribe(MQTT_RTOPIC);

  }