//! \file   PP6Particle.hpp
//! \author Ben Morgan
//! \brief  Declaration of Particle class
#ifndef PP6PARTICLE_HPP
#define PP6PARTICLE_HPP

#include <iosfwd>
#include <string>
#include <vector>

#include "PP6FourVector.hpp"
class ThreeVector;

class Particle {
 public:
  // Constructors
  Particle(); // default ctor, so we can make arrays of them (p = 0)
  Particle(const Particle& other); // copy ctor
  explicit Particle(const int pdg_code); // p = 0
  Particle(const int pdg_code, const ThreeVector& momentum);
  Particle(const int pdg_code, const double px, const double py, const double pz);
  explicit Particle(const std::string& name); // p = 0
  Particle(const std::string& name, const ThreeVector& momentum);
  Particle(const std::string& name, const double px, const double py, const double pz);

  // Copy assignment operator
  Particle& operator=(const Particle& other);

  // Accessors
  int getPDGCode() const { return pdg_code_; }
  std::string getName() const { return name_; }
  double getMassGeV() const { return mass_; }
  int getCharge() const { return charge_; }
  const FourVector& getFourMomentum() const { return momentum_; }
  const ThreeVector& getThreeMomentum() const { return momentum_.getThreeVector(); }
  double getMagMomentum() const { return getThreeMomentum().length(); }
  double getEnergy() const { return momentum_.getT(); }

  // Set methods for pdg code and momentum
  // New mass and charge are determined from the PDG code
  // Energy is computed from mass and momentum
  void setPDGCode(const int pdg_code);
  void setThreeMomentum(const ThreeVector& p);
  void setThreeMomentum(const double px, const double py, const double pz);

  // Method to boost the particle in z
  int boost_z( const double velocity );


 private:
  int pdg_code_;
  std::string name_;
  double mass_;
  int charge_;
  FourVector momentum_;
};

std::ostream& operator<<( std::ostream& out, const Particle& particle );
std::istream& operator>>( std::istream& out, Particle& particle );

double calculate_invariant_mass(const Particle& first, const Particle& second);
double calculate_invariant_mass(const std::vector<Particle>& particles);

#endif // PP6PARTICLE_HPP
