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
    //cerr << "gen: " << st.Full() << ' ' << st.Empty() << endl;
    // generator of energy
    while (true) {
        // generate after some time
        Wait(config.t_generate);

        // if its night stop generation
        if (isDay == false)
            break;

        //std::cout << "sunny\n";
        // according to weather generate certain amount
        if (weather_type == "sunny") {
            //std::cout << "sunny\n";
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
        (new Energy(false))->Activate();
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////
////                                     GENERATOR (END)                                    ////
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
////                                     WEATHER (BEGIN)                                    ////
////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * @brief 
 * 
 */
void Weather::Behavior()
{
    // set weather
    int uni = Uniform(0, 100);
    //std::cout << uni << std::endl;
    if (uni <= config.p_sunny) {
        weather_type = "sunny";
        cerr << "Weather: sunny\n"; 
    }
    else if (config.p_sunny < uni && uni <= config.p_sunny + config.p_middle) {
        weather_type = "middle";
        cerr << "Weather: middle\n";
    }
    else {
        weather_type = "cloudy";
        cerr << "Weather: cloudy\n";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
////                                     WEATHER (END)                                      ////
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
        this->consumption_high();;
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
                Wait(1);
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
    //cerr << "st_high: " << st_high_consumption.Used() << ' ' <<st_high_consumption.Capacity() << '\n'; 
    Enter(st_high_consumption, 1);
        
    if (st_high_consumption.Full()) {
        // buffer is full of energy and this single process will continue and wait for consumtion time
        Seize(fa_high_timer);
        Leave(st_high_consumption, config.high_consume);
        Wait(Exponential(config.t_consume));
        Release(fa_high_timer);
    }
    else {
        // there is not enough energy
        return;
    }
}

void Energy::consumption_low()
{
    //cerr << "st_low: " << st_low_consumption.Used() << ' ' <<st_low_consumption.Capacity() << '\n'; 
    Enter(st_low_consumption, 1);
        

    if (st_low_consumption.Full()) {
        // buffer is full of energy and this single process will continue and wait for consumtion time
        Seize(fa_low_timer);
        Leave(st_low_consumption, config.low_consume);
        Wait(Exponential(config.t_consume));
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