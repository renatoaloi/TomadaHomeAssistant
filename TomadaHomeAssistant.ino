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
const char* topicCommand = "aloioff/tomada1";
const char* topicState = "aloioff/tomada1";
const char* uniqueId = "tomada_escritorio";
const char* deviceClass = "switch";
const char* name = "Tomada Inteligente";
const char* payloadOn = "ON";
const char* payloadOff = "OFF";
const char* stateOn = "ON";
const char* stateOff = "OFF";
String topicConfigJson;

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

  topicConfigJson.reserve(2000);
  topicConfigJson = generateConfigJson(
    uniqueId, 
    deviceClass, 
    name, 
    topicState, 
    topicCommand,
    payloadOn,
    payloadOff,
    stateOn,
    stateOff
  );
  
  publishConfigTopic();
  subscribeSwitchTopic();
  publishInitialStateTopic();
}

void loop() {
  loopMQTT();
}
