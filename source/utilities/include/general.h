
#ifndef _GENERAL_H_
#define _GENERAL_H_



void calculate_schedule(int program) ;

bool calculate_next_water(int *next_water_hour,int *next_water_minute, int *next_water_day, int *next_water_program ); 

void autoValves();

void closeValves();

void manualValves();

#endif