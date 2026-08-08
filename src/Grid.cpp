#include "Grid.h"

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

namespace std {
    std::size_t hash<Point>::operator()(const Point& p) const {
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
}

Grid::Grid(int width, int height) 
    : m_width(width), m_height(height), m_data(width * height, 0) {}

void Grid::setObstacle(Point p) {
    if (isValid(p)) {
        m_data[p.y * m_width + p.x] = 1;
    }
}

bool Grid::isObstacle(Point p) const {
    if (!isValid(p)) return true;
    return m_data[p.y * m_width + p.x] == 1;
}

bool Grid::isValid(Point p) const {
    return p.x >= 0 && p.x < m_width && p.y >= 0 && p.y < m_height;
}

int Grid::getWidth() const { return m_width; }
int Grid::getHeight() const { return m_height; }