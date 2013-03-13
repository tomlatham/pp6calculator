// PP6Day5Menu.cpp : Definitions for PP6Day4Menu functions
//
#include "PP6Day5Menu.hpp"

// Standard Library
#include <iostream>
#include <iterator>

// This Project
#include "PP6Math.hpp"
#include "PP6ParticleInfo.hpp"
#include "PP6TwoBodyGenerator.hpp"

bool initialize_database() {
  // As ParticleInfo is a singleton, we only need to initialize it once
  static bool dbIsUninitialized(true);
  if (dbIsUninitialized) {
    std::string dbtFilename;
    std::cout << "Enter path to .dbt file for initializing ParticleInfo: ";
    dbtFilename = getString();

    // Open the ParticleInfo with supplied file
    const ParticleInfo& dataBase = ParticleInfo::Instance(dbtFilename);

    // Check it has entries
    std::cout << "Checking ParticleInfo contains entries... ";
    if (!dataBase.size()) {
      std::cout << "fail" << std::endl;
      return false;
    } else {
      std::cout << "ok" << std::endl;
      dbIsUninitialized = false;
    }
  }

  return !dbIsUninitialized;
}


int pp6day5_test_twobodygenerator() {
  if (!initialize_database()) return 1;

  // Create generator
  TwoBodyGenerator generator("B0", "K+", "pi-");
  int b0PDG = ParticleInfo::Instance().getPDGCode("B0");
  double expectedMass = ParticleInfo::Instance().getMassGeV(b0PDG);
  // Loop, generate, calculate invariant mass of products and print
  // this and products
  for (int i(0); i < 50; ++i) {
    std::cout << "Iteration " << i << std::endl;
    std::vector<Particle> decayProducts = generator.generate(0.56);
    double invMass = calculate_invariant_mass(decayProducts);
    std::copy(decayProducts.begin(), decayProducts.end(),
              std::ostream_iterator<Particle>(std::cout, "\n"));
    std::cout << "Invariant Mass = " << invMass 
             << " (Expected : " << expectedMass <<")"
             << std::endl << std::endl;
  }
  return 0;
}

void pp6day5_menu() {
  // Declare the variables
  // Variables for i/o
  double resultCode(0); 
  char op('\0');

  while (true)
  {
    // Ask the user what they want to do
    std::cout << "PP6Calculator - Day 5 Menu" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Enter the operation you would like to perform:" << std::endl;
    std::cout << "1)  Test TwoBodyGenerator with 50 B_0->K+pi- decays" << std::endl;
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
      resultCode = pp6day5_test_twobodygenerator();
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

