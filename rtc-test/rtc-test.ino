#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <HardwareSerial.h>



HardwareSerial output_serial(1);

const char* ssid = "WLANAP-Z";
const char* password = "arianwenmax";

// NTP Server details
const char* ntpServer = "pool.ntp.org";
long gmtOffset_sec;
const int daylightOffset_sec = 0;

WiFiUDP udp;
NTPClient timeClient(udp, ntpServer, 0, 60000);  // Initial offset is 0, will be set later

void setup() {
  Serial.begin(115200);
  output_serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");


  gmtOffset_sec = 3600;


  timeClient.setTimeOffset(gmtOffset_sec);
  timeClient.begin();
}

void loop() {

  String nmea = generate_nmea();
  Serial.println(nmea);
  output_serial.println(nmea);
  delay(10000);  // Update every 10 seconds
}

String generate_nmea() {
  timeClient.update();  // Ensure timeClient is updated


  String time = getFormattedTime();
  String date = getDateStr(timeClient.getEpochTime());

  String prefix = "$GNRMC,";
  String second_part = ".00,4717.1006,N,00147.3434,W,000.0,000.0,";
  String final_part = ",015.0,E,002.0,0000*2C";

  String nmea = prefix + time + second_part + date + final_part;




  return nmea;
}



String getFormattedTime() {
  int hours = timeClient.getHours();
  int minutes = timeClient.getMinutes();
  int seconds = timeClient.getSeconds();

  String hoursStr = (hours < 10) ? "0" + String(hours) : String(hours);
  String minutesStr = (minutes < 10) ? "0" + String(minutes) : String(minutes);
  String secondsStr = (seconds < 10) ? "0" + String(seconds) : String(seconds);


  String formattedTime = hoursStr + minutesStr + secondsStr;

  return formattedTime;
}

String getDateStr(unsigned long epochTime) {
  struct tm* timeinfo;
  timeinfo = localtime((time_t*)&epochTime);

  // Extract day, month, and year
  int day = timeinfo->tm_mday;
  int month = timeinfo->tm_mon + 1;    // Months are 0-11
  int year = timeinfo->tm_year % 100;  // Years since 1900

  // Format date as DDMMYY
  String dayStr = (day < 10) ? "0" + String(day) : String(day);
  String monthStr = (month < 10) ? "0" + String(month) : String(month);
  String yearStr = String(year);

  return dayStr + monthStr + yearStr;
}