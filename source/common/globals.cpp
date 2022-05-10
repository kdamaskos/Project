#include "globals.h"
#include <cstdint>

//

 EventFlags event_flag;



volatile int menu;
volatile int options_submenu = SELECT_OPTION;
volatile int programs_submenu = SELECT_PROGRAM;
volatile int select_menu;
volatile int select_submenu;
 

 volatile bool wifi_connect = true;

volatile int wifi_setup_selection = WIFI_SSID;
volatile char string_char = 33;
volatile char char_pos = 0;

volatile int options_wifi_submenu_select = WIFI_SETUP;
volatile int options_wifi_submenu = WIFI_SUBMENU_SELECT;


bool refresh_elapsed_time,refresh_watering_valves,refresh_display, publish_valves, publish_starts, publish_days, publish_water_budget,publish_manual; 

  volatile int durations[TOTAL_ZONES][TOTAL_PROGRAMS]; // valvei = {x,duration,program} x is used to auto run 
  volatile int start_times[TOTAL_STARTS][2][TOTAL_PROGRAMS]; 
  volatile int week_days[7][TOTAL_PROGRAMS];
  volatile int rain[TOTAL_ZONES];
  volatile int flow[TOTAL_ZONES];
  volatile int manual_valves[TOTAL_ZONES]; //for manual control
  volatile int auto_valves[TOTAL_ZONES]; // schedule for auto run for each time interval

 
struct schedule schedule[TOTAL_ZONES][TOTAL_PROGRAMS];


int water_budget[] = {100,100,100,100,100,100,100,100,100,100,100,100};

int month;

char* location;

  volatile int cycle; //each start time
  volatile int valve; 
  volatile int day; 
  volatile int program;
  volatile bool is_watering=false;
bool refresh_rain_values;

  volatile int timezone;
  volatile float supply_flow = 50;
  volatile int online;
  volatile int leak_detection;
  volatile int flow_read;

char *ssid,*psw;

  bool back_pressed; 
  bool next_pressed; 
  bool program_refresh;
  bool rotary_pressed;
  bool rotary_rotated; 
  volatile int rotary_pressed_count; 
  volatile int warning;


bool flow_refresh;

bool temp_refresh;

bool weather_refresh;

struct program_duration water_duration;



int temperature;

int humidity;

char weather[20];