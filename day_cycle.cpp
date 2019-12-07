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
        (new Energy(true))->Activate();
    }
    
    while (true) {
        // ============ DAY LOW - BEGIN ===============
        print("DAY LOW");


        //cerr << "works: " << st.Full() << ' ' << st.Empty() << endl;

        isDay = true;
        isHigh = false;  
        
        // create new weather setter and new generator for a day
        (new Weather)->Activate();
        (new Generator)->Activate();
        
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