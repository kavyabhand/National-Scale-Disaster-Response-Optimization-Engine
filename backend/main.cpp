#include <iostream>
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

    std::cout << "Regions Loaded: " << regions.size() << std::endl;

    std::cout << "\nPrefix Search: Pu -> ";
    if (trie.searchPrefix("Pu"))
        std::cout << "Found region starting with Pu\n";

    std::cout << "\nTotal Population (0-2): ";
    std::cout << seg.rangeQuery(0, 2) << std::endl;

    std::cout << "\nRescue Priority Order:\n";

    while (!pq.empty())
    {
        Region r = pq.extractMax();
        std::cout << r.name << " | urgency: " << r.urgency_score << std::endl;
    }

    return 0;
}