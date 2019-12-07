#include "generator.h"

#include <iostream>

#include "simlib.h"
#include "config.h"
#include "objects.h"

using namespace std;



////////////////////////////////////////////////////////////////////////////////////////////////
////                                     GENERATOR (BEGIN)                                  ////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief 
 * 
 */
void Generator::Behavior()
{
    // generator of energy
    while (true) {
        // generate after some time
        Wait(config.t_generate);

        // if its night stop generation
        if (isDay == false)
            break;

        this->checker->Passivate();
        while (! qu_energy_buffer.Empty())
        {
            qu_energy_buffer.GetFirst()->Activate();
        }

        // according to weather generate certain amount
        if (weather_type == "sunny") {
            generate(config.energy_sunny);
        }
        else if (weather_type == "middle") {
            generate(config.energy_middle);
        }
        else if (weather_type == "cloudy") {
            generate(config.energy_cloudy);
        }
        else {
            std::cerr << "Error: weather is not set\n";
        }

        //this->checker->Activate();
    }
}

/**
    * @brief Generation of certain amount of energy
    * 
    * @param amount how much energy to generate
    */
void Generator::generate(int amount)
{
    cerr << "amount: " << amount << endl;
    for (int i = 0; i < amount; i++) {
        Energy *tmp = new Energy(false);
        qu_energy_buffer.Insert(tmp);
        tmp->Passivate();
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////
////                                     GENERATOR (END)                                    ////
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
////                                     ENERGY (BEGIN)                                     ////
////////////////////////////////////////////////////////////////////////////////////////////////


void Energy::Behavior() 
{
    // cerr << "++ " << isHigh << " " << st_high_consumption.Full() << endl;
    //cerr << "++ full: " << st_capacity.Full() << " empty: " << st_capacity.Empty() << endl;
    //cerr << "++ isInit " << this->isInit << '\n';

    if (this->isInit == false && isHigh == true && ! st_high_consumption.Full()) {
        cerr << "gen -> high\n";
        this->consumption_high();
    }
    else if (this->isInit == false && isHigh == false && ! st_low_consumption.Full())
    {
        cerr << "gen -> low\n";
        this->consumption_low();
    }
    else if (! st_capacity.Full()) {
        Enter(st_capacity, 1);

        if (this->isInit == false)
        {
            if (qu_effectivity.Length() == 10) {
                for (int i = 0; i < config.battery_efficiency; i++) {
                    qu_effectivity.GetFirst()->Activate();
                }
                qu_effectivity.Clear();
            }
            qu_effectivity.Insert(this);
            Passivate();
        }
        cerr << "gen -> battery \n";
        
        while (true) {
            if (isHigh == true && ! st_high_consumption.Full())
            {
                cerr << "-> high\n";
                Leave(st_capacity, 1);
                this->consumption_high();
                break;
            }
            else if (isHigh == false && ! st_low_consumption.Full()) {
                cerr << "-> low\n";
                Leave(st_capacity, 1);
                this->consumption_low();
                break;
            }
            else if (! fa_discharge.Busy()) {
                cerr << "-> discharge\n";
                Seize(fa_discharge);
                Wait(config.t_discharge);
                Release(fa_discharge);
                break;
            }
            else {
                //cerr << "-> battery\n";
                // TODO
                qu_actual_battery_capacity.Insert(this);
                Passivate();
                //Wait(1);
            }  
        }      
    }
    else {
        // unused energy
        cerr << "gen -> trash\n";
    }
}

void Energy::consumption_high() 
{
    cerr << "st_high: " << st_high_consumption.Used() << ' ' <<st_high_consumption.Capacity() << '\n'; 
    Enter(st_high_consumption, 1);
        
    if (st_high_consumption.Full()) {
        // buffer is full of energy and this single process will continue and wait for consumtion time
        Seize(fa_high_timer);
        Leave(st_high_consumption, config.high_consume);
        Leave(st_high_checker, config.high_consume);
        Wait(Exponential(config.t_consume));
        //Wait(config.t_consume);
        Release(fa_high_timer);
    }
    else {
        // there is not enough energy
        return;
    }
}

void Energy::consumption_low()
{
    cerr << "st_low: " << st_low_consumption.Used() << ' ' <<st_low_consumption.Capacity() << '\n'; 
    Enter(st_low_consumption, 1);
        
    if (st_low_consumption.Full()) {
        // buffer is full of energy and this single process will continue and wait for consumtion time
        Seize(fa_low_timer);
        Leave(st_low_consumption, config.low_consume);
        Leave(st_low_checker, config.low_consume);
        Wait(Exponential(config.t_consume));
        //Wait(config.t_consume);
        Release(fa_low_timer);
    }
    else {
        // there is not enough energy
        return;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
////                                     ENERGY (END)                                       ////
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
////                                     CHECKER (BEGIN)                                    ////
////////////////////////////////////////////////////////////////////////////////////////////////

void Checker::Behavior()
{
    while (true)
    {
        if (isHigh == true)
        {
            std::cerr << "++CHECKER: st_high_enter\n";
            Enter(st_high_checker, 1);
            std::cerr << "++CHECKER: st_high_leave\n";
            std::cerr << "capacity: " << qu_actual_battery_capacity.Length() << '\n';
            if (! qu_energy_buffer.Empty())
            {
                qu_energy_buffer.GetFirst()->Activate();
            }
            else if (! qu_actual_battery_capacity.Empty())
            {
                Energy* tmp = dynamic_cast<Energy*> (qu_actual_battery_capacity.GetFirst());
                tmp->isInit = true;
                tmp->Activate();
            }
            else
            {
                std::cerr<< "++CHECKER: pass\n";
                Passivate();
            }
        }
        else
        {
            std::cerr << "++CHECKER: st_low_enter "<< st_low_checker.Used() << ' ' << st_low_checker.Capacity() <<"\n";

            Enter(st_low_checker, 1);
            std::cerr << "++CHECKER: st_low_leave\n";
            std::cerr << "capacity: " << qu_actual_battery_capacity.Length() << '\n';


            if (! qu_energy_buffer.Empty())
            {
                qu_energy_buffer.GetFirst()->Activate();
            }
            else if (! qu_actual_battery_capacity.Empty())
            {
                Energy* tmp = dynamic_cast<Energy*> (qu_actual_battery_capacity.GetFirst());
                tmp->isInit = true;
                tmp->Activate();
            }
            else
            {
                std::cerr<< "++CHECKER: pass\n";
                Passivate();
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
////                                     CHECKER (END)                                      ////
////////////////////////////////////////////////////////////////////////////////////////////////