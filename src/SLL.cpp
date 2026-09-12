#include "SLL.h"

SinglyLinkedList singlylinkedlist;

SinglyLinkedList::SinglyLinkedList() {}
SinglyLinkedList::~SinglyLinkedList() {}

void SinglyLinkedList::Draw() {
    std::vector<Node> nodes;
    std::vector<Edge> edges;

    SLL* temp = root.get();
    while(temp != nullptr) {
        nodes.push_back(*temp);
        
        // modify the off-edge properties
        if(temp->val != -1) nodes.back().text = nodes.back().subText = std::to_string(temp->val);
        else nodes.back().text = nodes.back().subText = "nullptr";
        
        // move to the next, add edge
        if(temp->next != nullptr) edges.push_back({temp->id, temp->next->id});
        temp = temp->next.get();
    }
    temp = nullptr;

    visualizer.SetData(nodes, edges);
}

void SinglyLinkedList::SetPoint() {
    std::vector<Point> points = visualizer.GetPoint();
    
    SLL* temp = root.get();
    while(temp != nullptr) {
        while(temp->id >= points.size()) {
            points.push_back(Point());
        }

        temp = temp->next.get();
    }

    visualizer.SetPoint(points);
}

SLL::SLL(int id) : Node(id, -1), next(nullptr) {}
SLL::SLL(int id, int val) : Node(id, val), next(nullptr) {}
SLL::~SLL() {}

bool SinglyLinkedList::Import(const std::string& filePath) {
    // import from file
    std::fstream fin(filePath, std::ios::in);
    if(!fin.is_open()) {
        return false;
    }

    std::cerr << "Import SLL from " << filePath << "\n";

    std::string line;
    std::getline(fin, line);
    std::stringstream ss(line);
    
    int val;
    std::vector<int> values;
    while(ss >> val) {
        values.push_back(val);
    }
    if(!ss.eof()) {
        return false;
    }
    
    idGenerator.ResetID();
    root.reset();

    if(values.size() == 0) {
        root = std::make_unique<SLL>(idGenerator.GetID());
        root->color = updatingColor;
        Draw();
        root->color = color;
        Draw();
        return true;
    }

    root = std::make_unique<SLL>(idGenerator.GetID(), values[0]);
    root->color = updatingColor;
    Draw();
    root->color = color;

    SLL* temp = root.get();
    for(int i=1;i<values.size();++i) {
        temp->next = std::make_unique<SLL>(idGenerator.GetID(), values[i]);

        temp = temp->next.get();
        temp->color = updatingColor;
        Draw();
        temp->color = color;
    }

    Draw();
    temp = nullptr;

    std::cerr << "Import SLL successfully\n";

    fin.close();

    return true;
}

bool SinglyLinkedList::Export() {
    const std::string filePath = "../save/SLL/SLL.txt";
    std::fstream fout(filePath, std::ios::out);

    SLL* temp = root.get();
    while(temp != nullptr) {
        if(temp->val != -1) {
            fout << temp->val << " ";
        }
        temp = temp->next.get();
    }

    temp = nullptr;
    fout.close();

    return true;
}

void SinglyLinkedList::Init(int n) {
    // delete all singly linked list SLL
    idGenerator.ResetID();
    root.reset();

    if(n == 0) {
        root = std::make_unique<SLL>(idGenerator.GetID());
        root->color = updatingColor;
        Draw();
        root->color = color;
        Draw();
        return;
    }

    root = std::make_unique<SLL>(idGenerator.GetID(), 1);
    root->color = updatingColor;
    Draw();
    root->color = color;

    SLL* temp = root.get();
    for(int i=1;i<n;++i) {
        temp->next = std::make_unique<SLL>(idGenerator.GetID(), i+1);

        temp = temp->next.get();
        temp->color = updatingColor;
        Draw();
        temp->color = color;
    }

    Draw();
    temp = nullptr;
}

void SinglyLinkedList::Add(int x) {
    if(root->val == -1) {
        root->val = x;
        root->color = updatingColor;
        Draw();
        root->color = color;
        Draw();
    }
    else {
        SLL* temp = root.get();
        temp->color = updatingColor;
        Draw();
        temp->color = color;
        
        while(temp->next != nullptr) {
            temp->next->color = updatingColor;
            Draw();
            temp->next->color = color;
            
            temp = temp->next.get();
        }
        temp->next = std::make_unique<SLL>(idGenerator.GetID(), x);
        temp->next->color = this->updatingColor;
        Draw();
        temp->next->color = color;

        Draw();
        temp = nullptr;
    }
}

bool SinglyLinkedList::Search(int x) {
    if(root->val == -1) {
        root->color = updatingColor;
        Draw();
        root->color = color;
        Draw();

        return false;
    }
    else {
        bool yes = false;
        SLL* temp = root.get();
        temp->color = updatingColor;
        Draw();
        if(temp->val == x) {
            yes = true;
        }
        temp->color = color;
        
        while(temp->next != nullptr && !yes) {
            temp->next->color = updatingColor;
            Draw();

            temp->next->color = color;
            if(temp->next->val == x) {
                yes = true;
                break;
            }
            Draw();
            
            temp = temp->next.get();
        }

        return yes;
    }

    return false;
}

void SinglyLinkedList::Delete(int x) {
    if(root->val == -1) {
        root->color = updatingColor;
        Draw();
        root->color = color;
        Draw();

        return;
    }
    else {
        bool yes = false;
        SLL* temp = root.get();
        temp->color = updatingColor;
        Draw();
        if(temp->val == x) {
            yes = true;
            
            std::unique_ptr<SLL> del = std::move(root);
            root = std::move(del->next);

            if(root == nullptr) {
                root = std::make_unique<SLL>(del->id);
            }
            else idGenerator.RemoveID(del->id);

            Draw();
            return;
        }
        temp->color = color;

        
        while(temp->next != nullptr && !yes) {
            temp->next->color = updatingColor;
            Draw();

            temp->next->color = color;
            if(temp->next->val == x) {
                yes = true;
                break;
            }
            Draw();
            
            temp = temp->next.get();
        }

        if(yes) {
            std::unique_ptr<SLL> del = std::move(temp->next);
            temp->next = std::move(del->next);

            idGenerator.RemoveID(del->id);
            Draw();
        }

        temp = nullptr;
        return;
    }

    return;
}

bool SinglyLinkedList::Update(int id, int val) {
    if(id == -1) return false;

    if(root->val == -1) {
        root->color = updatingColor;
        Draw();
        root->color = color;
        Draw();

        return false;
    }
    else {
        bool yes = false;
        SLL* temp = root.get();
        temp->color = updatingColor;
        Draw();
        if(temp->id == id) {
            temp->val = val;
            Draw();
            yes = true;
        }
        temp->color = color;
        
        while(temp->next != nullptr && !yes) {
            temp->next->color = updatingColor;
            Draw();

            if(temp->next->id == id) {
                temp->next->val = val;
                Draw();
                temp->next->color = color;
                yes = true;
                break;
            }
            temp->next->color = color;
            Draw();
            
            temp = temp->next.get();
        }

        temp = nullptr;
        return yes;
    }

    return false;
}