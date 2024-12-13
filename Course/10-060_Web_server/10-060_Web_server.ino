#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;
const int led_gpio = 2;
const char* ssid     = "ardwifi";
const char* password = "ardwifi987";
WiFiServer server(80);
void setup()
{
  Serial.begin(115200);
  bool status;
  status = bme.begin(0x76);
  pinMode(led_gpio, OUTPUT);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
int value = 0;
void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Refresh: 5");
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.print("<p>Click <a href=\"/H\">here</a> to turn the LED on pin ");
            client.print(led_gpio);
            client.print(" on.</p>");
            client.print("<p>Click <a href=\"/L\">here</a> to turn the LED on pin ");
            client.print(led_gpio);
            client.print(" off.</p>");
            client.print("<hl>");
            client.print("<p>Temperature:");
            client.print(bme.readTemperature());
            client.print(" &deg;C</p>");
            client.print("<p>Humidity:");
            client.print(bme.readHumidity());
            client.println(" %</p>");
            client.println("</html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(led_gpio, HIGH);
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(led_gpio, LOW);
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
