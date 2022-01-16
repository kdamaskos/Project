
#include "display.h"

#include <utilities/include/graphics.h>

#include <utilities/include/general.h>

#include <network.h>

#include "mbed.h"

#include "string"

#include "buttons.h"

#include "sensors_task.h"

#include "globals.h"

#include "mbed.h"

#include "icons/wifi_icon.h"

#include "icons/water_drop.h"

bool refresh_date = true, refresh_wifi_icon = true ;


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

    int previous_menu = -2, previous_programs_submenu, previous_options_submenu = SELECT_OPTION, next_water_hour, next_water_min,next_water_program,next_water_day;

    init_graphics();
   
    Programs programs;

    Start starts;

    WeekDay weekdays;

    Duration duration;

    Table duration_table(230,75, 455,291, 8, 5);

    Table flow_table( 70, 65, 280, 290, 8, 5);
    
    Table rain_table( 70, 65, 280, 290, 8, 5);

    Table manualTable( 70, 65, 280, 290, 8, 5);

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
           
                    auto_graphics();

                }
                
                if (is_watering) 
                {
                        
                    tft.fillrect( 50, 60, 270,  190,  Blue); 
                    
                    tft.foreground( White); 

                    tft.background( Blue); 

                    tft.set_font((unsigned char *)Arial24x23);

                    tft.locate(80,80);

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

                    tft.locate(55, 120);

                    tft.printf("          ");

                    tft.locate(70, 120);

                    // print valves which is watering
                    for (int i = 0; i < count; i++) 
                    {

                        tft.printf("%d ", waterring_valves[i] + 1);
                        
                    }

                } 
                else
                {

                    tft.fillrect( 50, 60, 270,  190,  AUTO_C1);

                    int ret = calculate_next_water(&next_water_hour, &next_water_min, &next_water_day, &next_water_program );

                    tft.background( AUTO_C3);

                    tft.foreground( White);

                    if (ret) 
                    {
                        tft.set_font((unsigned char *)Arial24x23);

                        tft.locate(330,95);

                        tft.printf("%s",WEEK_DAY[next_water_day]);

                        tft.locate(315,120);

                        tft.set_font((unsigned char *)Arial28x28);

                        tft.printf("%02d:%02d",next_water_hour,next_water_min);

                        tft.locate(300,155);

                        tft.set_font((unsigned char *)Goudy_Old_Style21x19);

                        tft.printf("Program %s",PROGRAM[next_water_program]);

                    }
                    else
                    {

                        tft.fillrect( 277, 90, 430, 190,  AUTO_C3);

                        tft.set_font((unsigned char *)Goudy_Old_Style21x19);

                        tft.locate(330,110);

                        tft.printf("None");
                    }

                }

                if (rain_refresh)
                {
                    if (is_raining) 
                    {

                            tft.set_font((unsigned char *)Goudy_Old_Style21x19);

                            tft.background( AUTO_C2);

                            tft.foreground( Green);

                            tft.locate(2215,230);

                            tft.printf("ON");

                    } 
                    else 
                    {

                            tft.set_font((unsigned char *)Goudy_Old_Style21x19);

                            tft.background( AUTO_C2);

                            tft.foreground( Red);

                            tft.locate(215,230);

                            tft.printf("OFF");

                    }

                    rain_refresh = false;

                }

                if (temp_refresh)
                {
                    
                    tft.set_font((unsigned char *)Goudy_Old_Style21x19);

                    tft.background( AUTO_C4);

                    tft.foreground( White);

                    tft.locate(355,210);

                    tft.printf("18 C");

                    tft.circle(410, 210,3, White);

                    tft.locate(355,235);
                    
                    tft.printf("85 %%");

                    temp_refresh = false;


                }

                if(flow_refresh)
                {
                    tft.set_font((unsigned char *)Goudy_Old_Style21x19);

                    tft.background( AUTO_C2);

                    tft.foreground( White);

                    tft.locate(130,230);
                    
                    tft.printf("25 L/m");

                    flow_refresh = false;

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
                        tft.set_font((unsigned char *)Arial16x16);

                        tft.locate(290, 150);
                        tft.printf("Max Active Valves");

                        tft.set_font((unsigned char *)Arial28x28);
                        tft.locate(360, 180);
                        tft.printf("%d", MAXVALVES);

                        warning = 0;
                    }
                    else 
                    {
                        tft.foreground(Red);
                        tft.background(White);
                        tft.set_font((unsigned char *)Arial16x16);

                        tft.locate(290, 150);
                        tft.printf("               ");

                        tft.set_font((unsigned char *)Arial28x28);
                        tft.locate(360, 180);
                        tft.printf("   ");


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

                    case WATER_BUDGET:

                        if(previous_options_submenu != options_submenu)
                        {

                            previous_options_submenu = WATER_BUDGET;

                            water_budget_graphics();

                        }

                        tft.background( PROGRAM_COLOR);

                        tft.foreground(Black);

                        tft.set_font((unsigned char *)Arial28x28);

                        tft.locate(200, 150);

                        tft.printf("%d  ",water_budget);

                        tft.locate(250, 150);

                        tft.printf("%%");

                        event_flag.wait_any(REFRESH_DISPLAY);

                        break;

                    case NETWORK:

                        if(previous_options_submenu != options_submenu)
                        {

                            previous_options_submenu = NETWORK;


                        }
                            
                        event_flag.wait_any(REFRESH_DISPLAY);
  
                        break;

                    case STATISTICS:

                        if(previous_options_submenu != options_submenu)
                        {

                            previous_options_submenu = STATISTICS;


                        }

                        event_flag.wait_any(REFRESH_DISPLAY);

                        break;

                    case OFFLINE:

  
                        if(previous_options_submenu != options_submenu)
                        {

                            previous_options_submenu = OFFLINE;


                        }

                        event_flag.wait_any(REFRESH_DISPLAY);

                        break;                                

                }  

                break;
            }

        }// menu

        if (previous_menu != menu || previous_options_submenu != options_submenu )
        {
            
            tft.fillrect(30 , 50, 455, 291, BACKGROUND_MAIN);

        }
    
    }// while(1)
} // display 


