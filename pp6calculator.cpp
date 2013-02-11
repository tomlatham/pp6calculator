#include <iostream>
#include <limits>

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
  double res(0);
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
    else
    {
      std::cerr << "[error] Operation '" << op << "' not recognised."
                << std::endl;
      continue;
    }
      
    // print the result
    std::cout << "[result]: " << res << std::endl;
  }
  
  std::cout << "Thank you for using pp6calculator!" << std::endl;
  return 0;
}

