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
    for (int i = 0; i < config.battery_init; i++)
    {
        qu_actual_battery_capacity.Insert(new Energy(true));
    }
    
    Checker* checker = new Checker;
    checker->Activate();

    while (true) {
        // ============ DAY LOW - BEGIN ===============
        print("DAY LOW");
        isDay = true;
        isHigh = false;  
        
        // create new weather setter and new generator for a day
        int uni = Uniform(0, 100);
        //std::cout << uni << std::endl;
        if (uni <= config.p_sunny) {
            weather_type = "sunny";
            cerr << "Weather: sunny\n"; 
        }
        else if (config.p_sunny < uni && uni <= config.p_sunny + config.p_middle) {
            weather_type = "middle";
            cerr << "Weather: middle\n";
        }
        else {
            weather_type = "cloudy";
            cerr << "Weather: cloudy\n";
        }
        
        (new Generator(checker))->Activate();
        // ============ DAY LOW - END =================

        Wait(config.t_day_low);

        // ============ DAY HIGH - BEGIN ===============
        print("DAY HIGH");
        isDay = true;
        isHigh = true;  
        // ============ DAY HIGH - END ===============

        Wait(config.t_day_high);

        // ============ NIGHT HIGH - BEGIN ===============
        print("NIGHT HIGH");
        isDay = false;
        isHigh = true;  
        // ============ NIGHT HIGH - END ===============

        Wait(config.t_night_high);

        // ============ NIGHT LOW - BEGIN ===============
        print("NIGHT LOW");
        isDay = false;
        isHigh = false;  
        // ============ NIGHT LOW - END ===============

        Wait(config.t_night_low);
    }
}