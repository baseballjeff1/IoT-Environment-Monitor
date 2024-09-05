#include "secrets.h" // private file including variables for my WiFi and AWS IoT private keys & certificates
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

// MQTT publish & subscribe topics
#define AWS_IOT_PUBLISH_TOPIC "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

#define BME280_ADDRESS 0x76

Adafruit_BME280 bme; // BME280 object

void connectAWS() {
  // this function is called in void setup to connect to wifi and establish a connection to AWS IoT
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("...");
    delay(500);
  }
  Serial.println("Connected to the WiFi network");

  // sending all the certifications and keys to AWS IoT
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_PRIVATE_KEY);

  client.setServer(AWS_IOT_ENDPOINT, 8883);

  Serial.println("Connecting to AWS IoT");

  while (!client.connect(THINGNAME)) {
    Serial.println("...");
    delay(100);
  }

  if(!client.connected()){
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // subscribe to esp32/sub topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

void publishMessage() {
  // this function will take temperature, pressure, and humidity readings from the BME280 sensor and write them into a JSON document
  // it will then serialize the JSON doc to an array and publish it to esp32/pub topic
  StaticJsonDocument<200> doc;
  doc["temperature °F"] = floor(toFahrenheit(bme.readTemperature()));
  doc["pressure Pa"] = floor(bme.readPressure());
  doc["humidity %"] = floor(bme.readHumidity());
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

float toFahrenheit(float temp) {
  return (temp * 9 / 5) + 32;
}

void setup() {
  Serial.begin(115200);
  connectAWS();

  if (bme.begin(BME280_ADDRESS)) {
    Serial.println("Connected to the BME280 sensor!");
  }
}

void loop() {
  // publishes the data to AWS IoT console every 5 seconds
  publishMessage();
  client.loop();
  delay(5000);
}