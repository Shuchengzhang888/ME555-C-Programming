#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
Vector2D::Vector2D() : x(0.0), y(0.0) {
}
Vector2D::Vector2D(double init_x, double init_y) : x(init_x), y(init_y) {
}

double Vector2D::getMagnitude() const {
  return std::sqrt(x * x + y * y);
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D v;
  v.x = x + rhs.x;
  v.y = y + rhs.y;
  return v;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x = x + rhs.x;
  y = y + rhs.y;
  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  return rhs.x * x + rhs.y * y;
}

void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
}
