void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
  Serial.println(">>>>>");
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&receive_Data, incomingData, sizeof(receive_Data));
  Serial.println();
  battery_drone = receive_Data.battery_drone;
  velocity_drone = receive_Data.velocity_drone;
  altitude_drone = receive_Data.altitude_drone;
  Serial.println("Receive Data: ");
  Serial.println(battery_drone);
  Serial.println(velocity_drone);
  Serial.println(altitude_drone);
}

void resetData(){
  send_Data.throttle = 0;
  send_Data.yaw = 2048;
  send_Data.pitch = 2048;
  send_Data.roll = 2048;
  send_Data.pot=0; //revisar si se envía correctamente o que valor va
  send_Data.left_encoder=0;
  send_Data.right_encoder=0;
  send_Data.btn=0;
  }

long readEncoder(int CLK_PIN, int DT_PIN, long &encoderValue, int &lastCLKState, int &lastDTState) {
  // Leemos el estado actual de los pines del encoder
  int CLKState = digitalRead(CLK_PIN);
  int DTState = digitalRead(DT_PIN);
  
  // Verificamos si el encoder ha girado en sentido horario
  if (CLKState != lastCLKState && CLKState == HIGH) {
    if (DTState == LOW) {
      encoderValue++;
    } else {
      encoderValue--;
    }
    return encoderValue;
  }
  
  // Verificamos si el encoder ha girado en sentido antihorario
  if (DTState != lastDTState && DTState == HIGH) {
    if (CLKState == LOW) {
      encoderValue--;
    } else {
      encoderValue++;
    }
    return encoderValue;
  }
  
  // Actualizamos el estado anterior de los pines del encoder
  lastCLKState = CLKState;
  lastDTState = DTState;
}
