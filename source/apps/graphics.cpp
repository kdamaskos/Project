
#include "graphics.h"

#include "icons/menu_icon.h"

#include "icons/template.h"

#include "icons/company.h"

#include "icons/wifi_icon.h"

#include "icons/temp_icon.h"

#include "icons/water_drop.h"

#include "icons/humid_icon.h"

#include <cstring>

#include "include/task_display.h"

#include "config/pins_config.h"


const char *WEEK_DAY[] = {"Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat"};

const char *PROGRAM[] = {"A", "B", "C", "D"};

const char *MONTHS[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};



ILI9486 tft(PAR_8, PortC, PIN_CS, PIN_RST, PIN_DC, PIN_WR, PIN_RD,
            "myLCD"); /// isplayproto, port, CS, reset, DC, WR, RD, LCDSIZE_X,
                      /// LCDSIZE_Y, name




void select( int selection)
{
    int x=90, y=85, dx=100,dy=120;

    static int prev = 0;

    short color = Black,  background = White;

 

         
    for(int j=15; j>0;j--)
    {

        tft.line(x + prev * dx - j , y - j ,   x + prev * dx + j, y - j , background);

        tft.line(x + prev * dx - j, y + j + dy, x + prev * dx + j, y + j + dy, background);
         
    }

    prev = selection;
             
    for(int j=15; j>0;j--)
    {

        tft.line(x + selection * dx - j , y - j  ,   x + selection * dx + j, y - j , color);

        tft.line(x + selection * dx - j, y + j + dy, x + selection * dx + j, y + j + dy, color);
         
    }

 

}



void update_wifi_icon(bool is_connected)
{

    tft.background( BACKGROUND_TOP);
    
    tft.foreground(BACKGROUND_BOT);
    
    tft.set_font((unsigned char *)Goudy_Old_Style21x19);
    
    tft.locate(60, 10);

    if (is_connected)
    {

        tft.printf("%s", ssid);

        tft.Bitmap(40,10,20,16,(unsigned char *)image_data_wifi);

    }
    else
    {
        tft.background( BACKGROUND_TOP);
    
        tft.foreground(Red);

        tft.printf("            ");

        tft.Bitmap(40,10,20,16,(unsigned char *)image_data_wifi_not);


    }

}


void update_date_time() 
{
    
    time_t seconds = time(NULL);

    struct tm *t = localtime(&seconds);

    tft.background( BACKGROUND_TOP);

    tft.foreground(BACKGROUND_BOT);

    tft.set_font((unsigned char *)Goudy_Old_Style21x19);

    tft.locate(305, 10);

    tft.printf("%d %s %02d:%02d",t->tm_mday, WEEK_DAY[t->tm_wday], t->tm_hour, t->tm_min);

}


void init_graphics()
{

    tft.set_orientation(1);

    tft.set_auto_up(1);

    tft.fillrect (0, 0, 480, 75,BACKGROUND_TOP );

    tft.fillrect(0, 75, 480, 320,BACKGROUND_BOT);

    tft.fillrect(20, 40, 460, 300,BACKGROUND_MAIN);

    tft.fillrect(20, 40, 40, 60, BACKGROUND_TOP);

    tft.fillrect(440, 40, 460, 60, BACKGROUND_TOP);

    tft.fillrect(20, 280, 40, 300, BACKGROUND_BOT);

    tft.fillrect(440, 280, 460,300, BACKGROUND_BOT);

    tft.fillcircle(40,60, 20,  BACKGROUND_MAIN);

    tft.fillcircle(440, 60, 20,  BACKGROUND_MAIN);

    tft.fillcircle(40, 280, 20,  BACKGROUND_MAIN);

    tft.fillcircle(440, 280, 20,  BACKGROUND_MAIN);

}

void menu_graphics()
{

    // tft.Bitmap(50,80,388,124,(unsigned char *)image_data_menuIcons);
    tft.Bitmap(42,90,400,114,(unsigned char *)image_data_Untitled);

    tft.set_font((unsigned char *)Goudy_Old_Style21x19);

    tft.foreground(Black);

    tft.background( PROGR_C);

    tft.locate(45, 165 );

    tft.printf("Program");

    tft.fillrect(128, 165,137 , 185,White);

    tft.background( AUTO_C);

    tft.locate(160, 165 );

    tft.printf("Auto");

    tft.background( MANUAL_C);

    tft.locate(255, 165 );

    tft.printf("Manual");

    tft.fillrect(335, 165,345 , 185,White);

    tft.background( OPTIONS_C);

    tft.locate(360, 165 );

    tft.printf("Options");

    tft.fillrect(439, 165,450 , 185,White);

    tft.set_font((unsigned char *)Goudy_Old_Style21x19);

    tft.foreground(Blue);

    tft.background( White);

    tft.locate(190, 265 );

    tft.printf("AQUA AG");
        



}

void program_graphics()
{
    tft.fillrect(36 , 51, 454, 289, PROGRAM_COLOR);

    tft.rect(35,50,455,290, Black);

    tft.set_font((unsigned char *)Goudy_Old_Style21x19);

    tft.background( 0xF777);

    tft.foreground( Black);

    tft.locate(83,55);

    tft.printf("START");

    tft.locate(170,55);

    tft.printf("DAY");

    tft.locate(270,55);

    tft.printf("DURATION");

    tft.line(36 , 75,455, 75, Black);

    tft.line(80, 50,80, 290, Black);

    tft.line(165 , 50,165, 290, Black);

    tft.line(230 , 50,230, 290, Black);

}


void manual_graphics()
{
    
    tft.background( White);

    tft.foreground(Black);

    tft.set_font((unsigned char *)Goudy_Old_Style21x19);

    tft.set_orientation(0);

    tft.locate(65, 30);

    tft.printf("Manual Control");

    tft.set_orientation(1);

}

void auto_graphics()
{

    tft.background( White);

    tft.foreground(Black);

    tft.set_font((unsigned char *)Goudy_Old_Style21x19);

    tft.set_orientation(0);

    tft.locate(85, 27);

    tft.printf("Auto Control");

    tft.set_orientation(1);
  
    int xa =50, ya = 60, xb =270 , yb =190, d =7 ;

    tft.fillrect( xa, ya, xb,  yb,  AUTO_C1);

    tft.fillrect( xa  , yb+d,  xa + (xb-xa)/2, 270,  AUTO_C2a);

    tft.fillrect(  xa + (xb-xa)/2 +d , yb+d, xb, 270,  AUTO_C2b);

    tft.fillrect( xb+d, ya, 430,  270,  AUTO_C3);

    tft.set_font((unsigned char *)Goudy_Old_Style21x19);

    tft.background( AUTO_C2a);

    tft.foreground( White);

    tft.locate(80,200);

    tft.printf("Flow");

    tft.background( AUTO_C2b);

    tft.locate(190,200);

    tft.printf("Rain");

    tft.background( AUTO_C3);

    tft.locate(310,70);

    tft.printf("Weather");

}

void flow_graphics()
{
    tft.background( White);

    tft.foreground(Black);

    tft.set_font((unsigned char *)Goudy_Old_Style21x19);

    tft.set_orientation(0);

    tft.locate(120, 30);

    tft.printf("Set Flow");

    tft.set_orientation(1);
}

void rain_graphics()
{
   tft.background( White);

    tft.foreground(Black);

    tft.set_font((unsigned char *)Goudy_Old_Style21x19);

    tft.set_orientation(0);

    tft.locate(60, 30);

    tft.printf("Set Rain Sensor");

    tft.set_orientation(1);

}

void water_budget_graphics()
{
   tft.background( White);

    tft.foreground(Black);

    tft.set_font((unsigned char *)Goudy_Old_Style21x19);

    tft.set_orientation(0);

    tft.locate(60, 30);

    tft.printf("Set Water Budget");

    tft.set_orientation(1);

}

void wifi_info_graphics()
{
    tft.background( White);

    tft.foreground(Black);

    tft.set_font((unsigned char *)Goudy_Old_Style21x19);

    tft.set_orientation(0);

    tft.locate(60, 30);

    tft.printf("Network");

    tft.set_orientation(1);

    tft.fillrect(80 ,70, 400, 280, PROGRAM_COLOR);

    tft.rect(80 ,70, 400, 280, Black);

    tft.locate(100, 90);

    tft.printf("Status  : ");

    tft.locate(100, 130);

    tft.printf("SSID    : ");

    tft.locate(100, 170);

    tft.printf("IP      : ");

    tft.locate(100, 210);

    tft.printf("MAC     : ");

    tft.locate(100, 250);

    tft.printf("Signal  : ");

}


