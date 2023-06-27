//---------------Librerías a utilizar-----------------
#include <esp_now.h>
#include <WiFi.h>

//---------------Dirección MAC-----------------
uint8_t broadcastAddress[] = {0x7C, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF}; //--> REPLACE WITH THE MAC Address of your receiver.

//---------------Designación de pines-----------------
#define throttle_pin 32
#define yaw_pin 33
#define roll_pin 34
#define pitch_pin 35
#define pot_pin 39
#define left_clk_pin 18
#define left_dt_pin 19
#define right_clk_pin 22
#define right_dt_pin 23
#define btn_pin 36

//---------------Creación de Variables-----------------
int lastCLKState_left = LOW;
int lastDTState_left = LOW;
int lastCLKState_right = LOW;
int lastDTState_right = LOW;

int battery_drone=0;
int velocity_drone=0;
int altitude_drone=0;

String success; //--> Variable to store if sending data was successful

// Ejemplo de structure para enviar data
typedef struct struct_sent{
  long throttle;
  long yaw;
  long roll;
  long pitch;
  long pot;
  long left_encoder;
  long right_encoder;
  bool btn;
  }struct_sent;

struct_sent send_Data;

// Ejemplo de structure para recibir data
typedef struct struct_received{
  long battery_drone;
  long velocity_drone;
  long altitude_drone;
  }struct_received;

struct_received receive_Data;

void setup()
{
  pinMode(throttle_pin, INPUT); 
  pinMode(yaw_pin, INPUT);
  pinMode(roll_pin, INPUT);
  pinMode(pitch_pin, INPUT);
  pinMode(pot_pin, INPUT);
  pinMode(left_clk_pin, INPUT); // revisar si alguno es INPUT_PULLDOWN
  pinMode(left_dt_pin, INPUT);
  pinMode(right_clk_pin, INPUT);
  pinMode(right_dt_pin, INPUT);

  Serial.begin(115200);
  WiFi.mode(WIFI_STA); //--> Set device as a Wi-Fi Station
  
  //----------------------------------------Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //----------------------------------------
//----------------------------------------Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  //----------------------------------------
  
  //----------------------------------------Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  //----------------------------------------
  
  //----------------------------------------Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  //----------------------------------------
  
  esp_now_register_recv_cb(OnDataRecv); //--> Register for a callback function that will be called when data is received

  resetData(); // Se llama a la función de reset para inicializar
}

void loop(){
  // Preparando los valores a enviar
  long throttle = analogRead(throttle_pin);
  long yaw = analogRead(yaw_pin);
  long roll = analogRead(roll_pin);
  long pitch = analogRead(pitch_pin);
  long pot = analogRead(pot_pin);
  long left_encoder = readEncoder(left_clk_pin,left_dt_pin, left_encoder, lastCLKState_left, lastDTState_left);
  long right_encoder = readEncoder(right_clk_pin,right_dt_pin, right_encoder, lastCLKState_right, lastDTState_right);
  bool btn;  

  send_Data.throttle = throttle;
  send_Data.yaw = yaw;
  send_Data.pitch = pitch;
  send_Data.roll = roll;
  send_Data.pot=pot; 
  send_Data.left_encoder=left_encoder;
  send_Data.right_encoder=right_encoder;
  send_Data.btn=btn;

  Serial.println("Send data");

  //----------------------------------------Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &send_Data, sizeof(send_Data));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  //----------------------------------------
  
}
