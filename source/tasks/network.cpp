
#include "include/network.h"
#include "config/pins_config.h"
#include "mbed.h"
#include "network.h"
#include "ESP8266Interface.h"
#include "globals.h"
#include "mbed.h"
#include <MQTTClientMbedOs.h>
#include <cstring>
#include <string>
#include <time.h>
#include <utilities/include/network_utils.h>
#include <utilities/include/json_parser.h>



// 0,        /*!< no error */
//-3001,     /*!< no data is not available but call is non-blocking */
//-3002,     /*!< unsupported functionality */
//-3003,     /*!< invalid configuration */
//-3004,     /*!< not connected to a network */
//-3005,     /*!< socket not available for use */
//-3006,     /*!< IP address is not known */
//-3007,     /*!< memory resource not available */
//-3008,     /*!< ssid not found */
//-3009,     /*!< DNS failed to complete successfully */
//-3010,     /*!< DHCP failed to complete successfully */
//-3011,     /*!< connection to access point failed */
//-3012,     /*!< failure interfacing with the network processor */
//-3013,     /*!< operation (eg connect) in progress */
//-3014,     /*!< operation (eg connect) already in progress */
//-3015,     /*!< socket is already connected */
//-3016,     /*!< connection lost */
//-3017,     /*!< connection timed out */
//-3018,     /*!< Address already in use */
//-3019,     /*!< operation timed out */
//-3020,     /*!< device is busy and cannot accept new operation */


DigitalInOut reset_esp(RESET_ESP);

DigitalInOut power_esp(PA_11);


//b72bf77dd82cb3ff9a431a86b59c42c6


ESP8266Interface esp(ESP_TX_PIN, ESP_RX_PIN);

#define BUFFER_SIZE  600
#define TOTAL_BUFFER_SIZE 1200
 
char buffer1[BUFFER_SIZE];
char buffer2[BUFFER_SIZE];
char total_buffer[BUFFER_SIZE];

char ServerName[] = "api.openweathermap.org";
char http_cmd[] = "GET /data/2.5/weather?q=Athens&appid=d850f7f52bf19300a9eb4b0aa6b80f0d HTTP/1.0\r\n\r\n";
 

void weather_retrieve_task()
{

     printf(" Welcome \n");

    SocketAddress a;
    esp.get_ip_address(&a);
 
    printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");
 
 
        // Initialize the TCP Socket Connection
        TCPSocket socket;
        socket.open(&esp);
        esp.gethostbyname(ServerName, &a);
        printf("IP of server: %s\n", a.get_ip_address());
        a.set_port(80);
 
        if(socket.connect(a) < 0)
            printf("-- Connect - Fail -- \r\n");



        while(1)
        {

        
        // ThisThread::sleep_for(3s);
        socket.send(http_cmd, sizeof(http_cmd));
 
        int n = socket.recv(buffer1, sizeof buffer1);
 
        char *ret ;
        ret = strstr(buffer1,"POST");
        ret = strstr(buffer1,"{");
        strcpy(total_buffer,ret);
        int n2 = socket.recv(buffer2, sizeof buffer2);
        strcat(total_buffer,buffer2);
 
 
        printf("\n\n2  %s \n\n",total_buffer);

        ThisThread::sleep_for(15s);

        }

}


NTPClient ntp(&esp);

//Store device IP
SocketAddress deviceIP;
//Store broker IP
SocketAddress MQTTBroker;

TCPSocket socket;

MQTTClient client(&socket);


Thread thread23(osPriorityNormal, 10 * 1024);


void internet() 
{
   // thread23.start(callback(weather_retrieve_task));

    printf("Hello from Mbed OS %d.%d", MBED_MAJOR_VERSION, MBED_MINOR_VERSION);

    printf("\nConnecting wifi..\n");

reconnect:

    power_esp = 1;

    reset_esp  = 1;

    int rc = esp.connect("dimdamas", "damas61311", NSAPI_SECURITY_WPA_WPA2);

    if(rc != 0) 
    {
        printf("\nConnection error %d\n",rc);
        
        reset_esp  = 0;

        ThisThread::sleep_for(2s);

        goto reconnect;

    } 
    else
    {
        esp.get_ip_address(&deviceIP);

        printf("IP via DHCP: %s\n", deviceIP.get_ip_address());
    }

    ntpGetTime(ntp);

    // Use with DNS
    rc =  esp.gethostbyname("test.mosquitto.org", &MQTTBroker, NSAPI_IPv4,"esp");

    if (rc != 0)
    {
        printf("Get hostanme error %d\n", rc);

        esp.disconnect();

        reset_esp  = 0;

        ThisThread::sleep_for(2s);

        goto reconnect;
    }
    
    MQTTBroker.set_port(1883);

    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;

    data.MQTTVersion = 3;

    data.clientID.cstring = (char *)"mbed-sample";

    data.username.cstring = (char *)"user";

    data.password.cstring = (char *)"1234a!";

    if ((rc = socket.open(&esp)) != 0) 
    {
        printf("\nSocket Open error %d\n", rc);

    }

    if ((rc = socket.connect(MQTTBroker)) != 0) 
    {

        printf("\nBroker Connection error %d\n", rc);
    }

    if ((rc = client.connect(data)) != 0) 
    {

        printf("Client Connection error %d\n", rc);

        reset_esp  = 0;

        ThisThread::sleep_for(2s);

        goto reconnect;

    }


   if ((rc = client.subscribe("controller1/newValves", MQTT::QOS1,
                             messageArrived)) != 0) 
    {

        printf("rc from valves subscribe is %d\r\n", rc);

       
    }

    if ((rc = client.subscribe("controller1/start_times", MQTT::QOS1,
                             messageArrived)) != 0) 
    {

        printf("rc from start_times subscribe is %d\r\n", rc);

    }

    if ((rc = client.subscribe("controller1/days", MQTT::QOS1, messageArrived)) !=
      0) 
    {
        printf("rc from days subscribe is %d\r\n", rc);

    
    }

    if ((rc = client.subscribe("controller1/manual", MQTT::QOS1,
                             messageArrived)) != 0) 
    {
        printf("rc from manual subscribe is %d\r\n", rc);

   
    }


//   char buffer[500];
//   MQTT::Message msg;
//   msg.qos = MQTT::QOS1;
//   msg.retained = true;
//   msg.dup = false;
//
    while (1) 
    {

        rc = client.yield(500);

        if (rc < 0) 
        {

            printf("rc from yield is %d\r\n", rc);

            client.disconnect();

            esp.disconnect();

            socket.close();

            reset_esp  = 0;

            ThisThread::sleep_for(2s);

            goto reconnect;
        }

        //publish_data(buffer ,msg, client);

        // Sleep time must be less than TCP timeout
        // TODO: check if socket is usable before publishing
    }
}



