#include "smprotocol.h"

class SmRadio
{
public:
    virtual void openReadingPipe(uint8_t number, const uint8_t *address) = 0;
    virtual void openWritingPipe(const uint8_t *address) = 0;
    virtual void startListening() = 0;
    virtual void stopListening() = 0;
    virtual void begin() = 0;
    virtual bool available() = 0;
    virtual void read(void *buf, uint8_t len) = 0;
    virtual bool write(const void *buf, uint8_t len) = 0;

    bool registerInHub();
};