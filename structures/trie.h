#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <unordered_map>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEnd;

    TrieNode() {
        isEnd = false;
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(std::string word) {
        TrieNode* node = root;

        for (char c : word) {
            if (!node->children[c])
                node->children[c] = new TrieNode();

            node = node->children[c];
        }

        node->isEnd = true;
    }

    bool searchPrefix(std::string prefix) {
        TrieNode* node = root;

        for (char c : prefix) {
            if (!node->children[c])
                return false;

            node = node->children[c];
        }

        return true;
    }
};

#endif