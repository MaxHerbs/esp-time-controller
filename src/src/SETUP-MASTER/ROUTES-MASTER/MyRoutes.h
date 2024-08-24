#ifndef MYROUTES_H
#define MYROUTES_H
#include <Arduino.h>  


bool set_wifi_credentials(String ssid, String password);
String get_wifi_credentials();

bool set_timezone_details(int hours, int minutes);
String get_timezone_details();
#endif