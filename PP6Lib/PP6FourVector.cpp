// PP6FourVector.cpp : Implementation of PP6FourVector

#include <cmath>
#include <PP6FourVector.hpp>

//! local consts for speed of light
const double c = 3E8;
const double c2 = 9E16;

double interval(const double t, const double x, const double y, 
                const double z)
{
  // interval s^2 = (ct)^2 - (x^2 + y^2 + z^2)
  double s = c2*t*t - (x*x + y*y + z*z);        
  return s;
}

int boost_z(const double t, const double x,const double y, const double z, 
            const double velocity, double& t_prime, double& x_prime, 
            double& y_prime, double& z_prime) 
{
  if ( velocity >= c ) // Cannot boost faster than speed of light
  {
    return 1; // Indicate error
  }

  // Boost along z direction
  // x and y remain unchanged
  x_prime = x;
  y_prime = y;
  // Calculate Lorentz factor
  double gamma = 1.0 / sqrt(1.0 - velocity * velocity / c2);
  // Apply boost in z direction
  z_prime = gamma * ( z - velocity * t);
  t_prime = gamma * ( t - velocity * z / c2);
  
  return 0; // Indicate success
}


