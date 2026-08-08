#pragma once
#include "Grid.h"
#include <vector>
#include <functional>
#include <unordered_map>

// Event Queue Node
struct AStarNode {
    Point pt;
    int f_score;
    int sequence_id; // Enforces stability in the priority queue

    bool operator<(const AStarNode& other) const;
};

class MazeRouter {
public:
    // Enforcing Dependency Injection
    explicit MazeRouter(const Grid& grid);

    std::vector<Point> route(Point start, Point end, std::function<int(Point, Point)> heuristic);

private:
    const Grid& m_grid;

    std::vector<Point> reconstructPath(std::unordered_map<Point, Point>& cameFrom, Point current);
};