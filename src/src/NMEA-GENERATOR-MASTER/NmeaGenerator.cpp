#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ezTime.h>

// Prototypes for private functions.
String getFormattedTime(Timezone timeClient);
String getDateStr(Timezone timeClient);

String generate_nmea(Timezone timeClient)
{


  String time = getFormattedTime(timeClient);
  String date = getDateStr(timeClient);

  String prefix = "$GNRMC,";
  String second_part = ".00,4717.1006,N,00147.3434,W,000.0,000.0,";
  String final_part = ",015.0,E,002.0,0000*2C";

  // TODO - Use actual catchsum (2C) incase some devices check value.
  String nmea = prefix + time + second_part + date + final_part;

  return nmea;
}

String getFormattedTime(Timezone timeClient) {  
  return timeClient.dateTime("His");
}

String getDateStr(Timezone timeClient)
{
    return timeClient.dateTime("dmy");
}
