#include "HASH.h"

HashTable hashtable;

HashTable::HashTable() {}

HashTable::~HashTable() {}

void HashTable::Draw() {
    std::vector<Node> nodes;
    std::vector<Edge> edges;

    for (int i = 0; i < tableSize; ++i) {
        nodes.push_back(table[i]);

        // modify the off-edge properties
        if (table[i].val != -1) {
            nodes.back().text = nodes.back().subText = std::to_string(table[i].val);
        } else {
            nodes.back().text = nodes.back().subText = "nullptr";
        }

        // move to the next, add edge
        if(i+1 < tableSize) {
            edges.push_back({table[i].id, table[i+1].id});
        }
    }

    visualizer.SetData(nodes, edges);
}

void HashTable::SetPoint() {
    std::vector<Point> points = visualizer.GetPoint();

    for (int i = 0; i < tableSize; ++i) {
        while(table[i].id >= points.size()) {
            points.push_back(Point());
        }
    }

    visualizer.SetPoint(points);
}

HashNode::HashNode() : Node(-1, -1) {}
HashNode::HashNode(int id) : Node(id, -1) {}
HashNode::HashNode(int id, int val) : Node(id, val) {}
HashNode::~HashNode() {}

bool HashTable::Import(const std::string& filePath) {
    std::fstream fin(filePath, std::ios::in);
    if (!fin.is_open()) return false;

    std::cerr << "Import HashTable from " << filePath << "\n";

    std::string line;
    std::getline(fin, line);
    std::stringstream ss(line);

    int size;
    if(!(ss >> size)) return false;
    ss >> size;
    if (size <= 0) return false;

    std::getline(fin, line);
    ss.clear();
    ss.str(line);

    int val;
    std::vector<int> vals;
    while (ss >> val) {
        vals.push_back(val);
    }
    if (!ss.eof()) return false;

    table.clear();
    idGenerator.ResetID();

    tableSize = size;
    table.assign(tableSize, HashNode());
    for(int i=0;i<tableSize;++i) {
        table[i].id = idGenerator.GetID();
        table[i].color = color;
    }
    for (int i = 0; i < tableSize; ++i) {
        table[i].color = updatingColor;
        Draw();
        table[i].color = color;
    }

    std::cerr << "Import HashTable successfully\n";
    fin.close();
    return true;
}

bool HashTable::Export() {
    const std::string filePath = "../save/HASH/HASH.txt";
    std::fstream fout(filePath, std::ios::out);

    fout << tableSize << "\n";
    for (int i = 0; i < tableSize; ++i) {
        fout << table[i].val << " ";
    }

    fout.close();
    return true;
}

void HashTable::Init(int n) {
    table.clear();
    idGenerator.ResetID();

    tableSize = n;
    table.assign(tableSize, HashNode());
    for(int i=0;i<tableSize;++i) {
        table[i].id = idGenerator.GetID();
        table[i].color = color;
    }
    for (int i = 0; i < tableSize; ++i) {
        table[i].color = updatingColor;
        Draw();
        table[i].color = color;
    }
    Draw();
}

void HashTable::Add(int val) {
    int pos = val % tableSize;

    int counter = 0;
    while(table[pos].val != -1 && counter < tableSize) {
        table[pos].color = updatingColor;
        Draw();
        table[pos].color = color;
        pos = (pos + 1) % tableSize;
        counter++;
    }

    if(counter < tableSize) {
        table[pos].val = val;
        table[pos].color = updatingColor;
        Draw();
        
        table[pos].val = val;
        Draw();

        table[pos].color = color;
        Draw();
    }
}

bool HashTable::Search(int val) {
    int pos = val % tableSize;

    int counter = 0;
    while(table[pos].val != val && counter < tableSize) {
        table[pos].color = updatingColor;
        Draw();
        table[pos].color = color;
        pos = (pos + 1) % tableSize;
        counter++;
    }

    if(counter < tableSize) {
        table[pos].val = val;
        table[pos].color = updatingColor;
        Draw();

        table[pos].val = val;
        Draw();

        table[pos].color = color;
        Draw();

        return true;
    }
    
    return false;
}

void HashTable::Delete(int val) {
    int pos = val % tableSize;

    int counter = 0;
    while(table[pos].val != val && counter < tableSize) {
        table[pos].color = updatingColor;
        Draw();
        table[pos].color = color;
        pos = (pos + 1) % tableSize;
        counter++;
    }

    if(counter < tableSize) {
        table[pos].val = val;
        table[pos].color = updatingColor;
        Draw();

        table[pos].val = -1;
        Draw();

        table[pos].color = color;
        Draw();
    }
}

bool HashTable::Update(int id, int val) {
    int pos = val % tableSize;

    int counter = 0;
    while(table[pos].id != id && counter < tableSize) {
        table[pos].color = updatingColor;
        Draw();
        table[pos].color = color;
        pos = (pos + 1) % tableSize;
        counter++;
    }

    if(counter < tableSize) {
        table[pos].val = val;
        table[pos].color = updatingColor;
        Draw();

        table[pos].val = val;
        Draw();

        table[pos].color = color;
        Draw();
        return true;
    }
    
    return false;
}