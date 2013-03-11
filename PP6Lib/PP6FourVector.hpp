//! \file   PP6FourVector.hpp
//! \author Ben Morgan
//! \brief  Declaration of PP6FourVector
#ifndef PP6FOURVECTOR_HH
#define PP6FOURVECTOR_HH

// Standard Library
#include <string>

//! FourVector class
class FourVector {
 public: // we can use access specifiers as many times as we like
         // it's usually best to use this to break things up by
         // function, e.g. constants/typedefs first, then member functions
         // then member variables
  //! Default constructor
  FourVector() : t_(0.0), x_(0.0), y_(0.0), z_(0.0), s_(0.0) {}

  //! Copy Constructor
  FourVector(const FourVector& other) : t_(other.getT()), x_(other.getX()), y_(other.getY()), z_(other.getZ()), s_(other.interval()) {}

  //! Constructor with values
  FourVector(const double t, const double x, const double y, const double z)
      : t_(t), x_(x), y_(y), z_(z) {compute_interval();}

  //! Copy-assignment operator
  FourVector& operator=(const FourVector& other);
  
  //! Add a vector to this one
  FourVector& operator+=(const FourVector& rhs);

  //! Subtract a vector from this one
  FourVector& operator-=(const FourVector& rhs);

  //! return the interval of the vector
  double interval() const;

  //! boost the vector along the z-axis [1]
  int boost_z(const double velocity);

  //! return a string representation of this vector
  std::string asString() const;

  //! get t, x, y, z components of vector
  double getT() const {return t_;}
  double getX() const {return x_;}
  double getY() const {return y_;}
  double getZ() const {return z_;}

  //! set t, x, y, z components of vector
  void setT(const double t) {t_ = t; compute_interval();}
  void setX(const double x) {x_ = x; compute_interval();}
  void setY(const double y) {y_ = y; compute_interval();}
  void setZ(const double z) {z_ = z; compute_interval();}

 private:
  //! constants, but only needed internally to FourVector
  static const double c;
  static const double c2;
 private:
  //! recompute interval whenever components change
  void compute_interval();
 private:
  //! member variables
  double t_;
  double x_;
  double y_;
  double z_;
  double s_; // current interval
};

/*
 * [1] There are several design choices here, boost_z could be:
 * - a const member function, returning a boosted copy of the original
 * - a non-const member function, modifying the original (as shown)
 * - a free function taking a const FourVector and returning a boosted copy
 * - a free function taking a ref. to a FourVector and boosting it
 */

// We can keep the following free functions simply for convenience

//! Default Create a new FourVector instance
FourVector* createFourVector();

//! Create a new FourVector instance with components
FourVector* createFourVector(const double t, const double x, const double y,
                             const double z);

//! Destroy a FourVector instance, nulling the supplied pointer
void destroyFourVector(FourVector *&p);

//! Free I/O streaming operators
std::istream& operator>>(std::istream& in, FourVector& vec);
std::ostream& operator<<(std::ostream& out, const FourVector& vec);

//! Free arithmetic operators
FourVector operator+(const FourVector& lhs, const FourVector& rhs);
FourVector operator-(const FourVector& lhs, const FourVector& rhs);

#endif // PP6FOURVECTOR_HH

