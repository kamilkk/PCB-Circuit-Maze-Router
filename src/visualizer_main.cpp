#include "MazeRouter.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>

using namespace ftxui;

int manhattan(Point a, Point b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

int main() {
    int width = 30;
    int height = 15;
    Grid grid(width, height);
    
    // Create a challenging maze environment
    for (int y = 2; y <= 12; ++y) {
        grid.setObstacle({10, y});
    }
    grid.setObstacle({11, 2});
    grid.setObstacle({12, 2});
    
    for (int y = 0; y <= 8; ++y) {
        grid.setObstacle({20, y});
    }

    MazeRouter router(grid);
    Point start{2, 7};
    Point end{26, 7};
    
    auto path = router.route(start, end, manhattan);

    // Fast lookup for the path
    std::vector<std::vector<bool>> is_path(height, std::vector<bool>(width, false));
    for (const auto& p : path) {
        is_path[p.y][p.x] = true;
    }

    // Build the FTXUI Grid
    Elements rows;
    for (int y = 0; y < height; ++y) {
        Elements cells;
        for (int x = 0; x < width; ++x) {
            Point p{x, y};
            if (p == start) {
                cells.push_back(text(" S ") | bgcolor(Color::Blue) | color(Color::White) | bold);
            } else if (p == end) {
                cells.push_back(text(" E ") | bgcolor(Color::Green) | color(Color::White) | bold);
            } else if (grid.isObstacle(p)) {
                cells.push_back(text("   ") | bgcolor(Color::Red));
            } else if (is_path[y][x]) {
                cells.push_back(text(" * ") | bgcolor(Color::Yellow) | color(Color::Black) | bold);
            } else {
                cells.push_back(text(" . ") | color(Color::GrayDark));
            }
        }
        rows.push_back(hbox(std::move(cells)));
    }

    auto document = border(
        vbox({
            text(" PCB Maze Router Visualization ") | bold | center,
            separator(),
            vbox(std::move(rows)) | center,
        })
    );
    
    auto screen = Screen::Create(Dimension::Fit(document), Dimension::Fit(document));
    Render(screen, document);
    screen.Print();
    
    return 0;
}