#ifndef NMEAGENERATOR_H
#define NMEAGENERATOR_H
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>


#include <Arduino.h>  

String generate_nmea(NTPClient timeClient);


#endif

