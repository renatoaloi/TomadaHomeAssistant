#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const int relayPin = 1;

//Informações do WiFi
#define WIFISSID "AloiTech"
#define WIDIPASS "papajoao23"

//Informações do Servidor MQTT
const char* mqttserver = "raspberrypi.local";
int mqttserverport = 1883;
const char* mqttuser = "aloitech";
const char* mqttpass = "aloioff";

// Informações dos tópicos
const char* topicConfig = "homeassistant/switch/aloioff/tomada1/config";
const char* topicCommand = "homeassistant/switch/aloioff/tomada1/command";
const char* topicState = "homeassistant/switch/aloioff/tomada1/state";
const char* topicConfigJson = "{\"unique_id\": \"tomada_escritorio\", \"device_class\": \"switch\", \"name\": \"Tomada Inteligente\", \"state_topic\": \"homeassistant/switch/aloioff/tomada1/state\", \"command_topic\": \"homeassistant/switch/aloioff/tomada1/command\" }";

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

WiFiClient wifiClient;
PubSubClient clientMQTT(wifiClient);
int lastValue = 0;
int timeCounter = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  reconnectWiFi();
  if (!clientMQTT.connected()) {
    reconnectMQTT();
  }
  publishConfigTopic();
  subscribeSwitchTopic();
  publishInitialStateTopic();
}

void loop() {
  loopMQTT();
}
