#pragma once

#include <string>
#include <vector>

#include "simlib.h"
#include "config.h"

extern bool isDay;
extern double time_consume;
extern int energy_amount;

extern Facility fa_high_timer;

extern Queue qu_effectivity;
extern Queue qu_actual_reservoir_capacity;
extern Queue qu_energy_buffer;

extern Store st_high_consumption;
extern Store st_capacity;

extern Store st_high_checker;

int set_efficiency();

int set_work();

double set_time(std::string type);

class DayStats
{
public:
    int day_weather;

    int night_start_reservoir;
    int night_end_reservoir;

    int day_generation;
    int day_consumption;

    DayStats()
    {   
        day_weather = 0;

        night_start_reservoir = 0;
        night_end_reservoir = 0;

        day_generation = 0;
        day_consumption = 0;
    }
};



class Statistics 
{
public:
    Histogram weather;

    int excess_energy;
    int no_energy;

    int current_day_generation;
    int current_day_consumption;

    std::vector<DayStats> day_stats;

    Statistics() :
        weather("Weather", 0, 1, 3)
    {
        excess_energy = 0;
        no_energy = -1; //objects always wait on the first energy
        current_day_generation = 0;
        current_day_consumption = 0;
    }
};

extern Statistics stats;

