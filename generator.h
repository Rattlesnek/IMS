#pragma once

#include "simlib.h"


class Checker : public Process
{
public:
    void Behavior();
};

class Generator : public Process
{
public:
    Checker *checker;

    Generator() { checker = new Checker(); }

    void Behavior();
};


class Energy : public Process
{
public:
    void Behavior();

    void consumption_high();

    void battery_switch();
};

class SelfDischarge : public Process
{
public:
    void Behavior();
};
