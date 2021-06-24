typedef unsigned char uint8_t;

const uint8_t hubAddress[5] = {'S', 'M', 'H', 'U', 'B'};
const uint8_t nodeAddresses[4][5] = {
    {'N', 'O', 'D', 'E', '1'},
    {'N', 'O', 'D', 'E', '2'},
    {'N', 'O', 'D', 'E', '3'},
    {'N', 'O', 'D', 'E', '4'},
};

enum MessageType
{
    Ping,
    DeviceRegistration,
    DeviceRegistered,
    TemperatureReport
};

struct MessageHeader
{
    MessageType type;
    int contentSize;
};

struct DeviceRegistrationResponse
{
    bool registered;
    uint8_t nodeIndex;
};
