#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const int relayPin = 1;

//Informações do WiFi
#define WIFISSID "AloiTech"
#define WIDIPASS "papajoao23"

//Informações do Servidor MQTT
const char* mqttserver = "raspberrypi.local";
int mqttserverport = "1883";
const char* mqttuser = "aloitech";
const char* mqttpass = "aloioff";

// Informações dos tópicos
const char* topicConfig = "homeassistant/switch/aloioff/tomada1/config";
const char* topicConfigJson = "{\"expire_after\": \"600\", \"icon\": \"mdi:power-socket-ch\", \"name\": \"Tomada Inteligente\", \"state_topic\": \"aloioff/tomada1/state\"}";

WiFiClient wifiClient;
PubSubClient clientMQTT(wifiClient);
int lastValue = 0;
int timeCounter = 0;

void reconnectMQTT() {
  clientMQTT.setServer(mqttserver, mqttserverport);
  Serial.println("Conectando ao Broker MQTT.");
  while (!clientMQTT.connected()) {
    clientMQTT.connect("esp8266",mqttuser,mqttpass);
    Serial.print(".");
    delay(300);
  }
  Serial.println("");
  Serial.println("MQTT conectado!");
}

void reconnectWiFi() {
  WiFi.begin(WIFISSID, WIDIPASS);
  Serial.println("Conectando ao WiFi.");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(300);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
}

void publishConfigTopic() {
  clientMQTT.publish(topicConfig, topicConfigJson, false);
}

void subscribeSwitchTopic() {
  //clientMQTT.publish(topicConfig, topicConfigJson, false);
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();

  reconnectWiFi();

  if (!clientMQTT.connected()) {
    reconnectMQTT();
  }

  publishConfigTopic();
  
}

void loop() {
  
}
