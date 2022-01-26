
#ifndef _GLOBALS_H_
#define _GLOBALS_H_


#include "mbed.h"


#define CONNECT_WIFI (1UL << 1)
#define SCAN_WIFI (1UL << 2)
#define SCAN_END (1UL << 3)


#define TOTAL_ZONES 40
#define TOTAL_PROGRAMS 4
#define TOTAL_STARTS 4
#define INTERVAL_TIME 1 //in minutes
#define MAXVALVES 5


//menu

#define MENU -1
#define PROGRAMS 0
#define AUTO 1
#define MANUAL 2
#define OPTIONS 3

#define SELECT_OPTION -1
#define FLOW 0
#define RAIN_SENSOR 1
#define WATER_BUDGET 2
#define NETWORK 3
#define STATISTICS 4
#define OFFLINE 5

#define SELECT_PROGRAM 0
#define STARTS 1
#define DAYS 2
#define DURATIONS 3



#define FLOW_SUB 0
#define AUTO_FLOW 1
#define MANUAL_FLOW 2
#define SUPPLY_FLOW 3

#define REFRESH_DISPLAY (1UL << 9)
#define MANUAL_REFRESH (1UL << 10)
#define LIVE_INFO_REFRESH (1UL << 11)


extern EventFlags event_flag;


//display
extern volatile int options_submenu ;
extern volatile int programs_submenu ;
extern volatile int menu;

extern  volatile int select_menu;
extern  volatile int select_submenu;


extern  bool refresh_display,refresh_elapsed_time,refresh_watering_valves, publish_valves, publish_starts, publish_days, publish_manual; 


extern  volatile int durations[TOTAL_ZONES][TOTAL_PROGRAMS]; // valvei = {x,duration,program} x is used to auto run 
extern  volatile int start_times[TOTAL_STARTS][2][TOTAL_PROGRAMS]; 
extern  volatile int week_days[7][TOTAL_PROGRAMS];
extern  volatile int rain[TOTAL_ZONES];
extern  volatile int flow[TOTAL_ZONES];
extern  volatile int manual_valves[TOTAL_ZONES]; //for manual control
extern  volatile int auto_valves[TOTAL_ZONES]; // schedule for auto run for each time interval

extern   int total_duration;
extern  volatile int duration_remain[TOTAL_ZONES];



extern  volatile int cycle; //each start time
extern  volatile int valve; 
extern  volatile int day; 
extern  volatile int program;
extern  volatile int is_watering;
extern  volatile int water_budget ;
extern  volatile int timezone;
extern  volatile float supply_flow;
extern  volatile int online;
extern  volatile int leak_detection;
extern  volatile int flow_read;

extern  bool back_pressed; 
extern  bool next_pressed; 
extern  bool program_refresh;
extern  bool rotary_pressed;
extern  bool rotary_rotated; 
extern  volatile int rotary_pressed_count; 
extern  volatile int warning;

struct schedule
{
    int time_shift;
    int duration;
};


extern struct schedule schedule[TOTAL_ZONES][TOTAL_PROGRAMS];

extern bool rain_refresh;

extern bool flow_refresh;

extern bool temp_refresh;

extern bool weather_refresh;


struct program_duration
{
    int total;
    int sec;
    int min;
   int hour;

};


extern struct program_duration water_duration;

extern int temperature;

extern int humidity;

extern char weather[20];




#endif