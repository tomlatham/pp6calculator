// PP6Day1Menu.cpp : Definitions for PP6Day1Menu functions
//
#include "PP6Day1Menu.hpp"

// Standard Library
#include <iostream>
#include <limits>

// This Project
#include "PP6Math.hpp"

void pp6day1_menu() {
  // Declare the variables
  double resultCode(0), answerHolder(0), answerHolder2(0);
  char op('\0');
  
  while (true)
  {
    // Ask the user what they want to do
    std::cout << "PP6Calculator - Day 1 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
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
    else if((op == '1') || (op == '2') || (op == '3') || (op == '4'))
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
                            e2, px2, py2, pz2, 
                            answerHolder);
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
    else 
    {
      std::cout << "[result]: " << answerHolder << std::endl;
    }
  }
}

