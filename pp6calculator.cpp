#include <iostream>

int main() 
{
  // Declare the variables
  double a(0), b(0), res(0);
  char op('\0');

  // Ask the user what they want to do
  std::cout << "Enter the operation you would like to perform (+, -, *, /):" << std::endl;
  std::cin >> op;

  // check for bad input
  if (!std::cin)
  {
    std::cerr << "[error] Error in input" << std::endl;
    return 1;
  }
  
  // Ask for two numbers from the user
  std::cout << "Enter the first number:" << std::endl;
  std::cin >> a;

  // check for bad input
  if (!std::cin)
  {
    std::cerr << "[error] Error in input" << std::endl;
    return 1;
  }

  std::cout << "Enter the second number:" << std::endl;
  std::cin >> b;

  // check for bad input
  if (!std::cin)
  {
    std::cerr << "[error] Error in input" << std::endl;
    return 1;
  }

  // calculate the result
  if (op == '+')
  {
    res = a + b;
  }
  else if (op == '-')
  {
    res = a - b;
  }
  else if (op == '*')
  {
    res = a * b;
  }
  else if (op == '/')
  {
    if (b == 0)
    {
      std::cerr << "[error] Divide by zero error" << std::endl;
      return 1;
    }
    else
    {
      res = a / b;
    }
  }
  else
  {
    std::cerr << "[error] Operation '" << op << "' not recognised." << std::endl;
    return 1;
  }
  
  // print the answer
  std::cout << "The result of the operation " << op 
            << " on " << a << " and " << b 
            << " is:  " << res << std::endl;
  
  return 0;
}

