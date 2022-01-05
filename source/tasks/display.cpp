
#include "display.h"

#include <utilities/include/graphics.h>

#include <utilities/include/general.h>

#include "mbed.h"

#include "string"

#include "buttons.h"

#include "sensors_task.h"

#include "globals.h"

#include "mbed.h"

#include "icons/wifi_icon.h"

#include "icons/water_drop.h"


Thread thread(osPriorityNormal-2);


void live_info_task()
{
    time_t seconds;

    struct tm *t;

    int prev_hour = 0, prev_min = 0;

    while(1)
    {
        
        ThisThread::sleep_for(3s);

        tft.Bitmap(40,10,20,16,(unsigned char *)image_data_wifi);

        tft.background( BACKGROUND_TOP);

        tft.foreground(BACKGROUND_BOT);

        tft.set_font((unsigned char *)Goudy_Old_Style21x19);

        tft.locate(60, 10);

        tft.printf("-30db");

        seconds = time(NULL);  

        t = localtime(&seconds); 

        if (prev_min != t->tm_min || prev_hour != t->tm_hour) 
        {
            prev_min = t->tm_min;  

            prev_hour = t->tm_hour;  
 
            update_date_time();   

        }

        ThisThread::sleep_for(100s);
    }
}



void display() 
{

    int previous_menu = -2, previous_programs_submenu, previous_options_submenu = SELECT_OPTION;

    init_graphics();
   
    Programs programs;

    Start starts;

    WeekDay weekdays;

    Duration duration;

    Table duration_table(230,75, 455,293, 8, 5);

    Table flow_table( 70, 65, 280, 290, 8, 5, Black);
    
    Table rain_table( 70, 65, 280, 290, 8, 5, Black);

    Table manualTable( 70, 65, 280, 290, 8, 5, Black);

    CustomRect2 submenu_icons(40, 70, 120,90, 20,  Green, White, 3,20);

    menu = MENU;

    //thread.start(callback(live_info_task));

    while (1) 
    {

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

                        break; 
                    }

                    case STARTS: 
                    {
                        if(previous_programs_submenu != programs_submenu)
                        {
                            previous_programs_submenu = STARTS;

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

                    tft.Bitmap(200,100,40,74,(unsigned char *)image_data_water_drop);

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

                    int shift = 0;

                    tft.locate(55+shift, 120);

                    tft.printf("          ");

                    // print valves which is watering
                    for (int i = 0; i < count; i++) 
                    {

                        tft.locate(70+ + shift, 120);

                        if ( waterring_valves[i] <0) 
                        {
                            tft.printf("*");
                        }
                        else
                        {
                            tft.printf("%d ", waterring_valves[i] + 1);
                        }

                        shift+=30;

                    }
                } 
                else
                {
                    tft.fillrect( 50, 60, 270,  190,  DarkGrey);

                }

                if (rain_refresh)
                {
                    if (is_raining) 
                    {

                            tft.set_font((unsigned char *)Goudy_Old_Style21x19);

                            tft.background( DarkCyan);

                            tft.foreground( Green);

                            tft.locate(2215,230);

                            tft.printf("ON");

                    } 
                    else 
                    {

                            tft.set_font((unsigned char *)Goudy_Old_Style21x19);

                            tft.background( DarkCyan);

                            tft.foreground( Red);

                            tft.locate(215,230);

                            tft.printf("OFF");

                    }

                    rain_refresh = false;

                }

                if (temp_refresh)
                {
                    
                    tft.set_font((unsigned char *)Goudy_Old_Style21x19);

                    tft.background( DarkCyan);

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

                    tft.background( DarkCyan);

                    tft.foreground( White);

                    tft.locate(135,335);
                    
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

                    rotary_rotated = true;

                    rotary_pressed = true;

                    manualTable.draw();
           
                    manualTable.populate((int *) manual_valves);

                    first_time_1 = false;

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

                            rotary_rotated = true;

                            rotary_pressed = true;

                            rain_table.draw();
                    
                            rain_table.populate((int *) rain);

                            first_time_1 = false;

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

                            tft.fillrect(100, 100, 300, 200,PROGRAM_COLOR);

                            first_time_1 = false;

                        }

                        tft.background( BACKGROUND_TOP);

                        tft.foreground(BACKGROUND_BOT);

                        tft.set_font((unsigned char *)Arial28x28);

                        tft.locate(150, 150);

                        tft.printf("%d %%",water_budget);

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


