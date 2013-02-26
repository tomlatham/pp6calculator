// PP6Day2VectorAnalysis.cpp : Definition of PP6Day2VectorAnalysis functions
//
#include "PP6Day2VectorAnalysis.hpp"

// Standard Library
#include <iostream>
#include <cmath>

// This Project
#include "PP6Math.hpp"

int pp6day2_vectoranalysis() {
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
      return 1;
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
      return 1;
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
      return 1;
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
      return 1;
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
    return 1;
  }

  return 0;
}

