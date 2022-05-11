// Library to use https://github.com/ARMmbed/mbed-mqtt
#include "mbed.h"

#include "tasks/include/task_display.h"

#include "tasks/include/task_sensors.h"

#include "tasks/include/task_network.h"

#include "tasks/include/task_valves.h"

#include "tasks/include/task_buttons.h"

#include "apps/include/general.h"


Thread thread1(osPriorityNormal, 8 * 1024);

Thread thread2(osPriorityNormal);

Thread thread3(osPriorityNormal);

Thread thread4(osPriorityNormal );

Thread thread5(osPriorityNormal);


int main() 
{

    printf("Hello from Mbed OS %d.%d \n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION);

    init();

    thread1.start(callback(internet));

   // ThisThread::sleep_for(2s);

    thread2.start(callback(display));

    thread3.start(callback(buttons));

    thread4.start(callback(valves_control));

    thread5.start(callback(sensors_task));
  
    while (1) 
    {

        ThisThread::sleep_for(100s);

    }
}


