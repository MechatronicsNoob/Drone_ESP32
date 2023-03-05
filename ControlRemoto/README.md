# Resultado Final
(Agregar imagen del resultado final)
# Inspiración

<img src="https://github.com/Bharuck/Drone_ESP32/blob/main/src/images/mando_ref1.jpg?raw=true" alt="img" align="right" height="150px">
<img src="https://github.com/Bharuck/Drone_ESP32/blob/main/src/images/mando_ref.jpg?raw=true" alt="img" align="right" height="150px">

Como se menciona en la página principal de este proyecto, se tomó una gran inspiración en el control Remoto de la marca *DJI* que se usa junto a su modelo *DJI Inspire 2* (Dicho modelo se muestra a la derecha)

Principalmente, se tomó como referencia la distribución física de los botones y demás entradas de control que se muestra a la izquierda.



# Hardware
Para la elaboración de este mando se utilizó nuevamente un ESP32 junto con algunos módulos de arduino, a continuación se muestra una lista de componentes a utilizar para elaborar el Mando de control remoto para el manejo de nuestro drone.


## Materiales
| Material                                      | Number |
|-----------------------------------------------|--------|
| Nodemcu-32 ESP32 Wifi                         | 1      |
| DC-DC voltage converter STEP-DOWN 2A MP1584EN | 1      |
| Joystick                                      | 2      |
| Encoder                                       | 2      |
| pulsadores                                    | 4      |
| potenciómetro                                 | 1      |
| switch                                        | 1      |
| switch (on-off-on) mts2                       | 1      |

## Conexiones
Para las realizar las conexiones, solo debe guiarse de la imagen anterior, recordar que el ESP32 trabaja con 3.3v; suministrarle voltajes superiores podría arruinar el microcontrolador.
En caso de quedar dudas con las conexiones, a continuación se muestra una tabla de referencia.