// PP6Day3Menu.cpp : Definitions for PP6Day2Menu functions
//
#include "PP6Day3Menu.hpp"

// Standard Library
#include <iostream>
#include <limits>

// This Project
#include "PP6FourVector.hpp"
#include "PP6Math.hpp"
#include "PP6Day3MuonAnalysis.hpp"

FourVector* userCreateFourVector() 
{
  double it(0), ix(0), iy(0), iz(0);

  // Ask user for vector components
  std::cout << "Enter the t-component: ";
  it = getNumber();
  std::cout << "Enter the x-component: ";
  ix = getNumber();
  std::cout << "Enter the y-component: ";
  iy = getNumber();
  std::cout << "Enter the z-component: ";
  iz = getNumber();
 
  return createFourVector(it, ix, iy, iz);
}


void pp6day3_menu() {
  // Declare the variables
  // Variables for i/o
  FourVector *iV(0), *iU(0);
  double ivelocity(0.0);
  
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
    std::cout << "3)  Add two FourVectors" << std::endl;
    std::cout << "4)  Analyse input files for muon pairs (Day 3 version)" 
              << std::endl;
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
      // Read in the four vector
      iV = userCreateFourVector();
      std::cout << "[result]: interval = " << iV->interval() << std::endl;
      destroyFourVector(iV);    
    }
    else if (op == '2')
    {
      // Read in the four vector and velocity
      iV = userCreateFourVector();

      std::cout << "Enter the boost speed along z: ";
      ivelocity = getNumber();

      resultCode = iV->boost_z(ivelocity);
      if (!resultCode) 
      {
        std::cout << "[result] v = " << iV->asString() << std::endl;
        destroyFourVector(iV);
      }
    }
    else if (op == '3')
    {
      // Read in the two FourVectors
      std::cout << "Details for 1st FourVector:" << std::endl;
      iV = userCreateFourVector();
      std::cout << "Details for 2nd FourVector:" << std::endl;
      iU = userCreateFourVector();
      FourVector sum = (*iV) + (*iU);
      std::cout << "[result] v = " << sum << std::endl;
      destroyFourVector(iV);
      destroyFourVector(iU);
    }
    else if (op == '4')
    {
      resultCode = pp6day3_muonanalysis();
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
      destroyFourVector(iV);
      destroyFourVector(iU);
      continue;
    }
  }
}
