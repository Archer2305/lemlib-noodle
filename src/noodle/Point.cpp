
#include "Point.hpp"
#include <cmath> // Include cmath for the std::fabs function

Point::Point() : x(0.0), y(0.0) {}
Point::Point(double x_val, double y_val) : x(x_val), y(y_val) {}

Point operator*(double scalar, const Point &point) {
  return Point(scalar * point.x, scalar * point.y);
}

bool Point::operator==(const Point& other) const {
  const double epsilon = 1e-5; // Define precision (5 decimal places in this case)
  return (std::fabs(x - other.x) < epsilon) && (std::fabs(y - other.y) < epsilon);
}


Point Point::operator*(double scalar) const {
  return Point(scalar * x, scalar * y);
}

Point Point::operator+(const Point &other) const {
  return Point(x + other.x, y + other.y);
}

void Point::print(std::string inp) const {
  std::cout << "(" << x << "," << y << ")" + inp;
}
