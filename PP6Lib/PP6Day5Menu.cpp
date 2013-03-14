// PP6Day5Menu.cpp : Definitions for PP6Day4Menu functions
//
#include "PP6Day5Menu.hpp"

// Standard Library
#include <iostream>
#include <algorithm>
#include <iterator>

// Third Party
#include <boost/shared_ptr.hpp>

// This Project
#include "PP6Math.hpp"
#include "PP6ParticleInfo.hpp"
#include "PP6TwoBodyGenerator.hpp"
#include "PP6ThreeBodyGenerator.hpp"
#include "FileReader.hpp"

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
  int dMinusPDG = ParticleInfo::Instance().getPDGCode("B0");
  double expectedMass = ParticleInfo::Instance().getMassGeV(dMinusPDG);
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

int pp6day5_test_threebodygenerator() {
  if (!initialize_database()) return 1;

  // Create generator
  ThreeBodyGenerator generator("D-", "K+", "pi-", "pi-");
  int b0PDG = ParticleInfo::Instance().getPDGCode("D-");
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

int pp6day5_test_dynamicgeneration() {
  if (!initialize_database()) return 1;

  // Create generators from user supplied text file
  std::string decayTableFile;
  std::cout << "Enter path to .decaytable file for loading EventGenerators: ";
  decayTableFile = getString();

  FileReader reader(decayTableFile);
  if (!reader.isValid()) {
    std::cerr << "[pp6day5_test_dynamicgeneration:error] "
              << decayTableFile
              << " is not a valid file"
              << std::endl;
    return 1;
  }

  // Variables for reading data
  typedef boost::shared_ptr<EventGenerator> EGPtr;
  typedef std::vector<EGPtr> EGCollection;
  EGCollection generators;
  std::string mother;
  std::string daug1;
  std::string daug2;
  std::string daug3;

  while (reader.nextLine()) {
    mother = reader.getField<std::string>(1);
    if (reader.inputFailed()) continue;

    daug1 = reader.getField<std::string>(2);
    if (reader.inputFailed()) continue;

    daug2 = reader.getField<std::string>(3);
    if (reader.inputFailed()) continue;

    daug3 = reader.getField<std::string>(4);
    if (reader.inputFailed()) {
      // This is a two body decay
      EGPtr ptr(new TwoBodyGenerator(mother, daug1, daug2));
      generators.push_back(ptr);
      continue;
    } else {
      // It's three body and we can do no more...
      EGPtr ptr(new ThreeBodyGenerator(mother, daug1, daug2, daug3));
      generators.push_back(ptr);
    }
  }

  // For each generator, generate a decay and print the products and
  // invariant mass to screen
  typedef std::vector<Particle> EGProducts;
  EGCollection::const_iterator iter = generators.begin();
  EGCollection::const_iterator end = generators.end();

  for ( ; iter != end; ++iter) {
    EGProducts decayProducts = (*iter)->generate(0.56);
    double invmass = calculate_invariant_mass(decayProducts);
    std::cout << "Generator " << *iter << std::endl;
    std::copy(decayProducts.begin(), decayProducts.end(),
              std::ostream_iterator<EGProducts::value_type>(std::cout, "\n"));
    std::cout << "Invariant Mass = " << invmass << std::endl << std::endl;
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
    std::cout << "2)  Test ThreeBodyGenerator with 50 D-->K+pi-pi- decays" << std::endl;
    std::cout << "3)  Test Dynamic Dispatch to collection of EventGenerators" << std::endl;
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
    else if (op == '2')
    {
      resultCode = pp6day5_test_threebodygenerator();
    }
    else if (op == '3')
    {
      resultCode = pp6day5_test_dynamicgeneration();
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

