#include "generator.h"

#include "simlib.h"
#include "config.h"
#include "objects.h"

#include <iostream>
#include <limits>

using namespace std;

void Generator::Behavior()
{
    bool isFirst = true;

generator_normal_start:

    while (true) {
        cerr << Time << endl;
        cerr << "[g] start generate\n";

        // if checker passivated itself -> activate checker
        if (qu_energy_buffer.Empty() && ! st_high_checker.Full()) {
            cerr << "[g] start checker\n"; 
            this->checker->Activate();
        }
        
        // add to reservoir or remove energy 
        int cnt = 0;
        while (! qu_energy_buffer.Empty()) {
            qu_energy_buffer.GetFirst()->Activate();
            cnt++;
        } 

        
        cerr << "[g] activate from buffer: " << cnt << endl;

        if (isDay == false) {
            cerr << "[g] passivate" << endl;
            Passivate();
            goto generator_normal_start; // GOTO !!!
        }

        // initialize energy reservoir for the first time
        if (isFirst) {
            cerr << "[g] initialize reservoir\n";
            for (int i = 0; i < config.reservoir_init; i++) {
                qu_energy_buffer.Insert(new Energy());
            }
            isFirst = false;
        }
    
        cerr << "[g] generate to buffer: " << energy_amount << endl ;
        // generate energy
        for (int i = 0; i < energy_amount; i++) {
            qu_energy_buffer.Insert(new Energy());
        }
        // statistics
        stats.current_day_generation += energy_amount;

        cerr << "[g] sleep\n";
        // wait till next generation
        Wait(config.t_generate);
    }
}


void Checker::Behavior()
{
    while (true) {
        // cerr << "[c] st_high " << st_high_checker.Capacity() << ' ' << st_high_checker.Used() << endl;
        cerr << " [c] before ENTER " << st_high_checker.Capacity() << ' ' << st_high_checker.Used() << endl;
        Enter(st_high_checker, 1);
        cerr << " [c] after  ENTER " << st_high_checker.Capacity() << ' ' << st_high_checker.Used() << endl;

        if (! qu_energy_buffer.Empty()) {
            qu_energy_buffer.GetFirst()->Activate();
            cerr << " [c] release energy buffer\n";
        }
        else if (! qu_actual_reservoir_capacity.Empty()) {
            cerr << " [c] release energy reservoir " << qu_actual_reservoir_capacity.Length() << "\n" ;
            qu_actual_reservoir_capacity.GetFirst()->Activate();
        }
        else {
            Leave(st_high_checker, 1);
            cerr << " [c] passivate " << st_high_checker.Capacity() << ' ' << st_high_checker.Used() << endl;
            Passivate();
        }
    }
}


void Energy::Behavior()
{   
    // ONLY NOW GENERATED
    if (! st_high_consumption.Full()) {
        // HIGH CONSUMPTION OBJECT
        cerr << "  [e] gen -> high\n";
        // statistics
        stats.current_day_consumption += 1;
        consumption_high();
    }
    else if (! st_capacity.Full()) {
        // RESERVOIR
        cerr << "  [e] gen -> effectivity\n";
        Enter(st_capacity, 1);

        if (qu_effectivity.Length() == 100) {
            for (int i = 0; i < set_efficiency(); i++) {
                qu_effectivity.GetFirst()->Activate();
            }
            for (int i = 0; i < 100 - set_efficiency(); i++) {
                Leave(st_capacity, 1);
            }
            qu_effectivity.Clear();
        }
        qu_effectivity.Insert(this);
        Passivate();

        cerr << "  [e] effectivity -> reservoir\n";
        // store to reservoir
        qu_actual_reservoir_capacity.Insert(this);
        Passivate();
        
        // IN RESERVOIR
        cerr << "  [e] reservoir released\n";
        if (! st_high_consumption.Full()) {
            // HIGH CONSUMPTION OBJECT
            cerr << "  [e] reservoir -> high\n";
            // statistics
            stats.current_day_consumption += 1;
            Leave(st_capacity, 1);
            this->consumption_high();
        }
        else {
            // TODO - dead code ?? maybe ??
            cerr << "WHAT?\n";
        }
    }
    else {
        cerr << "  [e] -\n";
        stats.excess_energy++;
    }
}


void Energy::consumption_high()
{
    cerr << "  [e] +\n";
    Enter(st_high_consumption, 1);
    
    if (st_high_consumption.Full()) {
        cerr << "  [e] before SEIZE\n";

        double time_start = Time;
        Seize(fa_high_timer);
        double time_end = Time;

        if (time_end - time_start < std::numeric_limits<double>::epsilon())
        {
            stats.no_energy++;
            stats.current_day_no_energy++;
        }

        cerr << "  [e] after SEIZE\n";
        
        cerr << "  [e] st_checker " << st_high_checker.Capacity() << ' ' << st_high_checker.Used() << endl;
        Leave(st_high_checker, config.high_consume);
        cerr << "  [e] st_checker " << st_high_checker.Capacity() << ' ' << st_high_checker.Used() << endl;
        
        cerr << "  [e] st_high    " << st_high_consumption.Capacity() << ' ' << st_high_consumption.Used() << endl;
        Leave(st_high_consumption, config.high_consume);
        cerr << "  [e] st_high    " << st_high_consumption.Capacity() << ' ' << st_high_consumption.Used() << endl;
        
        cerr << "  start " << Time << endl;
        Wait(Exponential(time_consume));
        cerr << "  end " << Time << endl;
        Release(fa_high_timer);
    }
    else {
        // remove excess energy and leave only single energy for timer
        return;
    }
}

void SelfDischarge::Behavior()
{
    while (true)
    {
        Wait(config.t_discharge);
        if (! qu_actual_reservoir_capacity.Empty())
        {
            qu_actual_reservoir_capacity.GetFirst();
            cerr <<  "   [d] - \n";

            Leave(st_capacity, 1);
        }
    }
}
