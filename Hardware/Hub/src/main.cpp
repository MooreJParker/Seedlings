#include <Arduino.h>
#include <SPI.h>
#include "RF24.h"
#include "PacketDefs.h"

#define LED 2

// Radio
RF24 radio(7, 8);
const byte address[6] = "00001";

void setup()
{
    Serial.begin(9600);

    // LED
    pinMode(LED, OUTPUT);

    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();
}

void loop()
{
    // RECEIVE
    if (radio.available())
    {
        Packet::packet_t packet;
        radio.read(&packet, sizeof(packet));
        Serial.write((char*)&packet, sizeof(packet));
    }
}
