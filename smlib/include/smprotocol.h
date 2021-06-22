typedef unsigned char uint8_t;

const uint8_t pipes[][6] = {"Prime", "1Node", "2Node"};
const uint8_t *registerPipe = pipes[0];
const uint8_t *dataPipe = pipes[1];

enum MessageType
{
    Ping,
    DeviceRegistration,
    TemperatureReport
};

struct MessageHeader
{
    MessageType type;
    uint8_t source[4];
    uint8_t destination[4];
    int contentSize;
};

struct DeviceRegistration
{
    uint8_t identifier[4];
};

struct DeviceRegistrationResponse
{
    bool registered;
};

struct Message
{
    MessageHeader header;
    uint8_t *content;
};
