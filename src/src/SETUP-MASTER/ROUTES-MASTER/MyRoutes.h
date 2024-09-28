#ifndef MYROUTES_H
#define MYROUTES_H
#include <Arduino.h>



bool set_wifi_credentials(String ssid, String password);
String get_wifi_credentials();
bool verify_wifi_credentials(String ssid, String password);
void get_available_wifi();
extern String defaultNetworks;

extern int flagStartValidation;
extern String testSsid;
extern String testPassword;
extern int searchComplete; //0: pending - 1: started - 2: success - 3: failure

extern int flagRescanWifi;

bool set_timezone_details(String continent, String city);
String get_timezone_details();

bool restore_config_file();
#endif