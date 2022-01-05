
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

void serialize(int topic, char *buffer) {
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
void deserialize(char *ret) {

  int x, i, j, temp;

  //internet_mutex.lock();
  if (ret[2] == 'v') { // set up valves json
    ret = strchr(ret, '[');
    for (i = 0; i < TOTAL_ZONES; i++) {

      ret = ret + 1;
      temp = atoi(ret);
      ret = strchr(ret, ',');
      if (temp > -1) {

        durations[i][1] = temp;
        ret = ret + 1;
        temp = atoi(ret);

        if (temp > -1) {

          durations[i][2] = temp;
        }
      }
      ret = strchr(ret, ',');
      ret = ret + 1;
      temp = atoi(ret);
      if (temp > -1) {
        rain[i] = temp;
      }
    }
    publish_valves = true;
  } else if (ret[2] == 's') {

    for (i = 0; i < TOTAL_STARTS; i++) { // start times json
      ret = strchr(ret, '[');

      for (j = 0; j < TOTAL_PROGRAMS; j++) {
        ret = ret + 1;
        temp = atoi(ret);
        if (temp > -1) {
          start_times[i][0][j] = temp;
        }
        ret = strchr(ret, ',');
        ret = ret + 1;
        temp = atoi(ret);
        if (temp > -1) {
          start_times[i][1][j] = temp;
        }
        ret = strchr(ret, ',');
      }
    }
    ret = strchr(ret, 'w');
    ret = strchr(ret, '[');
    water_budget = atoi(ret + 1);
    publish_starts = true;
  } else if (ret[2] == 'd') { // days json

    for (i = 0; i < TOTAL_PROGRAMS; i++) {
      ret = strchr(ret, '[');
      for (j = 0; j < 7; j++) {
        ret = ret + 1;
        temp = atoi(ret);
        if (temp > -1) {
          week_days[j][i] = temp;
          ret = strchr(ret, ',');
        }
      }
    }
    publish_days = true;
  } else if (ret[2] == 'm') { // manual json

    ret = strchr(ret, '[');
    temp = atoi(ret + 1);

    if (temp) {
      for (i = 0; i < TOTAL_ZONES; i++) {
        ret = strchr(ret, ',');
        ret = ret + 1;
        manual_valves[i] = atoi(ret);
      }
      // menu = MANUAL;
    } else {
      // menu = AUTO;
    }
  }
 // internet_mutex.unlock();
}
