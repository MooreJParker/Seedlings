#include <Arduino.h>
#include <SPI.h>
#include "RF24.h"
#include "PacketDefs.h"
#include "Sensors.h"

// Radio
RF24 radio(7, 8);
const byte address[6] = "00001";

void setup()
{
    // Initialize soil moisture sensor
    SoilMoistureSensor::init();

    // Initialize radio for transmitting
    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();
}

void loop()
{
    // Construct and send packet
    Packet::packet_t packet;
    packet.sensor_id = 11;
    packet.category = Packet::READING;
    packet.event = Packet::SOIL_MOISTURE;
    packet.payload = SoilMoistureSensor::getSoilReading();

    radio.write((char*)&packet, sizeof(packet));
    delay(1000);
}
