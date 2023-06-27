//---------------Librerías a utilizar-----------------
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

//---------------Dirección MAC-----------------
uint8_t broadcastAddress[] = {0x7C, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF}; //--> REPLACE WITH THE MAC Address of your receiver.


float RatePitch, RateRoll, RateYaw;
float RateCalibrationPitch, RateCalibrationRoll, RateCalibrationYaw;
int RateCalibrationNumber;

#include <PulsePosition.h> //receiver--se tiene que cambiar esto
PulsePositionInput ReceiverInput(RISING);
float ReceiverValue[]={0, 0, 0, 0, 0, 0, 0, 0};
int ChannelNumber=0; 

uint32_t LoopTimer;

//---------------Variables para el bucle de control PID-----------------
float DesiredRateRoll, DesiredRatePitch, DesiredRateYaw;
float ErrorRateRoll, ErrorRatePitch, ErrorRateYaw;
float InputRoll, InputThrottle, InputPitch, InputYaw;
float PrevErrorRateRoll, PrevErrorRatePitch, PrevErrorRateYaw;
float PrevItermRateRoll, PrevItermRatePitch, PrevItermRateYaw;
float PIDReturn[]={0, 0, 0};

//---------------Valores PID -----------------
float PRateRoll=0.6 ; float PRatePitch=PRateRoll; float PRateYaw=2;
float IRateRoll=3.5 ; float IRatePitch=IRateRoll; float IRateYaw=12;
float DRateRoll=0.03 ; float DRatePitch=DRateRoll; float DRateYaw=0;

float MotorInput1, MotorInput2, MotorInput3, MotorInput4; // Valores de entrada para los motores
void setup() {
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Wire.setClock(400000);
  Wire.begin();
  delay(250);
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  for (RateCalibrationNumber = 0; RateCalibrationNumber < 2000; RateCalibrationNumber ++) {
    gyro_signals();
    RateCalibrationRoll += RateRoll;
    RateCalibrationPitch += RatePitch;
    RateCalibrationYaw += RateYaw;
    delay(1);
  }
  RateCalibrationRoll /= 2000;
  RateCalibrationPitch /= 2000;
  RateCalibrationYaw /= 2000;

  //---------------Control de los motores -----------------
  analogWriteFrequency(1, 250);
  analogWriteFrequency(2, 250);
  analogWriteFrequency(3, 250);
  analogWriteFrequency(4, 250);
  analogWriteResolution(12);
  
  ReceiverInput.begin(14); //verificacion de emergencia
  while (ReceiverValue[2] < 1020 || ReceiverValue[2] > 1050) {
    read_receiver();
    delay(4);
  }
  LoopTimer = micros();
}
void loop() {
  gyro_signals();
  RateRoll -= RateCalibrationRoll;
  RatePitch -= RateCalibrationPitch;
  RateYaw -= RateCalibrationYaw;
  read_receiver();
  DesiredRateRoll = 0.15 * (ReceiverValue[0] - 1500);
  DesiredRatePitch = 0.15 * (ReceiverValue[1] - 1500);
  InputThrottle = ReceiverValue[2];
  DesiredRateYaw = 0.15 * (ReceiverValue[3] - 1500);
  ErrorRateRoll = DesiredRateRoll - RateRoll;
  ErrorRatePitch = DesiredRatePitch - RatePitch;
  ErrorRateYaw = DesiredRateYaw - RateYaw;
  pid_equation(ErrorRateRoll, PRateRoll, IRateRoll, DRateRoll, PrevErrorRateRoll, PrevItermRateRoll);
  InputRoll = PIDReturn[0];
  PrevErrorRateRoll = PIDReturn[1];
  PrevItermRateRoll = PIDReturn[2];
  pid_equation(ErrorRatePitch, PRatePitch, IRatePitch, DRatePitch, PrevErrorRatePitch, PrevItermRatePitch);
  InputPitch = PIDReturn[0];
  PrevErrorRatePitch = PIDReturn[1];
  PrevItermRatePitch = PIDReturn[2];
  pid_equation(ErrorRateYaw, PRateYaw,
               IRateYaw, DRateYaw, PrevErrorRateYaw,
               PrevItermRateYaw);
  InputYaw = PIDReturn[0];
  PrevErrorRateYaw = PIDReturn[1];
  PrevItermRateYaw = PIDReturn[2];
  if (InputThrottle > 1800) InputThrottle = 1800;
  MotorInput1 = 1.024 * (InputThrottle - InputRoll - InputPitch - InputYaw);
  MotorInput2 = 1.024 * (InputThrottle - InputRoll + InputPitch + InputYaw);
  MotorInput3 = 1.024 * (InputThrottle + InputRoll + InputPitch - InputYaw);
  MotorInput4 = 1.024 * (InputThrottle + InputRoll - InputPitch + InputYaw);
  if (MotorInput1 > 2000)MotorInput1 = 1999;
  if (MotorInput2 > 2000)MotorInput2 = 1999;
  if (MotorInput3 > 2000)MotorInput3 = 1999;
  if (MotorInput4 > 2000)MotorInput4 = 1999;
  int ThrottleIdle = 1180;
  if (MotorInput1 < ThrottleIdle) MotorInput1 =  ThrottleIdle;
  if (MotorInput2 < ThrottleIdle) MotorInput2 =  ThrottleIdle;
  if (MotorInput3 < ThrottleIdle) MotorInput3 =  ThrottleIdle;
  if (MotorInput4 < ThrottleIdle) MotorInput4 =  ThrottleIdle;
  int ThrottleCutOff = 1000;
  if (ReceiverValue[2] < 1050) {
    MotorInput1 = ThrottleCutOff;
    MotorInput2 = ThrottleCutOff;
    MotorInput3 = ThrottleCutOff;
    MotorInput4 = ThrottleCutOff;
    reset_pid();
  }
  analogWrite(1, MotorInput1);
  analogWrite(2, MotorInput2);
  analogWrite(3, MotorInput3);
  analogWrite(4, MotorInput4);
  battery_voltage();
  CurrentConsumed = Current * 1000 * 0.004 / 3600 + CurrentConsumed;
  BatteryRemaining = (BatteryAtStart - CurrentConsumed) / BatteryDefault * 100;
  if (BatteryRemaining <= 30) digitalWrite(5, HIGH);
  else digitalWrite(5, LOW);
  while (micros() - LoopTimer < 4000);
  LoopTimer = micros();
}
