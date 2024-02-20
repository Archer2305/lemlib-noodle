#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

class Point {
public:
  double x;
  double y;
  Point(); 
  Point(double x_val, double y_val);

  // Overloading the multiplication operator as a friend function
  friend Point operator*(double scalar, const Point& point);
  Point operator*(double scalar) const;

  // Overloading the addition operator
  Point operator+(const Point& other) const;
  bool operator==(const Point& other) const;

  // Print function
  void print(std::string inp) const;
};

#endif // POINT_HPP
