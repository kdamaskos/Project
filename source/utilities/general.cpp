
#include "config/pins_config.h"
#include "globals.h"
#include "mbed.h"
#include "pcf8574.h"


I2C _i2c(EXP_I2C_SDA, EXP_I2C_SCL ); // (sda,scl)


PCF8574 pcf0(&_i2c, 0x00, PCF8574_TYPE);

PCF8574 pcf1(&_i2c, 0x01, PCF8574_TYPE);

PCF8574 pcf2(&_i2c, 0x02, PCF8574_TYPE);

PCF8574 pcf3(&_i2c, 0x03, PCF8574_TYPE);

PCF8574 pcf4(&_i2c, 0x04, PCF8574_TYPE);

Mutex function_mutex;




struct sorted_valves 
{
    int index;
    int duration;
    bool check;

};



void calculate_schedule(int program ) 
{

    int temp;

    struct sorted_valves   srt_valves[TOTAL_ZONES];

    

    for (int i = 0; i < TOTAL_ZONES; ++i)
    {
        
        srt_valves[i].index = i;

        srt_valves[i].duration = durations[i][program];

        srt_valves[i].check = false;

        schedule[i][program].time_shift = -1;

        schedule[i][program].duration = 0;

    }


    for (int i = 0; i < TOTAL_ZONES; ++i)
    {

        for (int j = i + 1; j < TOTAL_ZONES; ++j) 
        { 

            if ( srt_valves[i].duration < srt_valves[j].duration )  
            {

                temp = srt_valves[i].index;

                srt_valves[i].index = srt_valves[j].index;

                srt_valves[j].index = temp;



                temp = srt_valves[i].duration;

                srt_valves[i].duration = srt_valves[j].duration;

                srt_valves[j].duration = temp;

            }
        }
    }

    int index, time_shift = 0, sum_flow = 0, valves_count = 0, j = 0;

    do
    {

        for ( int i = 0; i < TOTAL_ZONES; i++ )
        {

            if ( srt_valves[i].duration == 0 )
            {
                continue;
            }
            
            index = srt_valves[i].index;

            if (sum_flow <= (supply_flow + flow[index] ) &&  valves_count < MAXVALVES   &&   (schedule[index][program].time_shift == -1)  )
            {

                valves_count ++;

                sum_flow += flow[index];

                schedule[index][program].time_shift = j*INTERVAL_TIME;

                schedule[index][program].duration += INTERVAL_TIME;

                srt_valves[i].check = true;

            }
            else if (schedule[index][program].duration < srt_valves[i].duration  && srt_valves[i].check == true)
            {

                schedule[index][program].duration += INTERVAL_TIME;

            }
            else if ( schedule[index][program].duration == srt_valves[i].duration && srt_valves[i].check == true)
            {  

                valves_count --;

                sum_flow -= flow[index];

                srt_valves[i].check = false;

            }

        }

        j++;

    } while (valves_count != 0);

    program_duration[program] = (j-1);
/*
    for (int i=0; i<TOTAL_ZONES; i++)
    {
        printf("valve %d : %d,%d\n",i,schedule[i][program].time_shift,schedule[i][program].duration);
    }
*/
}




void manualValves() {

    unsigned int data, binary,shift;
    
    function_mutex.lock();

    // 0-7
    data = 0b00000000;
    shift = 0;

    for (int i = 0; i < 8; i++) {

        if (manual_valves[i] == 0) {

            binary = 0b00000000;
            
        } else {

            binary = 0b00000001;
        }

        binary = binary << shift;
        data = data | binary;
        shift++;
    }

    pcf0.WriteByte(data);

    // 8-15
    data = 0b00000000;
    shift = 0;
    for (int i = 8; i < 16; i++) {
        if (manual_valves[i] == 0) {
        binary = 0b00000000;
        } else {
        binary = 0b00000001;
        }
        binary = binary << shift;
        data = data | binary;
        shift++;
    }
    pcf1.WriteByte(data);
    // 16-23
    data = 0b00000000;
    shift = 0;
    for (int i = 16; i < 24; i++) {
        if (manual_valves[i] == 0) {
        binary = 0b00000000;
        } else {
        binary = 0b00000001;
        }
        binary = binary << shift;
        data = data | binary;
        shift++;
    }
    pcf2.WriteByte(data);
    // 24-31
    data = 0b00000000;
    shift = 0;
    for (int i = 24; i < 32; i++) {
        if (manual_valves[i] == 0) {
        binary = 0b00000000;
        } else {
        binary = 0b00000001;
        }
        binary = binary << shift;
        data = data | binary;
        shift++;
    }
    pcf3.WriteByte(data);
    // 32-39
    data = 0b00000000;
    shift = 0;
    for (int i = 32; i < 40; i++) {
        if (manual_valves[i] == 0) {
        binary = 0b00000000;
        } else {
        binary = 0b00000001;
        }
        binary = binary << shift;
        data = data | binary;
        shift++;
    }
    pcf4.WriteByte(data);
    function_mutex.unlock();
    
}

void autoValves() {
  unsigned int data, binary;
  int shift;
 
  function_mutex.lock();
  data = 0b00000000;
  shift = 0;
  for (int i = 0; i < 8; i++) {
    if (auto_valves[i] == 0) {
      binary = 0b00000000;
    } else {
      binary = 0b00000001;
    }
    binary = binary << shift;
    data = data | binary;
    shift++;
  }
  pcf0.WriteByte(data);

  data = 0b00000000;
  shift = 0;
  for (int i = 8; i < 16; i++) {
    if (auto_valves[i] == 0) {
      binary = 0b00000000;
    } else {
      binary = 0b00000001;
    }
    binary = binary << shift;
    data = data | binary;
    shift++;
  }
  pcf1.WriteByte(data);

  data = 0b00000000;
  shift = 0;
  for (int i = 16; i < 24; i++) {
    if (auto_valves[i] == 0) {
      binary = 0b00000000;
    } else {
      binary = 0b00000001;
    }
    binary = binary << shift;
    data = data | binary;
    shift++;
  }
  pcf2.WriteByte(data);

  data = 0b00000000;
  shift = 0;
  for (int i = 24; i < 32; i++) {
    if (auto_valves[i] == 0) {
      binary = 0b00000000;
    } else {
      binary = 0b00000001;
    }
    binary = binary << shift;
    data = data | binary;
    shift++;
  }
  pcf3.WriteByte(data);

  data = 0b00000000;
  shift = 0;
  for (int i = 32; i < 40; i++) {
    if (auto_valves[i] == 0) {
      binary = 0b00000000;
    } else {
      binary = 0b00000001;
    }
    binary = binary << shift;
    data = data | binary;
    shift++;
  }
  pcf4.WriteByte(data);
  function_mutex.unlock();
  
}

void closeValves() {
  
  function_mutex.lock();
  pcf0.WriteByte(0x00);
  pcf1.WriteByte(0x00);
  pcf2.WriteByte(0x00);
  pcf3.WriteByte(0x00);
  pcf4.WriteByte(0x00);
  function_mutex.unlock();
  
}


bool calculate_next_water(int *next_water_hour,int *next_water_minute, int *next_water_day, int *next_water_program ) 
{
    
    int next_day;

    *next_water_hour = 24;

    *next_water_minute = 60;

    time_t seconds = time(NULL);

    struct tm *t = localtime(&seconds);

    for (int k = 0; k < 8; k++)
    {
        next_day = t->tm_wday + k;

        if ( next_day > 6 )
        {
            next_day = next_day - 7;
        }

        for (int i = 0; i < TOTAL_PROGRAMS; i++) 
        {
   
            for (int j = 0; j < TOTAL_STARTS; j++) 
            {
                // if water today
                if ( week_days[next_day][i] && k == 0)
                {
                    
                    if ( start_times[j][0][i] < *next_water_hour &&  start_times[j][1][i] > -1 &&  start_times[j][0][i] >= t->tm_hour ) 
                    {      
                        
                        *next_water_hour = start_times[j][0][i];

                        *next_water_minute = start_times[j][1][i];

                        *next_water_day = t->tm_wday;

                        *next_water_program = i;
                    
                    }
                    else if(  start_times[j][0][i] == *next_water_hour &&  start_times[j][1][i] > -1 &&  start_times[j][1][i] < *next_water_minute &&  start_times[j][1][i] > t->tm_min) 
                    {

                        *next_water_hour = start_times[j][0][i];

                        *next_water_minute = start_times[j][1][i];

                        *next_water_day = t->tm_wday;

                        *next_water_program = i;

                    }

                }// if water next day
                else if( week_days[next_day][i] )
                {
                                        
                    if ( start_times[j][0][i] < *next_water_hour &&  start_times[j][1][i] > -1  ) 
                    {      
                        
                        *next_water_hour = start_times[j][0][i];

                        *next_water_minute = start_times[j][1][i];

                        *next_water_day = next_day;

                        *next_water_program = i;
                    
                    }
                    else if(  start_times[j][0][i] == *next_water_hour &&  start_times[j][1][i] > -1 &&  start_times[j][1][i] < *next_water_minute )
                    {

                        *next_water_hour = start_times[j][0][i];

                        *next_water_minute = start_times[j][1][i];

                        *next_water_day = next_day;

                        *next_water_program = i;

                    }
                }

            }
        }

        if ( *next_water_hour != 24)
        {
            return true;
        }

    }

    if ( *next_water_hour != 24)
    {
        return true;
    }
    else
    {
        return false;
    }

}
        


void init(){

     
    // initialize
    for (int i = 0; i < TOTAL_ZONES; i++) {
        rain[i] = 1;
        flow[i] = 5;
    }

    for (int j = 0; j < TOTAL_PROGRAMS; j++) {
        for (int i = 0; i < TOTAL_STARTS; i++) {
        start_times[i][1][j] = -1;
        }
    }


}


