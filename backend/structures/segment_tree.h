#pragma once
#include <vector>

class SegmentTree
{
    std::vector<int> tree;
    int n;

    void build(std::vector<int> &arr, int node, int start, int end)
    {
        if (start == end)
        {
            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;

        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);

        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    int queryRange(int node, int start, int end, int l, int r)
    {
        if (r < start || end < l)
            return 0;

        if (l <= start && end <= r)
            return tree[node];

        int mid = (start + end) / 2;

        return queryRange(2 * node, start, mid, l, r) +
               queryRange(2 * node + 1, mid + 1, end, l, r);
    }

public:
    SegmentTree(std::vector<int> arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }

    int query(int left, int right)
    {
        return queryRange(1, 0, n - 1, left, right);
    }
};