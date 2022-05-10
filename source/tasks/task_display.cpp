
#include "task_display.h"

#include <apps/include/graphics.h>

#include <apps/include/general.h>

#include <task_network.h>

#include "mbed.h"

#include "string"

#include "task_buttons.h"

#include "task_sensors.h"

#include "globals.h"

#include "mbed.h"

#include "icons/wifi_icon.h"

#include "icons/water_drop.h"

bool refresh_date = true, refresh_wifi_icon = true ;

extern int live_flow;

extern bool rain_refresh;

extern bool is_raining;

extern char ip_address[], mac_address[];

extern int signal;

extern DigitalIn rain_sensor;

Thread thread(osPriorityNormal);

void live_info_task()
{
    time_t seconds;

    struct tm *t;

    int prev_hour = 0, prev_min = 0, prev_wifi= false;

    while(1)
    {
        
        seconds = time(NULL);  

        t = localtime(&seconds); 

        if (prev_min != t->tm_min || prev_hour != t->tm_hour) 
        {
            prev_min = t->tm_min;  

            prev_hour = t->tm_hour;  

            refresh_date = true;
 
            event_flag.set(REFRESH_DISPLAY);

        }

        if(prev_wifi != is_connected)
        {
            refresh_wifi_icon = true;

            prev_wifi = is_connected;

            event_flag.set(REFRESH_DISPLAY);

        }

        ThisThread::sleep_for(1s);

    }
}



void display() 
{

    int previous_menu = -2, previous_programs_submenu, previous_options_wifi_submenu , previous_options_submenu = SELECT_OPTION, next_water_hour, next_water_min,next_water_program,next_water_day;

    init_graphics();
   
    Programs programs;

    Start starts;

    WeekDay weekdays;

    Duration duration;

    Table duration_table(230,75, 455,291, 8, 5);

    Table flow_table( 100, 65, 350, 290, 8, 5);
    
    Table3 rain_table( 100, 65, 360, 290, 8, 5);

    Table3 manualTable( 70, 65, 320, 290, 8, 5);

    Table2 water_bdg (120,70, 360,290, 6,2) ;

    CustomRect2 submenu_icons(40, 70, 120,90, 20,  0x4AF1, White, 3,20);

    menu = MENU;

    thread.start(callback(live_info_task));

    while (1) 
    {
        if (refresh_date)
        {
            update_date_time();  

            refresh_date = false;
        }

        if (refresh_wifi_icon)
        {
            update_wifi_icon(is_connected);  

            refresh_wifi_icon = false;
        }
        
        switch (menu) 
        {
            
            case MENU: 
            {

                if (previous_menu != menu)
                {
                    previous_menu = MENU;

                    menu_graphics();
                }

                select(select_menu);

                event_flag.wait_any(REFRESH_DISPLAY);

                break;
            }
            case PROGRAMS:
            {
                if (previous_menu != menu)
                {
                    previous_menu = PROGRAMS;

                    program_graphics();

                    programs.print_all();

                    duration_table.draw();

                }
            
                switch (programs_submenu) 
                {

                    case SELECT_PROGRAM:
                    {
                        previous_programs_submenu = SELECT_PROGRAM;

                        programs.select(program);

                        starts.print_all(program);

                        weekdays.print_all( program);

                        duration.print_all(program);

                        event_flag.wait_any(REFRESH_DISPLAY); 
                        
                        if (previous_programs_submenu != programs_submenu)
                        {
                            programs.clear_select( program);
                        }

                        break; 
                    }

                    case STARTS: 
                    {
                        if(previous_programs_submenu != programs_submenu)
                        {
                            previous_programs_submenu = STARTS;

                            rotary_pressed_count = 0;

                            rotary_rotated = true;
                        }
                        
                        if (rotary_rotated && rotary_pressed_count == 0) 
                        {

                            starts.select(cycle, program);

                            rotary_rotated = false;
                        }

                        if (refresh_display) 
                        {

                            starts.print(cycle, program);

                            refresh_display = false;

                        } 

                        event_flag.wait_any(REFRESH_DISPLAY); 

                        if (previous_programs_submenu != programs_submenu)
                        {
                            starts.clear_select(cycle, program);
                        }

                        
                        break; 
                    } 
 
                    case DAYS:
                    {
                        if(previous_programs_submenu != programs_submenu)
                        {
                            previous_programs_submenu = DAYS;

                            rotary_rotated = true;
                        }
 
                        if (rotary_pressed) 
                        {

                            weekdays.print( day, program );

                            rotary_pressed = false;
                        }

                        if (rotary_rotated ) 
                        {
                            weekdays.select( day );

                            rotary_rotated = false;

                        }

                        event_flag.wait_any(REFRESH_DISPLAY); 

                        if (previous_programs_submenu != programs_submenu)
                        {
                            weekdays.clear_select(day);
                        }

                        break;   
                    }
                    
                    case DURATIONS:
                    {

                        if(previous_programs_submenu != programs_submenu)
                        {
                            previous_programs_submenu = DURATIONS;

                            rotary_pressed_count = 0;
                        }

                        if (rotary_pressed_count == 0) 
                        {

                            duration.select(valve, program);
        
                        } 
                        else 
                        {

                            duration.print(valve, program);

                        }

                        // calculateProgramDuration(program);
                        //tft.printf("%d  ", program_duration[program]);

                        event_flag.wait_any(REFRESH_DISPLAY); 
                       
                        if (previous_programs_submenu != programs_submenu)
                        {
                            duration.clear_select(valve, program);

                            calculate_schedule(program);
                        }
                        
                        break;
                    }   
                        
                }
                              
                break; // programs
            }
            case AUTO: 
            {

                if (previous_menu != menu)
                {
                    previous_menu = AUTO;

                    refresh_display = true;

                    rain_refresh = true;

                    flow_refresh = true;

                    temp_refresh = true;

                    weather_refresh = true;

                    auto_graphics();

                }

                if(refresh_watering_valves)
                {
                    refresh_watering_valves = false;
                    
                    if (is_watering  ) 
                    {

                        tft.fillrect( 50, 60, 270,  190,  WATER_COLOR); 

                        tft.foreground( White); 

                        tft.background( WATER_COLOR); 

                        tft.set_font((unsigned char *)Arial24x23);

                        tft.locate(75,75);

                        tft.printf("Watering");

                        int count = 0;

                        int waterring_valves[MAXVALVES];

                        for (int i = 0; i < MAXVALVES; i++) 
                        {

                            waterring_valves[i] = -1;

                        }

                        for (int i = 0; i < TOTAL_ZONES; i++) 
                        {

                            if (auto_valves[i]) 
                            {
                                waterring_valves[count] = i;

                                count++;  
                            }
    
                        }

                        tft.background( Blue); 

                        tft.set_font((unsigned char *)Goudy_Old_Style21x19);

                        tft.locate(70, 110);

                        tft.printf("           ");

                        tft.locate(70, 110);

                        // print valves which is watering
                        for (int i = 0; i < count; i++) 
                        {

                            tft.printf("%d ", waterring_valves[i] + 1);

                        }

                    } 
                    else
                    {

                        tft.fillrect( 50, 60, 270,  190,  AUTO_C1);

                        tft.set_font((unsigned char *)Arial24x23);

                        int ret = calculate_next_water(&next_water_hour, &next_water_min, &next_water_day, &next_water_program );

                        tft.background( AUTO_C1);

                        tft.foreground( White);

                        tft.locate(65,70);

                        tft.printf("Next Watering");

                        if (ret) 
                        {

                            tft.set_font((unsigned char *)Arial24x23);

                            tft.locate(130,95);

                            tft.printf("%s",WEEK_DAY[next_water_day]);

                            tft.locate(115,120);

                            tft.set_font((unsigned char *)Arial28x28);

                            tft.printf("%02d:%02d",next_water_hour,next_water_min);

                            tft.locate(100,155);

                            tft.set_font((unsigned char *)Goudy_Old_Style21x19);

                            tft.printf("Program %s",PROGRAM[next_water_program]);

                        }
                        else
                        {

                            tft.fillrect( 50, 60, 270,  190,  AUTO_C1);

                            tft.set_font((unsigned char *)Goudy_Old_Style21x19);

                            tft.locate(130,110);

                            tft.printf("None");
                        }

                    }
                }
                

                if(refresh_elapsed_time &&  is_watering)
                {

                    if( water_duration.min <0 && water_duration.hour >0)
                    {
                        water_duration.hour--;
                        water_duration.min = 59;

                    }
                    if( water_duration.sec <0 && water_duration.min >0)
                    {
                        water_duration.min--;
                        water_duration.sec = 59;
                    }

                    tft.set_font((unsigned char *)Arial24x23);

                    tft.background( 0x428A);

                    tft.foreground( White);
               
                    tft.locate(80,145);

                    tft.printf("%02d:%02d:%02d",water_duration.hour,water_duration.min,water_duration.sec);

                    water_duration.sec--;

                    refresh_elapsed_time = false;

                }

                if (rain_refresh)
                {
                    if (!rain_sensor) 
                    {

                        tft.set_font((unsigned char *)Goudy_Old_Style21x19);

                        tft.background( AUTO_C2b);

                        tft.foreground( Green);

                        tft.locate(195,230);

                        tft.printf("ON ");

                    } 
                    else 
                    {

                        tft.set_font((unsigned char *)Goudy_Old_Style21x19);

                        tft.background( AUTO_C2b);

                        tft.foreground( Red);

                        tft.locate(195,230);

                        tft.printf("OFF");

                    }

                    rain_refresh = false;

                }

                if(flow_refresh)
                {
                    tft.set_font((unsigned char *)Goudy_Old_Style21x19);

                    tft.background( AUTO_C2a);

                    tft.foreground( White);

                    tft.locate(70,230);
                    
                    tft.printf("%d L/m",live_flow);

                    flow_refresh = false;

                }

                if (weather_refresh)
                {
                    tft.set_font((unsigned char *)Goudy_Old_Style21x19);

                    tft.background( AUTO_C3);

                    tft.foreground( White);

                    tft.locate(285,100);

                    tft.printf("           ");

                    tft.locate(285,100);

                    tft.printf("Zurich");

                    tft.locate(300,130);

                    tft.set_font((unsigned char *)Arial24x23);

                    tft.printf("%s",weather);

                    tft.set_font((unsigned char *)Arial12x12);

                    tft.locate(290,180);

                    tft.printf("Tempr");

                    tft.locate(290,220);

                    tft.printf("Humid");

                    tft.set_font((unsigned char *)Arial24x23);

                    tft.locate(340,180);

                    tft.printf("%d C",temperature);

                    tft.locate(340,220);

                    tft.printf("%d %%",humidity);
 
                    weather_refresh = false;

                }
   
                event_flag.wait_any(REFRESH_DISPLAY);

                break;
            } // AUTO

            case MANUAL:
            {
                
                if (previous_menu != menu)
                {
                    previous_menu = MANUAL;

                    manual_graphics();

                    rotary_rotated = true;

                    rotary_pressed = true;

                    manualTable.draw();
           
                    manualTable.populate((int *) manual_valves);


                }

                if (rotary_rotated)
                {

                    manualTable.select(valve,(int *) manual_valves);

                    rotary_rotated = false;
                }

                if ( rotary_pressed) 
                {

                    if (warning) 
                    {
                        tft.foreground(Red);

                        tft.background(White);

                        tft.set_font((unsigned char *)Arial28x28);

                        tft.locate(340, 150);

                        tft.printf("Max %d",MAXVALVES);

                        warning = 0;
                    }
                    else 
                    {

                        tft.background(White);

                        tft.set_font((unsigned char *)Arial28x28);

                        tft.locate(340, 150);

                        tft.printf("      ");


                    }

                    manualTable.print(valve,(int *) manual_valves);
  
                    rotary_pressed = false;

                }

                event_flag.wait_any(REFRESH_DISPLAY);
                

                break; //MANUAL
            }

            case OPTIONS:
            {
                
                switch (options_submenu) 
                {

                    case SELECT_OPTION:
                    {
                        
                        if(previous_options_submenu != options_submenu || previous_menu != OPTIONS )
                        {
                            previous_menu = OPTIONS;

                            previous_options_submenu = SELECT_OPTION;

                            submenu_icons.draw();

                            submenu_icons.set_label(0,(char *) "Flow");
                            submenu_icons.set_label(1, (char *)"Rain Sns");
                            submenu_icons.set_label(2, (char *)"Water %");
                            submenu_icons.set_label(3, (char *)"Wifi");
                            submenu_icons.set_label(4, (char *)"Statistics");
                            submenu_icons.set_label(5,(char *) "Offline");

                        }

                        submenu_icons.select(select_submenu);

                        event_flag.wait_any(REFRESH_DISPLAY);

                        break;
                    }

                    case FLOW:
                    {
                        
                        if(previous_options_submenu != options_submenu)
                        {

                            previous_options_submenu = FLOW;

                            flow_graphics();

                            rotary_rotated = true;

                            rotary_pressed = true;

                            flow_table.draw();
                    
                            flow_table.populate((int *) flow);

                        }
  
                        if (rotary_rotated)
                        {

                           flow_table.select(valve,(int *) flow);

                            rotary_rotated = false;
                        }

                        if ( rotary_pressed) 
                        {

                            flow_table.print(valve,(int *) flow);
  
                            rotary_pressed = false;

                        }

                        event_flag.wait_any(REFRESH_DISPLAY);

                        break;
                    }

                    case RAIN_SENSOR:
                    {

                        if (previous_options_submenu != options_submenu) 
                        {

                            previous_options_submenu = RAIN_SENSOR;

                            rain_graphics();

                            rotary_rotated = true;

                            rotary_pressed = true;

                            rain_table.draw();
                    
                            rain_table.populate((int *) rain);

                        }

                        if(refresh_rain_values)
                        {

                            refresh_rain_values = false;
                            rain_table.populate((int *) rain);
                        }

                        if (rotary_rotated)
                        {

                           rain_table.select(valve,(int *) rain);

                            rotary_rotated = false;
                        }

                        if ( rotary_pressed) 
                        {

                            rain_table.print(valve,(int *) rain);
  
                            rotary_pressed = false;

                        }

                        event_flag.wait_any(REFRESH_DISPLAY);

                        break;
                    }

                    case WATER_BUDGET:{

                        if(previous_options_submenu != options_submenu)
                        {
                            water_budget_graphics();

                            water_bdg.draw();

                            water_bdg.populate(water_budget);

                            previous_options_submenu = WATER_BUDGET;

                        }

                        if (rotary_rotated)
                        {

                           water_bdg.select(month,(int *) water_budget);

                            rotary_rotated = false;
                        }

                        if ( rotary_pressed) 
                        {

                            water_bdg.print(month,(int *) water_budget);
  
                            rotary_pressed = false;

                        }

                        event_flag.wait_any(REFRESH_DISPLAY);

                        break;
                    }
                    case NETWORK:

                        if(previous_options_submenu != options_submenu)
                        {
                        
                            previous_options_submenu = NETWORK;

                        }

                        switch (options_wifi_submenu) 
                        {
                            case WIFI_SUBMENU_SELECT:


                                if(previous_options_wifi_submenu != options_wifi_submenu)
                                {
                                    
                                    tft.fillrect(28 , 50, 455, 291, BACKGROUND_MAIN);
                                
                                    previous_options_wifi_submenu = WIFI_SUBMENU_SELECT;

                                }
                                
                                if( options_wifi_submenu_select == WIFI_SETUP )
                                {

                                    tft.set_font((unsigned char *)Arial28x28);

                                    tft.background( Black);

                                    tft.foreground( White);

                                    tft.locate(150, 100);

                                    tft.printf("WIFI SETUP");

                                    tft.background( White);

                                    tft.foreground(Black);

                                    tft.locate(120, 210);

                                    tft.printf("NETWORK INFO");

                                }
                                else if( options_wifi_submenu_select == WIFI_INFO )
                                {

                                    tft.set_font((unsigned char *)Arial28x28);

                                    tft.background( White);

                                    tft.foreground( Black);

                                    tft.locate(150, 100);

                                    tft.printf("WIFI SETUP");

                                    tft.background( Black);

                                    tft.foreground(White);

                                    tft.locate(120, 210);

                                    tft.printf("NETWORK INFO");
                                
                                }
      
                                break;

                            case WIFI_SETUP:

                                if(previous_options_wifi_submenu != options_wifi_submenu)
                                {
                                
                                    previous_options_wifi_submenu = WIFI_SETUP;

                                    tft.fillrect(28 , 50, 455, 291, BACKGROUND_MAIN);

                                    tft.set_font((unsigned char *)Arial24x23);

                                    tft.background( White);
    
                                    tft.foreground(Black);

                                    tft.locate(55, 80);

                                    tft.printf("Ssid: ");

                                    tft.locate(150, 80);

                                    tft.printf("%s",ssid);

                                    tft.locate(55, 140);

                                    tft.printf("Psw: ");

                                    tft.locate(150, 140);

                                    tft.printf("%s",psw);

                                    tft.locate(55, 200);

                                    tft.printf("Connect");

                                    tft.locate(55, 240);

                                    tft.printf("Disconnect");

                                }

                                tft.background( White);
    
                                tft.foreground(Black);
    
                                tft.set_font((unsigned char *)Arial24x23);

                                if ( wifi_setup_selection == WIFI_SSID )
                                {
                                    

                                    tft.locate(30, 140);

                                    tft.printf(" ");

                                    tft.locate(30, 200);

                                    tft.printf(" ");

                                    tft.locate(30, 240);

                                    tft.printf(" ");

                                    tft.locate(30, 80);

                                    tft.printf(">");


                                    tft.locate(150, 80);


                                    tft.printf("                  ");

                                    tft.locate(150, 80);

                                    tft.printf("%s",ssid);

                                }
                                else if ( wifi_setup_selection == WIFI_PSW )
                                {
                                    
                                    tft.locate(30, 80);

                                    tft.printf(" ");

                                    tft.locate(30, 200);

                                    tft.printf(" ");

                                    tft.locate(30, 240);

                                    tft.printf(" ");


                                    tft.locate(30, 140);

                                    tft.printf(">");

                                    tft.locate(150, 140);

                                    tft.printf("                  ");

                                    tft.locate(150, 140);

                                    tft.printf("%s",psw);
                                }
                                else if ( wifi_setup_selection == WIFI_CONNECT)
                                {

                                    tft.locate(30, 80);

                                    tft.printf(" ");

                                    tft.locate(30, 140);

                                    tft.printf(" ");

                                    tft.locate(30, 240);

                                    tft.printf(" ");

                                    tft.locate(30, 200);

                                    tft.printf(">");

                                    
                                }
                                else if ( wifi_setup_selection == WIFI_DISCONNECT)
                                {

                                    tft.locate(30, 80);

                                    tft.printf(" ");

                                    tft.locate(30, 140);

                                    tft.printf(" ");

                                    tft.locate(30, 200);

                                    tft.printf(" ");

                                    tft.locate(30, 240);

                                    tft.printf(">");
 
                                }
                            
                                break;

                            case WIFI_INFO:
                    

                                if(previous_options_wifi_submenu != options_wifi_submenu)
                                {
                                    tft.fillrect(28 , 50, 455, 291, BACKGROUND_MAIN);
                                
                                    previous_options_wifi_submenu = WIFI_INFO;

                                    wifi_info_graphics();

                                }

                                

                                if (is_connected)
                                {
                                    tft.locate(200, 90);

                                    tft.foreground(Green);

                                    tft.printf("Connected");

                                    tft.locate(200, 130);

                                    tft.printf("%.10s",ssid);
                                    printf("%s",ssid);

                                    tft.locate(200, 170);

                                    tft.printf("%s",ip_address);
                                    printf(" ip =%s",ip_address);

                                    tft.locate(200, 210);

                                    tft.printf("%s",mac_address);
                                    printf("mac = %s",mac_address);

                                    tft.locate(200, 250);

                                    tft.printf("%d db",signal);
                                }
                                else 
                                {
                                    tft.locate(200, 90);

                                    tft.foreground(Red);

                                    tft.printf("Not connected");

                                    tft.locate(200, 130);

                                    tft.printf("-");

                                    tft.locate(200, 170);

                                    tft.printf("-");

                                    tft.locate(200, 210);

                                    tft.printf("-");

                                    tft.locate(200, 250);

                                    tft.printf("-");
                                }

                        }

                        event_flag.wait_any(REFRESH_DISPLAY);

                        break;

                    case STATISTICS:

                        if(previous_options_submenu != options_submenu)
                        {

                            previous_options_submenu = STATISTICS;


                        }

                        tft.background( White);
    
                        tft.foreground(Black);
    
                        tft.set_font((unsigned char *)Arial24x23);

                        tft.locate(160, 230);

                        tft.printf("Under Construction...");

                        event_flag.wait_any(REFRESH_DISPLAY);

                        break;

                    case OFFLINE:

  
                        if(previous_options_submenu != options_submenu)
                        {

                            previous_options_submenu = OFFLINE;


                        }
                        tft.background( White);
    
                        tft.foreground(Black);
    
                        tft.set_font((unsigned char *)Arial24x23);

                        tft.locate(160, 230);

                        tft.printf("Under Construction...");


                        event_flag.wait_any(REFRESH_DISPLAY);

                        break;                                

                }  

                break;
            }

        }// menu

        if (previous_menu != menu || previous_options_submenu != options_submenu   )
        {
            
            tft.fillrect(28 , 50, 455, 291, BACKGROUND_MAIN);

        }

        
    
    }// while(1)
} // display 


