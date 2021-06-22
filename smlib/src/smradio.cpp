#include "../include/smradio.h"

#include <random>

using namespace std;

bool SmRadio::registerInHub()
{
    this->stopListening();
    this->openWritingPipe(registerPipe);

    struct MessageHeader header;
    struct DeviceRegistration deviceRegistration;
    struct Message message;

    header.source 

    return true;
}