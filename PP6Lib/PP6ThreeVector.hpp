//! \file   ThreeVector.hpp
//! \author Ben Morgan
//! \brief  Declaration of ThreeVector
#ifndef PP6THREEVECTOR_HH
#define PP6THREEVECTOR_HH

// Standard Library
#include <iosfwd> // Forward declarations for istream, ostream etc
#include <string>

//! ThreeVector class
class ThreeVector {
 public:
  //! Default constructor
  ThreeVector();

  //! Copy Constructor
  ThreeVector(const ThreeVector& other);

  //! Constructor with values
  ThreeVector(const double x, const double y, const double z);

  //! Copy-assignment operator
  ThreeVector& operator=(const ThreeVector& other);
  
  //! Add a vector to this one
  ThreeVector& operator+=(const ThreeVector& rhs);

  //! Subtract a vector from this one
  ThreeVector& operator-=(const ThreeVector& rhs);
  
  //! Multiply vector elements by a constant
  ThreeVector& operator*=(const double rhs);

  //! Divide vector elements by a constant
  ThreeVector& operator/=(const double rhs);

  //! return the length of the vector
  double length() const;

  //! return a string representation of this vector
  std::string asString() const;

  //! get t, x, y, z components of vector
  double getX() const {return x_;}
  double getY() const {return y_;}
  double getZ() const {return z_;}

  //! set t, x, y, z components of vector
  void setX(const double x);
  void setY(const double y);
  void setZ(const double z);

  //! get R, Theta, Phi components of vector
  double getR() const;
  double getTheta() const;
  double getPhi() const;

  //! set R, Theta, Phi components of vector
  void setR(const double r);
  void setTheta(const double theta);
  void setPhi(const double phi);

 private:
  //! recompute interval whenever components change
  void compute_length();
 private:
  //! member variables
  double x_;
  double y_;
  double z_;
  double l_; // current length
};


//! Free I/O streaming operators
std::istream& operator>>(std::istream& in, ThreeVector& vec);
std::ostream& operator<<(std::ostream& out, const ThreeVector& vec);

//! Free operators
ThreeVector operator+(const ThreeVector& lhs, const ThreeVector& rhs);
ThreeVector operator-(const ThreeVector& lhs, const ThreeVector& rhs);
ThreeVector operator*(const ThreeVector& lhs, const double rhs);
ThreeVector operator*(const double lhs, const ThreeVector& rhs);
ThreeVector operator/(const ThreeVector& lhs, const double rhs);
// Unary minus (negate a vector)
ThreeVector operator-(const ThreeVector& vec);

// Free Functions
double scalarProduct(const ThreeVector& a, const ThreeVector& b);


#endif // PP6FOURVECTOR_HH

