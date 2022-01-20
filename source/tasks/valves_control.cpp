

#include "include/valves_control.h"
#include "buttons.h"
#include "globals.h"
#include "mbed.h"
#include "network.h"
#include "string"
#include "utilities/include/general.h"
#include <cstdio>





void valves_control() 
{

    time_t seconds;

    struct tm *t;

    int start_time, current_time, t1,t2, watering_program, time_shift = 0;

    is_watering = false;

    while(1)
    {
        
        switch (menu) {

            case AUTO:
            {   

                if ( !is_watering )
                {

                    seconds = time(NULL);

                    t = localtime(&seconds);
                
                    for (int j = 0; j< TOTAL_PROGRAMS; j++) 
                    {
                        for (int i = 0; i < TOTAL_STARTS; i++) 
                        {
                            if ( t->tm_hour == start_times[i][0][j]  &&  t->tm_min == start_times[i][1][j]  &&  week_days[t->tm_wday][j] ) 
                            {
                                watering_program = j;

                                refresh_watering_valves = true;

                                is_watering = true;

                                start_time = time(NULL);    

                                calculate_schedule(watering_program);                           

                                break;
                            }

                        }
                        if (is_watering)
                        {
                            break;
                        }
                    }
                }
                else 
                {
                    current_time = time(NULL);

                    event_flag.set(REFRESH_DISPLAY);

                    refresh_elapsed_time = true;
                    
                    if (current_time > water_duration.total*60* water_budget / 100 + start_time)
                    {
                        for (int i = 0; i < TOTAL_STARTS; i++)
                        {
                            auto_valves[i] = false;
                        }

                        time_shift = 0;

                        is_watering = false;

                        refresh_watering_valves = true;

                        event_flag.set(REFRESH_DISPLAY);
                    }
                    else if ( current_time > start_time + 60 * time_shift * INTERVAL_TIME * water_budget / 100 )
                    {
                        for (int i = 0; i < TOTAL_ZONES; i++)
                        {
                            t1 = start_time + schedule[i][watering_program].time_shift * INTERVAL_TIME *60 * water_budget / 100;

                            t2 = start_time + schedule[i][watering_program].time_shift * INTERVAL_TIME * 60 * water_budget / 100 + schedule[i][watering_program].duration * INTERVAL_TIME * 60 * water_budget / 100;
                            
                            if (  current_time > t1 && current_time < t2)
                            {
                                auto_valves[i] = true;

                            }
                            else
                            {
                                auto_valves[i] = false;
                            }

                            //printf("valve %d = %d\n", i,auto_valves[i] );

                        }

                        refresh_watering_valves = true;

                        time_shift ++;

                    }


                }

                ThisThread::sleep_for(1s);


                break;
            }

            case MANUAL:

                event_flag.wait_any(MANUAL_REFRESH);


                break;
            }
        
    }//while
}