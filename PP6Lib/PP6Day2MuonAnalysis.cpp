// PP6Day2MuonAnalysis.cpp : Definition of PP6Day2MuonAnalysis functions
//
#include "PP6Day2MuonAnalysis.hpp"

// Standard Library
#include <iostream>
#include <cmath>

// Third Party
#include "FileReader.hpp"

// This Project
#include "PP6Math.hpp"

//! Count number of muons and antimuons in run file with specific run tag
int countMuons(const std::string& inputFile, const std::string& runName,
               int& numberOfMuons, int& numberOfAntiMuons) {
  // Create a filereader and check its validity
  FileReader counter(inputFile);
  if (!counter.isValid()) {
    std::cerr << "[countMuonPairs:error] "
              << inputFile
              << " is not valid"
              << std::endl;
    return 1;
  }

  numberOfMuons = 0;
  numberOfAntiMuons = 0;

  std::string particleName, dataID;

  while (counter.nextLine()) {
    // Valid lines should begin with an integer, continue without error
    // to skip header
    counter.getFieldAsInt(1);
    if (counter.inputFailed()) continue;

    particleName = counter.getFieldAsString(2);
    if (counter.inputFailed()) {
      std::cerr << "[countMuonPairs:error] Field 2 of "
                << inputFile
                << " is not a string"
                << std::endl;
      return 1;
    }

    dataID = counter.getFieldAsString(6);
    if (counter.inputFailed()) {
      std::cerr << "[countMuonPairs:error] Field 6 of "
                << inputFile
                << " is not a string"
                << std::endl;
      return 1;
    }

    if (dataID == runName) {
      if (particleName == "mu-") numberOfMuons++;
      if (particleName == "mu+") numberOfAntiMuons++;
    }
  }
  return 0;
}


int pp6day2_muonanalysis() {
  std::string muonFile;
  int resultCode(0);

  // Obtain filename from user
  std::cout << "Enter filename to analyse: ";
  muonFile = getString();

  std::string runID("run4.dat");
  int numberOfMuons(0), numberOfAntiMuons(0);

  // Count number of muons/antimuons in input file
  resultCode = countMuons(muonFile, runID, numberOfMuons, numberOfAntiMuons);
  if (resultCode) {
    std::cerr << "[pp6day2_muonanalysis:error] Failed to count muons in "
              << muonFile
              << std::endl;
    return resultCode;
  }

  //--------------------------------------------------------------------
  // - Create arrays to hold muon data
  int *muonEventNumber(new int[numberOfMuons]);
  double *muonEnergy(new double[numberOfMuons]);
  double *muonPx(new double[numberOfMuons]);
  double *muonPy(new double[numberOfMuons]);
  double *muonPz(new double[numberOfMuons]);

  int *antimuonEventNumber(new int[numberOfAntiMuons]);
  double *antimuonEnergy(new double[numberOfAntiMuons]);
  double *antimuonPx(new double[numberOfAntiMuons]);
  double *antimuonPy(new double[numberOfAntiMuons]);
  double *antimuonPz(new double[numberOfAntiMuons]);

  // - Read in data
  int eventNumber(0);
  std::string particleName, dataID;
  double particlePx(0), particlePy(0), particlePz(0);
  double particlePtot(0);
  const double muonMass(0.105658366);

  FileReader muonReader(muonFile);
  int muonCounter(0);
  int antimuonCounter(0);
  
  while (muonReader.nextLine()) {
     // Valid lines should begin with an integer, continue without error
    // to skip header
    eventNumber = muonReader.getFieldAsInt(1);
    if (muonReader.inputFailed()) continue;

    particleName = muonReader.getFieldAsString(2);
    if (muonReader.inputFailed()) {
      std::cerr << "[pp6day2_muonanalysis:error] Field 2 of "
                << muonFile
                << " is not a string"
                << std::endl;
      break;
    }

    dataID = muonReader.getFieldAsString(6);
    if (muonReader.inputFailed()) {
      std::cerr << "[pp6day2_muonanalysis:error] Field 6 of "
                << muonFile
                << " is not a string"
                << std::endl;
      break;
    }

    if (dataID == runID) {
      // Read the physics data
      particlePx = muonReader.getFieldAsDouble(3);
      if (muonReader.inputFailed()) {
      std::cerr << "[pp6day2_muonanalysis:error] Field 3 of "
                << muonFile
                << " is not a double"
                << std::endl;
      break;
      }

      particlePy = muonReader.getFieldAsDouble(4);
      if (muonReader.inputFailed()) {
      std::cerr << "[pp6day2_muonanalysis:error] Field 4 of "
                << muonFile
                << " is not a double"
                << std::endl;
      break;
      }

      particlePz = muonReader.getFieldAsDouble(5);
      if (muonReader.inputFailed()) {
      std::cerr << "[pp6day2_muonanalysis:error] Field 5 of "
                << muonFile
                << " is not a double"
                << std::endl;
      break;
      }

      if (particleName == "mu-") {
        // Fill muon data
        muonEventNumber[muonCounter] = eventNumber; 
        muonPx[muonCounter] = particlePx;
        muonPy[muonCounter] = particlePy;
        muonPz[muonCounter] = particlePz;
        length(particlePx, particlePy, particlePz, particlePtot);
        muonEnergy[muonCounter] = sqrt(particlePtot * particlePtot + 
                                       muonMass*muonMass); 
        ++muonCounter;
      }
      if (particleName == "mu+") {
        // Fill antimuon data
        antimuonEventNumber[antimuonCounter] = eventNumber; 
        antimuonPx[antimuonCounter] = particlePx;
        antimuonPy[antimuonCounter] = particlePy;
        antimuonPz[antimuonCounter] = particlePz;
        length(particlePx, particlePy, particlePz, particlePtot);
        antimuonEnergy[antimuonCounter] = sqrt(particlePtot * particlePtot + 
                                           muonMass*muonMass); 
        ++antimuonCounter;
      }
    }
  }

  if (muonReader.inputFailed()) {
    // - Clean up and return
    std::cerr << "[pp6day2_muonanalysis:error] Failed to extract physics data from "
              << muonFile 
              << std::endl;
    delete [] muonEventNumber;
    delete [] muonEnergy;
    delete [] muonPx;
    delete [] muonPy;
    delete [] muonPz;

    delete [] antimuonEventNumber;
    delete [] antimuonEnergy;
    delete [] antimuonPx;
    delete [] antimuonPy;
    delete [] antimuonPz;
    return 1;
  }

  //--------------------------------------------------------------------
  // - Analyse data...
  // Invariant mass and indexing array
  double *invariantMass(new double[numberOfMuons * numberOfAntiMuons]);
  int *muonPairIndex(new int[numberOfMuons * numberOfAntiMuons]);
  
  // - Loop over mu-/mu+ arrays, calculating invariant masses as we go
  for (int i(0); i < numberOfAntiMuons; ++i) {
    for (int j(0); j < numberOfMuons; ++j) {
      inv_mass(muonEnergy[j], muonPx[j], muonPy[j], muonPz[j],
               antimuonEnergy[i], antimuonPx[i], antimuonPy[i], 
               antimuonPz[i],
               invariantMass[i*numberOfMuons + j]);
      muonPairIndex[i*numberOfMuons + j] = i*numberOfMuons + j;
    }
  }

  // Use associative sort to sort masses
  associative_sort(invariantMass, muonPairIndex, 
                   numberOfMuons * numberOfAntiMuons);
  
  //--------------------------------------------------------------------
  // - Present results
  //
  std::cout << "Results:" << std::endl;
  std::cout << "========" << std::endl;
  std::cout << "Analysed File : " << muonFile << std::endl;
  std::cout << "Number of Muons     = " << numberOfMuons << std::endl;
  std::cout << "Number of AntiMuons = " << numberOfAntiMuons << std::endl;
  std::cout << "----------------------------" << std::endl;

  for (int i(0); i < 10; ++i) {
    int muonIndex(muonPairIndex[i] % numberOfMuons);
    int antimuonIndex((muonPairIndex[i] - muonIndex) / numberOfMuons);

    std::cout << "{InvariantMass : " << invariantMass[muonPairIndex[i]]
              << ",\n\t"
              << "{Muon : "
              << "Event = " << muonEventNumber[muonIndex] << ", "
              << "(E, P) = ("
              << muonEnergy[muonIndex] << ", "
              << muonPx[muonIndex] << ", "
              << muonPy[muonIndex] << ", "
              << muonPz[muonIndex] << ")}\n\t"
              << "{AntiMuon : "
              << "Event = " << antimuonEventNumber[antimuonIndex] << ", "
              << "(E, P) = ("
              << antimuonEnergy[antimuonIndex] << ", "
              << antimuonPx[antimuonIndex] << ", "
              << antimuonPy[antimuonIndex] << ", "
              << antimuonPz[antimuonIndex] << ")}\n"
              << "}"
              << std::endl;
  }


  // - Clean up arrays
  delete [] muonEventNumber;
  delete [] muonEnergy;
  delete [] muonPx;
  delete [] muonPy;
  delete [] muonPz;

  delete [] antimuonEventNumber;
  delete [] antimuonEnergy;
  delete [] antimuonPx;
  delete [] antimuonPy;
  delete [] antimuonPz;

  delete [] invariantMass;
  delete [] muonPairIndex;

  return 0;
}

