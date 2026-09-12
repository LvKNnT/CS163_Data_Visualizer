#ifndef HASH_H
#define HASH_H

#include "raylib.h"
#include "Visualizer.h"
#include <bits/stdc++.h>

struct HashNode : public Node {
    HashNode();
    HashNode(int id);
    HashNode(int id, int val);
    ~HashNode();
};

class HashTable {
public:
    HashTable();
    ~HashTable();

    bool Import(const std::string& filePath);
    bool Export();
    void Init(int n);
    void Add(int x);
    bool Search(int x);
    void Delete(int id);
    bool Update(int id, int val);
    void Draw();

    // for setting simulation section
    void SetPoint();

private:
    int tableSize = 0; // default value bleh
    std::vector<HashNode> table;

    Color color = PINK;
    Color updatingColor = YELLOW;
    int MOD = 1000;

    IDGenerator idGenerator;
};

extern HashTable hashtable;

#endif // HASH_H