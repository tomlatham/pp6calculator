// PP6FourVector.cpp : Implementation of PP6FourVector
#include <PP6FourVector.hpp>

#include <cmath>
#include <sstream>

//! local consts for speed of light
const double c = 3E8;
const double c2 = 9E16;

//! FourVector structure
struct FourVector
{
  double t;
  double x;
  double y;
  double z;
};


//! Default Create a new FourVector instance
FourVector* createFourVector() {
  return createFourVector(0.0, 0.0, 0.0, 0.0);
}

//! Create a new FourVector instance with components
FourVector* createFourVector(const double t, const double x, const double y,
                             const double z) {
  FourVector *p = new FourVector;
  p->t = t;
  p->x = x;
  p->y = y;
  p->z = z;
  return p;
}

//! Destroy a FourVector instance, nulling the supplied pointer
void destroyFourVector(FourVector *&p) {
  if (p) 
  {
    delete p;
    p = 0;
  }
}

double interval(const FourVector* v)
{
  // interval s^2 = (ct)^2 - (x^2 + y^2 + z^2)
  double s = c2* v->t * v->t - (v->x * v->x + v->y * v->y + v->z * v->z);        
  return s;
}

int boost_z(FourVector* v, const double velocity) 
{
  if ( velocity >= c ) // Cannot boost faster than speed of light
  {
    return 1; // Indicate error
  }

  // Boost along z direction
  // x and y remain unchanged
  
  // Calculate Lorentz factor
  double gamma = 1.0 / sqrt(1.0 - velocity * velocity / c2);
  
  // Apply boost in z direction - need temp variables due to mixing
  double z_prime = gamma * ( v->z - velocity * v->t);
  double t_prime = gamma * ( v->t - velocity * v->z / c2);
  v->z = z_prime;
  v->t = t_prime;

  return 0; // Indicate success
}

std::string asString(const FourVector* v)
{
  std::ostringstream s;
  s << "(" << v->t << ", " << v->x << ", " << v->y << ", " << v->z << ")";
  return s.str();
}

