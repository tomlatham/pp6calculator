#include <iostream>
#include <limits>
#include <cmath>

// Note that throughout I've used 'pow(x,y)' which does x^y (including 
// non-integer values)
// This is OK but is unnecessary in these cases as I'm mostly just 
// squaring. 
// This does add a *little* overhead for a function call but does make 
// things easier to read!

//----------------------------------------------------------------------
// Functions
//
double add(double a, double b)
{
  return a + b;
}

double subtract(double a, double b)
{
  return a - b;
}

double multiply(double a, double b)
{
  return a * b;
}

double divide(double a, double b)
{
  return a / b;
}

double intercept(double m, double c)
{
  return divide(-c, m);
}

double quadratic(double a, double b, double c, bool positiveRoot)
{
  double t(sqrt(pow(b, 2) - 4 * a * c));
  double res(0);

  if (positiveRoot)
  {
    res = (-b + t) / (2 * a);
  }
  else
  {
    res = (-b - t) / (2 * a);
  }

  return res;
} 

double length(double x, double y, double z)
{
  return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

double length(double t, double x, double y, double z)
{
  return sqrt(pow(t, 2) - pow(length(x, y, z), 2));
}

double getNumber()
{
  double res(0);

  std::cin >> res;

  while (!std::cin)
  {
    std::cout << "Error in input. Please re-enter." << std::endl;

    // clear the buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // retry
    std::cin >> res;
  }

  return res;
}

//----------------------------------------------------------------------
// Main program
//
int main() 
{
  // Declare the variables
  double res(0), res2(0);
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
    else if((op == '1') || (op == '2') || (op == '3') || (op == '4') )
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
        res = add(a, b);
      }
      else if (op == '2')
      {
        res = subtract(a, b);
      }
      else if (op == '3')
      {
        res = multiply(a, b);
      }
      else if (op == '4')
      {
        if (b == 0)
        {
          std::cerr << "[error] Divide by zero error" << std::endl;
          continue;
        }
        else
        {
          res = divide(a, b);
        }
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

      if (c==0)
      {
        std::cerr << "[error] Divide by zero error" << std::endl;
        continue;
      }
      else
      {
        res = intercept(m, c);
      }
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

      if (pow(b, 2) < (4 * a * c))
      {
        std::cerr << "[error]: No solutions possible (b^2 < 4ac)" 
                  << std::endl;
        continue;
      }
      if (a == 0)
      {
        std::cerr << "[error]: Divide by zero error (a=0)" << std::endl;
        continue;
      }
      else
      {
        res = quadratic(a, b, c, true);
        res2 = quadratic(a, b, c, false);
      }
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

      res = length(x, y, z);
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
  
      if (pow(t,2) < length(x, y, z))
      {
        std::cerr << "[error] Space-like component larger than Time-like"
                  << std::endl;
        continue;
      }

      res = length(t, x, y, z);
    }
    else
    {
      std::cerr << "[error] Operation '" << op << "' not recognised."
                << std::endl;
      continue;
    }
      
    // print the result(s)
    if (op == '6')
    {
      std::cout << "[result]: positive_root: " << res << std::endl;
      std::cout << "[result]: negative_root: " << res2 << std::endl;
    }
    else
    {
      std::cout << "[result]: " << res << std::endl;
    }
  }
  
  std::cout << "Thank you for using pp6calculator!" << std::endl;
  return 0;
}

