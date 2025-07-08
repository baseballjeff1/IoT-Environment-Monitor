# About the Project

My IoT Environmental Monitoring System is an experimental project that I conducted to explore how IoT devices work and what role cloud services play into it.
Throughout the researching process, I understood what IoT and it's impact on real-world industry. 
It was a great opportunity to learn how I could leverage my interests in both hardware and software to make awesome projects from real-time sensor data.
The project's materials are a breadboard, ESP32 WiFi microcontroller, jumper wires, and a BME280 module.

## Breadboard and Wire Management

Here is how to wire the ESP32 and BME280 sensor:

- Red Wire - 3.3V to VCC
- Black Wire - GND to GND
- Purple Wire - GPIO 22 Serial Clock Line pin
- Blue Wire - GPIO 21 Serial Data Line pin

### Picture

![IoT](https://github.com/user-attachments/assets/5e5c9252-e8a6-4f27-bc5b-f1d51caeabfa)

## The Result

Using AWS IoT Core, I was able to connect my ESP32 device to the AWS service through WiFi connectivity and MQTT protocol. I created secure policies and downloaded the certificates to establish a secure connection.
I then relayed JSON formatted messages to AWS IoT Core with the BME280's readings of temperature, pressure, and humidity. This data can be monitored anywhere in the world as long as the ESP32 is connected to a power source.

## What I Learned

Through my personal project, I gained foundational knowledge of IoT and its applications. I also experienced practical use of connecting a physical device to the AWS IoT Core to relay data.
Another concept I learned was the MQTT protocol, how to create a publish / subscribe topic, and the purpose of certificates for secure connection.
