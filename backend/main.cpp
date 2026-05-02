#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

#include "models/region.h"
#include "structures/priority_queue.h"
#include "structures/avl_tree.h"
#include "structures/quad_tree.h"
#include "structures/trie.h"
#include "utils/sample_data.h"

using json = nlohmann::json;

int main()
{
    std::vector<Region> regions = loadSampleRegions();

    // Core data structures
    PriorityQueue pq;
    AVLTree avl;
    QuadTree quad({-90.0, 90.0, -180.0, 180.0});
    Trie trie;

    json output;

    // Initialize JSON structure safely
    output["total_regions"] = 0;
    output["population_affected"] = 0;

    output["priority_order"] = json::array();
    output["resource_allocations"] = json::array();
    output["avl_sorted_regions"] = json::array();

    output["spatial_analysis"] = {
        {"indexed_regions", 0},
        {"partitioning", "Quad Tree Spatial Indexing Active"}};

    std::vector<std::string> resources = {
        "Team Alpha",
        "Team Beta",
        "Medical Unit 1",
        "Helicopter Squad",
        "Supply Convoy"};

    int totalPopulation = 0;

    // Build all structures
    for (const auto &region : regions)
    {
        pq.insert(region);
        avl.insert(region);
        quad.insert(region);
        trie.insert(region.name);

        totalPopulation += region.population;
    }

    output["total_regions"] = regions.size();
    output["population_affected"] = totalPopulation;

    int resourceIndex = 0;

    // Priority-based processing
    while (!pq.empty())
    {
        Region r = pq.extractMax();

        output["priority_order"].push_back({{"name", r.name},
                                            {"population", r.population},
                                            {"damage_level", r.damage_level},
                                            {"urgency_score", r.urgency_score},
                                            {"latitude", r.latitude},
                                            {"longitude", r.longitude}});

        if (resourceIndex < (int)resources.size())
        {
            output["resource_allocations"].push_back({{"resource", resources[resourceIndex]},
                                                      {"assigned_region", r.name},
                                                      {"urgency_score", r.urgency_score}});

            resourceIndex++;
        }
    }

    // Spatial analysis summary (AFTER insertions)
    output["spatial_analysis"]["indexed_regions"] = quad.countPoints();

    // AVL sorted output (descending urgency)
    std::vector<Region> sortedRegions = avl.getSortedDescending();

    for (const auto &r : sortedRegions)
    {
        output["avl_sorted_regions"].push_back({{"name", r.name},
                                                {"urgency_score", r.urgency_score}});
    }

    // Write output file
    std::ofstream file("data/results.json");
    file << output.dump(4);
    file.close();

    std::cout << "Results exported to data/results.json\n";

    return 0;
}