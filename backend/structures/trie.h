#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

class TrieNode
{
public:
    std::unordered_map<char, TrieNode *> children;
    bool isEnd;

    TrieNode()
    {
        isEnd = false;
    }
};

class Trie
{
private:
    TrieNode *root;

    void collectWords(TrieNode *node, std::string current, std::vector<std::string> &result)
    {
        if (node->isEnd)
            result.push_back(current);

        for (auto &pair : node->children)
        {
            collectWords(pair.second, current + pair.first, result);
        }
    }

public:
    Trie()
    {
        root = new TrieNode();
    }

    void insert(std::string word)
    {
        TrieNode *node = root;

        for (char c : word)
        {
            if (!node->children[c])
                node->children[c] = new TrieNode();

            node = node->children[c];
        }

        node->isEnd = true;
    }

    bool searchPrefix(std::string prefix)
    {
        TrieNode *node = root;

        for (char c : prefix)
        {
            if (!node->children[c])
                return false;

            node = node->children[c];
        }

        return true;
    }

    std::vector<std::string> getSuggestions(std::string prefix)
    {
        TrieNode *node = root;

        for (char c : prefix)
        {
            if (!node->children[c])
                return {};

            node = node->children[c];
        }

        std::vector<std::string> result;
        collectWords(node, prefix, result);

        return result;
    }
};

#endif