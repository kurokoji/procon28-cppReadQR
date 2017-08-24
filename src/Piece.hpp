#ifndef INCLUDE_PIECE_HPP
#define INCLUDE_PIECE_HPP

#include <iostream>
#include <vector>

struct Point {
  int x, y;
  Point() {}
  Point(int x, int y) : x(x), y(y) {}
  friend std::ostream& operator<<(std::ostream& os, const Point& rhs) {
    os << rhs.x << " " << rhs.y << '\n';
    return os;
  }
};

struct Polygon {
  std::vector<Point> points;
  Polygon() {}
  friend std::ostream& operator<<(std::ostream& os, const Polygon& rhs) {
    os << rhs.points.size() << '\n';
    for (auto&& p : rhs.points) {
      os << p;
    }
    return os;
  }
};


#endif
