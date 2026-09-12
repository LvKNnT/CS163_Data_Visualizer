#include "AVL.h"

AVLTree avltree;

AVLTree::AVLTree() {}
AVLTree::~AVLTree() {}

void AVLTree::Draw() {
    std::vector<Node> nodes;
    std::vector<Edge> edges;

    std::queue<AVLNode*> q;
    q.push(root.get());
    
    while(!q.empty()) {
        AVLNode* temp = q.front();
        q.pop();

        if(temp == nullptr) continue;

        nodes.push_back(*temp);
        
        // modify the off-edge properties
        if(temp->val != -1) nodes.back().text = nodes.back().subText = std::to_string(temp->val);
        else nodes.back().text = nodes.back().subText = "nullptr";
        
        // move to the next, add edge
        if(temp->left != nullptr) {
            edges.push_back({temp->id, temp->left->id});
            q.push(temp->left.get());
        }
        if(temp->right != nullptr) {
            edges.push_back({temp->id, temp->right->id});
            q.push(temp->right.get());
        }
    }

    visualizer.SetData(nodes, edges);
}

void AVLTree::SetPoint() {
    std::vector<Point> points = visualizer.GetPoint();
    
    std::queue<AVLNode*> q;
    q.push(root.get());

    while (!q.empty()) {
        AVLNode* temp = q.front();
        q.pop();

        if (temp == nullptr) continue;

        while (temp->id >= points.size()) {
            points.push_back(Point());
        }

        if (temp->left) q.push(temp->left.get());
        if (temp->right) q.push(temp->right.get());
    }

    visualizer.SetPoint(points);
}

AVLNode::AVLNode() : Node() {}
AVLNode::AVLNode(int id) : Node(id, -1) {}
AVLNode::AVLNode(int id, int val) : Node(id, val) {}
AVLNode::~AVLNode() {}

bool AVLTree::Import(const std::string& filePath) {
    // import from file
    std::fstream fin(filePath, std::ios::in);
    if(!fin.is_open()) {
        return false;
    }

    std::cerr << "Import AVLNode from " << filePath << "\n";

    std::string line;
    std::getline(fin, line);
    std::stringstream ss(line);

    int val;
    std::vector<int> values;
    while (ss >> val) {
        values.push_back(val);
    }
    if (!ss.eof()) {
        return false;
    }

    idGenerator.ResetID();
    root.reset();

    for (int v : values) {
        if(v == -1) continue;
        this->Add(v);
    }

    Draw();

    std::cerr << "Import AVLNode successfully\n";

    fin.close();
    return true;
}

bool AVLTree::Export() {
    const std::string filePath = "../save/AVL/AVL.txt";
    std::fstream fout(filePath, std::ios::out);

    std::queue<AVLNode*> q;
    if (root) q.push(root.get());

    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i) {
            AVLNode* temp = q.front();
            q.pop();

            if (temp == nullptr) {
                fout << -1 << " ";
                continue;
            }

            if (temp->val != -1) {
                fout << temp->val << " ";
            }

            if (temp->left) q.push(temp->left.get());
            if (temp->right) q.push(temp->right.get());
        }
    }

    fout << std::endl;

    fout.close();
    return true;
}

void AVLTree::Init(int n) {
    // Reset the tree and ID generator
    idGenerator.ResetID();
    root.reset();

    if (n == 0) {
        root = std::make_unique<AVLNode>(idGenerator.GetID());
        root->color = updatingColor;
        Draw();
        root->color = color;
        Draw();
        return;
    }

    // Insert values 1 to n into the AVL tree using AVL insert logic
    for (int i = 1; i <= n; ++i) {
        this->Add(i); // Replace Add with your AVL insert if implemented
    }
    Draw();
}

void AVLTree::Add(int x) {
    // Standard AVL insert with balancing and visualization

    // Helper lambda to get height
    auto height = [](const std::unique_ptr<AVLNode>& node) -> int {
        return node ? node->height : 0;
    };

    // Helper lambda to update height
    auto updateHeight = [&](AVLNode* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    };

    // Helper lambda to get balance factor
    auto getBalance = [&](AVLNode* node) -> int {
        return node ? height(node->left) - height(node->right) : 0;
    };

    // Right rotate
    auto rightRotate = [&](std::unique_ptr<AVLNode>& y) {
        std::unique_ptr<AVLNode> x = std::move(y->left);
        std::unique_ptr<AVLNode> T2 = std::move(x->right);

        x->right = std::move(y);
        x->right->left = std::move(T2);

        updateHeight(x->right.get());
        updateHeight(x.get());

        y = std::move(x);
    };

    // Left rotate
    auto leftRotate = [&](std::unique_ptr<AVLNode>& x) {
        std::unique_ptr<AVLNode> y = std::move(x->right);
        std::unique_ptr<AVLNode> T2 = std::move(y->left);

        y->left = std::move(x);
        y->left->right = std::move(T2);

        updateHeight(y->left.get());
        updateHeight(y.get());

        x = std::move(y);
    };

    // Recursive insert function
    std::function<void(std::unique_ptr<AVLNode>&, int)> insert = [&](std::unique_ptr<AVLNode>& node, int val) {
        if (!node) {
            node = std::make_unique<AVLNode>(idGenerator.GetID(), val);
            node->color = updatingColor;
            Draw();
            node->color = color;
            Draw();
            return;
        }

        node->color = updatingColor;
        Draw();

        if (val < node->val) {
            insert(node->left, val);
        } else if (val > node->val) {
            insert(node->right, val);
        } else {
            node->color = color;
            Draw();
            return; // Duplicate values not allowed
        }

        updateHeight(node.get());

        int balance = getBalance(node.get());

        // Left Left Case
        if (balance > 1 && val < node->left->val) {
            rightRotate(node);
            node->color = color;
            node->right->color = color;
            Draw();
            return;
        }

        // Right Right Case
        if (balance < -1 && val > node->right->val) {
            leftRotate(node);
            node->color = color;
            node->left->color = color;
            Draw();
            return;
        }

        // Left Right Case
        if (balance > 1 && val > node->left->val) {
            leftRotate(node->left);
            rightRotate(node);
            node->color = color;
            node->right->color = color;
            Draw();
            return;
        }

        // Right Left Case
        if (balance < -1 && val < node->right->val) {
            rightRotate(node->right);
            leftRotate(node);
            node->color = color;
            node->left->color = color;
            Draw();
            return;
        }

        node->color = color;
        Draw();
    };

    insert(root, x);
}

bool AVLTree::Search(int x) {
    AVLNode* curr = root.get();
    while (curr) {
        curr->color = updatingColor;
        Draw();

        if (curr->val == x) {
            curr->color = color;
            Draw();
            return true;
        }

        curr->color = color;
        Draw();

        if (x < curr->val) {
            curr = curr->left.get();
        } else {
            curr = curr->right.get();
        }
    }
    return false;
}

void AVLTree::Delete(int x) {
    // Standard AVL delete with balancing and visualization

    // Helper lambda to get height
    auto height = [](const std::unique_ptr<AVLNode>& node) -> int {
        return node ? node->height : 0;
    };

    // Helper lambda to update height
    auto updateHeight = [&](AVLNode* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    };

    // Helper lambda to get balance factor
    auto getBalance = [&](AVLNode* node) -> int {
        return node ? height(node->left) - height(node->right) : 0;
    };

    // Right rotate
    auto rightRotate = [&](std::unique_ptr<AVLNode>& y) {
        std::unique_ptr<AVLNode> x = std::move(y->left);
        std::unique_ptr<AVLNode> T2 = std::move(x->right);

        x->right = std::move(y);
        x->right->left = std::move(T2);

        updateHeight(x->right.get());
        updateHeight(x.get());

        y = std::move(x);
    };

    // Left rotate
    auto leftRotate = [&](std::unique_ptr<AVLNode>& x) {
        std::unique_ptr<AVLNode> y = std::move(x->right);
        std::unique_ptr<AVLNode> T2 = std::move(y->left);

        y->left = std::move(x);
        y->left->right = std::move(T2);

        updateHeight(y->left.get());
        updateHeight(y.get());

        x = std::move(y);
    };

    // Find min value node
    auto minValueNode = [](AVLNode* node) -> AVLNode* {
        AVLNode* current = node;
        while (current && current->left)
            current = current->left.get();
        return current;
    };

    // Recursive delete function
    std::function<void(std::unique_ptr<AVLNode>&, int)> erase = [&](std::unique_ptr<AVLNode>& node, int val) {
        if (!node) return;

        node->color = updatingColor;
        Draw();

        if (val < node->val) {
            erase(node->left, val);
        } else if (val > node->val) {
            erase(node->right, val);
        } else {
            // Node to be deleted found
            if (!node->left || !node->right) {
                std::unique_ptr<AVLNode> temp = node->left ? std::move(node->left) : std::move(node->right);
                idGenerator.RemoveID(node->id);
                node = std::move(temp);
                Draw();
                return;
            } else {
                AVLNode* minNode = minValueNode(node->right.get());
                node->val = minNode->val;
                erase(node->right, minNode->val);
            }
        }

        if (!node) return;

        updateHeight(node.get());

        int balance = getBalance(node.get());

        // Left Left Case
        if (balance > 1 && getBalance(node->left.get()) >= 0) {
            rightRotate(node);
            node->color = color;
            Draw();
            return;
        }

        // Left Right Case
        if (balance > 1 && getBalance(node->left.get()) < 0) {
            leftRotate(node->left);
            rightRotate(node);
            node->color = color;
            Draw();
            return;
        }

        // Right Right Case
        if (balance < -1 && getBalance(node->right.get()) <= 0) {
            leftRotate(node);
            node->color = color;
            Draw();
            return;
        }

        // Right Left Case
        if (balance < -1 && getBalance(node->right.get()) > 0) {
            rightRotate(node->right);
            leftRotate(node);
            node->color = color;
            Draw();
            return;
        }

        node->color = color;
        Draw();
    };

    erase(root, x);
}

bool AVLTree::Update(int id, int val) {
    if (id == -1) return false;

    // Find the node by id, update its value, remove it, and re-insert at the correct position
    AVLNode* target = nullptr;
    int oldVal = -1;

    // Helper: find node by id and get its value
    std::function<AVLNode*(AVLNode*)> findById = [&](AVLNode* node) -> AVLNode* {
        if (!node) return nullptr;
        if (node->id == id) return node;
        AVLNode* res = findById(node->left.get());
        if (res) return res;
        return findById(node->right.get());
    };

    target = findById(root.get());
    if (!target) return false;
    oldVal = target->val;

    // Remove the node with old value
    Delete(oldVal);

    // Insert the node with new value (using same id)
    // Temporarily override idGenerator to reuse the id
    int backupId = idGenerator.GetID();
    idGenerator.RemoveID(id); // Assume SetID exists, or implement a way to reuse id

    // Insert with custom id
    std::function<void(std::unique_ptr<AVLNode>&, int)> insertWithId = [&](std::unique_ptr<AVLNode>& node, int val) {
        if (!node) {
            node = std::make_unique<AVLNode>(id, val);
            node->color = updatingColor;
            Draw();
            node->color = color;
            Draw();
            return;
        }
        node->color = updatingColor;
        Draw();
        if (val < node->val) {
            insertWithId(node->left, val);
        } else if (val > node->val) {
            insertWithId(node->right, val);
        } else {
            node->color = color;
            Draw();
            return;
        }
        // Update height and balance
        auto height = [](const std::unique_ptr<AVLNode>& n) -> int {
            return n ? n->height : 0;
        };
        auto updateHeight = [&](AVLNode* n) {
            n->height = 1 + std::max(height(n->left), height(n->right));
        };
        auto getBalance = [&](AVLNode* n) -> int {
            return n ? height(n->left) - height(n->right) : 0;
        };
        auto rightRotate = [&](std::unique_ptr<AVLNode>& y) {
            std::unique_ptr<AVLNode> x = std::move(y->left);
            std::unique_ptr<AVLNode> T2 = std::move(x->right);
            x->right = std::move(y);
            x->right->left = std::move(T2);
            updateHeight(x->right.get());
            updateHeight(x.get());
            y = std::move(x);
        };
        auto leftRotate = [&](std::unique_ptr<AVLNode>& x) {
            std::unique_ptr<AVLNode> y = std::move(x->right);
            std::unique_ptr<AVLNode> T2 = std::move(y->left);
            y->left = std::move(x);
            y->left->right = std::move(T2);
            updateHeight(y->left.get());
            updateHeight(y.get());
            x = std::move(y);
        };
        updateHeight(node.get());
        int balance = getBalance(node.get());
        // Left Left
        if (balance > 1 && val < node->left->val) {
            rightRotate(node);
            node->color = color;
            node->right->color = color;
            Draw();
            return;
        }
        // Right Right
        if (balance < -1 && val > node->right->val) {
            leftRotate(node);
            node->color = color;
            node->left->color = color;
            Draw();
            return;
        }
        // Left Right
        if (balance > 1 && val > node->left->val) {
            leftRotate(node->left);
            rightRotate(node);
            node->color = color;
            node->right->color = color;
            Draw();
            return;
        }
        // Right Left
        if (balance < -1 && val < node->right->val) {
            rightRotate(node->right);
            leftRotate(node);
            node->color = color;
            node->left->color = color;
            Draw();
            return;
        }
        node->color = color;
        Draw();
    };

    insertWithId(root, val);

    // Restore idGenerator if needed
    idGenerator.RemoveID(backupId);

    return true;
}