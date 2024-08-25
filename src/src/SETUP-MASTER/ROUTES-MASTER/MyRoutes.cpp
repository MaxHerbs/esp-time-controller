#include "MyRoutes.h"
#include <ArduinoJson.h>
#include <Arduino.h>
#include "SPIFFS.h"
#include <WiFi.h>
#include "esp_system.h"
#include "esp_task_wdt.h"

// TODO - Dual band; verify credentials before storing
// Optional force-store even if wifi cannot be found
bool set_wifi_credentials(String ssid, String password)
{
    File input_file = SPIFFS.open("/credentials.txt", "r");

    if (!input_file)
    {
        Serial.println("Failed to open file for reading credentials #101");
        return false;
    }

    String text = input_file.readString();
    input_file.close();

    StaticJsonDocument<512> doc;
    Serial.println("Deserialising json to replace wifi credentials...");
    DeserializationError error = deserializeJson(doc, text);
    if (error)
    {
        Serial.print("deserializeJson() failed #102: ");
        Serial.println(error.f_str());
        return false;
    }

    doc["wifi"]["ssid"] = ssid;
    doc["wifi"]["password"] = password;
    Serial.println("Wifi credentials replaced!");

    String output_json;
    serializeJson(doc, output_json);
    Serial.println("Re-serialised JSON");

    File output_file = SPIFFS.open("/credentials.txt", FILE_WRITE);

    if (!output_file)
    {
        Serial.println("Failed to open credentials for writing #103");
        return false;
    }

    // Write to the file
    output_file.println(output_json);

    // Close the file
    output_file.close();
    return true;
}

String get_wifi_credentials()
{

    File credential_file = SPIFFS.open("/credentials.txt", "r");

    if (!credential_file)
    {
        Serial.println("Failed to open file for reading credentials #201");
        return "error";
    }

    String text = credential_file.readString();
    credential_file.close();

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, text);
    if (error)
    {
        Serial.print("deserializeJson() failed #202: ");
        Serial.println(error.f_str());
        return "error";
    }

    // TODO - Add redundancy if key is not present
    return doc["wifi"];
}

bool verify_wifi_credentials(String ssid, String password)
{

    unsigned long startAttemptTime = millis();
    const unsigned long timeout = 10000;
    Serial.print("Trying to verify wifi...");
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        if (millis() - startAttemptTime >= timeout)
        {
            Serial.println("Failed");
            return false;
        }
        delay(10);
        yield();
        esp_task_wdt_reset();
    }

    Serial.println("Success");
    return true;
}

//
//
//
//
//
//
//
/// TIMEZONE ///
bool set_timezone_details(int hours, int minutes)
{
    File input_file = SPIFFS.open("/credentials.txt", "r");

    if (!input_file)
    {
        Serial.println("Failed to open file for reading credentials #301");
        return false;
    }

    String text = input_file.readString();
    input_file.close();

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, text);
    if (error)
    {
        Serial.print(F("deserializeJson() failed #302: "));
        Serial.println(error.f_str());
        return false;
    }
    Serial.println("Deserialising json to replace wifi credentials...");
    doc["timezone"]["hours"] = hours;
    doc["timezone"]["minutes"] = minutes;
    Serial.println("Timezone credentials replaced!");

    String output_json;
    serializeJson(doc, output_json);
    Serial.println("Re-serialised JSON");

    File output_file = SPIFFS.open("/credentials.txt", FILE_WRITE);

    if (!output_file)
    {
        Serial.println("Failed to open credentials for writing #303");
        return false;
    }

    // Write to the file
    output_file.println(output_json);

    // Close the file
    output_file.close();
    return true;
}

String get_timezone_details()
{
    File credential_file = SPIFFS.open("/credentials.txt", "r");

    if (!credential_file)
    {
        Serial.println("Failed to open file for reading credentials #401");
        return "error";
    }

    String text = credential_file.readString();
    credential_file.close();

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, text);
    if (error)
    {
        Serial.print("deserializeJson() failed #402: ");
        Serial.println(error.f_str());
        return "error";
    }

    // TODO - Add redundancy if key is not present
    return doc["timezone"];
}


bool restore_config_file() {
    // Open file for writing
    File restore_file = SPIFFS.open("/credentials.txt", FILE_WRITE);
    
    if (!restore_file) {
        Serial.println("Failed to open credentials for writing #501");
        return false;
    }

    // Create a JSON document
    StaticJsonDocument<512> doc;
    doc["wifi"]["ssid"] = "temp";
    doc["wifi"]["password"] = "temp";
    doc["timezone"]["hours"] = 1;
    doc["timezone"]["minutes"] = 30;

    // Serialize JSON to string
    String jsonString;
    serializeJson(doc, jsonString);

    // Write JSON string to file
    if (restore_file.print(jsonString)) {
        Serial.println("Configuration file restored successfully.");
        restore_file.close();
        return true;
    } else {
        Serial.println("Failed to write configuration to file.");
        restore_file.close();
        return false;
    }
}
