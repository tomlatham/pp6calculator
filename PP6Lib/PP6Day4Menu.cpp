// PP6Day4Menu.cpp : Definitions for PP6Day4Menu functions
//
#include "PP6Day4Menu.hpp"

// Standard Library
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

// Third party
#include "FileReader.hpp"

// This Project
#include "PP6Math.hpp"
#include "PP6ParticleInfo.hpp"
#include "PP6Day4MuonAnalysis.hpp"

//! Operation to read/display the PDG database read in from a .dbt file
int pp6day4_io_pdg() {
  std::string dbtFilename;
  std::cout << "Enter path to .dbt file to be read: ";
  dbtFilename = getString();

  // Open the FileReader with supplied file
  FileReader dataBase(dbtFilename);

  if (!dataBase.isValid()) {
    std::cerr << "[pp6day4_io_pdg:error] "
              << dbtFilename
              << " is not a valid file"
              << std::endl;
    return 1;
  } else {
    // Create vectors to store columns
    std::vector<std::string> particleName;
    std::vector<int> particlePdgCode;
    std::vector<int> particleCharge;
    std::vector<double> particleMass;

    // Read and display data
    while (dataBase.nextLine()) {
      particleName.push_back(dataBase.getField<std::string>(1));
      if (dataBase.inputFailed()) {
        std::cout << "Could not get field 1 as std::string" << std::endl;
        continue;
      }

      particlePdgCode.push_back(dataBase.getField<int>(2));
      if (dataBase.inputFailed()) {
        std::cout << "Could not get field 2 as int" << std::endl;
        continue;
      }
      particleCharge.push_back(dataBase.getField<int>(3));
      if (dataBase.inputFailed()) {
        std::cout << "Could not get field 3 as int" << std::endl;
        continue;
      }

      particleMass.push_back(dataBase.getField<double>(4));
      if (dataBase.inputFailed()) {
        std::cout << "Could not get field 4 as double" << std::endl;
        continue;
      }
    }

    // present results
    // Iterators
    std::vector<std::string>::iterator nameIter(particleName.begin());
    std::vector<std::string>::iterator stopCond(particleName.end());

    // As all the vectors are the same size, we use nameIter and
    // stopCond to loop, and only need the begin() of the other
    // vectors
    std::vector<int>::iterator pdgIter = particlePdgCode.begin();
    std::vector<int>::iterator chargeIter = particleCharge.begin();
    std::vector<double>::iterator massIter = particleMass.begin();
  
    for ( ; nameIter != stopCond; ++nameIter, 
         ++pdgIter, ++chargeIter, ++massIter) {
      std::cout << *nameIter << " "
                << *pdgIter << " "
                << *chargeIter << " "
                << *massIter
                << std::endl;
    }
  }

  return 0;
}

int pp6day4_check_particleinfo() {
  std::string dbtFilename;
  std::cout << "Enter path to .dbt file for initializing ParticleInfo: ";
  dbtFilename = getString();

  // Open the ParticleInfo with supplied file
  const ParticleInfo& dataBase = ParticleInfo::Instance(dbtFilename);

  // Check it has entries
  std::cout << "Checking ParticleInfo contains entries... ";
  if (!dataBase.size()) {
    std::cout << "fail" << std::endl;
    return 1;
  } else {
    std::cout << "ok" << std::endl;
  }

  // It must contain mu+ and mu- 
  std::cout << "Checking ParticleInfo returns correct mu- PDG code... ";
  if (dataBase.getPDGCode("mu-") != 13) {
    std::cout << "fail" << std::endl;
    return 1;
  } else {
    std::cout << "ok" << std::endl;
  }

  std::cout << "Checking ParticleInfo returns correct mu+ PDG code... ";
  if (dataBase.getPDGCode("mu+") != -13) {
    std::cout << "fail" << std::endl;
    return 1;
  } else {
    std::cout << "ok" << std::endl;
  }

  // Check that mu+ and mu- entries return +ve masses
  std::cout << "Checking ParticleInfo returns +ve mass for mu-... ";
  if (dataBase.getMassMeV(13) <= 0.0) {
    std::cout << "fail" << std::endl;
    return 1;
  } else {
    std::cout << "ok" << std::endl;
  }

  std::cout << "Checking ParticleInfo returns +ve mass for mu+... ";
  if (dataBase.getMassMeV(-13) <= 0.0) {
    std::cout << "fail" << std::endl;
    return 1;
  } else {
    std::cout << "ok" << std::endl;
  }

  return 0;
}

int pp6day4_algorithm_demo() {
  // Query user for size of array to generate and sort
  // Restrict it to more than 10 and less than 100
  size_t s(0);
  while ((s < 10) || (s > 100)) {
    std::cout << "Enter size of array to generate/sort [10 <= N <= 100]: ";
    s = getNumber();
  }

  // Create a vector to hold the numbers, initializing to zero
  std::vector<double> v(s,0);

  // Fill the vector with random numbers between 0-1
  std::generate(v.begin(), v.end(), getRandom);

  // Print unsorted vector:
  std::cout << "Generated vector:" << std::endl;
  std::copy(v.begin(), v.end(), std::ostream_iterator<double>(std::cout, "\n"));
  
  // Find max/min elements in the vector:
  std::vector<double>::iterator maxElem = std::max_element(v.begin(), v.end());
  std::vector<double>::iterator minElem = std::min_element(v.begin(), v.end());

  std::cout << "Max Element = " << *maxElem << std::endl;
  std::cout << "Min Element = " << *minElem << std::endl;

  // Sort the vector in-place, and output again
  std::sort(v.begin(), v.end());

  std::cout << "Sorted vector:" << std::endl;
  std::copy(v.begin(), v.end(), std::ostream_iterator<double>(std::cout, "\n"));

  return 0;
}

void pp6day4_menu() {
  // Declare the variables
  // Variables for i/o
  double resultCode(0); 
  char op('\0');

  while (true)
  {
    // Ask the user what they want to do
    std::cout << "PP6Calculator - Day 4 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Enter the operation you would like to perform:" << std::endl;
    std::cout << "1)  Read and display the PDG Textfile Database" << std::endl;
    std::cout << "2)  Instantiate a ParticleInfo instance and test it" << std::endl;
    std::cout << "3)  Demonstrate use of STL algorithms to sort a random array" << std::endl;
    std::cout << "4)  Analyse input file for muon pairs (Day 4 version)" << std::endl;
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
      resultCode = pp6day4_io_pdg();
    }
    else if (op == '2')
    {
      resultCode = pp6day4_check_particleinfo();
    }
    else if (op == '3')
    {
      resultCode = pp6day4_algorithm_demo();
    }
    else if (op == '4')
    {
      resultCode = pp6day4_muonanalysis();
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

