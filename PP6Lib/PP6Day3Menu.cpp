// PP6Day3Menu.cpp : Definitions for PP6Day2Menu functions
//
#include "PP6Day3Menu.hpp"

// Standard Library
#include <iostream>

// This Project
#include "PP6FourVector.hpp"
#include "PP6Math.hpp"

void pp6day3_menu() {
  // Declare the variables
  // Variables for i/o
  FourVector iV = {0, 0, 0, 0};
  double ivelocity(0.0);
  
  double oInterval(0.0);
  
  double resultCode(0); 
  char op('\0');

  while (true)
  {
    // Ask the user what they want to do
    std::cout << "PP6Calculator - Day 3 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Enter the operation you would like to perform:" << std::endl;
    std::cout << "1)  Create a FourVector and calculate its interval" << std::endl;
    std::cout << "2)  Create and Boost a FourVector" << std::endl;
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
    else if (op == '1')
    {
      // Read in four values
      // Ask user for vector components
      std::cout << "Enter the t-component: ";
      iV.t = getNumber();
      std::cout << "Enter the x-component: ";
      iV.x = getNumber();
      std::cout << "Enter the y-component: ";
      iV.y = getNumber();
      std::cout << "Enter the z-component: ";
      iV.z = getNumber();
      
      oInterval = interval(iV);

      std::cout << "[result]: interval = " << oInterval << std::endl;     
    }
    else if (op == '2')
    {
      // Read in four values
      // Ask user for vector components
      std::cout << "Enter the t-component: ";
      iV.t = getNumber();
      std::cout << "Enter the x-component: ";
      iV.x = getNumber();
      std::cout << "Enter the y-component: ";
      iV.y = getNumber();
      std::cout << "Enter the z-component: ";
      iV.z = getNumber();
      std::cout << "Enter the boost speed along z: ";
      ivelocity = getNumber();

      resultCode = boost_z(iV, ivelocity);
      if (!resultCode) 
      {
        std::cout << "[result] v = ("
                  << iV.t << ", "
                  << iV.x << ", "
                  << iV.y << ", "
                  << iV.z << ")" 
                  << std::endl;
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
      resultCode = 0;
      continue;
    }
  }
}
