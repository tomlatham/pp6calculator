// PP6ThreeVector.cpp : Implementation of PP6ThreeVector
#include "PP6ThreeVector.hpp"

// define needed for MSVC support
#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include <sstream>

//! private arctangent function
double arctan(double y, double x)
{
  if ( x != 0 ) return atan2(y, x);
  if ( y == 0 ) return 0;
  if ( y > 0 ) return M_PI / 2.0;
  else return M_PI / 2.0;
}

ThreeVector::ThreeVector() : x_(0.0), y_(0.0), z_(0.0)
{
  compute_length();
}

ThreeVector::ThreeVector(const ThreeVector& other)
: x_(other.getX()), y_(other.getY()), z_(other.getZ())
{
  compute_length();
}

ThreeVector::ThreeVector(const double x, const double y, 
                               const double z) : x_(x), y_(y), z_(z)
{
  compute_length();
}

ThreeVector& ThreeVector::operator=(const ThreeVector& other)
{
  if ( this != &other ) // Ignore attepmts at self-assignment
  {
    x_ = other.getX();
    y_ = other.getY();
    z_ = other.getZ();
    compute_length();
  }
  return *this;
}

ThreeVector& ThreeVector::operator+=(const ThreeVector& rhs)
{
  x_ += rhs.getX();
  y_ += rhs.getY();
  z_ += rhs.getZ();
  compute_length();
  return *this;
}

ThreeVector& ThreeVector::operator-=(const ThreeVector& rhs)
{
  x_ -= rhs.getX();
  y_ -= rhs.getY();
  z_ -= rhs.getZ();
  compute_length();
  return *this;
}

ThreeVector& ThreeVector::operator*=(const double rhs)
{
  x_ *= rhs;
  y_ *= rhs;
  z_ *= rhs;
  compute_length();
  return *this;
}

ThreeVector& ThreeVector::operator/=(const double rhs)
{
  x_ /= rhs;
  y_ /= rhs;
  z_ /= rhs;
  compute_length();
  return *this;
}

double ThreeVector::length() const
{
  return l_;
}

std::string ThreeVector::asString() const
{
  std::ostringstream s;
  s << *this;
  return s.str();
}

void ThreeVector::setX(const double x)
{
  x_ = x;
  compute_length();
}

void ThreeVector::setY(const double y)
{
  y_ = y;
  compute_length();
}

void ThreeVector::setZ(const double z)
{
  z_ = z;
  compute_length();
}

double ThreeVector::getTheta() const
{
  double perp = sqrt(x_*x_ + y_*y_);
  return ( x_ == 0.0 && y_ == 0.0 && z_ == 0.0 ) ? 0.0 : arctan(perp, z_);
}

double ThreeVector::getPhi() const
{
  return (x_ == 0.0 && y_ == 0.0 && z_ == 0.0 ) ? 0.0 : arctan(y_, x_);
}

void ThreeVector::setR(const double r)
{
  double theta = getTheta();
  double phi = getPhi();
  x_ = r * sin(theta) * sin(phi);
  y_ = r * sin(theta) * cos(phi);
  z_ = r * cos(theta);
  compute_length();
}

void ThreeVector::setTheta(const double theta)
{
  double phi = getPhi();
  x_ = l_ * sin(theta) * cos(phi);
  y_ = l_ * sin(theta) * sin(phi);
  z_ = l_ * cos(theta);
  compute_length();
}

void ThreeVector::setPhi(const double phi)
{
  double perp = sqrt(x_*x_ + y_*y_);
  x_ = perp * cos(phi);
  y_ = perp * sin(phi);
  // z unchanged
  compute_length();
}

void ThreeVector::rotateX(const double angle)
{
  const double oldy = y_;
  const double oldz = z_;
  y_ = cos(angle)*oldy - sin(angle)*oldz;
  z_ = sin(angle)*oldy + cos(angle)*oldz;
}

void ThreeVector::rotateY(const double angle)
{
  const double oldx = x_;
  const double oldz = z_;
  z_ = cos(angle)*oldz - sin(angle)*oldx;
  x_ = sin(angle)*oldz + cos(angle)*oldx;
}

void ThreeVector::rotateZ(const double angle)
{
  const double oldx = x_;
  const double oldy = y_;
  x_ = cos(angle)*oldx - sin(angle)*oldy;
  y_ = sin(angle)*oldx + cos(angle)*oldy;
}

void ThreeVector::compute_length()
{
  l_ = sqrt(x_*x_ + y_*y_ + z_*z_);
}

ThreeVector operator+(const ThreeVector& lhs, const ThreeVector& rhs)
{
  ThreeVector temp(lhs);
  temp += rhs;
  return temp;
}

ThreeVector operator-(const ThreeVector& lhs, const ThreeVector& rhs)
{
  ThreeVector temp(lhs);
  temp -= rhs;
  return temp;
}

ThreeVector operator*(const ThreeVector& lhs, const double rhs)
{
  ThreeVector temp(lhs);
  temp *= rhs;
  return temp;
}

ThreeVector operator*(const double lhs, const ThreeVector& rhs)
{
  ThreeVector temp(rhs);
  temp *= lhs;
  return temp;
}

ThreeVector operator/(const ThreeVector& lhs, const double rhs)
{
  ThreeVector temp(lhs);
  temp /= rhs;
  return temp;
}

ThreeVector operator-(const ThreeVector& vec)
{
  return ThreeVector(-vec.getX(), -vec.getY(), -vec.getZ());
}

std::istream& operator>>(std::istream& in, ThreeVector& vec)
{
  // NB: As we use setX(), setY(), setZ() we call compute_length() 
  // three times! Whilst that's not great, it avoids having the streaming
  // operator as a friend of ThreeVector...
  std::string dummy;
  double x(0), y(0), z(0);
  in >> dummy >> x >> dummy >> y >> dummy >> z >> dummy;
  vec.setX(x);
  vec.setY(y);
  vec.setZ(z);
  return in;
}

std::ostream& operator<<(std::ostream& out, const ThreeVector& vec)
{
  out << "( " << vec.getX() << " , " << vec.getY() << " , " << vec.getZ() << " )";
  return out;
}

double scalarProduct(const ThreeVector& a, const ThreeVector& b)
{
  return a.getX() * b.getX() + a.getY() * b.getY()  + a.getZ() * b.getZ();
}

