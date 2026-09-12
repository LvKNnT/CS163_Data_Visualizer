#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "raylib.h"
#include <bits/stdc++.h>

class IDGenerator {
public:
    IDGenerator();
    ~IDGenerator();

    int GetID();
    void RemoveID(int id);
    void ResetID();
private:
    std::queue<int> idQueue;
    int currentID = 0;
};

struct Node {
    Node();
    Node(int val);
    Node(int id, int val);
    ~Node();

    int id; // -th in the vector
    int val;

    Color color = RED; // should not be this color
    std::string text = "";
    std::string subText = "";
};

struct Edge {
    Edge();
    Edge(int from, int to);
    ~Edge();

    int from;
    int to;
};

struct Point {
    Point();
    Point(float x, float y);
    ~Point();

    Vector2 position = {-1.0f, -1.0f};
    Vector2 velocity = {0.0f, 0.0f};
    Vector2 force = {0.0f, 0.0f};
};

class Visualizer {
public:
    Visualizer();
    ~Visualizer();

    void SetArea(float x, float y, float width, float height);
    void ResetData();
    void SetData(std::vector<Node>& nodes, std::vector<Edge>& edges);
    
    std::vector<Point> GetPoint();
    void SetPoint(std::vector<Point>& points);
    void ResetPoint();
    
    void SetHighlight(bool isHighlight);
    void SetArrow(bool isArrow);
    void SetCentered(bool isCentered);

    void Update();
    int Check();
    void Draw();

    void SetIsProgress(bool isProgress);
    bool GetIsProgress();
    void SetProgress(float progress);
    float GetProgress();
    void SetDif(float dif);
    float GetDif();
    std::string GetValueLastPick();
    void ResetProgess();
    void Draw2();

    // Dedicated drawing function
    void DrawEdge(Vector2 start, Vector2 end, float thickness, Color color);
    void DrawArrow(Vector2 start, Vector2 end, float arrowSize, float radius, Color color);

private:
    const float radius = 20.0f;
    Rectangle area;
    int idHolding = -1;
    int idLastPicked = -1;
    
    bool isArrow = false;
    bool isHighlight = true;
    bool isCentered = true;
    const float repulsionStrength = 50000.0f;    // Increased to spread nodes apart more
    const float springLength = 250.0f;            // Increase so springs aren't pulling nodes too tightly
    const float springStrength = 0.5f;          // Weaker springs to let repulsion dominate
    const float damping = 0.9f;                  // Strong damping to avoid jittering
    const float forceMultiplier = 2.5f;          // Moderate to avoid too slow or too aggressive movements
    const float gravityStrength = 25.0f;          // Turn off or reduce gravity if you want equal spacing
    
    std::vector<Point> points;
    // std::vector<Node> nodes;
    // std::vector<Edge> edges;
    std::vector<std::vector<Node> > nodeHistory;
    std::vector<std::vector<Edge> > edgeHistory;
    
    // simulation section
    float progress = 0.0f;
    bool isProgress = false;
    float progressLimit = 1000000.0f;
    float dif = 20.0f;
    float difMin = 2.0f;
    float difMax = 40.0f;

    // Camera
    Camera2D camera = { 0 };
    Vector2 cameraPosition;
    float cameraSpeed = 20.0f;
};

extern Visualizer visualizer;

#endif // VISUALIZER_H