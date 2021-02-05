#pragma once

#include <Arduino.h>
#include "PacketDefs.h"

namespace SoilMoistureSensor
{
    // Pins
    static const uint8_t VCC_PIN = 2;
    static const uint8_t READ_PIN = A0;

    // Const vals for reading
    static const uint8_t HIGH_MS = 50;

    // Set the state for the pins and disable sensor power
    void init()
    {
        pinMode(VCC_PIN, OUTPUT);
        pinMode(READ_PIN, INPUT);

        digitalWrite(VCC_PIN, LOW);
    }

    // Power up the sensor, get a reading, power it down
    // and return the reading
    Packet::Payload getSoilReading()
    {
        digitalWrite(VCC_PIN, HIGH);
        delay(HIGH_MS);

        uint16_t readVal = analogRead(READ_PIN);
        digitalWrite(VCC_PIN, LOW);

        return (Packet::Payload)readVal;
    }
};