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
        // ============ DAY LOW - BEGIN ===============
        print("DAY LOW");
        isDay = true;
        time_consume = set_time(false); 
        
        // set new weather for a day
        int uni = Uniform(0, 100);
        if (uni <= config.p_sunny) {
            cerr << "Weather: sunny\n"; 
            energy_amount = config.energy_sunny;

            stats.weather(0);
        }
        else if (config.p_sunny < uni && uni <= config.p_sunny + config.p_middle) {
            cerr << "Weather: middle\n";
            energy_amount = config.energy_middle;

            stats.weather(1);
        }
        else {
            cerr << "Weather: cloudy\n";
            energy_amount = config.energy_cloudy;

            stats.weather(2);
        }
        
        this->generator->Activate();


        Wait(config.t_day_low);
        // ============ DAY HIGH - BEGIN ===============
        print("DAY HIGH");
        isDay = true; 
        time_consume = set_time(true); 



        Wait(config.t_day_high);
        // ============ NIGHT HIGH - BEGIN ===============
        print("NIGHT HIGH");
        isDay = false; 
        time_consume = set_time(true); 

        // generator will passivate itself



        Wait(config.t_night_high);
        // ============ NIGHT LOW - BEGIN ===============
        print("NIGHT LOW");
        isDay = false;
        time_consume = set_time(false); 


        Wait(config.t_night_low);
    }
}