#include "objects.h"

#include <string>

#include "simlib.h"
#include "config.h"


bool isDay = false;
double time_consume = 0;
int energy_amount = 0;

Facility fa_high_timer("Timer facility");

Queue qu_effectivity("Effectivity queue");
Queue qu_actual_battery_capacity("Actual battery capacity");
Queue qu_energy_buffer("Energy buffer");

Store st_high_consumption("Consumption store", 0);
Store st_capacity("Battery capacity", 0);

Store st_high_checker("Checker", 0);

Statistics stats;

int set_work()
{
    // th = 1
    //  W = (th * Wh) / t
    return (1 * config.high_consume) / config.t_consume;
}

double set_time(bool isHigh)
{   
    if (isHigh) {
        // HIGH

        // th = 1
        return 1;
    }
    else {
        // LOW

        // th = 1
        // tl = (t * W) / Wl
        return (config.t_consume * set_work()) / (double)config.low_consume;
    }
}

