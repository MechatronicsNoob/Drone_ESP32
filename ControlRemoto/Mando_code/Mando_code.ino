//---------------Librerías a utilizar-----------------
//---------------Designación de pines-----------------
// Joystick Derecho

// Joystick Izquierdo

// Encoder Derecho
const int CLK_PIN_1 = 18; // GPIO18
const int DT_PIN_1 = 19;  // GPIO19

// Encoder Izquierdo
const int CLK_PIN_2 = 22; // GPIO22
const int DT_PIN_2 = 23;  // GPIO23

// Potenciometer
const int pot = 39; // GPIO39
// Pulsadores
const int btns = 36; // GPIO36

void setup()
{
  pinMode(CLK_PIN_1, INPUT_PULLUP);
  pinMode(DT_PIN_1, INPUT_PULLUP);
  pinMode(CLK_PIN_2, INPUT_PULLUP);
  pinMode(DT_PIN_2, INPUT_PULLUP);

  Serial.begin(9600);
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
}
