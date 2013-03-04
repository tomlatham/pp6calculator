// PP6Day2Menu.cpp : Definitions for PP6Day2Menu functions
//
#include "PP6Day2Menu.hpp"

// Standard Library
#include <iostream>
#include <cmath>
#include <limits>

// This Project
#include "PP6Math.hpp"
#include "PP6Day2VectorAnalysis.hpp"
#include "PP6Day2MuonAnalysis.hpp"

void pp6day2_menu() {
  // Declare the variables
  double resultCode(0); 
  char op('\0');

  while (true)
  {
    // Ask the user what they want to do
    std::cout << "PP6Calculator - Day 2 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Enter the operation you would like to perform:" << std::endl;
    std::cout << "1)  Swap Two Numbers" << std::endl;
    std::cout << "2)  Sort an Array of Numbers" << std::endl;
    std::cout << "3)  Generate and Analyse N Random 4-Vectors" << std::endl;
    std::cout << "4)  Analyse input files for muon pairs" << std::endl;
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
      // - Swap, so ask for two numbers from the user
      double a(0), b(0);
      std::cout << "Enter the first number: ";
      a = getNumber();
      std::cout << "Enter the second number: ";
      b = getNumber();
 
      std::cout << "Before swap (a,b) = (" << a << ", " << b << ")" 
                << std::endl;
      swap(a, b);
      std::cout << "After swap (a,b) = (" << a << ", " << b << ")"
                << std::endl; 
    }
    else if (op == '2')
    {
      // - Read in array, then sort
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
    else if (op == '3')
    {
      resultCode = pp6day2_vectoranalysis();
    }
    else if (op == '4')
    {
      resultCode = pp6day2_muonanalysis();
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
