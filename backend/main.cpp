#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include "models/region.h"
#include "structures/priority_queue.h"
#include "structures/trie.h"
#include "structures/segment_tree.h"
#include "structures/union_find.h"
#include "utils/sample_data.h"

int main()
{
    std::vector<Region> regions = loadSampleRegions();

    PriorityQueue pq;
    Trie trie;
    std::vector<int> populations;

    for (auto &r : regions)
    {
        pq.insert(r);
        trie.insert(r.name);
        populations.push_back(r.population);
    }

    SegmentTree seg(populations);

    UnionFind uf(regions.size());

    uf.unite(0, 1);
    uf.unite(1, 2);

    json output;

    output["total_regions"] = regions.size();
    output["population_affected"] = seg.rangeQuery(0, 2);

    std::vector<std::string> resources = {
        "Team Alpha",
        "Team Beta",
        "Medical Unit 1",
        "Helicopter Squad",
        "Supply Convoy"};

    int resourceIndex = 0;

    while (!pq.empty())
    {
        Region r = pq.extractMax();

        output["priority_order"].push_back({{"name", r.name},
                                            {"population", r.population},
                                            {"damage_level", r.damage_level},
                                            {"urgency_score", r.urgency_score},
                                            {"latitude", r.latitude},
                                            {"longitude", r.longitude}});

        if (resourceIndex < resources.size())
        {
            output["resource_allocations"].push_back({{"resource", resources[resourceIndex]},
                                                      {"assigned_region", r.name},
                                                      {"urgency_score", r.urgency_score}});

            resourceIndex++;
        }
    }

    std::ofstream file("data/results.json");
    file << output.dump(4);
    file.close();

    std::cout << "Results exported to data/results.json\n";

    return 0;
}