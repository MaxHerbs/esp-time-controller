//TODO:
// 1) Manual rescan wifi
// 2) Improve stability of `verify wifi` 
// 3) Fix continent drop down
// 4) Improve ui feedback/stability

#include <ESP8266WiFi.h>

#include <ESPAsyncWebServer.h>

#include <FS.h>
#include "src/SETUP-MASTER/Setup.h" //SRC is a bad folder namebut neccessary for recursive compilation of the functions within each folder
#include "src/SETUP-MASTER/ROUTES-MASTER/MyRoutes.h"
#include "src/NMEA-GENERATOR-MASTER/NmeaGenerator.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ezTime.h>
#include <DNSServer.h>


Timezone timeClient;
DNSServer dnsServer;
pin
int button_pin = 0; 
bool run_setup;
int last_millis = 0;
int update_interval = 10000; //Frequency at which serial prints GPS time message

void setup()
{
  Serial.begin(115200);
  pinMode(button_pin, INPUT);

  // Check SPIFFS is okay. Code cannot function without
  if (!SPIFFS.begin())
  {
    Serial.println("Failed to mount SPIFFS");
    return;
  }
  Serial.println("");
  Serial.println("Waiting for decision...");
  delay(5000);


  run_setup = !digitalRead(button_pin); //'Not' due to pin setup in testing

  String decision = run_setup ? "Config Mode" : "Printing NMEA";
  Serial.print("Decision: ");
  Serial.println(decision);

  if (run_setup)
  {
    Serial.println("Running setup...");
    bool success = configure(dnsServer); // External function. Contains all HTTP routes and starts access point
    get_available_wifi();

  }
  else
  {
    //Connect to wifi and setup the NTP time client
    //Both need to successfully retrieve SSID,password,timezone from the SPIFFS
    connect_to_wifi();
    configure_time_client();
  }
}

void loop()
{
  if (run_setup)
  {
    dnsServer.processNextRequest();
    if (startValidation) {
      validate_wifi();
    }
  }
  else
  {
    //Reconnect wifi if necessary
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("WiFi connection lost. Reconnecting...");
      connect_to_wifi();
    }

    if (millis() - last_millis > update_interval) //Only post message every 10 seconds
    {
      events();
      last_millis = millis();
      String nmea_time_str = generate_nmea(timeClient);
      Serial.println(nmea_time_str);
    }
    delay(50);
  }
}




void validate_wifi() {
  //extern int startValidation;
  //extern String testSsid;
  //extern String testPassword;
  //extern int searchComplete;

  searchComplete = 1;

  unsigned long startAttemptTime = millis();
  const unsigned long timeout = 15000;
  Serial.print("Trying to verify wifi...");
  WiFi.begin(testSsid.c_str(), testPassword.c_str());
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    if (millis() - startAttemptTime >= timeout)
    {
      Serial.println("Failed");
      searchComplete = 3;
      testSsid = "";
      testPassword = "";
      startValidation = 0;
      return;
    }
    delay(100);
    yield();
  }

  searchComplete = 2;
  testSsid = "";
  testPassword = "";
  startValidation = 0;
  WiFi.disconnect();
  Serial.println("Success");
  return;



}





void connect_to_wifi()
{
  String wifi_json = get_wifi_credentials(); //Returns a json string containing the SSID and password
  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, wifi_json);
  if (error)
  {
    Serial.print("deserializeJson() failed in WiFi setup");
    Serial.println(error.f_str());
    return;
  }


  //TODO - Check both keys exis. Handle if not
  //Does the return type need to be bool based on success/fail?
  const char *imported_ssid = doc["ssid"];
  const char *imported_password = doc["password"];

  Serial.print("Connecting wifi with ssid: ");
  Serial.print(imported_ssid);
  Serial.print(" and password: ");
  Serial.println(imported_password);


  //TODO - Add a fail condition here if wifi is not present/credentials are wrong
  WiFi.begin(imported_ssid, imported_password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
}


bool configure_time_client()
{
  String timezone_json = get_timezone_details(); //Returns a JSON string with the `hours` and `minutes` of the offset
  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, timezone_json);
  if (error)
  {
    Serial.print("deserializeJson() failed in timezone setup");
    Serial.println(error.f_str());
    return false;
  }


  //TODO - Add redundancy/checking to ensure type and existance of both keys.
  String continent = doc["continent"];
  String city = doc["city"];


  Serial.print("Configuring timezone for " + city + ", " + continent);

  String location_str = continent + "/" + city;
  timeClient.setLocation(location_str);
  waitForSync();
  Serial.println("Local time: " + timeClient.dateTime());
  Serial.println("POSIX: " + timeClient.getPosix());
  Serial.print("Currently daylight saving? ");
  String dst = timeClient.isDST() ? "Yes" : "No";
  Serial.println(dst);


  return true;
}
