#pragma once
#include <vector>
#include "../models/region.h"

struct QuadBoundary
{
    double minLat, maxLat;
    double minLon, maxLon;

    bool contains(double lat, double lon)
    {
        return lat >= minLat && lat <= maxLat &&
               lon >= minLon && lon <= maxLon;
    }
};

class QuadTree
{
    QuadBoundary boundary;
    int capacity;
    std::vector<Region> points;

    bool divided = false;

    QuadTree *northeast = nullptr;
    QuadTree *northwest = nullptr;
    QuadTree *southeast = nullptr;
    QuadTree *southwest = nullptr;

    void subdivide()
    {
        double midLat = (boundary.minLat + boundary.maxLat) / 2;
        double midLon = (boundary.minLon + boundary.maxLon) / 2;

        northeast = new QuadTree({midLat, boundary.maxLat, midLon, boundary.maxLon}, capacity);
        northwest = new QuadTree({midLat, boundary.maxLat, boundary.minLon, midLon}, capacity);
        southeast = new QuadTree({boundary.minLat, midLat, midLon, boundary.maxLon}, capacity);
        southwest = new QuadTree({boundary.minLat, midLat, boundary.minLon, midLon}, capacity);

        divided = true;
    }

public:
    QuadTree(QuadBoundary b, int cap = 4) : boundary(b), capacity(cap) {}

    bool insert(Region region)
    {
        if (!boundary.contains(region.latitude, region.longitude))
            return false;

        if (points.size() < capacity)
        {
            points.push_back(region);
            return true;
        }

        if (!divided)
            subdivide();

        return northeast->insert(region) ||
               northwest->insert(region) ||
               southeast->insert(region) ||
               southwest->insert(region);
    }

    int countPoints()
    {
        int total = points.size();

        if (divided)
        {
            total += northeast->countPoints();
            total += northwest->countPoints();
            total += southeast->countPoints();
            total += southwest->countPoints();
        }

        return total;
    }
};