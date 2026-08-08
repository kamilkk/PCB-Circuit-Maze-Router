#include "MazeRouter.h"
#include <queue>
#include <algorithm>

// std::priority_queue acts as a max-heap by default.
// To make it a min-heap, we invert the comparison logic.
bool AStarNode::operator<(const AStarNode& other) const {
    if (f_score == other.f_score) {
        // Tie-breaker: older events (lower sequence_id) get higher priority
        return sequence_id > other.sequence_id; 
    }
    return f_score > other.f_score; 
}

MazeRouter::MazeRouter(const Grid& grid) : m_grid(grid) {}

std::vector<Point> MazeRouter::route(Point start, Point end, std::function<int(Point, Point)> heuristic) {
    if (!m_grid.isValid(start) || !m_grid.isValid(end)) {
        return {};
    }
    if (m_grid.isObstacle(start) || m_grid.isObstacle(end)) {
        return {};
    }

    std::priority_queue<AStarNode> openSet;
    std::unordered_map<Point, Point> cameFrom;
    std::unordered_map<Point, int> gScore;
    
    int sequence_counter = 0;

    gScore[start] = 0;
    openSet.push({start, heuristic(start, end), sequence_counter++});

    std::vector<Point> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!openSet.empty()) {
        Point current = openSet.top().pt;
        openSet.pop();

        if (current == end) {
            return reconstructPath(cameFrom, current);
        }

        for (const auto& dir : directions) {
            Point neighbor{current.x + dir.x, current.y + dir.y};

            if (!m_grid.isValid(neighbor) || m_grid.isObstacle(neighbor)) {
                continue;
            }

            int tentative_gScore = gScore[current] + 1;

            if (gScore.find(neighbor) == gScore.end() || tentative_gScore < gScore[neighbor]) {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentative_gScore;
                
                int f_score = tentative_gScore + heuristic(neighbor, end);
                openSet.push({neighbor, f_score, sequence_counter++});
            }
        }
    }

    return {}; // No path found
}

std::vector<Point> MazeRouter::reconstructPath(std::unordered_map<Point, Point>& cameFrom, Point current) {
    std::vector<Point> path;
    path.push_back(current);
    
    while (cameFrom.find(current) != cameFrom.end()) {
        current = cameFrom[current];
        path.push_back(current);
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}