#pragma once
#include <vector>

class DisjointSet
{
    std::vector<int> parent;
    std::vector<int> rank;

public:
    DisjointSet(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);

        return parent[x];
    }

    void unite(int x, int y)
    {
        int px = find(x);
        int py = find(y);

        if (px == py)
            return;

        if (rank[px] < rank[py])
        {
            parent[px] = py;
        }
        else if (rank[px] > rank[py])
        {
            parent[py] = px;
        }
        else
        {
            parent[py] = px;
            rank[px]++;
        }
    }

    int countSets()
    {
        int count = 0;

        for (int i = 0; i < parent.size(); i++)
        {
            if (find(i) == i)
                count++;
        }

        return count;
    }
};