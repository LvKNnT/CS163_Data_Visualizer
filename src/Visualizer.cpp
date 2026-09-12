#include "Visualizer.h"
#include "raymath.h"
#include "RenderUtilities.h"
#include "Properties.h"
#include "raylib.h"

IDGenerator::IDGenerator() : currentID(0) {}
IDGenerator::~IDGenerator() {}

int IDGenerator::GetID() {
    if (idQueue.empty()) {
        idQueue.push(currentID++);
    }

    int id = idQueue.front();
    idQueue.pop();
    return id;
}

void IDGenerator::RemoveID(int id) {
    idQueue.push(id);
}

void IDGenerator::ResetID() {
    while (!idQueue.empty()) {
        idQueue.pop();
    }
    currentID = 0;
}

Visualizer visualizer;

Visualizer::Visualizer() {
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    cameraPosition = Vector2{0.0f, 0.0f};
}
Visualizer::~Visualizer() {}

Node::Node() : val(0) {}
Node::Node(int val) : val(val) {}
Node::Node(int id, int val) : id(id), val(val) {}
Node::~Node() {}

Edge::Edge() {}
Edge::Edge(int from, int to) : from(from), to(to) {}
Edge::~Edge() {}

Point::Point() : position{(float) GetRandomValue(-300, 300), (float) GetRandomValue(-300, 300)} {}
Point::Point(float x, float y) : position{x, y} {}
Point::~Point() {}

void Visualizer::SetArea(float x, float y, float width, float height) {
    area = Rectangle{x, y, width, height};
}

std::vector<Point> Visualizer::GetPoint() {
    return points;
}

void Visualizer::SetPoint(std::vector<Point>& points) {
    this->points = points;
}

void Visualizer::ResetPoint() {
    points.clear();
}

void Visualizer::ResetData() {
    nodeHistory.clear();
    edgeHistory.clear();
}

void Visualizer::SetData(std::vector<Node>& nodes, std::vector<Edge>& edges) {
    for(const auto& node : nodes) {
        while(node.id >= points.size()) {
            points.push_back(Point());
        }
    }

    nodeHistory.push_back(nodes);
    edgeHistory.push_back(edges);

    progressLimit = float(nodeHistory.size() - 1);
    progress = 0.0f;
}

void Visualizer::SetArrow(bool isArrow) {
    this->isArrow = isArrow;
}

void Visualizer::SetHighlight(bool isHighlight) {
    this->isHighlight = isHighlight;
}

void Visualizer::SetCentered(bool isCentered) {
    this->isCentered = isCentered;
}

void Visualizer::Update() {
    for (auto& point : points) {
        point.force = {0, 0};
    }
    
    std::vector<Edge> edges = edgeHistory[int(progress)];
    
    // Apply repulsion between all nodes
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            Vector2 delta = Vector2Subtract(points[j].position, points[i].position);
            float dist = Vector2Distance(points[i].position, points[j].position) + 0.1f;  // Prevent divide by zero
            float forceMag = repulsionStrength / (dist * dist);
            
            Vector2 repulse = Vector2Scale(Vector2Normalize(delta), forceMag);
            points[i].force = Vector2Subtract(points[i].force, repulse);
            points[j].force = Vector2Add(points[j].force, repulse);
        }
    }
    
    // Apply spring (attraction) forces for connected nodes
    for (auto& edge : edges) {
        Point& nodeA = points[edge.from];
        Point& nodeB = points[edge.to];
        
        Vector2 delta = Vector2Subtract(nodeB.position, nodeA.position);
        float dist = Vector2Distance(nodeA.position, nodeB.position) + 0.1f;
        float forceMag = springStrength * (dist - springLength);
        
        Vector2 springForce = Vector2Scale(Vector2Normalize(delta), forceMag);
        nodeA.force = Vector2Add(nodeA.force, springForce);
        nodeB.force = Vector2Subtract(nodeB.force, springForce);
    }

    // Update velocities and positions
    Vector2 center = {0.0f, 0.0f};
    if(isCentered) {
        Vector2 centerArea = {0.0f, 0.0f};
        for (const auto& point : points) {
            centerArea = Vector2Add(centerArea, point.position);
        }
        centerArea = Vector2Scale(centerArea, 1.0f / points.size());
        for (auto& point : points) {
            Vector2 toCenter = Vector2Subtract(center, centerArea);
            point.velocity = Vector2Add(point.velocity, Vector2Scale(toCenter, gravityStrength * GetFrameTime()));
        }
    }

    for (auto& point : points) {
        point.velocity = Vector2Add(point.velocity, Vector2Scale(point.force, GetFrameTime() * forceMultiplier));
        point.velocity = Vector2Scale(point.velocity, damping);  // Apply damping
        point.position = Vector2Add(point.position, Vector2Scale(point.velocity, GetFrameTime()));

        // Bounderies
        // point.position.x = std::min(std::max(point.position.x, area.x + radius), area.x + area.width - radius);
        // point.position.y = std::min(std::max(point.position.y, area.y + radius), area.y + area.height - radius);
    }
}

int Visualizer::Check() {
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera); // mouse's position in camera

    if (idHolding == -1 && CheckCollisionPointRec(GetMousePosition(), area) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        // Iterate from top to bottom (reverse order)
        for (int i = points.size() - 1; i >= 0; i--) {
            if (CheckCollisionPointCircle(mouseWorldPos, points[i].position, radius)) {
                points[i].position = mouseWorldPos;
                idHolding = i;
                idLastPicked = i;
                break;
            }
        }
    }

    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) idHolding = -1;
    if(idHolding != -1) {
        points[idHolding].position = mouseWorldPos;
    }

    return idLastPicked;
}

std::string Visualizer::GetValueLastPick() {
    if(idLastPicked == -1) return ""; // should not happen
    
    std::vector<Node> nodes = nodeHistory[int(progress)];
    for(const auto& node : nodes) {
        if(node.id == idLastPicked) return node.subText;
    }
    return ""; // should not happen
}

void Visualizer::DrawArrow(Vector2 start, Vector2 end, float arrowSize, float radius, Color color) {
    // Calculate direction
    Vector2 direction = Vector2Normalize(Vector2Subtract(end, start));
    end = Vector2Subtract(end, Vector2Scale(direction, radius));

    // Calculate perpendicular vector for arrowhead
    Vector2 perp = { -direction.y, direction.x };

    // Arrowhead points
    Vector2 arrowLeft = Vector2Subtract(end, Vector2Scale(direction, arrowSize));
    arrowLeft = Vector2Add(arrowLeft, Vector2Scale(perp, arrowSize * 0.5f));

    Vector2 arrowRight = Vector2Subtract(end, Vector2Scale(direction, arrowSize));
    arrowRight = Vector2Subtract(arrowRight, Vector2Scale(perp, arrowSize * 0.5f));

    // Draw the arrowhead
    DrawTriangle(arrowLeft, end, arrowRight, color);
}

void Visualizer::DrawEdge(Vector2 start, Vector2 end, float thickness, Color color) {
    Vector2 direction = Vector2Normalize(Vector2Subtract(end, start));
    end = Vector2Subtract(end, Vector2Scale(direction, radius));
    start = Vector2Add(start, Vector2Scale(direction, radius));

    DrawLineEx(start, end, thickness, PINK);
}

void Visualizer::Draw() {
    // simulation settings.
    if(progress < progressLimit && isProgress) progress += GetFrameTime() * dif;
    progress = std::min(progress, progressLimit);
    
    std::vector<Node> nodes = nodeHistory[int(progress)];
    std::vector<Edge> edges = edgeHistory[int(progress)];

    // camera settings.
    camera.offset = (Vector2){area.x + area.width / 2, area.y + area.height / 2};  // Offset to render in a specific area
    
    if(CheckCollisionPointRec(GetMousePosition(), area)) camera.zoom += ((float)GetMouseWheelMove()*0.05f);
    
    if (camera.zoom > 3.0f) camera.zoom = 3.0f;
    else if (camera.zoom < 0.1f) camera.zoom = 0.1f;
    if (IsKeyPressed(KEY_R)) {
        camera.zoom = 1.0f;
        camera.rotation = 0.0f;
    }
    
    if (IsKeyDown(KEY_RIGHT)) cameraPosition.x += cameraSpeed;
    if (IsKeyDown(KEY_LEFT)) cameraPosition.x -= cameraSpeed;
    if(IsKeyDown(KEY_UP)) cameraPosition.y -= cameraSpeed;
    if(IsKeyDown(KEY_DOWN)) cameraPosition.y += cameraSpeed;
    camera.target = (Vector2){cameraPosition.x, cameraPosition.y};
    

    BeginScissorMode((int) area.x, (int) area.y, (int) area.width, (int) area.height);
    BeginMode2D(camera);
    
    for(const auto& edge : edges) {
        DrawEdge(points[edge.from].position, points[edge.to].position, 2.0f, nodes[edge.from].color);
        if(isArrow) DrawArrow(points[edge.from].position, points[edge.to].position, 10.0f, radius, nodes[edge.from].color);
        
        DrawEdge(points[edge.from].position, points[edge.to].position, 2.0f, PINK);
        if(isArrow) DrawArrow(points[edge.from].position, points[edge.to].position, 10.0f, radius, PINK);
    }
    
    for (const auto& node : nodes) {
        
        DrawCircleV(points[node.id].position, radius, node.color);
        if(isHighlight && node.id == idLastPicked) {
            DrawCircleV(points[node.id].position, radius, GREEN);
        }
        
        DrawTextCenEx(Properties::fonts["Rubik-Regular_15"], node.text.c_str(), points[node.id].position.x, points[node.id].position.y, 15, 2, BLACK);
    }
    
    EndMode2D();
    EndScissorMode();
}

void Visualizer::SetIsProgress(bool isProgress) {
    this->isProgress = isProgress;
}

bool Visualizer::GetIsProgress() {
    return this->isProgress;
}

void Visualizer::SetProgress(float progress) {
    this->progress = progress * this->progressLimit;
}

float Visualizer::GetProgress() {
    return progress / progressLimit;
}

void Visualizer::SetDif(float dif) {
    this->dif = difMin + dif * (difMax - difMin);
}

float Visualizer::GetDif() {
    return (this->dif - difMin) / (difMax - difMin);
}

void Visualizer::ResetProgess() {
    progress = 0.0f;
}
