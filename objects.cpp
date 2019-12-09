#include "objects.h"

#include <string>

#include "simlib.h"
#include "config.h"


bool isDay = false;
double time_consume = 0;
int energy_amount = 0;

Facility fa_high_timer("Timer facility");

Queue qu_effectivity("Effectivity queue");
Queue qu_actual_reservoir_capacity("Actual reservoir capacity");
Queue qu_energy_buffer("Energy buffer");

Store st_high_consumption("Consumption store", 0);
Store st_capacity("Reservoir capacity", 0);

Store st_high_checker("Checker", 0);

Statistics stats;

int set_efficiency()
{
    return (config.pump_efficiency * config.turbine_efficiency) / 100;
}

int set_work()
{
    // th = 1
    //  W = (th * Wh) / t
    return (1 * config.high_consume) / config.t_consume;
}

double set_time(std::string type)
{   
    if (type == "high") {
        // HIGH

        // th = 1
        return 1;
    }
    else if (type == "middle") {
        // MIDDDLE

        return (config.t_consume * set_work()) / (double)config.middle_consume;
    }
    else if (type == "low") {
        // LOW

        // th = 1
        // tl = (t * W) / Wl
        return (config.t_consume * set_work()) / (double)config.low_consume;
    }
    
    return 1;
}

