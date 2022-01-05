#include "globals.h"

//

 EventFlags event_flag;


volatile int menu;
volatile int options_submenu = SELECT_OPTION;
volatile int programs_submenu = SELECT_PROGRAM;
volatile int select_menu;
volatile int select_submenu;
 

volatile int refresh_hour;
volatile int refresh_internet;

bool refresh_display, publish_valves, publish_starts, publish_days, publish_manual; 

  volatile int durations[TOTAL_ZONES][TOTAL_PROGRAMS]; // valvei = {x,duration,program} x is used to auto run 
  volatile int start_times[TOTAL_STARTS][2][TOTAL_PROGRAMS]; 
  volatile int week_days[7][TOTAL_PROGRAMS];
  volatile int rain[TOTAL_ZONES];
  volatile int flow[TOTAL_ZONES];
  volatile int manual_valves[TOTAL_ZONES]; //for manual control
  volatile int auto_valves[TOTAL_ZONES]; // schedule for auto run for each time interval

 
struct schedule schedule[TOTAL_ZONES][TOTAL_PROGRAMS];

int program_duration[TOTAL_PROGRAMS];

  volatile int cycle; //each start time
  volatile int valve; 
  volatile int day; 
  volatile int program;
  volatile int is_watering;
  volatile int water_budget = 100;
  volatile int timezone;
  volatile float supply_flow = 50;
  volatile int online;
  volatile int leak_detection;
  volatile int flow_read;



  bool back_pressed; 
  bool next_pressed; 
  bool program_refresh;
  bool rotary_pressed;
  bool rotary_rotated; 
  volatile int rotary_pressed_count; 
  volatile int warning;


  bool rain_refresh;

bool flow_refresh;

bool temp_refresh;