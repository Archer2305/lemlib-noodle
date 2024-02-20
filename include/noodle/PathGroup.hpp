#ifndef __PATH_G_H__
#define __PATH_G_H__
#include "NoodlePath.hpp"
#include "Point.hpp"

class PathGroup{

public:
PathGroup();
PathGroup(const std::vector<NoodlePath> inp);
void printLanes(int splineNumber=0);
std::vector<NoodlePath> arr;
Point generatePoint(double t);
NoodlePath fetchLeftLane(int splineNumber);
NoodlePath fetchRightLane(int splineNumber);
Point generatePointFromLeftLane(double t);
Point generatePointFromRightLane(double t);

int size();
};
#endif