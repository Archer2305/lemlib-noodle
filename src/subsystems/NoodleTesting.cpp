#include "noodle/NoodlePath.hpp"
#include "noodle/PathController.hpp"
#include "noodle/Point.hpp"
#include <cmath>
#include <iostream>
using namespace std;
void func(){
  NoodlePath firstSpline;
  firstSpline.setTarget(Point(1, 1), 22.5);
  firstSpline.generatePoints(Point(0, 0), 89.99);

   NoodlePath secondSpline;
   secondSpline.setTarget(Point(2, 2), 89, 99);
   secondSpline.generatePoints(Point(1, 1), 22.5);

  PathGroup path({firstSpline,secondSpline});
  PathController controller;
  controller.runPath(path);
  cout << "\n\n\n\n\n";
  cout << " ";
}