#include "simulation.h"

#include <iostream>
#include "simlib.h"

#include "day_cycle.h"
#include "objects.h"




void Simulation::run(unsigned long runtime)
{
    //std::cout << "runtime: " << runtime << std::endl;
    st_high_consumption.SetCapacity(config.high_consume);
    st_low_consumption.SetCapacity(config.low_consume);
    st_capacity.SetCapacity(config.battery_capacity - config.battery_init);

    Init(0, runtime);
    
    std::cout << "run simulation\n";
    (new DayCycle)->Activate();    

    Run();
}