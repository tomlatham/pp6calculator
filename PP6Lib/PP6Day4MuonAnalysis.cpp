// PP6Day4MuonAnalysis.cpp : Definition of PP6Day4MuonAnalysis functions
//
#include "PP6Day4MuonAnalysis.hpp"

// Standard Library
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>


// Third Party
#include "FileReader.hpp"

// This Project
#include "PP6Math.hpp"
#include "PP6Particle.hpp"
#include "PP6ParticleInfo.hpp"

//! Typedefs for this problem. Hidden in a namespace so they aren't global.
namespace InvMass {
//! A pair linking event id to a Particle
typedef std::pair<int, Particle> Event;

//! A vector to hold Events
typedef std::vector<Event> EventVector; 

//! A map between run name and vector of Events in that run
typedef std::map<std::string, std::vector<Event> > RunMap;

//! A multimap between Invariant Mass and the pair of Particles used
// to calculate that mass. Changes the multimap Compare comparison to
// std::greater<double> so masses are sorted in descending order.
typedef std::pair<Event, Event> InvMassPair;
typedef std::multimap<double, 
                      InvMassPair,
                      std::greater<double> > InvMassTable;
}

//! operator<< for InvMass Event
// This helps to print out results at the end
std::ostream& operator<<(std::ostream& out, const InvMass::Event& e) {
  out << "{" 
      << "Event : " << e.first << ", "
      << "Particle(" << e.second.getPDGCode()
      << ", " 
      << "(E, p) : " << e.second.getFourMomentum()
      << "}";
  return out;
}

//! IsNotPDGCode
// A simple Predicate functor whose operator() (function call operator)
// is overloaded to take a Event instance and return false if the
// Event's Particle does not have a PDG code matching that of the pdgCode_
// data member
// The constructor takes a PDG code.
class IsNotPDGCode {
 public:
  explicit IsNotPDGCode(int pdgCode) : pdgCode_(pdgCode) {;}
  ~IsNotPDGCode() {;}

  // return 
  bool operator()(const InvMass::Event& p) const {
    return (p.second).getPDGCode() != pdgCode_;
  }

 private:
  int pdgCode_;
};

// Function to read run based data from an input file, filling a
// supplied RunMap object using a supplied ParticleInfo database to get
// particle codes and masses.
bool read_run_data(const std::string& runFile, const ParticleInfo& db, 
                   InvMass::RunMap& runTable) {
  // Open the file and check validity
  FileReader reader(runFile);
  if (!reader.isValid()) {
    std::cerr << "[read_run_data:error] "
              << runFile
              << " is not valid"
              << std::endl;  
    return false;
  }

  // read in one line to get rid of header
  reader.nextLine();

  // Now read in the particle/run data
  // Fields are:
  // event(int), name(string), px(double), py(double), pz(double),
  // run(string)
  std::string name(""), run("");
  int eventId(0);
  double px(0.0), py(0.0), pz(0.0);

  // Variable for use in the loop
  int pdgCode(0);

  while (reader.nextLine()) {
    eventId = reader.getField<int>(1);
    if (reader.inputFailed()) {
      std::cerr << "[read_run_data:error] Failed to to read event field from "
                << runFile
                << std::endl;
      return false;
    }

    name = reader.getField<std::string>(2);
    if (reader.inputFailed()) {
      std::cerr << "[read_run_data:error] Failed to to read name field from "
                << runFile
                << std::endl;
      return false;
    }

    px = reader.getField<double>(3);
    if (reader.inputFailed()) {
      std::cerr << "[read_run_data:error] Failed to to read p_x field from "
                << runFile
                << std::endl;
      return false;
    }

    py = reader.getField<double>(4);
    if (reader.inputFailed()) {
      std::cerr << "[read_run_data:error] Failed to to read p_y field from "
                << runFile
                << std::endl;
      return false;
    }

    pz = reader.getField<double>(5);
    if (reader.inputFailed()) {
      std::cerr << "[read_run_data:error] Failed to to read p_z field from "
                << runFile
                << std::endl;
      return false;
    }

    run = reader.getField<std::string>(6);
    if (reader.inputFailed()) {
      std::cerr << "[read_run_data:error] Failed to to read Data Source field from "
                << runFile
                << std::endl;
      return false;
    }

    // If all the data's been read in, we can fill the map.
    pdgCode = db.getPDGCode(name);

    // Create the particle and add it to the map.
    Particle tmp(pdgCode, px, py, pz);
    runTable[run].push_back(InvMass::Event(eventId,tmp));
  }

  return true;
}


int pp6day4_muonanalysis() {
  // Query the user for the .dbt file, create the database and check it
  std::string dbtFilename;
  std::cout << "Enter path to .dbt file for initializing ParticleInfo: ";
  dbtFilename = getString();

  const ParticleInfo& particleDB = ParticleInfo::Instance(dbtFilename);
  std::cout << "Checking ParticleInfo contains entries... ";
  if (!particleDB.size()) {
    std::cout << "fail" << std::endl;
    return 1;
  } else {
    std::cout << "ok" << std::endl;
  }

  // Query the user for the .dat file, and read in the information to
  // a RunMap instance
  //
  std::string muonFile;
  std::cout << "Enter filename to analyse: ";
  muonFile = getString();
 
  InvMass::RunMap allRuns;

  if (!read_run_data(muonFile, particleDB, allRuns)) {
    std::cerr << "[pp6day4_muonanalysis:error] Failed to read data from "
              << muonFile
              << std::endl;
    return 1;
  }

  //----------------------------------------------------------------------
  // Extract all mu- and mu+ particles that are in run4.dat
  InvMass::RunMap::iterator requiredRun = allRuns.find("run4.dat");
  if (requiredRun == allRuns.end()) {
    std::cerr << "[pp6day4_muonanalysis:error] No run4.dat records found in "
              << muonFile
              << std::endl;
    return 1;
  } 

  InvMass::EventVector negativeMuons;
  InvMass::EventVector positiveMuons;
  InvMass::RunMap::mapped_type::iterator start = (*requiredRun).second.begin();
  InvMass::RunMap::mapped_type::iterator stop = (*requiredRun).second.end();

  // A trick - the STL does not provide a copy_if algorithm (they apparently
  // forgot about it!). The remove_copy_if algorithm provides almost the
  // same functionality for our task, *but* the Predicate has to have
  // reversed logic. This is why we use the IsNotPDGCode functor.
  // We want this to return *false* for muons, because remove_copy_if
  // will only copy elements for which the predicate returns *false*.
  // See:
  //  http://www.sgi.com/tech/stl/remove_copy_if.html
  //
  // We use std::back_inserter so that we push_back onto the vectors, and
  // hence don't need to know how many +ve or -ve muons are present.
  std::remove_copy_if(start, 
                      stop, 
                      std::back_inserter(negativeMuons), 
                      IsNotPDGCode(particleDB.getPDGCode("mu-")));

  std::remove_copy_if(start, 
                      stop, 
                      std::back_inserter(positiveMuons), 
                      IsNotPDGCode(particleDB.getPDGCode("mu+")));

  //----------------------------------------------------------------------
  // Now take Cartesian Product of vectors, with product operation being the
  // calculation of the invariant masses.
  // There's no Cartesian Product algorithm, so a for loop is used. 
  InvMass::InvMassTable invMasses;

  InvMass::EventVector::iterator negIter = negativeMuons.begin();
  InvMass::EventVector::iterator negEnd = negativeMuons.end();
  InvMass::EventVector::iterator posIter = positiveMuons.begin();
  InvMass::EventVector::iterator posEnd = positiveMuons.end();
  double invMass(0.0);

  for ( ; negIter != negEnd; ++negIter ) {
    // reset the positive muon vector
    posIter = positiveMuons.begin();

    for ( ; posIter != posEnd; ++posIter ) {
      invMass = calculate_invariant_mass((*negIter).second, (*posIter).second);
      invMasses.insert(std::make_pair(invMass, InvMass::InvMassPair(*negIter, *posIter)));
    }
  }

  // -----
  // Where's the sort?? We've used a trick - by storing the invariant 
  // masses in a multimap as the keys of the multimap, the map will sort 
  // the keys for us. We used a multimap so that we handle any cases where 
  // we get identical invariant masses.
  
  // -----
  // Finally, print out the results
  // Annoyingly, there's no ostream_iterator for printing the contents of a
  // map, so a for loop is easiest here.
  // We use both the iterator and a counter to only print first 10 entries
  // or the entire map, whichever is smaller
  InvMass::InvMassTable::iterator imIter = invMasses.begin();
  InvMass::InvMassTable::iterator imStop = invMasses.end();

  for (size_t i(0) ; imIter != imStop, i < 10 ; ++imIter, ++i) {
    std::cout << "{InvariantMass : " << (*imIter).first 
              << ",\n\t"
              << (*imIter).second.first 
              << "\n\t"
              << (*imIter).second.second
              << std::endl;
  }

  return 0;
}

