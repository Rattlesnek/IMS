#include "simulation.h"

#include <iostream>
#include "simlib.h"

#include "day_cycle.h"
#include "objects.h"
#include "generator.h"

using namespace std;

void Simulation::run(unsigned long runtime)
{
    cout << "WORK:      " << set_work() << '\n';
    cout << "TIME low:  " << set_time(false) << '\n'; 
    cout << "TIME high: " << set_time(true) << '\n';
    
    st_high_consumption.SetCapacity(set_work());
    st_high_checker.SetCapacity(set_work());
    // st_low_consumption.SetCapacity(config.low_consume);
    // st_low_checker.SetCapacity(config.low_consume);
    st_capacity.SetCapacity(config.battery_capacity);

    Init(0, runtime);
    (new DayCycle)->Activate();   
    (new SelfDischarge)->Activate(); 
    Run();


    // --------------- STAT ------------------
    //fa_high_timer.Output();

    //qu_effectivity.Output();
    qu_actual_battery_capacity.Output();
    //qu_energy_buffer.Output();

    st_high_consumption.Output();
    st_capacity.Output();

    //st_high_checker.Output();


    stats.weather.Output();
    cout << "Excess energy: " << stats.excess_energy << '\n';
    cout << "No energy: " << stats.no_energy << '\n';
}