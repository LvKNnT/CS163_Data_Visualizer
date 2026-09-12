#ifndef TRIE_H
#define TRIE_H

#include "raylib.h"
#include "Visualizer.h"
#include <bits/stdc++.h>

// we should notice that var val in the Node is in type int
// hence we have to convert from char to int for storing
// and reverse it to output on the screen

struct TRIENode : public Node {
    TRIENode();
    TRIENode(int id);
    TRIENode(int id, int val);
    ~TRIENode();

    std::unordered_map<char, std::unique_ptr<TRIENode>> children; // children nodes
    bool isEndOfWord = false; // true if this node is the end of a word
    std::string s;
};

class TRIETree {
public:
    TRIETree();
    ~TRIETree();

    bool Import(const std::string& filePath);
    bool Export();
    void Init(std::string x);
    void Add(std::string x);
    bool Search(std::string x);
    void Delete(std::string x);
    bool Update(int id, std::string x);
    void Draw();

    // for setting simulation section
    void SetPoint();

private:
    std::unique_ptr<TRIENode> root;

    Color color = PINK;
    Color updatingColor = YELLOW;
    int MOD = 1000;

    IDGenerator idGenerator;
};

extern TRIETree trietree;

#endif // TRIE_H