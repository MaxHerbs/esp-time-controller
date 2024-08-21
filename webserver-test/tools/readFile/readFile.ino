#include "SPIFFS.h"

void setup() {
  Serial.begin(115200);
  
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  File file = SPIFFS.open("/credentials.txt", "r");
  
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  while (file.available()) {
    String line = file.readString();
    Serial.print(line);
  }
  file.close();
}

void loop() {

}