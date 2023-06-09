void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String message = "";
  for (int i = 0; i < length; i++) {
    message.concat((char)payload[i]);
  }
  Serial.print(message);
  Serial.println();

  if ((strcmp(message.c_str(), "ON") == 0)) {
    digitalWrite(RELE, HIGH);
  } else {
    digitalWrite(RELE, LOW);
  }
}

void reconnectMQTT() {
  clientMQTT.setServer(mqttserver, mqttserverport);
  clientMQTT.setCallback(callback);
  Serial.println("Conectando ao Broker MQTT.");
  while (!clientMQTT.connected()) {
    clientMQTT.connect("esp8266",mqttuser,mqttpass);
    Serial.print(".");
    delay(300);
  }
  Serial.println("");
  Serial.println("MQTT conectado!");
}

void loopMQTT() {
  if (!clientMQTT.connected()) {
    reconnectMQTT();
  }
  clientMQTT.loop();
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
  Serial.println();
  Serial.println(topicConfig);
  Serial.println(topicConfigJson);
  Serial.println(topicConfigJson.c_str());
  clientMQTT.setBufferSize(2000);
  clientMQTT.publish(topicConfig, topicConfigJson.c_str(), true);
}

void publishInitialStateTopic() {
  clientMQTT.publish(topicState, "ON");
}

void subscribeSwitchTopic() {
  clientMQTT.subscribe(topicCommand);
}

void subscribeStateTopic() {
  clientMQTT.subscribe(topicState);
}
