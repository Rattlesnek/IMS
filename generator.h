#pragma once 

#include "simlib.h"


class Generator : public Process
{
public:
    void Behavior();

    /**
     * @brief Generation of certain amount of energy
     * 
     * @param amount how much energy to generate
     */
    void generate(int amount);
};


class Weather : public Process
{
public:
    void Behavior();
};


class Energy : public Process
{
public:
    Energy(bool _isInit) { isInit = _isInit; }

    void Behavior();

    void consumption_high();

    void consumption_low();


    bool isInit;
};

