#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

// Prototypes for private functions.
String getFormattedTime(NTPClient timeClient);
String getDateStr(unsigned long epochTime, NTPClient timeClient);

String generate_nmea(NTPClient timeClient)
{
  timeClient.update();

  String time = getFormattedTime(timeClient);
  String date = getDateStr(timeClient.getEpochTime(), timeClient);

  String prefix = "$GNRMC,";
  String second_part = ".00,4717.1006,N,00147.3434,W,000.0,000.0,";
  String final_part = ",015.0,E,002.0,0000*2C";

  // TODO - Use actual catchsum (2C) incase some devices check value.
  String nmea = prefix + time + second_part + date + final_part;

  return nmea;
}

String getFormattedTime(NTPClient timeClient)
{
  int hours = timeClient.getHours();
  int minutes = timeClient.getMinutes();
  int seconds = timeClient.getSeconds();

  String hoursStr = (hours < 10) ? "0" + String(hours) : String(hours);
  String minutesStr = (minutes < 10) ? "0" + String(minutes) : String(minutes);
  String secondsStr = (seconds < 10) ? "0" + String(seconds) : String(seconds);

  String formattedTime = hoursStr + minutesStr + secondsStr;

  return formattedTime;
}

String getDateStr(unsigned long epochTime, NTPClient timeClient)
{
  struct tm *timeinfo;
  timeinfo = localtime((time_t *)&epochTime);

  // Extract day, month, and year
  int day = timeinfo->tm_mday;
  int month = timeinfo->tm_mon + 1;   // Months are 0-11
  int year = timeinfo->tm_year % 100; // Years since 1900

  // Format date as DDMMYY
  String dayStr = (day < 10) ? "0" + String(day) : String(day);
  String monthStr = (month < 10) ? "0" + String(month) : String(month);
  String yearStr = String(year);

  return dayStr + monthStr + yearStr;
}
