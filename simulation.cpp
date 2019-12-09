#include "simulation.h"

#include <iostream>
#include <fstream>
#include <string>
#include "simlib.h"

#include "day_cycle.h"
#include "objects.h"
#include "generator.h"

using namespace std;

void Simulation::run(unsigned long runtime, std::string day_csv, std::string reservoir_csv)
{
    cout << "WORK:        " << set_work() << '\n';
    cout << "TIME low:    " << set_time("low") << '\n'; 
    cout << "TIME middle: " << set_time("middle") << '\n';
    cout << "TIME high:   " << set_time("high") << '\n';
    
    st_high_consumption.SetCapacity(set_work());
    st_high_checker.SetCapacity(set_work());
    st_capacity.SetCapacity(config.reservoir_capacity);

    Init(0, runtime);
    (new DayCycle)->Activate();   
    (new SelfDischarge)->Activate(); 
    Run();


    // --------------- STAT ------------------
    //fa_high_timer.Output();

    //qu_effectivity.Output();
    qu_actual_reservoir_capacity.Output();
    //qu_energy_buffer.Output();

    st_high_consumption.Output();
    st_capacity.Output();

    //st_high_checker.Output();


    stats.weather.Output();
    cout << "Excess energy: " << stats.excess_energy << '\n';
    cout << "No energy: " << stats.no_energy << '\n';

    fstream fday;
    fday.open(day_csv, fstream::out);
    
    fstream freservoir;
    freservoir.open(reservoir_csv, fstream::out);

    for (unsigned long i = 0; i < stats.day_stats.size(); i++) {
        auto &day_stat  = stats.day_stats[i];
        cout << "=======================================\n";
        cout << " DAY: " << i << endl;
        cout << " weather type: " << day_stat.day_weather << endl;
        cout << " generation:   " << day_stat.day_generation << endl;
        cout << " consumption:  " << day_stat.day_consumption << endl;
        cout << " night start reservoir: " << day_stat.night_start_reservoir << endl;
        cout << " night end reservoir:   " << day_stat.night_end_reservoir << endl;
        cout << " no energy:             " << day_stat.no_energy << endl;
        cout << "=======================================\n";

        fday << i << ',' << day_stat.day_weather << ',' << day_stat.day_generation << ',' << day_stat.day_consumption << ',' << day_stat.no_energy << endl;
        
        freservoir << i << ',' << day_stat.night_start_reservoir << endl;
        freservoir << i + 0.5 << ',' << day_stat.night_end_reservoir << endl;
    }

    fday.close();
    freservoir.close();
}