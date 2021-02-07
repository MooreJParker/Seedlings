#pragma once

// Packet structure for transmitting sensor data
namespace Packet
{
    // Sensor ID type. Generated and hardware unique
    typedef uint8_t SensorId;

    // The category of the packet. It provides context for
    // the event
    typedef uint8_t Category; enum
    {
        READING = 0,
        ALERT
    };

    // The specific event that caused the event to take
    // place.
    typedef uint8_t Event;
    enum ReadingEvent
    {
        SOIL_MOISTURE = 0,
        SUNLIGHT,
        HUMIDITY,
        READING_EVENT_END
    };

    enum AlertEvent
    {
        LOW_BATTERY = READING_EVENT_END + 1
    };

    // Payload type. A generic buffer for holding the
    // actual data being transmitted
    typedef uint16_t Payload;

    // The packet type for receiving and sending
    struct packet_t
    {
        SensorId sensor_id;
        Category category;
        Event event;
        Payload payload;
    } __attribute((packed));
};
