#pragma once
#include <vector>
#include <algorithm>
#include "../models/region.h"

struct AVLNode
{
    Region data;
    AVLNode *left;
    AVLNode *right;
    int height;

    AVLNode(Region r) : data(r), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree
{
    AVLNode *root = nullptr;

    int height(AVLNode *node)
    {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLNode *node)
    {
        return node ? height(node->left) - height(node->right) : 0;
    }

    AVLNode *rotateRight(AVLNode *y)
    {
        AVLNode *x = y->left;
        AVLNode *t2 = x->right;

        x->right = y;
        y->left = t2;

        y->height = 1 + std::max(height(y->left), height(y->right));
        x->height = 1 + std::max(height(x->left), height(x->right));

        return x;
    }

    AVLNode *rotateLeft(AVLNode *x)
    {
        AVLNode *y = x->right;
        AVLNode *t2 = y->left;

        y->left = x;
        x->right = t2;

        x->height = 1 + std::max(height(x->left), height(x->right));
        y->height = 1 + std::max(height(y->left), height(y->right));

        return y;
    }

    AVLNode *insertNode(AVLNode *node, Region region)
    {
        if (!node)
            return new AVLNode(region);

        if (region.urgency_score < node->data.urgency_score)
            node->left = insertNode(node->left, region);
        else
            node->right = insertNode(node->right, region);

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        if (balance > 1 && region.urgency_score < node->left->data.urgency_score)
            return rotateRight(node);

        if (balance < -1 && region.urgency_score > node->right->data.urgency_score)
            return rotateLeft(node);

        if (balance > 1 && region.urgency_score > node->left->data.urgency_score)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && region.urgency_score < node->right->data.urgency_score)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void reverseInorder(AVLNode *node, std::vector<Region> &result)
    {
        if (!node)
            return;

        reverseInorder(node->right, result);
        result.push_back(node->data);
        reverseInorder(node->left, result);
    }

    // ✅ ONLY ONE COPY (KEEP PRIVATE)
    void collectAboveThreshold(AVLNode *node, int threshold, std::vector<Region> &result)
    {
        if (!node)
            return;

        if (node->data.urgency_score >= threshold)
        {
            collectAboveThreshold(node->right, threshold, result);
            result.push_back(node->data);
            collectAboveThreshold(node->left, threshold, result);
        }
        else
        {
            collectAboveThreshold(node->right, threshold, result);
        }
    }

public:
    void insert(Region region)
    {
        root = insertNode(root, region);
    }

    std::vector<Region> getSortedDescending()
    {
        std::vector<Region> result;
        reverseInorder(root, result);
        return result;
    }

    // (Optional API wrapper — SAFE way to expose it)
    std::vector<Region> collectAboveThreshold(int threshold)
    {
        std::vector<Region> result;
        collectAboveThreshold(root, threshold, result);
        return result;
    }
};