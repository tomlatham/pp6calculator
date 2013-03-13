//! \file   PP6ParticleInfo.hpp
//! \author Ben Morgan
//! \brief  Declaration of PP6 ParticleInfo class
#ifndef PP6PARTICLEINFO_HPP
#define PP6PARTICLEINFO_HPP

#include <map>
#include <string>

// ParticleInfo database, implemented using the singleton design pattern

class ParticleInfo {
 public:
  // The instance accessor static member function
  static const ParticleInfo& Instance( const std::string& dbFile = std::string("pdg.dbt") );

  // Normal member functions
  size_t size() const;
  int getPDGCode(const std::string& name) const;
  int getCharge(const int id) const;
  std::string getName(const int id) const;
  double getMassMeV(const int id) const;
  double getMassGeV(const int id) const;

 private:
  // The private ctor, dtor and unimplemented copy ctor and copy assignment operator
  explicit ParticleInfo( const std::string& dbFile ); // ctor - impl. in source file
  ParticleInfo(const ParticleInfo&); // copy ctor - do not implement
  ~ParticleInfo() {} // dtor
  ParticleInfo& operator=(const ParticleInfo&); // copy assignment op - do not implement

  // The instance member variable
  static ParticleInfo* theInstance;

  // Normal member variables
  std::map<std::string, int> name_to_id;
  std::map<int, std::string> id_to_name;
  std::map<int, int> id_to_charge;
  std::map<int, double> id_to_mass;
};

#endif // PP6PARTICLEINFO_HPP
