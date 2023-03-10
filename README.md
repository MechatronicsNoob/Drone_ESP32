# Introducción

Este es un Proyecto elaborado en mis horas de ocio, el cual abarca la elaboración de un drone cuadricópero y su respectivo mando de control remoto, a partir de tecnología Open Source; en esta ocasión se hará uso del microcontrolador ESP32,  ya que este dispositivo posee todas las tecnologías necesarias para este proyecto (como pines ADC, PWM, Wifi, Bluetooth, etc). Para esta primera versión solo me centraré en hacer que el drone logré volar correctamente, pero dejando oportunidad a futuras versiones.

# Hardware
## Microcontrolador
El microcontrolador a utilizar en esta ocasión se presenta en la siguiente imagen.
<img src="https://github.com/Bharuck/Drone_ESP32/blob/main/src/images/ESP32-Pinout.jpg?raw=true" alt="img" >
Como una breve descripción, el ESP32 es un microcontrolador de bajo costo y bajo consumo de energía diseñado por la empresa china Espressif Systems. Es un dispositivo altamente integrado que combina un procesador de doble núcleo a 32 bits, conectividad WiFi y Bluetooth, interfaces de entrada/salida (GPIO), conversores analógico-digital (ADC), conversores digital-analógico (DAC), un reloj en tiempo real (RTC) y otros componentes periféricos.

## MPU6050

Para lograr que el dron se mantenga estable en el aire se hará uso de un mpu6050, este es un sensor de movimiento de seis ejes (3 ejes de acelerómetro y 3 ejes de giroscopio) diseñado por la compañía InvenSense. Este sensor es muy popular en el campo de la electrónica y la robótica, ya que proporciona información precisa sobre la orientación, la velocidad angular y la aceleración de un objeto.
## Mando

## Cuadricóptero
