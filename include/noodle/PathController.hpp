#include "Point.hpp"
#include "NoodlePath.hpp"
#include "PathGroup.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"

extern lemlib::Chassis chassis;

// #include "<vector>"
class PathController{
// private:
// Point currentPosition;
// Point predictedPosition;
// double currentError;
// double predictedError;
// double finalError; // distance way from 
// double errorAngle; //where am i facing vs where should i be facing 


  

public: 
void fetchError(PathGroup path, Point currentPosition,Point passedPoint);//fetch the error
std::vector<double> fetchLaneErrors(PathGroup path, Point currentPosition,
 int currentSplineNumber);
void printLanes(int spline=0);
void updateMap(double leftDistance, double rightDistance);
void runPath(PathGroup path);
// void addAction( void (*functionPointer)(void));
// void executePath(NoodlePath path);//implement this as a thread  in actual code 


};