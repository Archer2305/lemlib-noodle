#include "NoodlePath.hpp"
#include <cmath>
#include <stdexcept>

// Define the static member variable
std::vector<Point> points;
NoodlePath::NoodlePath() {
  // Constructor implementation
}

Point NoodlePath::p(double t, Point p0, Point p1) {
  return ((1 - t) * p0) + (t * p1);
}

Point NoodlePath::generateSinglePoint(double t) {
  return ((1 - t) * p(t, p0, p1) + (t * p(t, p2, p3)));
}
void NoodlePath::setTarget(Point P, double angle, bool isDegrees) {
  p3.x = P.x;
  p3.y = P.y;
  if (isDegrees) {
    DT = angle;
    Ta = DT * (PI / 180.0);
  } else if (!isDegrees) {
    Ta = angle;
  }
}

void NoodlePath::setTargetPoint(Point P) {
  p3.x = P.x;
  p3.y = P.y;
}

void NoodlePath::setTargetAngle(double angle, bool isDegrees) {
  if (isDegrees) {
    DT = angle;
    Ta = DT * (PI / 180.0);
  } else if (!isDegrees) {
    Ta = angle;
  }
}

void NoodlePath::generatePoints(Point P, double angle, bool isDegrees) {

  p0.x = P.x;
  p0.y = P.y;
  if (isDegrees) {
    DI = angle;
    Ia = DI * (PI / 180.0);
  } else if (!isDegrees) {
    Ia = angle;
  }

  p1.x = ((p3.y - p0.y) - (p3.x * tan(Ta)) + (p0.x * tan(Ia))) /
         (tan(Ia) - tan(Ta));
  p2.x = p1.x;
  p1.y = tan(Ta) * (p1.x - p3.x) + p3.y;
  p2.y = p1.y;

  for (double t = 0.0; t <= 1; t += 0.01) {
    points.push_back((1 - t) * p(t, p0, p1) + (t * p(t, p2, p3)));
  }
}

void NoodlePath::printPoints() {
  if (points.empty()) {
    throw std::invalid_argument("Need to generate points to print!");
  }
  if (!points.empty()) {
    for (int i = 0; i < points.size(); i++) {
      if (i != points.size() - 1) {
        points[i].print(", ");
      } else {
        points[i].print("");
      }
    }
  }
}

Point NoodlePath::getInitialPoint() { return p0; }
Point NoodlePath::getTargetPoint() { return p3; }
double NoodlePath::getTargetAngle() { return Ta; }
double NoodlePath::getInitialAngle() { return Ia; }
double NoodlePath::getTerminalAngle() { return Ta; }
