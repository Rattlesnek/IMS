#include "objects.h"

#include <string>

#include "simlib.h"
#include "config.h"


bool isDay = false;
bool isHigh = false;

std::string weather_type;

Facility fa_high_timer("High timer facility");
Facility fa_low_timer("Low timer facility");

Facility fa_discharge("Discharge facility");

Queue qu_effectivity("Effectivity queue");
Queue qu_actual_battery_capacity("Actual battery capacity");

Store st_high_consumption("High consumtion store", 0);
Store st_low_consumption("Low consumtion store", 0);
Store st_capacity("Batterycapacity", 0);