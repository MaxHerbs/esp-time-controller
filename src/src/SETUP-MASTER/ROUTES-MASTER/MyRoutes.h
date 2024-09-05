#ifndef MYROUTES_H
#define MYROUTES_H
#include <Arduino.h>

bool set_wifi_credentials(String ssid, String password);
String get_wifi_credentials();
bool verify_wifi_credentials(String ssid, String password);

bool set_timezone_details(String continent, String city);
String get_timezone_details();

bool restore_config_file();
#endif