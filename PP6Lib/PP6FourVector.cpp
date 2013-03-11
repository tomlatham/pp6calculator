// PP6FourVector.cpp : Implementation of PP6FourVector
#include <PP6FourVector.hpp>

#include <cmath>
#include <sstream>

//! FourVector consts for speed of light
// Set both to 1 if you want natural units
const double FourVector::c(3E8);
const double FourVector::c2(9E16);

//----------------------------------------------------------------------
// Member functions

double FourVector::interval() const
{
  return s_;
}

int FourVector::boost_z(const double velocity) 
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
  double z_prime = gamma * ( z_ - velocity * t_);
  double t_prime = gamma * ( t_ - velocity * z_ / c2);
  z_ = z_prime;
  t_ = t_prime;

  return 0; // Indicate success
}

std::string FourVector::asString() const
{
  std::ostringstream s;
  s << "(" << getT() << ", " << getX() << ", " << getY() << ", " << getZ() << ")";
  return s.str();
}

void FourVector::compute_interval()
{
  // interval s^2 = (ct)^2 - (x^2 + y^2 + z^2)
  s_ = c2*t_*t_ - (x_*x_ + y_*y_ + z_*z_);        
} 


//----------------------------------------------------------------------
// Free functions - we can retain these for convenience!

//! Default Create a new FourVector instance
FourVector* createFourVector() {
  return new FourVector;
}

//! Create a new FourVector instance with components
FourVector* createFourVector(const double t, const double x, const double y,
                             const double z) {
  FourVector *p = new FourVector(t, x, y, z);
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

