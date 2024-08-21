#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME280_ADDRESS 0x76

Adafruit_BME280 bme;

const char* ssid = "Dodgers#1";
const char* password = "calmhorse123";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Conneting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("...");
    delay(500);
  }

  Serial.println("Connected to the WiFi network");
  Serial.print("IP adress: ");
  Serial.println(WiFi.localIP());

  if (bme.begin(BME280_ADDRESS)) {
    Serial.println("Connected to the BME280 sensor!");
    Serial.println("");
  }
}

float toFahrenheit(float temp) {
  return (temp * 9 / 5) + 32;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Temperature: ");
  Serial.print(toFahrenheit(bme.readTemperature()));
  Serial.println("°F");

  Serial.print("Pressure: ");
  Serial.print(bme.readPressure());
  Serial.println("hPa");

  Serial.print("Humidity: ");
  Serial.print(bme.readHumidity());
  Serial.println("%");
  Serial.println("");

  delay(3000);
}