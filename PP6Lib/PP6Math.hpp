//! \file   PP6Math.hpp
//! \author Ben Morgan
//! \brief  Declarations for PP6Math Functions  
#ifndef PP6CALCULATOR_PP6MATH_HH
#define PP6CALCULATOR_PP6MATH_HH

#include <string>

// - Arithmetic
int add(double a, double b, double& answer);
int subtract(double a, double b, double& answer);
int multiply(double a, double b, double& answer);
int divide(double a, double b, double& answer);

// - Solvers
int intercept(double m, double c, double& answer);
int quadratic(double a, double b, double c, double& positiveRoot,
              double& negativeRoot);

// - Statistics
int getMeanAndStdDev(double *x, int size, double& mean, double& stddev);

// - Vectors
double length(double x, double y, double z, double& vectorLength);
double length(double t, double x, double y, double z, double& vectorLength);

int sumVectors(double *x, double *y, double *z, int size, 
               double &sumX, double &sumY, double &sumZ);

// - Physics
double inv_mass(double e1, double px1, double py1, double pz1, 
                double e2, double px2, double py2, double pz2,
                double& invariantMass);

// - Utility
int swap(double &a, double &b);
int swap(int &a, int &b);
int basic_sort(double *arr, int size);
int associative_sort(double *arr, int *indices, int size);
void printArray(double *arr, int size);

double getRandom();

double getNumber();
std::string getString();

#endif // PP6CALCULATOR_PP6MATH_HH

