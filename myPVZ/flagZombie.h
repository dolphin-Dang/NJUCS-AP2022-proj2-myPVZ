#pragma once
#include "Zombies.h"

class flagZombie :
    public Zombies
{
public:
    flagZombie();
    ~flagZombie();
    void advance(int phase);

    bool dying;
    int shootSpan;
    int shootCounter;

};

