// Standard Library
#include <iostream>
#include <limits>
#include <cmath>

// This Project
#include "PP6Math.hpp"

//----------------------------------------------------------------------
// Main program
//
int main() 
{
  // Declare the variables
  double resultCode(0), answerHolder(0), answerHolder2(0);
  char op('\0');
  
  while (true)
  {
    // Ask the user what they want to do
    std::cout << "Enter the operation you would like to perform:" << std::endl;
    std::cout << "1)  Addition" << std::endl;
    std::cout << "2)  Subtraction" << std::endl;
    std::cout << "3)  Multiplication" << std::endl;
    std::cout << "4)  Division" << std::endl;
    std::cout << "5)  Intercept" << std::endl;
    std::cout << "6)  Quadratic Solver" << std::endl;
    std::cout << "7)  Length of 3-Vector" << std::endl;
    std::cout << "8)  Length of 4-Vector" << std::endl;
    std::cout << "9)  Invariant Mass of Two Particles" << std::endl;
    std::cout << "0)  Swap Two Numbers" << std::endl;
    std::cout << "s)  Sort an Array of Numbers" << std::endl;
    std::cout << "q)  Quit" << std::endl;
    std::cout << ">> ";
    
    std::cin >> op;
      
    // check for bad input
    if(!std::cin)
    {
      std::cerr << "[error] Error in input" << std::endl;
    
      // clear the buffer
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    // Handle menu operation
    if (op == 'q')
    {
      break;
    }
    else if((op == '1') || (op == '2') || (op == '3') || (op == '4') || 
            (op == '0'))
    {
      // Arithmetic operations, so ask for two numbers from the user
      double a(0), b(0);
      std::cout << "Enter the first number: ";
      a = getNumber();
      std::cout << "Enter the second number: ";
      b = getNumber();
       
      // calculate the result
      if (op == '1')
      {
        resultCode = add(a, b, answerHolder);
      }
      else if (op == '2')
      {
        resultCode = subtract(a, b, answerHolder);
      }
      else if (op == '3')
      {
        resultCode = multiply(a, b, answerHolder);
      }
      else if (op == '4')
      {
        resultCode = divide(a, b, answerHolder);
      }
      else if (op == '0')
      {
        std::cout << "Before swap (a,b) = (" << a << ", " << b << ")" 
                  << std::endl;
        swap(a, b);
        std::cout << "After swap (a,b) = (" << a << ", " << b << ")"
                  << std::endl; 
      }
    }
    else if (op == '5')
    {
      double m(0), c(0);

      // Ask for two numbers from the user
      std::cout << "Enter the gradient: ";
      m = getNumber();
      std::cout << "Enter the y intercept: ";
      c = getNumber();
      resultCode = intercept(m, c, answerHolder);
    }
    else if (op == '6')
    {
      // Solve ax^2 + bx + c = 0
      double a(0), b(0), c(0);

      // Ask user for quadratic coefficients
      std::cout << "Enter the square coefficient: ";
      a = getNumber();
      std::cout << "Enter the linear coefficient: ";
      b = getNumber();
      std::cout << "Enter the constant coefficient: ";
      c = getNumber();
      
      resultCode = quadratic(a, b, c, answerHolder, answerHolder2);
    }
    else if (op == '7')
    {
      // Calculate sqrt(x^2+y^2+z^2)
      double x(0), y(0), z(0);

      // Ask user for vector components
      std::cout << "Enter the x-component: ";
      x = getNumber();
      std::cout << "Enter the y-component: ";
      y = getNumber();
      std::cout << "Enter the z-component: ";
      z = getNumber();

      resultCode = length(x, y, z, answerHolder);
    }
    else if (op == '8')
    {
      // Calculate sqrt(t^2 - (x^2+y^2+z^2))
      double x(0), y(0), z(0), t(0);

      // Ask user for vector components
      std::cout << "Enter the x-component: ";
      x = getNumber();
      std::cout << "Enter the y-component: ";
      y = getNumber();
      std::cout << "Enter the z-component: ";
      z = getNumber();
      std::cout << "Enter the t-component: ";
      t = getNumber();
      
      resultCode = length(t, x, y, z, answerHolder);
    }
    else if (op == '9')
	  {
      double e1(0), px1(0), py1(0), pz1(0), e2(0), px2(0), py2(0), pz2(0);

      // Ask for eight numbers from the user
      std::cout << "Enter the px value for the first particle: ";
      px1 = getNumber();
      std::cout << "Enter the py value for the first particle: ";
      py1 = getNumber();
      std::cout << "Enter the pz value for the first particle: ";
      pz1 = getNumber();
      std::cout << "Enter the e value for the first particle: ";
      e1 = getNumber();

      std::cout << "Enter the px value for the second particle: ";
      px2 = getNumber();
      std::cout << "Enter the py value for the second particle: ";
      py2 = getNumber();
      std::cout << "Enter the pz value for the second particle: ";
      pz2 = getNumber();
      std::cout << "Enter the e value for the second particle: ";
      e2 = getNumber();

      resultCode = inv_mass(e1, px1, py1, pz1, 
                            e1, px1, py1, pz1, 
                            answerHolder);
    }
    else if (op == 's')
    {
      int arraySize(0);
      std::cout << "Enter the size of the array: ";
      arraySize = getNumber();
      if ((arraySize > 0) && (arraySize < 11))
      {
        double *currentArray = new double[arraySize];
        for (int i = 0; i < arraySize; ++i)
        {
          std::cout << "Enter the value of element " << i << ": ";
          currentArray[i] = getNumber();
        }

        std::cout << "Array before sorting:" << std::endl;
        printArray(currentArray, arraySize);
        
        basic_sort(currentArray, arraySize);
        
        std::cout << "Array after sorting:" << std::endl;
        printArray(currentArray, arraySize);
        
        delete [] currentArray;
      }
      else {
        std::cerr << "[error]: Array size must be between 1 and 10" << std::endl;
      }
    }
    else
    {
      std::cerr << "[error] Operation '" << op << "' not recognised."
                << std::endl;
      continue;
    }

    // Handle any errors
    if (resultCode)
    {
      std::cerr << "[error] Operation '" << op 
                << "' returned a non-zero code '" << resultCode
                << "'. Please check parameters."
                << std::endl;
      continue;
    }

    // if all is well, print the result(s)
    if (op == '6')
    {
      std::cout << "[result]: positive_root: " << answerHolder << std::endl;
      std::cout << "[result]: negative_root: " << answerHolder2 << std::endl;
    }
    else if ((op != '0') && (op != 's'))
    {
      std::cout << "[result]: " << answerHolder << std::endl;
    }
  }
  
  std::cout << "Thank you for using pp6calculator!" << std::endl;
  return 0;
}


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


