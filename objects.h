#pragma once

#include <string>
#include "simlib.h"
#include "config.h"

extern bool isDay;
extern bool isHigh;

extern std::string weather_type;

extern Facility fa_high_timer;
extern Facility fa_low_timer;

extern Facility fa_discharge;

extern Queue qu_effectivity;

extern Store st_high_consumption;
extern Store st_low_consumption;
extern Store st_capacity;
