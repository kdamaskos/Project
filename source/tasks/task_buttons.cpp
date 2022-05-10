
#include "include/task_buttons.h"

#include "pins_config.h"

#include "PinDetect.h"

#include "globals.h"

#include "string"
#include "apps/include/valves_control.h"

#define BACK (1UL << 0)
#define NEXT (1UL << 1)
#define ROTARY_PRESS (1UL << 2)
#define ROTATE_L (1UL << 3)
#define ROTATE_R (1UL << 4)


PinDetect BACK_B(PIN_BACK_B);

PinDetect NEXT_B(PIN_NEXT_B );

PinDetect ROTARY_B(PIN_ROTARY_B );

PinDetect ROTARY_R(PIN_ROTARY_L);

InterruptIn ROTARY_L(PIN_ROTARY_R);


bool first_time_1;

bool first_time_2;

bool clear_display;

void pressBack() 
{ 
    event_flag.set(BACK);
 }

void pressNext() 
{ 
    event_flag.set(NEXT); 
}

void pressRotary() 
{
    event_flag.set(ROTARY_PRESS);
}

void rightRotary() 
{ 
    event_flag.set(ROTATE_R);
}

void leftRotary() 
{
    event_flag.set(ROTATE_L);
}

void rcBrise_handler() //  Index pulse interrupt handler,
{

    if (ROTARY_R) 
    {

        leftRotary();

    } 
    else 
    {

        rightRotary();
    }

}


void init_buttons()
{

    BACK_B.mode(PullUp);

    NEXT_B.mode(PullUp);

    ROTARY_B.mode(PullUp);

    ROTARY_R.mode(PullDown);

    ROTARY_L.mode(PullDown);

    ROTARY_L.rise(&rcBrise_handler);

    BACK_B.attach_deasserted(&pressBack);

    NEXT_B.attach_deasserted(&pressNext);

    ROTARY_B.attach_deasserted(&pressRotary);

    BACK_B.setSampleFrequency();

    NEXT_B.setSampleFrequency();

    ROTARY_B.setSampleFrequency();

}



void buttons() 
{

    init_buttons();

    //disable irq

    while (1) {

        switch (event_flag.wait_any(BACK|NEXT|ROTARY_PRESS|ROTATE_R|ROTATE_L)) 
        {

            case BACK:

               switch (menu) 
               {
                    case MENU:
                        
                        break;

                    case PROGRAMS:

                        if (programs_submenu == SELECT_PROGRAM) 
                        {

                            menu = MENU;
                            
                            publish_valves = 1;
                            publish_starts = 1;
                            publish_days = 1;

                        } 
                        else 
                        {

                            programs_submenu --;
                        }

                        break;

                    case AUTO:

                        closeValves(); 

                        is_watering = false;

                        menu = MENU;

                        break;

                    case MANUAL:

                        closeValves(); 

                        menu = MENU;
                        
                        break;

                    case OPTIONS:

                        if (options_wifi_submenu != WIFI_SUBMENU_SELECT )
                        {

                            options_wifi_submenu = WIFI_SUBMENU_SELECT;

                            options_wifi_submenu_select = WIFI_SETUP;
                        }
                        else if(options_submenu == WATER_BUDGET)
                        {
                            options_submenu = SELECT_OPTION;
                            publish_water_budget = 1;
                        }
                        else if (options_submenu == SELECT_OPTION)
                        {
                            menu = MENU;
                        }
                        else 
                        {
                            options_submenu = SELECT_OPTION;

                        }


                        
                        break;

                } //switch menu

                back_pressed = true;

                break; 

            case NEXT:
                
               switch (menu) 
               {
                    case PROGRAMS:

                        if (programs_submenu < DURATIONS) 
                        {
                            programs_submenu ++;
                        }

                        break;

                    case AUTO:

                        break;

                    case MANUAL:

                        break;

                    case OPTIONS:

                        if(options_wifi_submenu == WIFI_SETUP && options_submenu == NETWORK)
                        {
                            wifi_setup_selection ++;

                            if(wifi_setup_selection > 4)
                            {
                                wifi_setup_selection  = 1;

                            }


                            char_pos = 0;
                            
                            
                        }
                        

                        break;

                } 

                next_pressed = true;

                break;

            case ROTARY_PRESS:

                switch (menu)
                {

                    case MENU:

                        switch (select_menu) 
                        {

                            case PROGRAMS:

                                menu = PROGRAMS;

                                programs_submenu = SELECT_PROGRAM;

                                break;

                            case AUTO:

                                menu = AUTO;

                                refresh_watering_valves = true;

                                break;

                            case MANUAL:

                                menu = MANUAL;

                                break;

                            case OPTIONS:

                                menu = OPTIONS;

                                options_submenu = SELECT_OPTION;

                                break;
                        }

                        break;

                    case PROGRAMS:

                        switch (programs_submenu) 
                        {

                            case STARTS:

                                rotary_pressed_count++;

                                if (rotary_pressed_count > 2) 
                                {

                                    rotary_pressed_count = 0;
                                }

                                refresh_display = true;

                                break;

                            case DAYS:

                                week_days[day][program] = !week_days[day][program];
                                
                                break;
                            
                            case DURATIONS:
                                
                                rotary_pressed_count++;

                                if (rotary_pressed_count > 1) 
                                {

                                    rotary_pressed_count = 0;
                                }

                                break;

                        } 
                        
                        break;

                    case MANUAL: 
                    {

                        rotary_pressed_count = 1;

                        int active_valves = 0;

                        for (int i = 0; i < TOTAL_ZONES; i++) 
                        {

                            if (manual_valves[i]) 
                            {

                                active_valves++;
                            }
                        }

                        if (active_valves == 5) 
                        {

                            if (manual_valves[valve]) 
                            {

                                manual_valves[valve] = 0;

                            } 
                            else 
                            {

                                warning = true;
                            }

                        } 
                        else if (active_valves < 5) 
                        {

                            manual_valves[valve] = !manual_valves[valve];
                            
                        }
                        event_flag.set(MANUAL_REFRESH);

                        break;

                    } 

                    case OPTIONS:
                        
                        switch(options_submenu)
                        {

                            case SELECT_OPTION:

                                switch (select_submenu) 
                                {

                                    case FLOW:

                                        options_submenu = FLOW;

                                        break;

                                    case RAIN_SENSOR:

                                        options_submenu = RAIN_SENSOR;

                                        break;

                                    case WATER_BUDGET:

                                        options_submenu = WATER_BUDGET;

                                        break;

                                    case NETWORK:

                                        options_submenu = NETWORK;

                                        break;

                                    case STATISTICS:

                                        options_submenu = STATISTICS;

                                        break;

                                    case OFFLINE:

                                        options_submenu = OFFLINE;

                                        break;                                
                                }  
                  
                                break;

                            case FLOW:


                                if (rotary_pressed_count == 0)
                                {
                                    rotary_pressed_count = 1;
                                }
                                else
                                {
                                    rotary_pressed_count = 0;
                                }

                                break;

                            case RAIN_SENSOR:

                                rain[valve] = !rain[valve];

                                break;

                            case WATER_BUDGET:

                                if (rotary_pressed_count == 0)
                                {
                                    rotary_pressed_count = 1;
                                }
                                else
                                {
                                    rotary_pressed_count = 0;
                                }


                                break;

                            case NETWORK:

                               switch (options_wifi_submenu) 
                                {
                                    case WIFI_SUBMENU_SELECT:
                                        
                                        if (options_wifi_submenu_select == WIFI_INFO) 
                                        {
                                            options_wifi_submenu = WIFI_INFO;
                                        }
                                        else if ( options_wifi_submenu_select == WIFI_SETUP ) 
                                        {
                                            options_wifi_submenu = WIFI_SETUP;
                                        }

                                        break;

                                    case WIFI_SETUP:

                                        if ( wifi_setup_selection == WIFI_CONNECT) 
                                        {
                                            wifi_connect = true;

                                        }
                                        else if( wifi_setup_selection == WIFI_DISCONNECT)
                                        {
                                            wifi_connect = false;

                                        }
                                        else if ( wifi_setup_selection == WIFI_SSID) 
                                        {
                                            if(ssid[char_pos] != NULL)
                                            {
                                                char_pos ++;
                                            }

                                            
                                        }
                                        else if(wifi_setup_selection == WIFI_PSW)
                                        {

                                            if(psw[char_pos] != NULL)
                                            {
                                                char_pos ++;
                                            }

                                        }
                                        

                                        break;

                                    case WIFI_INFO:

                                        break;

                                }
                              
                                break;

                            case STATISTICS:

                     

                                break;

                            case OFFLINE:

                      

                                break;                                

                        }
                    
                        break;// case OPTIONS
                }

                rotary_pressed = true;

                break; //case ROTARY PRESS

            case ROTATE_R:

                switch (menu) 
                {

                    case MENU:
                    
                        if (select_menu < 3)
                         {

                            select_menu ++;
                        }

                        break;

                    case PROGRAMS:

                        switch (programs_submenu) 
                        {

                            case SELECT_PROGRAM:

                                if (program <TOTAL_PROGRAMS-1) 
                                {

                                    program++;
                                }
                                

                                break;

                            case STARTS:

                                if (rotary_pressed_count == 0) 
                                {

                                    cycle++;

                                    if (cycle > 3) 
                                    {

                                        cycle = 3;
                                    }

                                } 
                                else if (rotary_pressed_count == 1)
                                {

                                    start_times[cycle][1][program] += 1;

                                    if (start_times[cycle][1][program] > 59) 
                                    {

                                        start_times[cycle][1][program] = 0;
                                    }

                                } 
                                else 
                                {

                                    start_times[cycle][0][program] += 1;

                                    if (start_times[cycle][0][program] > 23) 
                                    {

                                        start_times[cycle][0][program] = 0;
                                    }
                                }
                                refresh_display = true;

                                break;

                            case DAYS:

                                day++;

                                if (day > 6) 
                                {

                                    day = 6;
                                }

                                break;

                            case DURATIONS:

                                if (rotary_pressed_count == 0) 
                                {

                                    if (valve < TOTAL_ZONES -1 ) 
                                    {
                                        valve++;
                                    }

                                } 
                                else 
                                {

                                    if (durations[valve][program]<90)
                                    {
                                        durations[valve][program] += INTERVAL_TIME;
                                    }
                                    

                                }

                                break;

                        }//switch (submenu) 

                        break;

                    case MANUAL:

                        valve++;

                        if (valve == TOTAL_ZONES) 
                        {

                            valve = 0;

                        }

                        break;


                    case OPTIONS:

                        switch (options_submenu) 
                        {
                            case SELECT_OPTION:

                                if (select_submenu<5)
                                {
                                    select_submenu++; 
                                }

                                break;

                            case FLOW:


                                if (rotary_pressed_count == 0)
                                {
                                    if (valve < TOTAL_ZONES -1 ) 
                                    {
                                        valve++;
                                    }
                                }
                                else 
                                {
                                    if (flow[valve] < supply_flow)
                                    {
                                        flow[valve] ++;
                                    }
                                }
                            
                                break;

                            case RAIN_SENSOR:

                                if (valve < TOTAL_ZONES -1 ) 
                                {
                                    valve++;
                                }

                                break;

                            case WATER_BUDGET:

                                if (rotary_pressed_count == 1)
                                {
                                    if (water_budget[month] < 200)
                                    {
                                        water_budget[month] +=10;
                                    }
                                }
                                else 
                                {
                                    if (month < 11)
                                    {
                                        month++;
                                    }
                                }

                                break;
                            
                            case NETWORK:

                               switch (options_wifi_submenu) 
                                {
                                    case WIFI_SUBMENU_SELECT:
                                        
                                        options_wifi_submenu_select = WIFI_INFO;

                                        break;

                                    case WIFI_SETUP:

                                        if( wifi_setup_selection == WIFI_SSID)
                                        {
                                            
                                            if(ssid[char_pos] <32 || ssid[char_pos] > 126 && ssid[char_pos] != NULL)
                                            {
                                                ssid[char_pos] = 33;
                                            } 
                                            else if( ssid[char_pos] < 126)
                                            {
                                    
                                                ssid[char_pos] ++;
                                            }
                                        }
                                        else if( wifi_setup_selection == WIFI_PSW )
                                        {    

                                            if(psw[char_pos] <32 || psw[char_pos] > 126 && psw[char_pos] != NULL)
                                            {
                                                psw[char_pos] = 33;
                                            } 
                                            else if( psw[char_pos] < 126)
                                            {

                                                psw[char_pos] ++;
                                            }
                                            
                                        }

                                        break;

                                    case WIFI_INFO:

                                        break;

                                }
                              

                                break;
                            
                            case STATISTICS:


                                break;
                            
                            case OFFLINE:


                                break;
                            
                        }

                        break;

                }

                rotary_rotated = true;

                break; //case ROTARY R

            case ROTATE_L:

                switch (menu) 
                {
                    case MENU:

                        if (select_menu > 0) 
                        {

                            select_menu--;

                        }

                        break;

                    case PROGRAMS:

                        switch (programs_submenu) 
                        {

                            case SELECT_PROGRAM:
                                
                                
                                if (program > 0) 
                                {

                                    program--;
                                }
                                

                                break;

                            case STARTS:
                                
                                if (rotary_pressed_count == 0)
                                 {
                                    
                                    if (cycle > 0) 
                                    {

                                        cycle--;
                                    }

                                } 
                                else if (rotary_pressed_count == 1) 
                                {

                                    start_times[cycle][1][program] -= 1;

                                    if (start_times[cycle][1][program] < -1) 
                                    {

                                        start_times[cycle][1][program] = 59;
                                    }

                                } 
                                else 
                                {

                                    start_times[cycle][0][program] -= 1;

                                    if (start_times[cycle][0][program] < 0) 
                                    {

                                        start_times[cycle][0][program] = 23;
                                    }
                                }

                                refresh_display = true;

                                break;

                            case DAYS:

                                if (day > 0) 
                                {

                                    day--;
                                }

                                break;

                            case DURATIONS:

                                if (rotary_pressed_count == 0) 
                                {

                                    if (valve > 0) 
                                    {

                                        valve--;
                                    }

                                } 
                                else 
                                {

                                    if (durations[valve][program] > 0) 
                                    {

                                        durations[valve][program] -= INTERVAL_TIME;

                                    }
                                }

                                break;

                        }// switch (submenu) 

                        break;

                    case MANUAL:

                        valve--;

                        if (valve < 0) 
                        {

                            valve = TOTAL_ZONES - 1;

                        }

                        break;

                    case OPTIONS:

                        switch (options_submenu) 
                        {
                            case SELECT_OPTION:

                                if (select_submenu > 0)
                                {
                                    select_submenu--; 
                                }

                                break;

                            case FLOW:

                                if (rotary_pressed_count == 0)
                                {
                                    if (valve > 0 ) 
                                    {
                                        valve--;
                                    }
                                }
                                else 
                                {
                                    if (flow[valve] > 0)
                                    {
                                        flow[valve] --;
                                    }
                                }
                            
                                break;

                            case RAIN_SENSOR:

                                
                                if (valve > 0 ) 
                                {
                                    valve--;
                                }
                                

                                break;

                            case WATER_BUDGET:

                                if (rotary_pressed_count == 1)
                                {
                                    if (water_budget[month] > 5)
                                    {
                                        water_budget[month] -=5;
                                    }
                                }
                                else 
                                {
                                    if (month > 0)
                                    {
                                        month--;
                                    }
                                }

                                break;
                            
                            case NETWORK:

                                switch (options_wifi_submenu) 
                                {
                                    case WIFI_SUBMENU_SELECT:
                                        
                                        options_wifi_submenu_select = WIFI_SETUP;

                                        break;

                                    case WIFI_SETUP:

                                       if( wifi_setup_selection == WIFI_SSID)
                                        {

                                            if( (ssid[char_pos] <32 || ssid[char_pos] > 126 ) && ssid[char_pos] != NULL)
                                            {
                                                ssid[char_pos] = 33;
                                            } 
                                            else if( ssid[char_pos] > 32)
                                            {
                                    
                                                ssid[char_pos] --;
                                            }
                                            
                                            if ( ssid[char_pos] == 32)
                                            {
                                                ssid[char_pos] = NULL;
                                            }
                                          
                                        }else if( wifi_setup_selection == WIFI_PSW )
                                        {    

                                            if(psw[char_pos] <33 || psw[char_pos] > 126 && psw[char_pos] != NULL)
                                            {
                                                psw[char_pos] = 33;
                                            } 
                                            else if( psw[char_pos] > 33)
                                            {

                                                psw[char_pos] --;
                                            }

                                            if ( psw[char_pos] == 32)
                                            {
                                                psw[char_pos] = NULL;
                                            }
                                            
                                        }

                                        break;

                                    case WIFI_INFO:

                                        break;

                                }


                                break;
                            
                            case STATISTICS:


                                break;
                            
                            case OFFLINE:


                                break;
                            
                        }

                        break;

                }//switch (menu) {
                
                rotary_rotated = true;

                break;

        }//switch (action) {

        event_flag.set(REFRESH_DISPLAY);

        ThisThread::sleep_for(50ms);

    }//while(1)

}//void buttons



