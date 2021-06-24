#define DEBUG

#ifdef DEBUG
#define smprintln(msg) Serial.println(msg)
#define smprint(msg) Serial.print(msg)
#else
#define smprintln(msg)
#define smprint(msg)
#endif

#include <Arduino.h>
#include <LowPower.h>
#include "smnoderadio.h"

RF24 radio(9, 10);
SmNodeRadio nodeRadio(radio, &millis);

void setup()
{
#ifdef DEBUG
    Serial.begin(115200);
#endif

    if (!nodeRadio.begin())
    {
        Serial.println("Failed to initialize radio hardware");
        Serial.flush();
        LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    };

    Serial.println("Radio hardware initialized");

    nodeRadio.registerInHub();
}

void loop()
{
}