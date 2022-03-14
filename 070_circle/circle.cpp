#include "circle.hpp"

#include <cmath>
#include <cstdio>
#include <cstdlib>

#define pi acos(-1.0)

Circle::Circle(Point & center, const double radius) : center(center), radius(radius) {
}
void Circle::move(double dx, double dy) {
  center.Point::move(dx, dy);
}
double Circle::intersectionArea(const Circle & otherCircle) {
  double d = center.Point::distanceFrom(otherCircle.center);
  if (d >= radius + otherCircle.radius) {
    return 0;
  }
  if (otherCircle.radius - radius >= 0) {
    if (otherCircle.radius - radius >= d) {
      return pi * radius * radius;
    }
    double ang1 =
        acos((radius * radius + d * d - otherCircle.radius * otherCircle.radius) /
             (2 * radius * d));
    double ang2 =
        acos((otherCircle.radius * otherCircle.radius + d * d - radius * radius) /
             (2 * otherCircle.radius * d));
    return ang1 * radius * radius + ang2 * otherCircle.radius * otherCircle.radius -
           radius * d * sin(ang1);
  }
  else {
    if (radius - otherCircle.radius >= d) {
      return pi * otherCircle.radius * otherCircle.radius;
    }
    double ang1 =
        acos((otherCircle.radius * otherCircle.radius + d * d - radius * radius) /
             (2 * otherCircle.radius * d));
    double ang2 =
        acos((radius * radius + d * d - otherCircle.radius * otherCircle.radius) /
             (2 * radius * d));
    return ang1 * otherCircle.radius * otherCircle.radius + ang2 * radius * radius -
           otherCircle.radius * d * sin(ang1);
  }
}
