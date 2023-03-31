# TomadaHomeAssistant

### Instruções

- Baixar o código na pasta `TomadaHomeAssistant`
- Abrir o `TomadaHomeAssistant.ino` no Arduino IDE
- Ajustar com as suas configurações de WiFi e MQTT
- Subir o Código para o ESP8266
- Instalar e configurar o NodeRed
- Instalar plugin `Dashboard` no NodeRed
- Instalar e configurar o Mosquitto Broker
- Importar o arquivo `flows.json` no NodeRed
- Ajustar configurações do seu ambiente
- Acessar o dashboard do NodeRed e testar

### Comando para publicar mensagem retida no tópico do Mosquitto

```sh
mosquitto_pub -h 192.168.0.104 -p 1883 -t "homeassistant/switch/aloioff/tomada1/config" -m '{"unique_id": "tomada_escritorio", "device_class": "switch", "name": "Tomada Inteligente", "state_topic": "aloioff/tomada1", "command_topic": "aloioff/tomada1", "payload_on": "ON", "payload_off": "OFF", "state_on": "ON", "state_off": "OFF" }' -u aloitech -P aloioff -r
```

### Comando para se inscrever no tópico

```sh
mosquitto_sub -t 'homeassistant/switch/aloioff/tomada1/config' -u aloitech -P aloioff
```

### Comando para remover mensagem retida no tópico

```sh
mosquitto_sub -t 'homeassistant/switch/aloioff/tomada1/config' --remove-retained -u aloitech -P aloioff
```

### Comando para acionar o Relay no Mosquitto

```sh
mosquitto_pub -t 'homeassistant/switch/aloioff/tomada1/command' -m 'ON' -u aloitech -P aloioff
```

### Observações sobre os comandos do Mosquitto

- substitua `aloitech` pelo seu nome de usuário
- substitua `aloioff` pela sua senha
- para excluir um dispositivo do Home Assistant basta remover a mensagem retida no tópico.
