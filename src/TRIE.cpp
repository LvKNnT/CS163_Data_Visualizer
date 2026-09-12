#include "TRIE.h"

TRIETree trietree;

TRIETree::TRIETree() {}
TRIETree::~TRIETree() {}

void TRIETree::Draw() {
    std::vector<Node> nodes;
    std::vector<Edge> edges;

    std::queue<TRIENode*> q;
    q.push(root.get());
    
    while(!q.empty()) {
        TRIENode* temp = q.front();
        q.pop();

        if(temp == nullptr) continue;

        nodes.push_back(*temp);
        
        // modify the off-edge properties
        if(temp->val != -1) {
            nodes.back().text = char(temp->val);
            nodes.back().subText = temp->s;
        }
        else {
            nodes.back().text = "nullptr";
            nodes.back().subText = "nullptr";
        }
        
        // move to the next, add edge
        for(auto& child : temp->children) {
            edges.push_back({temp->id, child.second->id});
            q.push(child.second.get());
        }
    }

    visualizer.SetData(nodes, edges);
}

void TRIETree::SetPoint() {
    std::vector<Point> points = visualizer.GetPoint();
    
    std::queue<TRIENode*> q;
    q.push(root.get());

    while (!q.empty()) {
        TRIENode* temp = q.front();
        q.pop();

        if (temp == nullptr) continue;

        while (temp->id >= points.size()) {
            points.push_back(Point());
        }

        for(auto& child : temp->children) {
            q.push(child.second.get());
        }
    }

    visualizer.SetPoint(points);
}

TRIENode::TRIENode() : Node() {}
TRIENode::TRIENode(int id) : Node(id, -1) {}
TRIENode::TRIENode(int id, int val) : Node(id, val) {}
TRIENode::~TRIENode() {}

bool TRIETree::Import(const std::string& filePath) {
    // import from file
    std::fstream fin(filePath, std::ios::in);
    if (!fin.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return false;
    }

    std::cerr << "Import TRIENode from " << filePath << "\n";
    std::string line;
    std::getline(fin, line);
    std::stringstream ss(line);

    std::string word;
    std::vector<std::string> words;
    while (ss >> word) {
        words.push_back(word);
    }

    idGenerator.ResetID();
    root.reset();

    for(const std::string& w : words) {
        if (w.empty()) continue; // Skip empty words
        Add(w);
    }

    Draw();

    std::cerr << "Import TRIENode successfully\n";

    fin.close();
    return true;
}

bool TRIETree::Export() {
    const std::string filePath = "../save/TRIE/TRIE.txt";
    std::fstream fout(filePath, std::ios::out);

    std::queue<TRIENode*> q;
    std::vector<std::string> words;
    if (root) q.push(root.get());

    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i) {
            TRIENode* temp = q.front();
            q.pop();

            if(temp->isEndOfWord) {
                words.push_back(temp->s);
            }

            for (const auto& child : temp->children) {
                q.push(child.second.get());
            }
        }
    }

    for (const std::string& word : words) {
        fout << word << " ";
    }

    fout.close();

    return true;
}

void TRIETree::Init(std::string x) {
    idGenerator.ResetID();
    root.reset();

    if (x.empty()) {
        root = std::make_unique<TRIENode>(idGenerator.GetID());
        root->color = updatingColor;
        Draw();
        root->color = color;
        Draw();
        return;
    }

    // Insert values 1 to n into the TRIE tree
    root = std::make_unique<TRIENode> (idGenerator.GetID());
    root->color = updatingColor;
    Draw();
    root->color = color;

    TRIENode* cur = root.get();
    for(const char& c : x) {
        if(!cur->children[c]) {
            cur->children[c] = std::make_unique<TRIENode>(idGenerator.GetID(), int(c));
            cur->children[c]->s = cur->s + c; // Store the string representation
        }
        cur = cur->children[c].get();
        cur->color = updatingColor;
        Draw();
        cur->color = color;
    }

    cur->isEndOfWord = true;
}

void TRIETree::Add(std::string x) {
    TRIENode* cur = root.get();
    cur->color = updatingColor;
    Draw();
    cur->color = color;

    for(const char& c : x) {
        if(!cur->children[c]) {
            cur->children[c] = std::make_unique<TRIENode>(idGenerator.GetID(), int(c));
            cur->children[c]->s = cur->s + c; // Store the string representation
        }
        cur = cur->children[c].get();
        cur->color = updatingColor;
        Draw();
        cur->color = color;
    }

    cur->isEndOfWord = true;
}

bool TRIETree::Search(std::string x) {
    TRIENode* cur = root.get();
    cur->color = updatingColor;
    Draw();

    for(const char& c : x) {
        if(!cur->children[c]) {
            cur->color = color;
            Draw();
            return false; // Not found
        }
        cur = cur->children[c].get();
        cur->color = updatingColor;
        Draw();
    }

    if(cur->isEndOfWord) {
        cur->color = color;
        Draw();
        return true; // Found
    } else {
        cur->color = color;
        Draw();
        return false; // Not found
    }
}

void TRIETree::Delete(std::string x) {
    if(!Search(x)) return;

    TRIENode* cur = root.get();
    cur->color = updatingColor;
    Draw();
    cur->color = color;

    auto IsEmpty = [&](std::unique_ptr<TRIENode>& cur) {
        for(char i = 'a'; i <= 'z'; ++i) {
            if(!cur->children[i]) continue;
            return false;
        }

        return true;
    };

    std::function<void(std::unique_ptr<TRIENode>&, int)> DeleteNode = [&](std::unique_ptr<TRIENode>& cur, int pos) {
        if(!cur) return;

        cur->color = updatingColor;
        Draw();
        cur->color = color;
        
        if(pos == x.size()) {
            if(cur->isEndOfWord) {
                cur->isEndOfWord = false;
            }

            if(IsEmpty(cur)) {
                idGenerator.RemoveID(cur->id);
                cur.reset();
            }

            return;
        }

        DeleteNode(cur->children[x[pos]], pos + 1);
        if(IsEmpty(cur) && cur->isEndOfWord == false && cur->val != -1) {
            std::cerr << cur->s << "\n";
            idGenerator.RemoveID(cur->id);
            cur.reset();
        }
        return;
    };

    DeleteNode(root, 0);
    Draw();
}

bool TRIETree::Update(int id, std::string x) {
    if(id == -1 || x.empty()) return false;

    TRIENode* target = nullptr;
    std::string oldVal;

    // Find the node with the given id
    std::function<TRIENode*(TRIENode*)> findById = [&](TRIENode* node) -> TRIENode* {
        if (!node) return nullptr;
        if (node->id == id) return node;
        for (auto& child : node->children) {
            TRIENode* res = findById(child.second.get());
            if (res) return res;
        }
        return nullptr;
    };

    target = findById(root.get());
    if (!target) return false;
    oldVal = target->s;

    // Remove the node with old value
    Delete(oldVal);

    // Insert the node with new value 
    Add(x);
    
    return true;
}