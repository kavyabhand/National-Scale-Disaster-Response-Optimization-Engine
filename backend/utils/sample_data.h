#ifndef SAMPLE_DATA_H
#define SAMPLE_DATA_H

#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../models/region.h"

using json = nlohmann::json;

std::vector<Region> loadSampleRegions()
{
    std::ifstream file("data/live_disasters.json");
    json data;
    file >> data;

    std::vector<Region> regions;

    int id = 1;

    for (auto &item : data)
    {
        regions.push_back(
            Region(
                id++,
                item["name"],
                item["population"],
                item["damage_level"]));
    }

    return regions;
}

#endif