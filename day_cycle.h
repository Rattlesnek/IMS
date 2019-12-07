#pragma once

#include "simlib.h"
#include "generator.h"

class DayCycle : public Process
{
public:
    Generator *generator; 

    DayCycle() { generator = new Generator(); }

    void Behavior();
};