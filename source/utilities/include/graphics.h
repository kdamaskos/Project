#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "include/display.h"

#include "ILI9486.h"

#include "globals.h"

#include "Arial12x12.h"

#include "Arial24x23.h"

#include "Arial28x28.h"

#include "Terminal6x8.h"

#include "gabriola.h"

#include "topbar.h"



#define LCD_SIZE_Y   320

#define LCD_SIZE_X  480



#define BACKGROUND_TOP 0x39E7

#define BACKGROUND_MAIN White

#define BACKGROUND_BOT   0xD6BB

#define SHAPE_COLOR   0xAED7

#define PROGRAM_COLOR  0xF777

#define PROGR_C 0x47E0

#define AUTO_C 0x459F

#define MANUAL_C 0xFEC0

#define OPTIONS_C 0xBEBB

#define BACKGROUND_C 0x03ef

//auto boxes colors
#define AUTO_C1 0xA535

#define AUTO_C2 0x1A37

#define AUTO_C3 0x31EC

#define AUTO_C4 0xD54E

extern ILI9486 tft;


extern const char *WEEK_DAY[];

extern const char *PROGRAM[];


void select( int selection);

void update_date_time();

void update_wifi_icon(bool is_connected);

class CustomRect2
{


        int x,x2, y,y2, w, h, d, no, curve , prev = 0;

        short color,  background;

    public:

        CustomRect2(int X, int Y, int W, int H, int D,  unsigned short Color, unsigned short Backg, int No = 4, int Curve = 15)
        {
            x = X;
            y= Y;
            h = H;
            w = W;
            d = D;
            color = Color;
            background = Backg;
            no = No;
            curve = Curve;
        }


        void draw()
        {
            
            x2 = x + w;
            y2 = y + h;

            for(int i = 0; i< no; i++)  
            {

                tft.fillrect(   x + i*(w+d),    y,      x2+ i*(w+d),      y2,  color);               
                tft.fillrect(   x + i*(w+d) ,   y,      x + i*(w+d) + curve, y + curve, background);     
                tft.fillrect(x2+ i*(w+d) -curve, y, x2+ i*(w+d) , y+curve, background);                  
                tft.fillrect(x + i*(w+d) , y2-curve, x + i*(w+d) +curve, y2, background);                  
                tft.fillrect(x2+ i*(w+d) -curve,y2-curve, x2+ i*(w+d) ,y2, background);                
                tft.fillcircle(x + i*(w+d) +curve,y+curve, curve,  color);                  
                tft.fillcircle(x + i*(w+d) +curve, y2-curve, curve,  color);                 
                tft.fillcircle(x2+ i*(w+d) -curve, y2-curve, curve,  color);                 
                tft.fillcircle(x2+ i*(w+d) -curve, y+curve, curve,  color);     

            }

            int shift = y2 + d;
            int h= y2-y;

            for(int i = 0; i< no; i++)  
            {
                tft.fillrect(x + i*(w+d) , shift,  x2+ i*(w+d) , shift+ h,  color);               
                tft.fillrect(x + i*(w+d) , shift, x + i*(w+d) +curve, shift+curve, background);                  
                tft.fillrect(x2+ i*(w+d) -curve, shift, x2+ i*(w+d) , shift+curve, background);                  
                tft.fillrect(x + i*(w+d) ,shift+ h-curve, x + i*(w+d) +curve,shift+ h, background);                  
                tft.fillrect(x2+ i*(w+d) -curve,shift+h-curve, x2+ i*(w+d) ,shift+h, background);                
                tft.fillcircle(x + i*(w+d) +curve,shift+curve, curve,  color);                  
                tft.fillcircle(x + i*(w+d) +curve,shift+ h-curve, curve,  color);                 
                tft.fillcircle(x2+ i*(w+d) -curve,shift+ h-curve, curve,  color);                 
                tft.fillcircle(x2+ i*(w+d) -curve, shift+curve, curve,  color);     

            }

        }

        void select (int i)
        {

            if (prev<3) 
            {
                
                for(int j=0; j<15;j++)
                {
                    tft.line(x + prev*(w+d)+ w/2 -j   , y-j-2,  x+ prev*(w+d)+ w/2 +j, y-j-2, background);

                    tft.line(x + prev*(w+d) + w/2 -j , y2+j+2, x+ prev*(w+d)+ w/2 +j, y2+j+2, background);
                }
            }
            else 
            {

                prev -= 3;

                for(int j=0; j<15;j++)
                {
                

                    tft.line(x + prev*(w+d) + w/2 -j   , y-j-2 +  h  + d,  x+ prev*(w+d)+ w/2 +j, y-j-2 +  h  + d, background);

                    tft.line(x + prev*(w+d)+ w/2 -j  , y2+j+2+  h  + d, x+ prev*(w+d)+ w/2 +j, y2+j+2+  h  + d, background);
                }
            }

            prev = i;

            if (i<3) 
            {
                for(int j=0; j<15;j++)
                {
                    tft.line(x + i*(w+d) + w/2 -j  , y-j-2,  x+ i*(w+d)+ w/2 +j, y-j-2, color);

                    tft.line(x + i*(w+d) + w/2 -j , y2+j+2, x+ i*(w+d)+ w/2 +j, y2+j+2, color);
                }
            }
            else 
            {
                
                i -= 3;

                for(int j=0; j<15;j++)
                {

                    tft.line(x + i*(w+d)+ w/2 -j , y-j-2 +  h  + d,  x+ i*(w+d)+ w/2 +j, y-j-2 +  h  + d, color);

                    tft.line(x + i*(w+d) + w/2 -j , y2+j+2+  h  + d, x+ i*(w+d)+ w/2 +j, y2+j+2+  h  + d, color);
                }
            }
                
        }

        void set_label(int select, char * label) 
        {
            tft.background( color);
            tft.foreground(White);
            //tft.set_font((unsigned char *)Terminal6x8);
            tft.set_font((unsigned char *)Goudy_Old_Style21x19);
            if (select<3) 
            {
                tft.locate(select*(w+d) + x+10, y2 - 25);
            }
            else 
            {
                select -= 3;
                tft.locate(select*(w+d) + x+10, y2 - 25+h+d);

            }
            tft.printf("%s", label);
        }

};


class Programs
{
        int prev =0, x = 45, y=90, d=45;

    public:

        void print_all()
        {
            for(int i=0; i<TOTAL_PROGRAMS;i++)
            {
                tft.set_font((unsigned char *)Goudy_Old_Style21x19);
                tft.background( 0xF777);
                tft.foreground(0xAD75);
                tft.locate(x, y + i*d);
                tft.printf("%s",PROGRAM[i]);
            }

        }

        void select (int program)
        {
            tft.set_font((unsigned char *)Arial28x28);
            tft.background( 0xF777);
            tft.foreground(0xAD75);
            tft.locate(x, y + prev*d); 
            tft.printf(" ");
            tft.set_font((unsigned char *)Goudy_Old_Style21x19); 
            tft.locate(x, y + prev*d); 
            tft.printf("%s",PROGRAM[prev]);  

            prev = program;
 
           tft.set_font((unsigned char *)Arial28x28);
            tft.background( Black);
            tft.foreground(White);
            tft.locate(x, y + program*d);
            tft.printf("%s",PROGRAM[program]);


        }
        void clear_select(int program)
        {
            tft.set_font((unsigned char *)Arial28x28);
            tft.background( 0xF777);
            tft.foreground(Black);
            tft.locate(x, y + prev*d); 
            tft.printf("%s",PROGRAM[prev]);  

        }
};


 class Start 
 {
        int  prev = 0, x = 95 , y = 120, d = 35 ;

    public:


        void print_all(int program)
        {
            tft.set_font((unsigned char *)Goudy_Old_Style21x19);
            tft.background( 0xF777);
            tft.foreground(Black);
            for (int i=0; i< TOTAL_STARTS; i++)
            {
                tft.locate(x,y +i*d);
                if (start_times[i][1][program] != -1)
                {
                    tft.printf("%02d:%02d", start_times[i][0][program],
                                                start_times[i][1][program]);                    
                }
                else 
                {
                    tft.printf(" -:- ");
                }
                

            }
        }


        void clear_select(int Start_no, int program)
        {
            tft.set_font((unsigned char *)Goudy_Old_Style21x19);
            tft.background( 0xF777);
            tft.foreground(Black);
            tft.locate(x,y + Start_no*d);

            if (start_times[Start_no][1][program] != -1)
            {
                tft.printf("%02d:%02d ", start_times[Start_no][0][program],
                                            start_times[Start_no][1][program]);                    
            }
            else 
            {
                tft.printf(" -:- ");
            }

        }

        void select (int Start_no, int program)
        {

           clear_select(prev, program);

            tft.background( Black);
            tft.foreground(White);
            tft.locate(x,y + Start_no*d);

            if (start_times[Start_no][1][program] != -1)
            {
                tft.printf("%02d:%02d", start_times[Start_no][0][program],
                                            start_times[Start_no][1][program]);                    
            }
            else 
            {
                tft.printf(" -:- ");
            }

             prev =   Start_no;                                           

        }

        void print(int Start_no, int program) 
        {
            tft.set_font((unsigned char *)Goudy_Old_Style21x19);
            tft.background( Black);
            tft.foreground(White);
            tft.locate(x,y + Start_no*d);

            if (start_times[Start_no][1][program] != -1)
            {
                tft.printf("%02d:%02d", start_times[Start_no][0][program],
                                            start_times[Start_no][1][program]);                    
            }
            else 
            {
                tft.printf(" -:- ");
            }

        }

 };

class WeekDay 
{
        int prev=0, x =175, y= 90, d = 30 ;

    public:
    
        void print_all(int program)
        {
            
            tft.background( 0xF777);
            tft.set_font((unsigned char *)Goudy_Old_Style21x19);

            for (int i=0; i< 7; i++)
            {
                tft.locate(x, y +i*d );
                         
                if (week_days[i][program] == 1) 
                {
                    tft.foreground(Blue);
                    
                } 
                else 
                {
                    tft.foreground(0xAD75);
                }
                tft.printf("%s",WEEK_DAY[i]);
            }
        }

        void clear_select(int day)
        {
            tft.set_font((unsigned char *)Goudy_Old_Style21x19);
            tft.background( 0xF777);
            tft.locate(x, y +day*d); 

            if (week_days[day][program] == 1) 
            {
                tft.foreground(Blue);
                
            } 
            else 
            {
                tft.foreground(0xAD75);
            }  
            tft.printf("%s",WEEK_DAY[day]);

        }

        void select(int day)  
        {   

            clear_select(prev);

            tft.background( Black);
            tft.locate(x, y +day*d);

            if (week_days[day][program] == 1) 
            {
                tft.foreground(Blue);
                
            } 
            else 
            {
                tft.foreground(0xAD75);
            }            
            tft.printf("%s",WEEK_DAY[day]);

            prev = day;

        
        }  

        void print(int day, int program)
        {
            
            tft.background( Black);
            tft.set_font((unsigned char *)Goudy_Old_Style21x19);

            tft.locate(x, y +day*d);
                     
            if (week_days[day][program] == 1) 
            {
                tft.foreground(Blue);
                
            }
            else 
            {
                tft.foreground(0xAD75);
            }

            tft.printf("%s",WEEK_DAY[day]);

        }

};

class Duration
{   

        int prev=0;

    public:

        void print_all(int program)
        {
            tft.set_font((unsigned char *)Goudy_Old_Style21x19);
            tft.foreground( Black); 
            tft.background( 0xF777); 

            int i= 0;
            for (int x=0; x< 5; x++) 
            {

                for (int y=0; y< 8; y++) 
                {

                    tft.locate(x*46+243,77+y*27); 

                    tft.printf("%d", durations[i][program]);

                    
                    i++;
                    
                }
            }

        }
        void clear_select (int valve, int program)
        {
            tft.set_font((unsigned char *)Goudy_Old_Style21x19);
            tft.foreground( Black); 
            tft.background( 0xF777); 
            tft.locate( (valve/8) *46+243, 77+ ( valve%8) *27); 


            tft.printf("%d", durations[valve][program]);
                

        }


        void select (int valve, int program)
        {

            clear_select(prev,  program);

            tft.foreground( White); 
            tft.background( Black); 

            tft.locate( (valve/8) *46+243, 77+ ( valve%8) *27); 


            tft.printf("%d", durations[valve][program]);
                
  

            prev = valve;
        }

        void print(int valve, int program)
        {

            tft.set_font((unsigned char *)Goudy_Old_Style21x19);

            tft.foreground(White); 
            tft.background(Black); 
            tft.locate( (valve/8) *46+243, 77+ ( valve%8) *27); 


            tft.printf("%d", durations[valve][program]);
  

        }


};

class Table 
{

    int x1, y1, x2, y2, nrow, ncol,color,color_table, cell_x, cell_y, prev = 0, length, col, row;

    public:


    Table(int X1, int Y1, int X2, int Y2, int Nrow, int Ncol,unsigned int Color_Table = PROGRAM_COLOR, unsigned int Color = Black,  int Length = 40) 
    {

        x1=X1, y1=Y1, x2=X2, y2=Y2, nrow=Nrow, ncol=Ncol,color=Color,color_table =Color_Table;
        cell_x = (x2-x1)/ncol;
        cell_y = (y2-y1)/nrow;
        length = Length;

    }

        void draw()
        {

            tft.background(color_table); 

            tft.foreground( Black); 

            tft.set_font((unsigned char *)Terminal6x8);

            int i =0;

            for ( col=0; col<=ncol; col++) 
            {
                tft.line(x1+cell_x*col , y1, x1+cell_x*col,  y2, color);

                for ( row=0; row<= nrow; row++) 
                {
                    tft.line(x1 , y1+row*cell_y, x2,  y1+row*cell_y, color);

                }
            }

            for ( col=0; col<ncol; col++) 
            {

                for ( row=0; row< nrow; row++) 
                {

                    tft.locate(col*cell_x+x1+1,y1+1+row*cell_y); 

                    tft.printf("%d", i++);

                }
            }  
     
        }

        void populate(int *Data = NULL)
        {
            tft.set_font((unsigned char *)Goudy_Old_Style21x19);

            tft.foreground( Black); 

            tft.background( color_table); 

            int i= 0;

            for (int col=0; col< ncol; col++) 
            {

                for (int row=0; row< 8; row++) 
                {

                    tft.locate( (i/nrow) *cell_x+x1+8, y1+8+ (i%nrow) *cell_y); 

                    tft.printf("%d",Data[i]);

                    i++;
  
                }
            }           
        }

        void clear_select (int cell, int  *Data = NULL)
        {

            tft.set_font((unsigned char *)Goudy_Old_Style21x19);

            tft.foreground( Black); 

            tft.background( color_table); 

            tft.locate( (cell/nrow) *cell_x+x1+8, y1+8+ ( cell%nrow) *cell_y); 

            tft.printf("%d", Data[cell]);
            
        }

        void select (int cell, int  *Data = NULL)
        {

            clear_select (prev, Data);

            tft.set_font((unsigned char *)Goudy_Old_Style21x19);

            tft.foreground( White); 

            tft.background( Black); 

            tft.locate( (cell/nrow) *cell_x+x1+8, y1+8+ (cell%nrow) *cell_y); 

            tft.printf("%d", Data[cell]);

            prev = cell;
        }


        void print(int cell, int *Data= NULL)
        {

            tft.set_font((unsigned char *)Goudy_Old_Style21x19);

            tft.foreground(White); 
            tft.background(Black); 
            tft.locate( (cell/nrow) *cell_x+x1+8, y1+8+ (cell%nrow) *cell_y); 
            tft.printf("%d",Data[cell]);

        }


};


void init_graphics();

void menu_graphics();

void program_graphics();

void auto_graphics();

void manual_graphics();

void water_budget_graphics();

void rain_graphics();

void flow_graphics();


#endif