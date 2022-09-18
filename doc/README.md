


![Austral Ingenieria](https://encrypted-tbn0.gstatic.com/images?q=tbn%3AANd9GcQooGo7vQn4t9-6Bt46qZF-UY4_QFpYOeh7kVWzwpr_lbLr5wka)


# Proyecto 33-dht-server

## Secciones

- [Objetivo](#objetivo)
- [Hardware](#hardware)
- [Programa](#programa)
- [platformio.ini](#platformio.ini)
- [Bibliotecas](#bibliotecas)
- [Constantes](#constantes)
- [WiFi](#wifi)
- [Links](#links)
- [Videos](#videos)

## Objetivo

>   Crear una página de Web residente en el ESPxx.
>   Esta página configura un server asincrónico
>   Mediante la misma, se podrán observar los valores de temperatura y presión
>   Estos valores provienen de un sensor DHTxx
>   Los valores se muestran separados por un lapso de tiempo razonable


## Hardware

    1 Sensor de temperature y humedad: DHT11 or DHT22  
    1 10K resistor  
    Jumper wires  

    Conectar Pin 1 de DHT-XX a 3.3 V  
    Conectar Pin 2 de DHT-XX a GPIO "DHTPIN"  
    Dejar Pin 3 de DHT-XX desconectado  
    Conectar Pin 4 de DHT-XX a GND  

    Conectar Pin 2 de DHT-XX a un extremo del resistor  
    Conectar otro extremo de resistor 10 K a 3.3V  


## Programa

   (13)  Archivo de inclusión del sistema Arduino  
   (14-20)  Archivos de inclusión de biblioteca Arduino y de bibliotecas externas  
   (26)  Archivo de inclusión de este proyecto para conexión a WiFi  

   (28-36) Comentarios de definiciones realizadas a través de _platformio.ini_  

   (39)  Constante privada del módulo _interval_ inicializada con el tiempo de actualización de DHT  

   (41-46) Creación de objetos  

   (48-53) Variables globales del módulo  

   (55)  Inclusión del archivo con la página HTML (para mayor claridad del código)    
   Este archivo _html_page.h_ se encuentra en el mismo directorio de _main.cpp_

   (57-81)  Funciones auxiliares y privadas del módulo  
   (61-67): _processor_: función para ser encuestada por el servidor y obtener cada una de las magnitudes medidas  
   (69-81): _get_temp_hum_: función llamada desde _loop_ para leer y guardar ambas magnitudes para la encuesta del servidor 
   (83-126) Funciones públicas  

   (87-106) _setup_  
   (90): Inicialización de _Serial_.  
   (91): Inicialización del objeto _dht_  
   (93): Conexión a WiFi  
   (95-102): Requerimientos al servidor para obtener y presentar ambas magnitudes  
   (105): Arranque del servidor  

   (108-126) _loop_  
   (111): creación e inicialización de la variable _currentMillis_ con el valor actual del contador de milisegundos  
   (113): Verifica, teniendo en cuenta _currentMillis_ y _previousMillis_ si han pasado los milisegundos de _interval_  
   (115): Si pasaron, se recarga _previousMillis_ con el valor de _currentMillis_ y se pasa a la acción  
   (116): Se llama a _get_temp_hum_ para obtener la temperatura y humedad  
   (117-122): si no hay error, se imprimen en _serial_ ambas  
   (123-124): si hay error, se lo imprime en _Serial_  

## platformio.ini

   Define:  
   _DHTPIN_: GPIO para conectar sensor _DHTxx_  
   _DHTTYPE_: Tipo de sensor = _DHT11_ o _DHT22_  
   _SERIAL_BAUD_: Baud reate de la conexión serie 


## Bibliotecas

   Aparte de las bibliotecas propias del sistema Arduino:  

   _Adafruit Unified Sensor_: Biblioteca de Adafruit para todos sus sensores  
   _DHT Sensor Library_: Biblioteca específica de los sensors _DHTxx_  
   _ESP Async WebServer_: Biblioteca para el manejo de Servidores Asincrónicos  
   _AsyncTCP_: Conexión TCP para servidores asincrónicos  

## Constantes

  Las definidas en _platformio.ini_  
  Dentro de _main.cpp_ la constante _interval_

## WiFi

 Para acceso a WiFi simplificado usado en este proyecto, ver archivo _esp32wifi.md_ en este mismo directorio.  

## Links

[ESP32 DHT11/DHT22 Web Server – Temperature and Humidity](https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-web-server-arduino-ide/)

[Adafruit DHT sensors](https://learn.adafruit.com/dht)

[ESP32 with DHT sensors](https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-sensor-arduino-ide/)

## Videos

[ESP32 DHT11/DHT22 Asynchronous Web Server](https://www.youtube.com/watch?v=tDdL5urWvH4)

[Using DHT22 sensor with ESP32](https://www.youtube.com/watch?v=IPrEjQn_cTM)


