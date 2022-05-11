

#include "globals.h"
#include "mbed.h"



struct sorted_valves 
{
    int index;
    int duration;
    bool check;

};



void calculate_schedule(int program ) 
{

    int temp;

    struct sorted_valves   srt_valves[TOTAL_ZONES];

    

    for (int i = 0; i < TOTAL_ZONES; ++i)
    {
        
        srt_valves[i].index = i;

        srt_valves[i].duration = durations[i][program];

        srt_valves[i].check = false;

        schedule[i][program].time_shift = -1;

        schedule[i][program].duration = 0;

    }


    for (int i = 0; i < TOTAL_ZONES; ++i)
    {

        for (int j = i + 1; j < TOTAL_ZONES; ++j) 
        { 

            if ( srt_valves[i].duration < srt_valves[j].duration )  
            {

                temp = srt_valves[i].index;

                srt_valves[i].index = srt_valves[j].index;

                srt_valves[j].index = temp;



                temp = srt_valves[i].duration;

                srt_valves[i].duration = srt_valves[j].duration;

                srt_valves[j].duration = temp;

            }
        }
    }

    int index, time_shift = 0, sum_flow = 0, valves_count = 0, j = 0;

    do
    {

        for ( int i = 0; i < TOTAL_ZONES; i++ )
        {

            if ( srt_valves[i].duration == 0 )
            {
                continue;
            }
            
            index = srt_valves[i].index;

            if (sum_flow <= (supply_flow + flow[index] ) &&  valves_count < MAXVALVES   &&   (schedule[index][program].time_shift == -1)  )
            {

                valves_count ++;

                sum_flow += flow[index];

                schedule[index][program].time_shift = j*INTERVAL_TIME;

                schedule[index][program].duration += INTERVAL_TIME;

                srt_valves[i].check = true;

            }
            else if (schedule[index][program].duration < srt_valves[i].duration  && srt_valves[i].check == true)
            {

                schedule[index][program].duration += INTERVAL_TIME;

            }
            else if ( schedule[index][program].duration == srt_valves[i].duration && srt_valves[i].check == true)
            {  

                valves_count --;

                sum_flow -= flow[index];

                srt_valves[i].check = false;

            }

        }

        j++;

    } while (valves_count != 0);

    
    time_t seconds;

    struct tm *t;
    seconds = time(NULL);

    t = localtime(&seconds);
    water_duration.total = (j-1)*INTERVAL_TIME * water_budget[t->tm_mon] / 100;

    water_duration.sec = 0;

    water_duration.min = water_duration.total % 60;

    water_duration.hour = water_duration.total / 60;


/*
    for (int i=0; i<TOTAL_ZONES; i++)
    {
        printf("valve %d : %d,%d\n",i,schedule[i][program].time_shift,schedule[i][program].duration);
    }
*/
}






bool calculate_next_water(int *next_water_hour,int *next_water_minute, int *next_water_day, int *next_water_program ) 
{
    
    int next_day;

    *next_water_hour = 24;

    *next_water_minute = 60;

    int next_water_minute_2 = 60;

    time_t seconds = time(NULL);

    struct tm *t = localtime(&seconds);

    for (int k = 0; k < 8; k++)
    {
        next_day = t->tm_wday + k;

        if ( next_day > 6 )
        {
            next_day = next_day - 7;
        }

        for (int i = 0; i < TOTAL_PROGRAMS; i++) 
        {
   
            for (int j = 0; j < TOTAL_STARTS; j++) 
            {
                if (start_times[j][1][i] != -1)
                {
                    // if water today
                    if ( week_days[next_day][i] && k == 0)
                    {
                        if( start_times[j][0][i] == t->tm_hour && start_times[j][1][i] < next_water_minute_2 && start_times[j][1][i] > t->tm_min  )
                        {
                            
                            next_water_minute_2 = start_times[j][1][i];
    
                            *next_water_hour = start_times[j][0][i];
    
                            *next_water_minute = start_times[j][1][i];
    
                            *next_water_day = t->tm_wday;
    
                            *next_water_program = i;
    
                        }
                        else if ( (start_times[j][0][i] < *next_water_hour &&  start_times[j][0][i] > t->tm_hour ) ||
                        ( start_times[j][0][i] == *next_water_hour &&  start_times[j][1][i] < *next_water_minute  &&  start_times[j][0][i] > t->tm_hour)  ) 
                        {     
                        
                            
                            *next_water_hour = start_times[j][0][i];
    
                            *next_water_minute = start_times[j][1][i];
    
                            *next_water_day = t->tm_wday;
    
                            *next_water_program = i;
                        
                        }
    
                    }// if water next day
                    else if( week_days[next_day][i] )
                    {
                                            
                        if ( (start_times[j][0][i] < *next_water_hour) || 
                        (start_times[j][0][i] == *next_water_hour && start_times[j][1][i] < *next_water_minute)) 
                        {      
                            
                            *next_water_hour = start_times[j][0][i];
    
                            *next_water_minute = start_times[j][1][i];
    
                            *next_water_day = next_day;
    
                            *next_water_program = i;
                        
                        }
    
                    }
                }

            }

        }
        
        if ( *next_water_hour != 24)
        {           
            return true;
        }

    }

    if ( *next_water_hour != 24)
    {
        return true;
    }
    else
    {
        return false;
    }

}
        


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


