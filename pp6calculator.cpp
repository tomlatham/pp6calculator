#include <iostream>

int main() 
{
  // Declare the variables
  double a(0), b(0);
  
  // Ask for two numbers from the user
  std::cout << "Enter the first number:" << std::endl;
  std::cin >> a;
  
  std::cout << "Enter the second number:" << std::endl;
  std::cin >> b;
  
  // calculate the product and print the answer
  std::cout << "The product of " << a << " and " << b << " is:  " << a*b << std::endl;
  
  return 0;
}

