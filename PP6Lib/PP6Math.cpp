// PP6Math.cpp : Definitions for PP6Math Functions
//
#include "PP6Math.hpp"

// Standard Library
#include <iostream>
#include <limits>
#include <cmath>

//----------------------------------------------------------------------
// Function Definitions
//
// Note that throughout I've used 'pow(x,y)' which does x^y (including 
// non-integer values)
// This is OK but is unnecessary in these cases as I'm mostly just 
// squaring. 
// This does add a *little* overhead for a function call but does make 
// things easier to read!

int add(double a, double b, double& answer)
{
  answer = a + b;
  return 0;
}

int subtract(double a, double b, double& answer)
{
  answer = a - b;
  return 0;
}

int multiply(double a, double b, double& answer)
{
  answer = a * b;
  return 0;
}

int divide(double a, double b, double& answer)
{
  if (b == 0)
  {
    return 1;
  }
  
  answer = a / b;
  return 0;
}

int intercept(double m, double c, double& answer)
{
  return divide(-c, m, answer);
}

int quadratic(double a, double b, double c, double& positiveRoot,
              double& negativeRoot)
{
  // No divide by zero
  if (a == 0)
  {
    return 1;
  }

  double t(pow(b, 2) - 4 * a * c);

  // Only allow real roots
  if (t < 0)
  {
    return 2;
  }

  positiveRoot = (-b + sqrt(t)) / (2 * a);
  negativeRoot = (-b - sqrt(t)) / (2 * a);

  return 0;
} 

double length(double x, double y, double z, double& vectorLength)
{
  vectorLength = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
  return 0;
}

double length(double t, double x, double y, double z, double& vectorLength)
{
  double spaceLength(0);
  if (length(x, y, z, spaceLength))
  {
    return 1;
  }

  double timeSquared(pow(t, 2));
  double spaceSquared(pow(spaceLength, 2));

  // Only time-like vectors allowed
  if (timeSquared < spaceSquared)
  {
    return 2;
  }

  vectorLength = sqrt(timeSquared - spaceSquared);
  return 0;
}

double inv_mass(double e1, double px1, double py1, double pz1, 
                double e2, double px2, double py2, double pz2,
                double& invariantMass)
{
  double tot_e(e1 + e2);
  double tot_px(px1 + px2);
  double tot_py(py1 + py2);
  double tot_pz(pz1 + pz2);

  if (length(tot_e, tot_px, tot_py, tot_pz, invariantMass))
  {
    return 1;
  }
  return 0; 
}

int swap(double& a, double& b)
{
  double tmp(a);
  a = b;
  b = tmp;
  return 0;
}

int basic_sort(double *arr, int size)
{
  // Perform a bubble sort on the given array
  bool done(true);

  while (true)
  {
    done = true;

    for (int i = 0; i < size-1; ++i)
    {
      if (arr[i] < arr[i+1])
      {
        swap(arr[i], arr[i+1]);
        done = false;
      }
    }

    if (done)
    {
      break;
    }
  }
  return 0;
}

void printArray(double *arr, int size)
{
  std::cout << "[array:" << arr << "]{";
  for (int i = 0; i < size - 1; ++i)
  {
    std::cout << arr[i] << ", ";
  }
  std::cout << arr[size - 1] << "}" << std::endl;
}

double getNumber()
{
  double res(0);

  std::cin >> res;

  while (!std::cin)
  {
    std::cout << "Error in input. Please re-enter >> ";

    // clear the buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // retry
    std::cin >> res;
  }

  return res;
}

