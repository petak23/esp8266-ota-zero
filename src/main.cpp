/*
  Rui Santos
  Complete project details
    - Arduino IDE: https://RandomNerdTutorials.com/esp8266-nodemcu-ota-over-the-air-arduino/
    - VS Code: https://RandomNerdTutorials.com/esp8266-nodemcu-ota-over-the-air-vs-code/
    
  This sketch shows a Basic example from the AsyncElegantOTA library: ESP8266_Async_Demo
  https://github.com/ayushsharma82/AsyncElegantOTA
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

#include "definitions.h"                  // Súbor nastavení a prihlasovacích údajov

AsyncWebServer server(80);

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP8266. To update type: '/update' after IP adress.");
  });

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  AsyncElegantOTA.loop();
}
