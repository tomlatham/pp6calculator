//! \file   PP6FourVector.hpp
//! \author Ben Morgan
//! \brief  Declaration of PP6FourVector
#ifndef PP6FOURVECTOR_HH
#define PP6FOURVECTOR_HH

// Standard Library
#include <string>

//! FourVector class
class FourVector {
 public:
  //! constants and typedefs
  static const double c;
  static const double c2;

 public: // we can use access specifiers as many times as we like
         // it's usually best to use this to break things up by
         // function, e.g. constants/typedefs first, then member functions
         // then member variables
  //! Default constructor
  FourVector() : t(0.0), x(0.0), y(0.0), z(0.0) {}

  //! Copy Constructor
  FourVector(const FourVector& other) : t(other.t), x(other.x), y(other.y), z(other.z) {}

  //! Constructor with values
  FourVector(const double t, const double x, const double y, const double z)
      : t(t), x(x), y(y), z(z) {}

  //! return the interval of the vector
  double interval() const;

  //! boost the vector along the z-axis [1]
  int boost_z(const double velocity);

  //! return a string representation of this vector
  std::string asString() const;

 public:
  //! member variables
  double t;
  double x;
  double y;
  double z;
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

#endif // PP6FOURVECTOR_HH

