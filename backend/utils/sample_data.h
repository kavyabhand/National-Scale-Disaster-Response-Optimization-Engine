#ifndef SAMPLE_DATA_H
#define SAMPLE_DATA_H

#include <vector>
#include "../models/region.h"

std::vector<Region> loadSampleRegions()
{

    std::vector<Region> regions;

    regions.push_back(Region(1, "Pune", 500000, 7));
    regions.push_back(Region(2, "Mumbai", 800000, 9));
    regions.push_back(Region(3, "Nashik", 300000, 6));
    regions.push_back(Region(4, "Nagpur", 450000, 8));
    regions.push_back(Region(5, "Kolhapur", 200000, 5));

    return regions;
}

#endif