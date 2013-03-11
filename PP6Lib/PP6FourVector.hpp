//! \file   PP6FourVector.hpp
//! \author Ben Morgan
//! \brief  Declaration of PP6FourVector
#ifndef PP6FOURVECTOR_HH
#define PP6FOURVECTOR_HH

//! compute interval of four vector
double interval(const double t, const double x, const double y, 
                const double z);

//! boost four vector in z direction
int boost_z(const double t, const double x, const double y, const double z, 
            const double velocity, double& t_prime, double& x_prime, 
            double& y_prime, double& z_prime);

#endif // PP6FOURVECTOR_HH

