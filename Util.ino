String generateConfigJson(
  const char* unique_id, 
  const char* device_class, 
  const char* name, 
  const char* state_topic, 
  const char* command_topic,
  const char* payload_on,
  const char* payload_off,
  const char* state_on,
  const char* state_off
) {
  String payload = "{\"unique_id\": \"";
  payload.concat(unique_id);
  payload.concat("\", \"device_class\": \"");
  payload.concat(device_class);
  payload.concat("\", \"name\": \"");
  payload.concat(name);
  payload.concat("\", \"state_topic\": \"");
  payload.concat(state_topic);
  payload.concat("\", \"command_topic\": \"");
  payload.concat(command_topic);
  payload.concat("\", \"payload_on\": \"");
  payload.concat(payload_on);
  payload.concat("\", \"payload_off\": \"");
  payload.concat(payload_off);
  payload.concat("\", \"state_on\": \"");
  payload.concat(state_on);
  payload.concat("\", \"state_off\": \"");
  payload.concat(state_off);
  payload.concat("\" }");
  return payload;
}
