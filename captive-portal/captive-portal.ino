#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>

const char *ssid = "ESP32-AP";
const char *password = "123456789";

AsyncWebServer server(80);
DNSServer dns;

void setup() {
  Serial.begin(115200);

  // Set up the Access Point
  WiFi.softAP(ssid, password);

  // Set up the DNS server to redirect all DNS requests to the ESP32's IP address
  dns.start(53, "*", WiFi.softAPIP());

  // Serve the captive portal page
  server.onNotFound([](AsyncWebServerRequest *request){
    // Redirect to captive portal page
    request->redirect("/");
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "<h1>Welcome to the ESP32 Captive Portal</h1>");
  });

  server.begin();
}

void loop() {
  dns.processNextRequest();
}
