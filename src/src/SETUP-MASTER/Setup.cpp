#include "Setup.h"
#include <ArduinoJson.h>
#include "ROUTES-MASTER/MyRoutes.h"
#include <ESP8266WiFi.h>

#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <DNSServer.h>

AsyncWebServer server(80);

const char *ssid = "ESP-ACCESS-POINT";
const char *password = "Password123!";



bool configure(DNSServer& dnsServer)
{
  // if (!WiFi.softAPConfig(local_IP, gateway, subnet))
  // {
  //   Serial.println("Failed to configure AP");
  // }


  WiFi.mode(WIFI_AP_STA);
  delay(100);
  if (!WiFi.softAP(ssid, password))
  {
    Serial.println("Failed to start AP");
  }


    // DNS server for captive portal
    Serial.println("Starting dns");
    if (dnsServer.start(53, "*", WiFi.softAPIP()))
    {
      Serial.println("DNS server started successfully");
    }
    else
    {
      Serial.println("Failed to start DNS server");
    }



  // Define routes -Static
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    Serial.println("Routing on /");
    request->send(SPIFFS, "/index.html", "text/html"); });

  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    Serial.println("Routing on /script.js");
    request->send(SPIFFS, "/script.js", "text/javascript"); });




  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    Serial.println("Routing on /style.css");
    request->send(SPIFFS, "/style.css", "text/css"); });
    
  server.onNotFound([](AsyncWebServerRequest *request){
    String requestedUrl = request->url();
    Serial.println("Requested endpoint not found: " + requestedUrl);
    if(requestedUrl == "/favicon.ico"){
      request->send(404, "text/plain", "");
      return;
    }

    request->redirect("/");
  });

  //
  //
  //
  //
  //
  //
  //
  //

server.on("/set_wifi_credentials", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Routing on set_wifi_credentials");
    if (!(request->hasParam("ssid") && request->hasParam("password"))) {
        request->send(400, "text/plain", "Failure: Missing parameters");
        return;
    }
    String input_ssid = request->getParam("ssid")->value();
    String password = request->getParam("password")->value();
    bool success = set_wifi_credentials(input_ssid, password);
    String response = success ? "Success" : "Failure";
    request->send(200, "text/plain", response);
});

server.on("/get_wifi_credentials", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Routing on get_wifi_credentials");
    String credentials = get_wifi_credentials();
    request->send(200, "text/plain", credentials);
});

server.on("/verify_wifi_credentials", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (!(request->hasParam("ssid") && request->hasParam("password"))) {
        request->send(400, "text/plain", "Failure: Missing parameters");
        return;
    }  
    String input_ssid = request->getParam("ssid")->value();
    String password = request->getParam("password")->value();
    if(input_ssid.length() < 2 || password.length() < 2){
      request->send(400, "text/plain", "Failure: SSID or passoword too short");
      return;
    }
    bool success = verify_wifi_credentials(input_ssid, password);
    String response = success ? "Success" : "Failure";
    request->send(200, "text/plain", response);
});

server.on("/check_wifi_verification", HTTP_GET, [](AsyncWebServerRequest *request) {
  Serial.println("Checking wifi verification");

  StaticJsonDocument<512> doc;
  doc["validationState"] = startValidation;
  doc["ssid"] = testSsid;
  doc["password"] = testPassword;
  doc["status"] = searchComplete;

    // Serialize JSON to string
  String jsonString;
  serializeJson(doc, jsonString);


  Serial.print("Start validation ");
  Serial.println(startValidation);
  Serial.print("testSsid ");
  Serial.println(testSsid);
  Serial.print("testPassword ");
  Serial.println(testPassword);
  Serial.println("Search complete ");
  Serial.println(searchComplete);

  request->send(200, "application/json", jsonString);

});




server.on("/get_available_wifi", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", defaultNetworks);
});


  //
  //
  //
  //
  //
  //
  //

  // Routes relating to the timezone
  server.on("/set_timezone_details", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    Serial.println("Routing on set_timezone_details");

    if (!(request->hasParam("continent") && request->hasParam("city")))
    {
      request->send(400, "text/plain", "Failure: Missing parameters");
      return;
    }

    String continent = request->getParam("continent")->value();
    String city = request->getParam("city")->value();
    

    bool success = set_timezone_details(continent, city);
    String response = success ? "Success" : "Failure";
    request->send(200, "text/plain", response); });

  server.on("/get_timezone_details", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    Serial.println("Routing on get_timezone_details");
    String credentials = get_timezone_details();
    request->send(200, "text/plain", credentials); });
  //
  //
  //
  //
  //
  // General
  server.on("/reboot", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    Serial.println("Routing on reboot");

    request->send(200, "text/plain", "Rebooting");
    ESP.restart(); });

  server.on("/restore_config_file", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    Serial.println("Routing on restore_config_file");
    bool success = restore_config_file();

    String response = success ? "Success": "Failure";
    
    request->send(200, "text/plain", response); });


  server.begin();
  Serial.println("Setup finished");

  return true;
}
