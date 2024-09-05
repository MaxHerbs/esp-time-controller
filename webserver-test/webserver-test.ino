#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <FS.h>
#include "src/ROUTES-MASTER/MyRoutes.h"
#include <Arduino.h>

const char* ssid = "ESP-AP";
const char* password = "Password123!";


AsyncWebServer server(80);
IPAddress local_IP(192, 168, 0, 1);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);




void setup() {
  Serial.begin(115200);


  //Try mount the SPIFFS. Contains the HTML and style sheets etc
  if (!SPIFFS.begin(true)) {
    Serial.println("Failed to mount SPIFFS");
    return;
  }


  //Set up the ESP32 as an access point
  if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
    Serial.println("Failed to configure AP");
  }

  //Start the access point
  if (!WiFi.softAP(ssid, password)) {
    Serial.println("Failed to start AP");
  }



  // DEFINE ROUTES
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    Serial.println("Routing on /");
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest* request) {
    Serial.println("Routing on /script.js");
    request->send(SPIFFS, "/script.js", "text/javascript");
  });

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest* request) {
    Serial.println("Routing on /style.css");
    request->send(SPIFFS, "/style.css", "text/css");
  });






  server.on("/set_wifi_credentials", HTTP_GET, [](AsyncWebServerRequest* request) {
    Serial.println("Routing on set_wifi_credentials");
    if (!(request->hasParam("ssid") && request->hasParam("password"))) {
      request->send(400, "text/plain", "Failure: Missing parameters");
      return;
    }
    Serial.println("Both credentials present in GET.");
    String input_ssid = request->getParam("ssid")->value();
    String password = request->getParam("password")->value();


    bool success = set_wifi_credentials(input_ssid, password);
    String response = success ? "Success" : "Failure";
    Serial.println("Returning....");
    request->send(200, "text/plain", response);
  });

  server.on("/get_wifi_credentials", HTTP_GET, [](AsyncWebServerRequest* request) {
    Serial.println("Routing on get_wifi_credentials");

    String credentials = get_wifi_credentials();
    Serial.println("Returning....");
    Serial.println(credentials);
    request->send(200, "text/plain", credentials);
  });








  server.on("/set_timezone_details", HTTP_GET, [](AsyncWebServerRequest* request) {
    Serial.println("Routing on set_timezone_details");

    int hours = request->getParam("hours")->value().toInt();
    int minutes = request->getParam("minutes")->value().toInt();

    if (hours > 12 || hours < -12) {
      request->send(400, "text/plain", "Failure: Missing parameters");
      return;
    }
    if (minutes < 0 || minutes > 60 ) {
      request->send(400, "text/plain", "Failure: Missing parameters");
      return;
    }

    Serial.println("Both credentials present in GET.");

    bool success = set_timezone_details(hours, minutes);
    String response = success ? "Success" : "Failure";
    Serial.println("Returning....");
    request->send(200, "text/plain", response);
  });

  server.on("/get_timezone_details", HTTP_GET, [](AsyncWebServerRequest* request) {
    Serial.println("Routing on get_timezone_details");

    String credentials = get_timezone_details();
    Serial.println("Returning....");
    Serial.println(credentials);
    request->send(200, "text/plain", credentials);
  });









  // Start the server
  server.begin();
  Serial.println("Setup finished");
}

void loop() {
}
