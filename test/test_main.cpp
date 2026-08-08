#include "../src/MazeRouter.h"
#include <iostream>
#include <cassert>
#include <cmath>

// Custom Manhattan distance heuristic for routing
int manhattan(Point a, Point b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

void testSimpleRoute() {
    Grid grid(5, 5);
    
    // Create a wall in the middle
    grid.setObstacle({2, 0});
    grid.setObstacle({2, 1});
    grid.setObstacle({2, 2});
    grid.setObstacle({2, 3});
    
    // Instantiate Router by passing the grid dependency
    MazeRouter router(grid);
    
    Point start{0, 2};
    Point end{4, 2};
    
    auto path = router.route(start, end, manhattan);
    
    assert(!path.empty() && "Path should not be empty!");
    assert(path.front() == start && "Path must begin at start point");
    assert(path.back() == end && "Path must conclude at end point");
    
    std::cout << "[SUCCESS] testSimpleRoute passed.\n";
}

int main() {
    std::cout << "Running MazeRouter Tests...\n";
    testSimpleRoute();
    std::cout << "All tests passed successfully.\n";
    return 0;
}