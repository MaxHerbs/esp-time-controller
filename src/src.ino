#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <FS.h>
#include "src/SETUP-MASTER/Setup.h" //SRC is a bad folder namebut neccessary for recursive compilation of the functions within each folder
#include "src/SETUP-MASTER/ROUTES-MASTER/MyRoutes.h" 
#include "src/NMEA-GENERATOR-MASTER/NmeaGenerator.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ezTime.h>


Timezone timeClient;


//TODO - Decide on real pin
int button_pin = 39; //TBC - Correct for esp32 ATOM LITE
bool run_setup;
int last_millis = 0;
int update_interval = 10000; //Frequency at which serial prints GPS time message

void setup()
{
  Serial.begin(115200);
  pinMode(button_pin, INPUT);

  // Check SPIFFS is okay. Code cannot function without
  if (!SPIFFS.begin(true))
  {
    Serial.println("Failed to mount SPIFFS");
    return;
  }

  run_setup = !digitalRead(button_pin); //'Not' due to pin setup in testing

  if (run_setup)
  {
    Serial.println("Running setup...");
    bool success = configure(); // External function. Contains all HTTP routes and starts access point
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
    //Keep looping
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
      last_millis = millis();
      String nmea_time_str = generate_nmea(timeClient);
      Serial.println(nmea_time_str);
    }
    delay(50);
  }
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


  Serial.print("Configuring timezone with continent: ");
  Serial.print(continent);
  Serial.print(" and city: ");
  Serial.println(city);

  String location_str = continent + "/" + city;
  timeClient.setLocation(location_str);
  waitForSync();
  Serial.println("Local time: " + timeClient.dateTime());

  return true;
}
