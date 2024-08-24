#include "MyRoutes.h"
#include <ArduinoJson.h>
#include <Arduino.h>
#include "SPIFFS.h"

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
    return doc["wifi"];
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

    return doc["timezone"];
}
