#include "secrets.h"
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

#define AWS_IOT_PUBLISH_TOPIC "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

#define BME280_ADDRESS 0x76

Adafruit_BME280 bme;

void connectAWS() {
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("...");
    delay(500);
  }
  Serial.println("Connected to the WiFi network");

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

  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

void publishMessage() {
  StaticJsonDocument<200> doc;
  doc["temperature °F"] = floor(toFahrenheit(bme.readTemperature()));
  doc["pressure hPa"] = floor(bme.readPressure());
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
  delay(1000);

  if (bme.begin(BME280_ADDRESS)) {
    Serial.println("Connected to the BME280 sensor!");
    Serial.println("");
  }
}

void loop() {
  publishMessage();
  client.loop();
  delay(5000);
}