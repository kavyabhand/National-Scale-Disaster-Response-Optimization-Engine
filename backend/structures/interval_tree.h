#pragma once
#include <vector>
#include <string>

struct Interval
{
    int start;
    int end;
    std::string resource;
};

struct IntervalNode
{
    Interval interval;
    int maxEnd;
    IntervalNode *left;
    IntervalNode *right;

    IntervalNode(Interval i)
    {
        interval = i;
        maxEnd = i.end;
        left = right = nullptr;
    }
};

class IntervalTree
{
    IntervalNode *root = nullptr;

    IntervalNode *insertNode(IntervalNode *node, Interval interval)
    {
        if (!node)
            return new IntervalNode(interval);

        if (interval.start < node->interval.start)
            node->left = insertNode(node->left, interval);
        else
            node->right = insertNode(node->right, interval);

        node->maxEnd = std::max(node->maxEnd, interval.end);

        return node;
    }

    void findOverlaps(IntervalNode *node, Interval query, std::vector<std::string> &result)
    {
        if (!node)
            return;

        if (node->interval.start <= query.end &&
            query.start <= node->interval.end)
        {
            result.push_back(node->interval.resource);
        }

        if (node->left && node->left->maxEnd >= query.start)
            findOverlaps(node->left, query, result);

        findOverlaps(node->right, query, result);
    }

public:
    void insert(Interval interval)
    {
        root = insertNode(root, interval);
    }

    std::vector<std::string> query(Interval interval)
    {
        std::vector<std::string> result;
        findOverlaps(root, interval, result);
        return result;
    }
};