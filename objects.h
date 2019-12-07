#pragma once

#include <string>
#include "simlib.h"
#include "config.h"

extern bool isDay;
extern double time_consume;
extern int energy_amount;

extern Facility fa_high_timer;

extern Queue qu_effectivity;
extern Queue qu_actual_battery_capacity;
extern Queue qu_energy_buffer;

extern Store st_high_consumption;
extern Store st_capacity;

extern Store st_high_checker;


int set_work();

double set_time(bool isHigh);

class Statistics 
{
public:
    Statistics()
    {
        Histogram weather("Weather", 0, 1, 3);
        excess_energy = 0;
        no_energy = -1; //objects always wait on the first energy
    }

    Histogram weather;
    int excess_energy;

    int no_energy;
};
extern Statistics stats;

