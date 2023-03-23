# TomadaHomeAssistant

### Comando para publicar mensagem retida no tópico do Mosquitto

```sh
mosquitto_pub -h 192.168.0.104 -p 1883 -t "homeassistant/switch/aloioff/tomada1/config" -m '{"unique_id": "tomada_escritorio", "device_class": "switch", "name": "Tomada Inteligente", "state_topic": "homeassistant/switch/aloioff/tomada1/state", "command_topic": "homeassistant/switch/aloioff/tomada1/command" }' -u aloitech -P aloioff -r
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
