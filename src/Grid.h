#pragma once
#include <vector>
#include <functional>

struct Point {
    int x, y;
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
};

namespace std {
    template <>
    struct hash<Point> {
        std::size_t operator()(const Point& p) const;
    };
}

class Grid {
public:
    Grid(int width, int height);

    void setObstacle(Point p);
    bool isObstacle(Point p) const;
    bool isValid(Point p) const;
    
    int getWidth() const;
    int getHeight() const;

private:
    int m_width;
    int m_height;
    std::vector<int> m_data; // Flat vector for memory-efficient 2D grid
};