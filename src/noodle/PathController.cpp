#include "PathController.hpp"
#include "NoodlePath.hpp"
#include "C:\Users\arjin\OneDrive\Desktop\LemLibProject -Noodle\include\main.h"
#include "lemlib/chassis/chassis.hpp"
#include "vector"
#include <cmath>
  bool isDone=false;

std::vector<double> PathController::fetchLaneErrors(PathGroup path, Point currentPosition,int currentSplineNumber) {
  std::vector<double> arr;
  double distanceLeft = 99999;
  double tLeft = -1;
  double end = 120;
  bool Lbreak = false;
  bool Rbreak = false;
  if (currentSplineNumber == path.size()) {
    end = 100;
  }
  //[pranav is the ebst and he is daddy of noodle curve fuck aayush i want pr jk i love aayush i would love to see him suceed]
  for (int i = 0; i < end; i++) { // end is a  variable to account for the last
                                  // spline to prevent look ahead errors

    Point p = path.generatePointFromLeftLane(currentSplineNumber + (i / 100.0));
    if (distanceLeft > std::sqrt(std::pow(p.x - currentPosition.x, 2) +
                                 std::pow(p.y - currentPosition.y, 2))) {
      distanceLeft = std::sqrt(std::pow(p.x - currentPosition.x, 2) +
                               std::pow(p.y - currentPosition.y, 2));
      tLeft = i / 100.0;
    }
  }
 
  std::cout << " \n Closest Point Left: ";
  path.generatePointFromLeftLane(tLeft).print("\n\n");
  std::cout << "\n Left Lane Distance Error:\t" << distanceLeft;
  arr.push_back(distanceLeft);
  double distanceRight = 99999;
  double tRight = -1;
  for (int i = 0; i < end; i++) { // 120 to generate 20 points into the next spline
    Point p =
        path.generatePointFromRightLane(currentSplineNumber + (i / 100.0));
    if (distanceRight > std::sqrt(std::pow(p.x - currentPosition.x, 2) +
                                  std::pow(p.y - currentPosition.y, 2))) {
      distanceRight = std::sqrt(std::pow(p.x - currentPosition.x, 2) +
                                std::pow(p.y - currentPosition.y, 2));
      tRight = i / 100.0;
    }
  }
   if (end == 100) { // if its on the last spline
     //t is local so ther is no need to worry about using the correct spline 
     Lbreak= ( tLeft>0.70); //turn on the Left brake
     Rbreak= (tRight>0.70);// turn on the Right brake
     isDone=true;
     arr.push_back(0);
     arr.push_back(0);
     return arr;
    }
  std::cout << " \n Closest Point Right: ";
  path.generatePointFromRightLane(tRight).print("\n\n");
  std::cout << "\n Right Lane Distance Error:\t" << distanceRight;
  arr.push_back(distanceRight);
  return arr;
}


void PathController::runPath(PathGroup path){

  Point currentPos;
  std::vector<double> map;
  int splineNumber=0;
  //TODO 
/* current spline number
 * current position -- done
 *update isDone
 *
 *
 *
 */
while(!isDone){
  currentPos.x=chassis.getPose().x;
  currentPos.y=chassis.getPose().y;

  map=fetchLaneErrors(path,currentPos,splineNumber);  
  chassis.tank(map[0],map[1]);

}
}


// double PathController::fetchError( const NoodlePath& path, Point
// currentPosition,Point predictedPosition,Point passedPoint){

//   }
// }