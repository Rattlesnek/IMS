#include "day_cycle.h"

#include <iostream>

#include "simlib.h"
#include "config.h"
#include "generator.h"
#include "objects.h"

using namespace std;


void print(string fmt)
{
    cerr << "--------------------------------" << endl;
    cerr << "----------- " << fmt << endl;
    cerr << "--------------------------------" << endl;
}


void DayCycle::Behavior()
{

    while (true) {
        // statistics for a day
        DayStats day;
        stats.current_day_generation = 0;
        stats.current_day_consumption = 0;
        stats.current_day_no_energy = 0;
        
        /////////////////////////////////////////////////////
        ///             DAY MIDDLE - LOW                  ///
        /////////////////////////////////////////////////////
        print("DAY LOW");
        isDay = true;
        time_consume = set_time("low"); 
        
        // set new weather for a day
        int uni = Uniform(0, 100);
        if (uni <= config.p_sunny) {
            cerr << "Weather: sunny\n"; 
            energy_amount = config.energy_sunny;
            // statistics
            day.day_weather = 0;
            stats.weather(0);
        }
        else if (config.p_sunny < uni && uni <= config.p_sunny + config.p_middle) {
            cerr << "Weather: middle\n";
            energy_amount = config.energy_middle;
            // statistics
            day.day_weather = 1;
            stats.weather(1);
        }
        else {
            cerr << "Weather: cloudy\n";
            energy_amount = config.energy_cloudy;
            // statistics
            day.day_weather = 2;
            stats.weather(2);
        }
        
        this->generator->Activate();


        Wait(config.t_day_low);
        /////////////////////////////////////////////////////
        ///             DAY MIDDLE - BEGIN                ///
        /////////////////////////////////////////////////////
        print("DAY MIDDLE");
        isDay = true; 
        time_consume = set_time("middle"); 



        Wait(config.t_day_middle);
        /////////////////////////////////////////////////////
        ///             DAY HIGH - BEGIN                  ///
        /////////////////////////////////////////////////////
        print("DAY HIGH");
        isDay = true; 
        time_consume = set_time("high"); 



        Wait(config.t_day_high);
        /////////////////////////////////////////////////////
        ///             NIGH HIGH - BEGIN                 ///
        /////////////////////////////////////////////////////
        print("NIGHT HIGH");
        isDay = false; 
        time_consume = set_time("high");  
        // generator will passivate itself

        // statistics
        day.night_start_reservoir = qu_actual_reservoir_capacity.Length();


        Wait(config.t_night_high);
        /////////////////////////////////////////////////////
        ///             NIGH MIDDLE - BEGIN                 ///
        /////////////////////////////////////////////////////
        print("NIGHT MIDDLE");
        isDay = false;
        time_consume = set_time("middle"); 


        Wait(config.t_night_middle);
        /////////////////////////////////////////////////////
        ///             NIGH LOW - BEGIN                  ///
        /////////////////////////////////////////////////////
        print("NIGHT LOW");
        isDay = false;
        time_consume = set_time("low"); 



        Wait(config.t_night_low);

        // statistics
        day.night_end_reservoir = qu_actual_reservoir_capacity.Length();
        day.day_generation = stats.current_day_generation;
        day.day_consumption = stats.current_day_consumption;
        day.no_energy = stats.current_day_no_energy;
        stats.day_stats.push_back(day);
    }
}