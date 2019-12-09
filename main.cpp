#include <iostream>
#include <string.h>

#include "simlib.h"
#include "config4cpp/Configuration.h"

#include "config.h"
#include "simulation.h"
#include "objects.h"

using namespace std;
using namespace config4cpp;


int main(int argc, char ** argv)
{
    unsigned long time_of_simulation = 0;
    if (argc != 5)
    {
        std::cerr << "Invalid number of arguments!\n"; 
        std::cerr << "  Try ./main <config_file> <time_of_simulation> <day_info.csv> <reservoir.csv>\n";
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

    // cout << config.t_day_high << endl;
    // cout << config.t_generate << endl;
    // cout << config.p_sunny << endl;
    // cout << config.energy_sunny << endl;


    Simulation sim;
    sim.run(time_of_simulation, argv[3], argv[4]);

    return 0;
}
