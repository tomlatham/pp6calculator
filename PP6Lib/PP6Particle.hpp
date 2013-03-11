//! \file   PP6Particle.hpp
//! \author Ben Morgan
//! \brief  Declaration of Particle class
#ifndef PP6PARTICLE_HPP
#define PP6PARTICLE_HPP

#include <string>

#include "PP6FourVector.hpp"
#include "PP6ThreeVector.hpp"

class Particle {
 public:
  // Constructors
  Particle(); // default ctor, so we can make arrays of them (p = 0)
  Particle(const Particle& other); // copy ctor
  Particle(const int pdg_code, const double mass); // p = 0
  Particle(const int pdg_code, const double mass, const ThreeVector& momentum);
  Particle(const int pdg_code, const double mass, const double px, const double py, const double pz);

  // Copy assignment operator
  Particle& operator=(const Particle& other);

  // Accessors
  int getPDGCode() const { return pdg_code_; }
  double getMassGeV() const { return mass_; }
  const FourVector& getFourMomentum() const { return momentum_; }
  const ThreeVector& getThreeMomentum() const { return momentum_.getThreeVector(); }
  double getMagMomentum() const { return getThreeMomentum().length(); }
  double getEnergy() const { return momentum_.getT(); }

  // Set methods for pdg code, mass, momentum
  // energy is computed from mass and momentum
  void setPDGCode(const int pdg_code) { pdg_code_ = pdg_code; }
  void setMass(const double mass);
  void setThreeMomentum(const ThreeVector& p);
  void setThreeMomentum(const double px, const double py, const double pz);

 private:
  int pdg_code_;
  double mass_;
  FourVector momentum_;
};

double calculate_invariant_mass(const Particle& first, const Particle& second);

#endif // PP6PARTICLE_HPP
