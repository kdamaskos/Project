
#include "network.h"

#include "globals.h"

#include "json_parser.h"


int arrivedcount, reset = 3;



void messageArrived(MQTT::MessageData &md) 
{
    ++arrivedcount;

    MQTT::Message &message = md.message;
  /*
    printf("\nMessage arrived: qos %d, retained %d, dup %d, packetid %d\r\n",
    message.qos, message.retained, message.dup, message.id);
*/
    printf("size %d  \r\n", message.payloadlen);

    printf("  %.*s\r\n", message.payloadlen, (char *)message.payload);
  
    char *ret = (char *)message.payload;

    if (ret[0] == '{') 
    {
        deserialize(ret,message.payloadlen);

        programs_submenu = SELECT_PROGRAM;

        refresh_watering_valves = true;
    
        event_flag.set(REFRESH_DISPLAY);

    }
}

/*

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

*/

int ntpGetTime(NTPClient ntp) 
{

    time_t timestamp;

    int retries = 2;

    ntp.set_server("0.gr.pool.ntp.org", 123);

ntp_retry:

    int rc = ntp.get_timestamp(timestamp);

    if (rc < 0 && retries > 0) 
    {
        printf("An error occurred when getting the time. Code: %d\r\n", rc);
        
        retries--;

        goto ntp_retry;
    } 
    else if (rc ==0)
    {
        set_time(timestamp);

        timestamp = time(NULL);

        struct tm *t = localtime(&timestamp);

        t->tm_hour = t->tm_hour + 3;

        timestamp = mktime(t);

        set_time(timestamp);

        printf("Current time is %s\r\n", ctime(&timestamp));

        return 0;
    }
    else 
    {
        return -1;
    
    }
}



