#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
#include <DHT.h>

#if SIMULATED_DATA

void initSensor()
{
    // use SIMULATED_DATA, no sensor need to be inited
}

float readTemperature()
{
    return random(20, 30);
}

float readHumidity()
{
    return random(30, 40);
}

#else

static DHT dht(DHT_PIN, DHT_TYPE);
void initSensor()
{
    dht.begin();
}

float readSound()
{
    int sound = -1;
    if (Serial.available() >= 2) {
        sound = Serial.read() << 8;    // read high byte and shift it over
        sound |= Serial.read();        // read low byte
    }

    Serial.print("Sound level: ");
    Serial.println(sound);
    return sound;
}

float readHumidity()
{
    return dht.readHumidity();
}

#endif

bool readMessage(int messageId, char *payload)
{
    int decibal = readSound();
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["deviceId"] = DEVICE_ID;
    root["messageId"] = messageId;
    bool soundAlert = false;

    if (decibal != -1) {
        root["decibal"] = decibal;
        soundAlert = true;
    }
    
    // NAN is not the valid json, change it to NULL
    /*if (std::isnan(temperature))
    {
        root["decibal"] = decibal;
    }
    else
    {
        root["decibal"] = temperature;
        if (temperature > TEMPERATURE_ALERT)
        {
            temperatureAlert = true;
        }
    }*/

    root.printTo(payload, MESSAGE_MAX_LEN);
    return soundAlert;//temperatureAlert;
}

void parseTwinMessage(char *message)
{
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(message);
    if (!root.success())
    {
        Serial.printf("Parse %s failed.\r\n", message);
        return;
    }

    if (root["desired"]["interval"].success())
    {
        interval = root["desired"]["interval"];
    }
    else if (root.containsKey("interval"))
    {
        interval = root["interval"];
    }
}
