#pragma once
#include <string>
struct Region
{
    int id;
    std::string name;
    int population;
    int damage_level;
    int urgency_score;
    double latitude;
    double longitude;

    Region(int i, std::string n, int p, int d, double lat, double lon)
    {
        id = i;
        name = n;
        population = p;
        damage_level = d;
        urgency_score = p * d;
        latitude = lat;
        longitude = lon;
    }
};