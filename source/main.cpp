// Library to use https://github.com/ARMmbed/mbed-mqtt
#include "mbed.h"

#include "main.h"

#include "tasks/include/display.h"

#include "tasks/include/sensors_task.h"

#include "tasks/include/network.h"

#include "tasks/include/valves_control.h"

#include "tasks/include/buttons.h"

#include "utilities/include/general.h"


Thread thread1(osPriorityNormal, 10 * 1024);

Thread thread2(osPriorityNormal);

Thread thread3(osPriorityNormal);

Thread thread4(osPriorityNormal+15);

Thread thread5(osPriorityNormal+10);


int main() 
{

    init();

   // printf("hello\n");

    thread1.start(callback(internet));

    thread2.start(callback(display));

    thread3.start(callback(buttons));

    thread4.start(callback(valves_control));

    thread5.start(callback(sensors_task));
  

    while (1) 
    {

        ThisThread::sleep_for(10000s);

    }
}


