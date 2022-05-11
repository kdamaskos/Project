
#include "globals.h"

#include "mbed.h"
#include <cstring>
#include "apps/include/valves_control.h"


/*
**************functions for parsing and serializing json packets**************
*   json construction
*   topic valves       :  "v":[duri,progi,raini,duri+1,progi+1,raini+1,...]  i = No of valve 
*
*   topic days         :  "dp":[1,1,1,1,1,0,0]  p = programm 
*
*   topic start times  :  "si":[ha,ma,hb,mb,hc,mc,hd,md] "w":[waterBudget] i = No start time
*
*   topic manual :   "m":[1(manual or auto),m1,m2,...mn]  mi = 0 or 1
*
*/

void serialize(int topic, char *buffer) 
{
    int i, j;

    char temp[30];


    switch (topic) 
    {
        case 0:
            sprintf(buffer, "{\"v\":[");

            for (i = 0; i < TOTAL_ZONES; i++) 
            {
                sprintf(temp, "[%d,%d],",program,  durations[i][program]);
                strcat(buffer, temp);
            }

            buffer[strlen(buffer) - 1] = ']';
            strcat(buffer, "}");

            break;

        case 1:

            sprintf(buffer, "{");

            sprintf(temp, "\"s\":[");

            strcat(buffer, temp);

            for (j = 0; j < TOTAL_PROGRAMS; j++) 
            {

                for (i = 0; i < TOTAL_STARTS; i++) 
                {


                    if (start_times[i][1][j] == -1) 
                    {
                        sprintf(temp, "[\"%02d:00\",0],", start_times[i][0][j]);
                    }  
                    
                    sprintf(temp, "[\"%02d:%02d\", 1],", start_times[i][0][j], start_times[i][1][j]);
                    strcat(buffer, temp);

                }
            }
            buffer[strlen(buffer) - 1] = ']';
            strcat(buffer, "}");

            break;

        case 2:

            sprintf(buffer, "{");
            sprintf(temp, "\"d\":[");
            strcat(buffer, temp);
            for (i = 0; i < TOTAL_PROGRAMS; i++) 
            {
                strcat(buffer, "[");
                for (j = 0; j < 7; j++) 
                {
                    sprintf(temp, "%d,", week_days[j][i]);
                    strcat(buffer, temp);
                }
                    sprintf(temp, "%d", i);
                    strcat(buffer, temp);
                
                strcat(buffer, "],");

            }   
            buffer[strlen(buffer) - 1] = ']';
            strcat(buffer, "}");

            break;
 

        case 4:
        
            sprintf(buffer, "{");
            sprintf(temp, "\"w\":[");
            strcat(buffer, temp);
            for (i = 0; i < 12; i++) 
            {

  
                sprintf(temp, "[\"%d\",%d],",water_budget[i], i);
                strcat(buffer, temp);

            }   
            buffer[strlen(buffer) - 1] = ']';
            strcat(buffer, "}");



            break;
    }
}

// parsing json values in according variables
void deserialize(char *ret, int ln ) 
{

    int x, i, j, temp;

    int program;


    //internet_mutex.lock();
    if (ret[2] == 'v') 
    { // set up valves json

        ret = strchr(ret, '[');

        for (i = 0; i < TOTAL_ZONES; i++) 
        {

            ret = strchr(ret+1, '[');
            
            program = atoi(ret+1); 

            ret = strchr(ret, ',');

            durations[i][program] = atoi(ret+1);

            ret = strchr(ret+1, ',');

            rain[i] = atoi(ret+1);

        }

        refresh_rain_values = true;

    } 
    else if (ret[2] == 's') 
    {
        ret = strchr(ret, '[');

        for (j = 0; j < TOTAL_PROGRAMS; j++) 
        { // start times json
       
            for (i = 0; i < TOTAL_STARTS; i++) 
            {
                ret = strchr(ret, '"');

               if (  ret[1] == '"' )
               {
                    ret = ret +2;
                    continue;
               }

                start_times[i][0][j] = atoi(ret+1);
            
                ret = strchr(ret, ':');

                start_times[i][1][j] = atoi(ret+1);
                
                ret = strchr(ret, ',');

                if ( atoi(ret+1) == 0 ) 
                {
                    start_times[i][1][j] = -1;
                }

            }
        }

    } 
    else if (ret[2] == 'd') 
    { // days json

        ret = strchr(ret, '[') + 1;

        for (i = 0; i < TOTAL_PROGRAMS; i++) 
        {
            ret = strchr(ret, '[') + 1;

            for (j = 0; j < 7; j++) 
            {

                week_days[j][i] = atoi(ret);
             
                ret = strchr(ret, ',') + 1;
            }
        }
        
    } 
    else if (ret[2] == 'm') 
    { // manual json

        ret = strchr(ret, '[') + 1;

        for (i = 0; i < TOTAL_ZONES; i++) 
        {
            ret = strchr(ret, '[') + 2;
            manual_valves[i] = atoi(ret);

            
        }
        ret = strchr(ret, ',');
        ret = strchr(ret, '"');

        refresh_manual = true;
        is_watering = false;


        if (atoi(ret+1) == 1)
        {

            menu = MANUAL;

        }
        else 
        {

            menu = AUTO;
        }


        event_flag.set(MANUAL_REFRESH);

    }
    else if (ret[2] == 't') 
    {

        ret = strchr(ret, ':') + 1;

        temperature = atoi(ret) ;

        ret = strchr(ret+1, ':') + 1;

        humidity = atoi(ret);

        ret = strchr(ret+1, ':');

        ret = strchr(ret, '"')+1;

        int i =0;

        while(ret[i] != '"')
        {
            weather[i] = ret[i];

            i++;
        }

        weather[i] = NULL;

        weather_refresh = true;

    }
    else if (ret[2] == 'w') 
    {

        ret = strchr(ret, '[') + 3;

        for (i = 0; i < 12; i++) 
        {
            
            water_budget[i] = atoi(ret);

            ret = strchr(ret, '[') + 2;
        }

        location = ret;

        char *end = strstr(location,"\"");

        end[0] = NULL;

        weather_refresh = true;

    }
    else if (ret[2] == 'f') 
    {

        ret = strchr(ret, '[') + 1;

        supply_flow = atoi(ret);

        for (i = 0; i < TOTAL_ZONES; i++) 
        {
            ret = strchr(ret, ',') + 1;

            flow[i] = atoi(ret);

            
        }

        flow_values_refresh = true;

    }


 // internet_mutex.unlock();
}
