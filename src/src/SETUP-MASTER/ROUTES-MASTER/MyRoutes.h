#ifndef MYROUTES_H
#define MYROUTES_H
#include <Arduino.h>

struct ValidateWifiObject {
  int startValidation;
  String ssid;
  String password;
  int searchComplete; //0: polling - 1: success - 2: failed
};



bool set_wifi_credentials(String ssid, String password);
String get_wifi_credentials();
bool verify_wifi_credentials(String ssid, String password);
void get_available_wifi();
extern String defaultNetworks;

extern int startValidation;
extern String testSsid;
extern String testPassword;
extern int searchComplete; //0: pending - 1: started - 2: success - 3: failure


bool set_timezone_details(String continent, String city);
String get_timezone_details();

bool restore_config_file();
#endif