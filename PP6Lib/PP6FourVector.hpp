//! \file   PP6FourVector.hpp
//! \author Ben Morgan
//! \brief  Declaration of PP6FourVector
#ifndef PP6FOURVECTOR_HH
#define PP6FOURVECTOR_HH

//! FourVector structure
struct FourVector
{
  double t;
  double x;
  double y;
  double z;
};

//! compute interval of four vector
double interval(const FourVector& v);

//! boost four vector in z direction
int boost_z(FourVector& v, const double velocity);

#endif // PP6FOURVECTOR_HH

