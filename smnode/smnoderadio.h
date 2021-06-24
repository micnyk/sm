#include <Arduino.h>
#include <RF24.h>
#include "smlib/smprotocol.h"

typedef unsigned long (*MillisFn)();

class SmNodeRadio
{
public:
    SmNodeRadio(RF24 radio, MillisFn millisFn) : radio(radio)
    {
        this->millis = millisFn;
    }

    bool begin()
    {
        smprintln("Radio begin()");

        if (!this->radio.begin())
            return false;

        this->radio.setChannel(70);
        this->radio.setRetries(15, 15);
        this->radio.setDataRate(RF24_250KBPS);
        this->radio.openWritingPipe(hubAddress);
        this->radio.openReadingPipe(1, nodeAddresses[0]);

        return true;
    }

    bool registerInHub()
    {
        struct MessageHeader header;

        header.type = MessageType::DeviceRegistration;
        header.contentSize = 0;

        this->radio.stopListening();

        bool ack = false;
        uint8_t retries = 0;

        while (!ack)
        {
            if (retries == 10)
            {
                smprintln("Max device registration send retries reached");
                return false;
            }

            ack = this->radio.write(&header, sizeof(header));
            retries++;

            delay(1000);
        }

        this->radio.startListening();

        unsigned long startTime = this->millis();
        uint8_t buffer[32];

        while (1)
        {
            if (this->radio.available())
            {
                this->radio.read(buffer, 32);

                MessageHeader *responseHeader = reinterpret_cast<MessageHeader *>(buffer);

                if (responseHeader->type == MessageType::DeviceRegistered && responseHeader->contentSize == sizeof(DeviceRegistration))
                {
                    DeviceRegistrationResponse *response = reinterpret_cast<DeviceRegistrationResponse *>(buffer + sizeof(MessageHeader));

                    if (response->registered)
                    {
                        smprint("Node registered with index ");
                        smprint(response->nodeIndex);
                        smprintln();

                        this->nodeAddress = nodeAddresses[response->nodeIndex];
                        this->radio.openReadingPipe(1, this->nodeAddress);
                        return true;
                    }
                }
                else
                {
                    smprintln("Received corrupted message or address 0 already taken");
                }
            }

            if (this->millis() - startTime > 10000)
            {
                smprintln("10s waiting for response exceeded");
                return false;
            }

            delay(100);
        }

        return false;
    }

private:
    RF24 &radio;
    MillisFn millis;
    const uint8_t *nodeAddress;
};