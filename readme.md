## PCB / Circuit Maze Router

A grid-based pathfinding router built in modern C++ (C++17) to demonstrate advanced algorithmic knowledge, stable event queues, and software architecture (Dependency Injection) typical of Electronic Design Automation (EDA) systems.

### Features
- **A* Pathfinding Algorithm**: Highly optimized graph traversal to navigate obstacles.
- **Stable Event Queue**: Uses a custom sequence ID tie-breaker inside the `std::priority_queue` to ensure deterministic behavior for nodes with equal `f_score`.
- **Dependency Injection**: Strictly avoids singletons; grid dependencies are injected explicitly into the router engine.
- **Terminal UI**: Integrates **FTXUI** to render a beautiful, color-coded visualization of the routed path directly in your terminal.

### Big-O Complexity
- **Time Complexity**: `O(E log V)` where `V` is the number of valid grid cells and `E` is the number of edges. The use of `std::priority_queue` dominates the time complexity.
- **Space Complexity**: `O(V)` auxiliary space for the `gScore`, `cameFrom` maps, and the open set queue.

### Build Instructions
```bash
cmake -S . -B build
cmake --build build
```

### Running Instructions

- Execute the visualizer:
```bash
cd build
./maze_visualizer
```

- Execute unit tests:
```bash
cd build
ctest --output-on-failure
```