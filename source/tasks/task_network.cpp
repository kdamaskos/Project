
#include "include/task_network.h"

#include "config/pins_config.h"
#include "mbed.h"

#include "ESP8266Interface.h"
#include "globals.h"
#include "mbed.h"
#include <MQTTClientMbedOs.h>
#include <cstring>
#include <string>
#include <time.h>
#include <apps/include/network.h>
#include <apps/include/json_parser.h>



#include <apps/include/server.h>



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


bool is_connected;


char *ip_adress, *mac_adress;

int signal;

void internet() 
{

   server();

    ESP8266Interface esp(ESP_TX_PIN, ESP_RX_PIN);
    
    NTPClient ntp(&esp);

    //Store device IP
    SocketAddress deviceIP;
    //Store broker IP
    SocketAddress MQTTBroker;

    TCPSocket socket;

    MQTTClient client(&socket);

   // thread23.start(callback(weather_retrieve_task));

    printf("\nConnecting wifi..\n");

reconnect:

    power_esp = 1;

    reset_esp  = 1;

    int rc = esp.connect(ssid, psw, NSAPI_SECURITY_WPA_WPA2);
    //int rc = esp.connect("dimdamas", "damas61311", NSAPI_SECURITY_WPA_WPA2);
   // int rc = esp.connect("realme", "12345678", NSAPI_SECURITY_WPA_WPA2);

    if(rc != 0) 
    {
        printf("\nConnection error %d\n",rc);
        
        reset_esp  = 0;

        is_connected = false;

        ThisThread::sleep_for(2s);

        goto reconnect;

    } 
    else
    {
        esp.get_ip_address(&deviceIP);

        strcmp(ip_adress,deviceIP.get_ip_address());

        strcmp(mac_adress,esp.get_mac_address());

        signal = esp.get_rssi ();

        printf("Connected\n");

        is_connected = true;
    }

    ntpGetTime(ntp);

    // Use with DNS
    rc =  esp.gethostbyname("test.mosquitto.org", &MQTTBroker, NSAPI_IPv4,"esp");

    if (rc != 0)
    {
        is_connected = false;
        
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


    if ((rc = client.subscribe("controller1/valves", MQTT::QOS0,
                             messageArrived)) != 0) 
    {

        printf("rc from valves subscribe is %d\r\n", rc);

    }

    if ((rc = client.subscribe("controller1/days", MQTT::QOS0, messageArrived)) !=
      0) 
    {
        printf("rc from days subscribe is %d\r\n", rc);

    }

    if ((rc = client.subscribe("controller1/manual", MQTT::QOS0,
                             messageArrived)) != 0) 
    {
        printf("rc from manual subscribe is %d\r\n", rc);

    }


    if ((rc = client.subscribe("controller1/start_times", MQTT::QOS0,
                             messageArrived)) != 0) 
    {

        printf("rc from start_times subscribe is %d\r\n", rc);

    }

    if ((rc = client.subscribe("controller1/weather", MQTT::QOS0,
                             messageArrived)) != 0) 
    {

        printf("rc from weather subscribe is %d\r\n", rc);

    }
    if ((rc = client.subscribe("controller1/budget", MQTT::QOS0,
                             messageArrived)) != 0) 
    {

        printf("rc from budget subscribe is %d\r\n", rc);

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
            is_connected = false;

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



