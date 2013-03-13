// PP6ParticleInfo.cpp : Definitions for PP6ParticleInfo class
//
#include "PP6ParticleInfo.hpp"
#include "FileReader.hpp"

// allocate and initialise the static member pointer
ParticleInfo* ParticleInfo::theInstance = 0;

const ParticleInfo& ParticleInfo::Instance( const std::string& dbFile )
{
  if ( theInstance == 0 ) {
    theInstance = new ParticleInfo( dbFile );
  }
  return *theInstance;
}

ParticleInfo::ParticleInfo( const std::string& dbFile)
{
  // Open a FileReader for the supplied db file
  FileReader dbReader(dbFile);

  if (dbReader.isValid()) {
    // Create variables
    std::string name;
    int pdg(0), charge(0);
    double mass(0.0);

    while (dbReader.nextLine()) {
      name = dbReader.getField<std::string>(1);
      if (dbReader.inputFailed()) {
        continue;
      }

      pdg = dbReader.getField<int>(2);
      if (dbReader.inputFailed()) {
        continue;
      }

      charge = dbReader.getField<int>(3);
      if (dbReader.inputFailed()) {
        continue;
      }

      mass = dbReader.getField<double>(4);
      if (dbReader.inputFailed()) {
        continue;
      }

      // Fill collections...
      name_to_id.insert(std::make_pair(name, pdg));
      id_to_name.insert(std::make_pair(pdg, name));
      id_to_charge.insert(std::make_pair(pdg, charge));
      id_to_mass.insert(std::make_pair(pdg, mass));

    }
  }
}

size_t ParticleInfo::size() const
{
  return name_to_id.size();
}

int ParticleInfo::getPDGCode(const std::string& name) const
{
  std::map<std::string, int>::const_iterator iter = name_to_id.find(name);
  if ( iter != name_to_id.end() ) {
    return iter->second;
  } else {
    // could throw an exception here to indicate an error
    // or we could have formulated the functions so that
    // they returned bool to indicate success or failure
    return 0;
  }
}

int ParticleInfo::getCharge(const int id) const
{
  std::map<int, int>::const_iterator iter = id_to_charge.find(id);
  if ( iter != id_to_charge.end() ) {
    return iter->second;
  } else {
    // could throw an exception here to indicate an error
    // or we could have formulated the functions so that
    // they returned bool to indicate success or failure
    return 0;
  }
}

std::string ParticleInfo::getName(const int id) const
{
  std::map<int, std::string>::const_iterator iter = id_to_name.find(id);
  if ( iter != id_to_name.end() ) {
    return iter->second;
  } else {
    // could throw an exception here to indicate an error
    // or we could have formulated the functions so that
    // they returned bool to indicate success or failure
    return "";
  }
}

double ParticleInfo::getMassMeV(const int id) const
{
  std::map<int, double>::const_iterator iter = id_to_mass.find(id);
  if ( iter != id_to_mass.end() ) {
    return iter->second;
  } else {
    // could throw an exception here to indicate an error
    // or we could have formulated the functions so that
    // they returned bool to indicate success or failure
    return 0.0;
  }
}

double ParticleInfo::getMassGeV(const int id) const
{
  return this->getMassMeV(id) / 1000.0;
}

