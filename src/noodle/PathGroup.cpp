#include "noodle/PathGroup.hpp"
#include <cmath>
std::vector<NoodlePath> arr; // vector that only holds paths.

PathGroup::PathGroup(const std::vector<NoodlePath> inp) { arr = inp; }
Point PathGroup::generatePoint(double t) {
  t = t * 100.0; // to prevent dealing with flooring and modding issues
  // let localT be the t per spline;
  //  t=0.1, 1.2,2.4..
  //  localT= 0.1-0.99
  int splineNumber = floor(t / 100.0);
  double localT = std::fmod(t, 100.0) / 100;
  // std:: cout<< "Spline number: \t " << splineNumber <<"\n local T:\t " <<
  // localT << "\n\n";
  // add a case for if its possible to generate that point

  return arr[splineNumber].generateSinglePoint(localT);
}

void PathGroup::printLanes(int splineNumber) {
  // create the lane
  double K = 0.05;
  NoodlePath currentSpline = arr[splineNumber];
  double Ta = currentSpline.getTargetAngle();
  double Ia = currentSpline.getInitialAngle();
  NoodlePath leftLane;

  leftLane.setTarget(Point(currentSpline.getTargetPoint().x + K * sin(Ta),
                           currentSpline.getTargetPoint().y + K * cos(Ta)),
                     Ta * (180 / 3.1415));
  leftLane.generatePoints(
      Point(currentSpline.getInitialPoint().x + -K * sin(Ia),
            currentSpline.getInitialPoint().y + K * cos(Ia)),
      Ia * (180 / 3.1415));
  std::cout << "Left Lane: \t \n";
  leftLane.printPoints();

  NoodlePath rightLane;
  rightLane.setTarget(Point(currentSpline.getTargetPoint().x + (-K * sin(Ta)),
                            currentSpline.getTargetPoint().y + (-K * cos(Ta))),
                      Ta * (180 / 3.1415));
  rightLane.generatePoints(
      Point(currentSpline.getInitialPoint().x + K * sin(Ia),
            currentSpline.getInitialPoint().y + (-K * cos(Ia))),
      Ia * (180 / 3.1415));

  std::cout << " \n\n Right Lane: \t \n";
  rightLane.printPoints();
}
NoodlePath PathGroup::fetchLeftLane(int splineNumber) {
  // create the lane
  double K = 0.05;
  NoodlePath currentSpline = arr[splineNumber];
  double Ta = currentSpline.getTargetAngle();
  double Ia = currentSpline.getInitialAngle();
  NoodlePath leftLane;

  leftLane.setTarget(Point(currentSpline.getTargetPoint().x + K * sin(Ta),
                           currentSpline.getTargetPoint().y + K * cos(Ta)),
                     Ta * (180 / 3.1415));
  leftLane.generatePoints(
      Point(currentSpline.getInitialPoint().x + -K * sin(Ia),
            currentSpline.getInitialPoint().y + K * cos(Ia)),
      Ia * (180 / 3.1415));

  return leftLane;
}

NoodlePath PathGroup::fetchRightLane(int splineNumber) {
  // create the lane
  double K = 0.05;
  NoodlePath currentSpline = arr[splineNumber];
  double Ta = currentSpline.getTargetAngle();
  double Ia = currentSpline.getInitialAngle();

  NoodlePath rightLane;
  rightLane.setTarget(Point(currentSpline.getTargetPoint().x + (-K * sin(Ta)),
                            currentSpline.getTargetPoint().y + (-K * cos(Ta))),
                      Ta * (180 / 3.1415));
  rightLane.generatePoints(
      Point(currentSpline.getInitialPoint().x + K * sin(Ia),
            currentSpline.getInitialPoint().y + (-K * cos(Ia))),
      Ia * (180 / 3.1415));

  return rightLane;
}
Point PathGroup::generatePointFromLeftLane(double t) {
  t = t * 100.0; // to prevent dealing with flooring and modding issues
  // let localT be the t per spline;
  //  t=0.1, 1.2,2.4..
  //  localT= 0.1-0.99
  int splineNumber = floor(t / 100.0);
  double localT = std::fmod(t, 100.0) / 100;
  // std:: cout<< "Spline number: \t " << splineNumber <<"\n local T:\t " <<
  // localT << "\n\n";
  // add a case for if its possible to generate that point

  return fetchLeftLane(splineNumber).generateSinglePoint(localT);
}
Point PathGroup::generatePointFromRightLane(double t) {
  t = t * 100.0; // to prevent dealing with flooring and modding issues
  // let localT be the t per spline;
  //  t=0.1, 1.2,2.4..
  //  localT= 0.1-0.99
  int splineNumber = floor(t / 100.0);
  double localT = std::fmod(t, 100.0) / 100;
  // std:: cout<< "Spline number: \t " << splineNumber <<"\n local T:\t " <<
  // localT << "\n\n";
  // add a case for if its possible to generate that point

  return fetchRightLane(splineNumber).generateSinglePoint(localT);
}
int PathGroup::size() { return 101 * arr.size(); }