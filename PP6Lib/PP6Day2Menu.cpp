// PP6Day2Menu.cpp : Definitions for PP6Day2Menu functions
//
#include "PP6Day2Menu.hpp"

// Standard Library
#include <iostream>
#include <cmath>

// This Project
#include "PP6Math.hpp"

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
      // Read in number of 4-Vectors to generate
      //
      int numberOfVectors(0);
      std::cout << "Enter number of vectors to generate: ";
      numberOfVectors = getNumber();
      if ((numberOfVectors > 0) && (numberOfVectors < 1001))
      {
        // Create arrays and variables
        double *energy = new double[numberOfVectors];
        double *momnX = new double[numberOfVectors];
        double *momnY = new double[numberOfVectors];
        double *momnZ = new double[numberOfVectors];
        int *indices = new int[numberOfVectors];
        double mass(0);
        double momnMagnitude(0), totalMomnX(0), totalMomnY(0), totalMomnZ(0);
        double meanEnergy(0), stddevEnergy(0);

        // Loop to fill arrays
        for(int i(0); i < numberOfVectors; ++i)
        {
          // Index for use in sorting later
          indices[i] = i;

          // Momenta first
          momnX[i] = 100.0 * getRandom();
          momnY[i] = 100.0 * getRandom();
          momnZ[i] = 100.0 * getRandom();

          // Mass next
          mass = 100.0 * getRandom();

          // Momentum magnitude and energy
          length(momnX[i], momnY[i], momnY[i], momnMagnitude);
          energy[i] = sqrt(mass * mass + momnMagnitude);
        }

        // Compute and display total three momentum
        if (sumVectors(momnX, momnY, momnZ, numberOfVectors,
                       totalMomnX, totalMomnY, totalMomnZ))
        {
          std::cerr << "[error]: Failed to calculate total 3-momentum" << std::endl;
          // Tidy up arrays
          delete [] energy;
          delete [] momnX;
          delete [] momnY;
          delete [] momnZ;
          delete [] indices;
          continue;
        }

        if (length(totalMomnX, totalMomnY, totalMomnZ, momnMagnitude))
        {
          std::cerr << "[error]: Failed to calculate 3-momentum magnitude" << std::endl;
          // Tidy up arrays
          delete [] energy;
          delete [] momnX;
          delete [] momnY;
          delete [] momnZ;
          delete [] indices;
          continue;
        }

        std::cout << "[Total 3-Momentum] : P("
                  << totalMomnX << ", "
                  << totalMomnY << ", "
                  << totalMomnZ << "), "
                  << "|P| = "
                  << momnMagnitude 
                  << std::endl;

        // Calculate average energy and standard deviation
        if (getMeanAndStdDev(energy, numberOfVectors, meanEnergy, stddevEnergy))
        {
          std::cerr << "[error]: Failed to calculate energy statistics" << std::endl;
          // Tidy up arrays
          delete [] energy;
          delete [] momnX;
          delete [] momnY;
          delete [] momnZ;
          delete [] indices;
          continue;
        }

        std::cout << "[Mean Energy] : E = "
                  << meanEnergy 
                  << " +/- "
                  << stddevEnergy
                  << std::endl;

        // Sort and find highest energy
        if (associative_sort(energy, indices, numberOfVectors))
        {
          std::cerr << "[error]: Failed to sort energy array" << std::endl;
          // Tidy up arrays
          delete [] energy;
          delete [] momnX;
          delete [] momnY;
          delete [] momnZ;
          delete [] indices;
          continue;
        }

        std::cout << "[Maximum Energy] : E = "
                  << energy[indices[0]] 
                  << ", found at index "
                  << indices[0]
                  << " of " 
                  << numberOfVectors
                  << std::endl;

        // Tidy up arrays
        delete [] energy;
        delete [] momnX;
        delete [] momnY;
        delete [] momnZ;
        delete [] indices;
      }
      else {
        std::cerr << "[error]: Number must be between 1 and 1000" << std::endl;
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
  }
}
