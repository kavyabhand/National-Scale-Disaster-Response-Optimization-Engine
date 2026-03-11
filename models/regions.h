#ifndef REGION_H
#define REGION_H

#include <string>

struct Region
{
    int id;
    std::string name;
    int population;
    int damage_level;
    int urgency_score;

    Region() {}

    Region(int i, std::string n, int p, int d)
    {
        id = i;
        name = n;
        population = p;
        damage_level = d;
        urgency_score = p * d;
    }
};

#endif