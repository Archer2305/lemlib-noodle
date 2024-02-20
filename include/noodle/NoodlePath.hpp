#ifndef NOODLEPATH_HPP
#define NOODLEPATH_HPP

#include <vector>
#include "Point.hpp"

class NoodlePath {
private:
    double DI;//initial angle in degrees ( given as input)
    double Ia;// initial angle in radians ( used for calculations)
    double DT;// target angle in degrees (given as input)
    double Ta;// target angle in radians (used for calculations)
    Point p0;//point 0 (initial point)
    Point p1;//control point one
    Point p2;//control point two
    Point p3;//terminal point
    double PI = 3.14159;
    Point p(double t, Point p0, Point p1);// lerp function
    


public:

    NoodlePath();
     std::vector<Point> points;
    void setTarget(Point P, double angle, bool isDegrees=true);
    void setTargetPoint(Point P);
    void setTargetAngle(double angle, bool isDegrees=true);
    void generatePoints(Point P, double angle, bool isDegrees=true);
    void printPoints();
    Point getInitialPoint();
    Point getTargetPoint();
    double getInitialAngle();
    double getTargetAngle();
    Point getTerminalPoint(); //allias for target point
    double getTerminalAngle();// allias for target angle
    // NoodlePath merge(const NoodlePath& pathOne, const NoodlePath& pathTwo);
    Point generateSinglePoint(double t);
};

#endif // NOODLEPATH_HPP
