#include "task_sensors.h"

#include "mbed.h"

#include "config/pins_config.h"

#include "globals.h"

DigitalIn rain_sensor( RAIN_SENSOR_PIN );

InterruptIn flow_sensor( FLOW_SENSOR_PIN );


bool  rain_refresh;

int pulse;

int live_flow;

void pulse_count()
{
    pulse ++;

}


Timer t;

void sensors_task()
{
    flow_sensor.mode(PullDown);

    rain_sensor.mode(PullUp);

    flow_sensor.rise(&pulse_count);

    bool prev_rain;



    while(1)
    {

        t.start();

        ThisThread::sleep_for(1s);

        t.stop();

        live_flow =pulse/6;

        pulse = 0;

        if(prev_rain != rain_sensor)
        {
            prev_rain = rain_sensor;

            rain_refresh = true;

        }

        if(menu == AUTO)
        {
            event_flag.set(REFRESH_DISPLAY);
        }
        
    }
}

