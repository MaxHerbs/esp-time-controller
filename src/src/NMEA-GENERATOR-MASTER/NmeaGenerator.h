#ifndef NMEAGENERATOR_H
#define NMEAGENERATOR_H
#include <ESP8266WiFi.h>

#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ezTime.h>


#include <Arduino.h>  

String generate_nmea(Timezone timeClient);


#endif

