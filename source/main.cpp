// Library to use https://github.com/ARMmbed/mbed-mqtt

#include "main.h"

#include "config/pins_config.h"

#include "tasks/include/display.h"


#include "globals.h"

#include "mbed.h"

#include "tasks/include/network.h"

#include "tasks/include/valves_control.h"

#include "tasks/include/buttons.h"



Thread thread1(osPriorityNormal, 10 * 1024);

Thread thread2(osPriorityNormal);

Thread thread3(osPriorityNormal);

Thread thread4(osPriorityNormal+1);



void init(){

     
    // initialize
    for (int i = 0; i < TOTAL_ZONES; i++) {
        rain[i] = 1;
        flow[i] = 5;
    }

    for (int j = 0; j < TOTAL_PROGRAMS; j++) {
        for (int i = 0; i < TOTAL_STARTS; i++) {
        start_times[i][1][j] = -1;
        }
    }


}




int main() 
{

    init();

    printf("hello\n");

    thread1.start(callback(internet));

    thread2.start(callback(display));

    thread3.start(callback(buttons));

    thread4.start(callback(valves_control));
  

    while (1) 
    {


    }
}


