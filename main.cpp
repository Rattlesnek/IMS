#include <iostream>
#include <string.h>

#include "simlib.h"
#include "config4cpp/Configuration.h"
#include "config.h"
#include "simulation.h"

using namespace std;

extern Config config;

int main(int argc, char ** argv)
{
    unsigned long time_of_simulation;
    if (argc != 3)
    {
        std::cerr << "Invalid number of arguments!\n"; 
        std::cerr << "  Try ./main <config_file> <time_of_simulation>\n";
        return 1;
    }
    	
    try
    {
        config.load(argv[1]);
        time_of_simulation = atoi(argv[2]);
    }	
    catch(const ConfigurationException & ex)
    {
        cerr << ex.c_str() << endl;
        return 1;
    }

    Simulation sim();
    sim.run(time_of_simulation);

    return 0;
}
