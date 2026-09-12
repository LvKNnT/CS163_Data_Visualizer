#ifndef AVL_H
#define AVL_H

#include "raylib.h"
#include "Visualizer.h"
#include <bits/stdc++.h>

struct AVLNode : public Node {
    AVLNode();
    AVLNode(int id);
    AVLNode(int id, int val);
    ~AVLNode();

    int height = 1; // height of the node
    std::unique_ptr<AVLNode> left;
    std::unique_ptr<AVLNode> right;
};

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

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
    std::unique_ptr<AVLNode> root;

    Color color = PINK;
    Color updatingColor = YELLOW;
    int MOD = 1000;

    IDGenerator idGenerator;
};

extern AVLTree avltree;

#endif // AVL_H