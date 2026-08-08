#include "MazeRouter.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <random>

using namespace ftxui;

int manhattan(Point a, Point b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

int main() {
    int width = 30;
    int height = 15;
    Grid grid(width, height);
    
    // Setup random generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> x_dist(0, width - 1);
    std::uniform_int_distribution<> y_dist(0, height - 1);
    std::uniform_real_distribution<> prob(0.0, 1.0);
    // Generate random obstacles (20% probability)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (prob(gen) < 0.20) {
                grid.setObstacle({x, y});
            }
        }
    }
    MazeRouter router(grid);
    
    // CRITICAL: Ensure start and end are not obstacles, and are distinct
    Point start;
    do {
        start = {x_dist(gen), y_dist(gen)};
    } while (grid.isObstacle(start));
    Point end;
    do {
        end = {x_dist(gen), y_dist(gen)};
    } while (grid.isObstacle(end) || start == end);
    
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

    // Build the Legend
    auto legend = window(text(" Legend "), vbox({
        hbox(text(" S ") | bgcolor(Color::Blue) | color(Color::White) | bold, text(" Start Point ")),
        hbox(text(" E ") | bgcolor(Color::Green) | color(Color::White) | bold, text(" End Point ")),
        hbox(text("   ") | bgcolor(Color::Red), text(" Obstacle ")),
        hbox(text(" * ") | bgcolor(Color::Yellow) | color(Color::Black) | bold, text(" Routed Path ")),
        hbox(text(" . ") | color(Color::GrayDark), text(" Empty Space ")),
    }));

    // Combine Grid and Legend
    auto document = hbox({
        border(
            vbox({
                text(" PCB Maze Router ") | bold | center,
                separator(),
                vbox(std::move(rows)) | center,
            })
        ),
        legend
    });
    
    auto screen = Screen::Create(Dimension::Fit(document), Dimension::Fit(document));
    Render(screen, document);
    screen.Print();
    std::cout << std::endl;
    
    return 0;
}