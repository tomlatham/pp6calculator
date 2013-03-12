//! \file   PP6ParticleInfo.hpp
//! \author Ben Morgan
//! \brief  Declaration of PP6 ParticleInfo class
#ifndef PARTICLEINFO_HPP
#define PARTICLEINFO_HPP

#include <map>
#include <string>

class ParticleInfo {
 public:
  ParticleInfo(std::string dbFile); // default ctor - impl. in source file
  ~ParticleInfo() {} // dtor

  // Normal member functions
  size_t size() const;
  int getPDGCode(const std::string& name) const;
  int getCharge(const int id) const;
  std::string getName(const int id) const;
  double getMassMeV(const int id) const;
  double getMassGeV(const int id) const;

 private:
  ParticleInfo(const ParticleInfo&); // copy ctor - do not implement
  ParticleInfo& operator=(const ParticleInfo&); // copy assignment op - do not implement

 private:
  // Normal member variables
  std::map<std::string, int> name_to_id;
  std::map<int, std::string> id_to_name;
  std::map<int, int> id_to_charge;
  std::map<int, double> id_to_mass;
};

#endif
