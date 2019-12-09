#pragma once

#include "simlib.h"
#include "config.h"
#include "objects.h"

#include "generator.h"

class Simulation
{   

public:
    Simulation() {}

    void run(unsigned long runtime, std::string csv_file, std::string resevoir_csv);

};