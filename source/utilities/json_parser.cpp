
#include "globals.h"

#include "mbed.h"



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

    char temp[15];

    sprintf(buffer, "u");

    switch (topic) {
    case 0:
    strcat(buffer, "{\"v\":[");
    for (i = 0; i < TOTAL_ZONES; i++) {
      sprintf(temp, "%d,%d,%d,", durations[i][1], durations[i][2], rain[i]);
      strcat(buffer, temp);
    }

    buffer[strlen(buffer) - 1] = ']';
    strcat(buffer, "}");
    break;
  case 1:
    strcat(buffer, "{");
    for (i = 0; i < TOTAL_STARTS; i++) {
      sprintf(temp, "\"s%d\":[", i);
      strcat(buffer, temp);
      for (j = 0; j < TOTAL_PROGRAMS; j++) {
        sprintf(temp, "%d,%d,", start_times[i][0][j], start_times[i][1][j]);
        strcat(buffer, temp);
      }
      buffer[strlen(buffer) - 1] = ']';
      strcat(buffer, ",");
    }
    sprintf(temp, "\"w\":[%d]}", water_budget);
    strcat(buffer, temp);
    break;
  case 2:
    strcat(buffer, "{");
    for (i = 0; i < TOTAL_PROGRAMS; i++) {
      sprintf(temp, "\"d%d\":[", i);
      strcat(buffer, temp);
      for (j = 0; j < 7; j++) {
        sprintf(temp, "%d,", week_days[j][i]);
        strcat(buffer, temp);
      }
      buffer[strlen(buffer) - 1] = ']';
      strcat(buffer, ",");
    }
    buffer[strlen(buffer) - 1] = '}';

    break;
  case 3:
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

    } 
    else if (ret[2] == 's') 
    {
        ret = strchr(ret, '[');

        for (j = 0; j < TOTAL_PROGRAMS; j++) 
        { // start times json
       
            for (i = 0; i < TOTAL_STARTS; i++) 
            {
                ret = strchr(ret, '"');

                start_times[i][0][j] = atoi(ret+1);
            
                ret = strchr(ret, ':');

                start_times[i][1][j] = atoi(ret+1);
                
                ret = strchr(ret, ',');
            }
        }

        ret = strchr(ret, '"');

        water_budget = atoi(ret + 1);

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

        ret = strchr(ret, '[') + 3;

        for (i = 0; i < TOTAL_ZONES; i++) 
        {
            
            manual_valves[i] = atoi(ret);

            ret = strchr(ret, '[') + 2;
        }

        ret = strchr(ret, '"');

        if (ret[1])
        {
            menu = MANUAL;

        }
        else 
        {
            menu = AUTO;
        }

    }

    programs_submenu = SELECT_PROGRAM;
    
    event_flag.set(REFRESH_DISPLAY);

    

 // internet_mutex.unlock();
}
