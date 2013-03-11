//! \file   PP6FourVector.hpp
//! \author Ben Morgan
//! \brief  Declaration of PP6FourVector
#ifndef PP6FOURVECTOR_HH
#define PP6FOURVECTOR_HH

// Standard Library
#include <string>

//! FourVector structure
struct FourVector;

//! Default Create a new FourVector instance
FourVector* createFourVector();

//! Create a new FourVector instance with components
FourVector* createFourVector(const double t, const double x, const double y,
                             const double z);

//! Destroy a FourVector instance, nulling the supplied pointer
void destroyFourVector(FourVector *&p);

//! compute interval of four vector
double interval(const FourVector* v);

//! boost four vector in z direction
int boost_z(FourVector* v, const double velocity);

//! convert a FourVector to a string representation
std::string asString(const FourVector* v);

#endif // PP6FOURVECTOR_HH

