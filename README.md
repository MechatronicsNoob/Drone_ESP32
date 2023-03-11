# Introducción

Este es un Proyecto elaborado en mis horas de ocio, el cual abarca la elaboración de un drone cuadricópero y su respectivo mando de control remoto, a partir de tecnología Open Source; en esta ocasión se hará uso del microcontrolador ESP32,  ya que este dispositivo posee todas las tecnologías necesarias para este proyecto (como pines ADC, PWM, Wifi, Bluetooth, etc). Para esta primera versión solo me centraré en hacer que el drone logré volar correctamente, pero dejando oportunidad a futuras versiones.

# Hardware principal
## Microcontrolador
<img src="https://github.com/Bharuck/Drone_ESP32/blob/main/src/images/ESP32-Pinout.jpg?raw=true" alt="img" >
Como una breve descripción, el ESP32 es un microcontrolador diseñado por la empresa china Espressif Systems. Es un dispositivo que combina un procesador de doble núcleo a 32 bits, conectividad WiFi y Bluetooth, interfaces de entrada/salida (GPIO), conversores analógico-digital (ADC), conversores digital-analógico (DAC), un reloj en tiempo real (RTC) y otros componentes periféricos.

_______________________________________________________________

## MPU6050
<img src="https://github.com/Bharuck/Drone_ESP32/blob/dfb5477dcc08813cf6101ebc382a4915cd53c9d4/src/images/MPU6050.jpg?raw=true" alt="img" align="right" height="150px">

Para lograr que el dron se mantenga estable en el aire se hará uso de un mpu6050, este es un sensor de movimiento de seis ejes (3 ejes de acelerómetro y 3 ejes de giroscopio) diseñado por la compañía InvenSense. Este sensor es muy popular en el campo de la electrónica y la robótica, ya que proporciona información precisa sobre la orientación, la velocidad angular y la aceleración de un objeto.

_______________________________________________________________

# Elementos del Proyecto
## Control Remoto
<img src="https://github.com/Bharuck/Drone_ESP32/blob/main/src/images/mando_ref1.jpg?raw=true" alt="img" align="right" height="150px">
<img src="https://github.com/Bharuck/Drone_ESP32/blob/main/src/images/mando_ref.jpg?raw=true" alt="img" align="right" height="150px">

Para la elaboración del mando del drone,en este proyecto, se tomó como inspiración en el control Remoto de la marca *DJI* que se usa junto a su modelo *DJI Inspire 2* (Dicho modelo se muestra a la derecha)

Principalmente, se tomó como referencia la distribución física de los botones y demás entradas de control que se muestra en la imagen de la izquierda.

## Materiales
| Material                                      | Número |
|-----------------------------------------------|--------|
| Nodemcu-32 ESP32 Wifi                         | 1      |
| DC-DC voltage converter STEP-DOWN 2A MP1584EN | 1      |
| Joystick                                      | 2      |
| Encoder                                       | 2      |
| pulsadores                                    | 4      |
| potenciómetro                                 | 1      |
| switch                                        | 1      |
| switch (on-off-on) mts2                       | 1      |

___

# Cuadricóptero
En esta ocasión se hará uso de un chasis F450 (Esto hace referencia a la distancia en diagonal entre los motores que sería de 450mm) 