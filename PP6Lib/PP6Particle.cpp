// PP6FourVector.cpp : Implementation of PP6FourVector
#include "PP6Particle.hpp"

#include <cmath>

Particle::Particle()
: pdg_code_(0), mass_(0.0)
{}

Particle::Particle(const Particle& other)
: pdg_code_(other.pdg_code_), mass_(other.mass_), momentum_(other.momentum_)
{}

Particle::Particle(const int pdg_code, const double mass)
: pdg_code_(pdg_code), mass_(mass), momentum_(mass, ThreeVector())
{}

Particle::Particle(const int pdg_code, const double mass, const ThreeVector& momentum)
: pdg_code_(pdg_code), mass_(mass)
{
  this->setThreeMomentum(momentum);
}

Particle::Particle(const int pdg_code, const double mass, const double px, const double py, const double pz)
: pdg_code_(pdg_code), mass_(mass)
{
  ThreeVector mom(px, py, pz);
  this->setThreeMomentum(mom);
}

Particle& Particle::operator=(const Particle& other)
{
  if ( this != &other )
  {
    this->pdg_code_ = other.pdg_code_;
    this->mass_ = other.mass_;
    this->momentum_ = other.momentum_;
  }
  return *this;
}

void Particle::setMass(const double mass)
{
  mass_ = mass;
  this->setThreeMomentum(this->getThreeMomentum());
}

void Particle::setThreeMomentum(const ThreeVector& p)
{
  const double mod_p = p.length();
  const double E = sqrt(mod_p*mod_p + mass_*mass_);
  momentum_.setT(E);
  momentum_.setThreeVector(p);
}

void Particle::setThreeMomentum(const double px, const double py, const double pz)
{
  ThreeVector p(px, py, pz);
  this->setThreeMomentum(p);
}

double calculate_invariant_mass(const Particle& first, const Particle& second)
{
  const FourVector& p1 = first.getFourMomentum();
  const FourVector& p2 = second.getFourMomentum();
  FourVector p_tot = p1 + p2;
  return sqrt(p_tot.interval());
}
