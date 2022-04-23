
#include "NTPClient.h"

#include <MQTTClientMbedOs.h>

int ntpGetTime(NTPClient ntp);

int subscribe_channels(MQTTClient client);

void messageArrived(MQTT::MessageData &md);
