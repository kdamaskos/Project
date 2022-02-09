
#include "NTPClient.h"

#include <MQTTClientMbedOs.h>

int ntpGetTime(NTPClient ntp);

void publish_data (char * buffer,  MQTT::Message msg, MQTTClient client);

int subscribe_channels(MQTTClient client);

void messageArrived(MQTT::MessageData &md);
