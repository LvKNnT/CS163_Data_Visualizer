#ifndef SLL_H
#define SLL_H

#include "raylib.h"
#include "Visualizer.h"
#include <bits/stdc++.h>

struct SLL : public Node {
    SLL(int id);
    SLL(int id, int val);
    ~SLL();

    std::unique_ptr<SLL> next;
};

class SinglyLinkedList {
public:
    SinglyLinkedList();
    ~SinglyLinkedList();

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
    std::unique_ptr<SLL> root;
    Color color = PINK;
    Color updatingColor = YELLOW;
    int MOD = 1000;

    IDGenerator idGenerator;
};

extern SinglyLinkedList singlylinkedlist;

#endif // SLL_H