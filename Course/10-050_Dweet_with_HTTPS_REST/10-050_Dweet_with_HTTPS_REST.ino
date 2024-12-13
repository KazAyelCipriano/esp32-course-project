#include <WiFiClientSecure.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
const char* ssid     = "ardwifi";
const char* password = "ardwifi987";

const char*  server = "dweet.io";      
String url = "/dweet/for/peterslab?";


//Dweet root certificate
const char* dweetio_root_ca = \
                              "-----BEGIN CERTIFICATE-----\n" \
                              "MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n" \
                              "ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n" \
                              "b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n" \
                              "MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n" \
                              "b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n" \
                              "ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n" \
                              "9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n" \
                              "IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n" \
                              "VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n" \
                              "93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n" \
                              "jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n" \
                              "AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n" \
                              "A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n" \
                              "U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n" \
                              "N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n" \
                              "o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n" \
                              "5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n" \
                              "rqXRfboQnoZsG4q5WTP468SQvvG5\n" \
                              "-----END CERTIFICATE-----\n";


WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  delay(100);
  bme.begin(0x76);
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
}
void loop() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("Connected to ");
  Serial.println(ssid);
  client.setCACert(dweetio_root_ca);
  String get_request = "GET https://";
  get_request += server;
  get_request += url;
  get_request += "temp=";
  get_request += bme.readTemperature();
  get_request += "&hum=";
  get_request += bme.readHumidity();
  get_request += " HTTP/1.0";
  Serial.println("The GET request will be:");
  Serial.println(get_request);
  Serial.println("\nStarting connection to server...");
  if (!client.connect(server, 443))
    Serial.println("Connection failed!");
  else {
    Serial.println("Connected to server!");
    client.println(get_request);    
    client.println(String("Host: ") + server);
    client.println("Connection: close");
    client.println();
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("headers received");
        break;
      }
    }
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }
    client.stop();
  }
  delay(20000);
}
