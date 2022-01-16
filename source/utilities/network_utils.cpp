

#include "network_utils.h"

#include "globals.h"

#include "json_parser.h"


int arrivedcount, reset = 3;



void messageArrived(MQTT::MessageData &md) 
{
    ++arrivedcount;

    MQTT::Message &message = md.message;
  
    printf("\nMessage arrived: qos %d, retained %d, dup %d, packetid %d\r\n",
    message.qos, message.retained, message.dup, message.id);

    printf("Payload %.*s\r\n", message.payloadlen, (char *)message.payload);
  
    char *ret = (char *)message.payload;

    if (ret[0] == '{') 
    {
        deserialize(ret);

        
    }
  /*
  if (reset > 0 && ret[0] == 'u') {
      ret = ret +1;
    deserialize(ret);
    refresh_internet = 1;
    if (reset > 0) {
      reset--;
    }
  }
  */
}



int subscribe_channels(MQTTClient client)
{
    int rc;

    if ((rc = client.subscribe("controller1/newValves", MQTT::QOS1,
                             messageArrived)) != 0) 
    {

        printf("rc from valves subscribe is %d\r\n", rc);

        return rc;
    }


    if ((rc = client.subscribe("controller1/start_times", MQTT::QOS1,
                             messageArrived)) != 0) 
    {

        printf("rc from start_times subscribe is %d\r\n", rc);

        return rc;
    }

    if ((rc = client.subscribe("controller1/days", MQTT::QOS1, messageArrived)) !=
      0) 
    {
        printf("rc from days subscribe is %d\r\n", rc);

        return rc;
    }

    if ((rc = client.subscribe("controller1/manual", MQTT::QOS1,
                             messageArrived)) != 0) 
    {
        printf("rc from manual subscribe is %d\r\n", rc);

        return rc;
    }

    return rc;
}

void publish_data (char * buffer,  MQTT::Message msg, MQTTClient client)
{
    
    if (publish_valves) {
          serialize(0, buffer);
          msg.payload = (void *)buffer;
          msg.payloadlen = strlen(buffer);
          client.publish("controller1/newValves", msg);
          publish_valves = false;
          printf("%s\n", buffer);
        }
        if (publish_starts) {
          serialize(1, buffer);
          msg.payload = (void *)buffer;
          msg.payloadlen = strlen(buffer);
          client.publish("controller1/start_times", msg);
          publish_starts = false;
          printf("%s\n", buffer);
        }
        if (publish_days) {
          serialize(2, buffer);
          msg.payload = (void *)buffer;
          msg.payloadlen = strlen(buffer);
          client.publish("controller1/days", msg);
          publish_days = false;
          printf("%s\n", buffer);
        }
        if (publish_manual) {
          serialize(3, buffer);
          msg.payload = (void *)buffer;
          msg.payloadlen = strlen(buffer);
          client.publish("controller1/manual", msg);
          publish_manual = false;
          printf("%s\n", buffer);
        }
}



void ntpGetTime(NTPClient ntp) 
{

    ntp.set_server("0.gr.pool.ntp.org", 123);

    time_t timestamp;

ntp_retry:

    int rc = ntp.get_timestamp(timestamp);

    if (rc < 0) 
    {
        printf("An error occurred when getting the time. Code: %d\r\n", rc);
        
        goto ntp_retry;
    } 
    else 
    {
        set_time(timestamp);

        timestamp = time(NULL);

        struct tm *t = localtime(&timestamp);

        t->tm_hour = t->tm_hour + 3;

        timestamp = mktime(t);

        set_time(timestamp);

        printf("Current time is %s\r\n", ctime(&timestamp));
    }
}



