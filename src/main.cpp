/* 
 * Program pre ESP8266 OTA pre IoT
 *
 * Posledna zmena(last change): 16.05.2021
 * @author Ing. Peter VOJTECH ml. <petak23@gmail.com>
 * @copyright  Copyright (c) 2019 - 2021 Ing. Peter VOJTECH ml.
 * @license
 * @link    http://petak23.echo-msz.eu
 * @version 0.0.2
 * @link    https://RandomNerdTutorials.com/esp8266-nodemcu-ota-over-the-air-vs-code/
 * 
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include <Arduino_JSON.h>
#include <AsyncElegantOTA.h>

#include "definitions.h"                  // Súbor nastavení a prihlasovacích údajov

AsyncWebServer server(80);

// Initialize LittleFS
void initLittleFS() {
  if (!LittleFS.begin()) {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  Serial.println("LittleFS mounted successfully");
}

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup(void) {
  Serial.begin(115200);
  Serial.println("");

  initLittleFS();
  initWiFi();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html",false);
  });

  server.serveStatic("/", LittleFS, "/");

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
}

void loop(void) {
  AsyncElegantOTA.loop();
}
