#include "simulation.h"

#include <iostream>
#include "simlib.h"

#include "day_cycle.h"
#include "objects.h"
#include "generator.h"



void Simulation::run(unsigned long runtime)
{
    st_high_consumption.SetCapacity(config.high_consume);
    st_high_checker.SetCapacity(config.high_consume);
    st_low_consumption.SetCapacity(config.low_consume);
    st_low_checker.SetCapacity(config.low_consume);
    st_capacity.SetCapacity(config.battery_capacity);

    Init(0, runtime);
    (new DayCycle)->Activate();    
    Run();

    qu_actual_battery_capacity.Output();
}