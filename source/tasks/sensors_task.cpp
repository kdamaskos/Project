#include "mbed.h"

#include "config/pins_config.h"

DigitalIn rain_sensor( RAIN_SENSOR_PIN );

InterruptIn flow_sensor( FLOW_SENSOR_PIN );



bool is_raining = false;

int pulse;

int live_flow;


void pulse_count()
{
    pulse ++;

}

Timer t;

void sensors_task()
{
    printf("hello\n");

    
    flow_sensor.rise(&pulse_count);

    while(1)
    {

        t.start();

        ThisThread::sleep_for(1s);

        t.stop();

        live_flow =pulse/6;

        //printf("%d\n", live_flow);


        ThisThread::sleep_for(1s);

        pulse = 0;

    
    }
}

