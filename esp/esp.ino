#include <WiFi.h>;

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
}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("You can try to ping me");
    delay(5000);
  }
}
