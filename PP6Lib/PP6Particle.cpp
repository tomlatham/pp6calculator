// PP6FourVector.cpp : Implementation of PP6FourVector
#include "PP6Particle.hpp"

#include <cmath>
#include <iostream>
#include <vector>

#include "PP6ParticleInfo.hpp"
#include "PP6FourVector.hpp"
#include "PP6ThreeVector.hpp"

Particle::Particle()
  : pdg_code_(0),
    name_(""),
    mass_(0.0),
    charge_(0),
    momentum_()
{}

Particle::Particle(const Particle& other)
: pdg_code_(other.pdg_code_),
    name_(other.name_),
    mass_(other.mass_),
    charge_(other.charge_),
    momentum_(other.momentum_)
{}

Particle::Particle(const int pdg_code)
: pdg_code_(pdg_code),
    name_(ParticleInfo::Instance().getName(pdg_code)),
    mass_(ParticleInfo::Instance().getMassGeV(pdg_code)),
    charge_(ParticleInfo::Instance().getCharge(pdg_code)),
    momentum_(mass_, ThreeVector())
{}

Particle::Particle(const int pdg_code, const ThreeVector& momentum)
: pdg_code_(pdg_code),
    name_(ParticleInfo::Instance().getName(pdg_code)),
    mass_(ParticleInfo::Instance().getMassGeV(pdg_code)),
    charge_(ParticleInfo::Instance().getCharge(pdg_code)),
    momentum_(mass_, ThreeVector())
{
  this->setThreeMomentum(momentum);
}

Particle::Particle(const int pdg_code, const double px, const double py, const double pz)
: pdg_code_(pdg_code),
    name_(ParticleInfo::Instance().getName(pdg_code)),
    mass_(ParticleInfo::Instance().getMassGeV(pdg_code)),
    charge_(ParticleInfo::Instance().getCharge(pdg_code)),
    momentum_(mass_, ThreeVector())
{
  ThreeVector mom(px, py, pz);
  this->setThreeMomentum(mom);
}

Particle::Particle(const std::string& name)
: pdg_code_(ParticleInfo::Instance().getPDGCode(name)),
    name_(name),
    mass_(ParticleInfo::Instance().getMassGeV(pdg_code_)),
    charge_(ParticleInfo::Instance().getCharge(pdg_code_)),
    momentum_(mass_, ThreeVector())
{}

Particle::Particle(const std::string& name, const ThreeVector& momentum)
: pdg_code_(ParticleInfo::Instance().getPDGCode(name)),
    name_(name),
    mass_(ParticleInfo::Instance().getMassGeV(pdg_code_)),
    charge_(ParticleInfo::Instance().getCharge(pdg_code_)),
    momentum_(mass_, ThreeVector())
{
  this->setThreeMomentum(momentum);
}

Particle::Particle(const std::string& name, const double px, const double py, const double pz)
: pdg_code_(ParticleInfo::Instance().getPDGCode(name)),
    name_(name),
    mass_(ParticleInfo::Instance().getMassGeV(pdg_code_)),
    charge_(ParticleInfo::Instance().getCharge(pdg_code_)),
    momentum_(mass_, ThreeVector())
{
  ThreeVector mom(px, py, pz);
  this->setThreeMomentum(mom);
}

Particle& Particle::operator=(const Particle& other)
{
  if ( this != &other )
  {
    this->pdg_code_ = other.pdg_code_;
    this->name_ = other.name_;
    this->mass_ = other.mass_;
    this->charge_ = other.charge_;
    this->momentum_ = other.momentum_;
  }
  return *this;
}

void Particle::setPDGCode(const int pdg_code)
{
  pdg_code_ = pdg_code;
  name_ = ParticleInfo::Instance().getName(pdg_code);
  mass_ = ParticleInfo::Instance().getMassGeV(pdg_code);
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

int Particle::boost_z( const double velocity )
{
  return momentum_.boost_z( velocity );
}

std::ostream& operator<<( std::ostream& out, const Particle& particle )
{
  out << particle.getName() << " : " << particle.getFourMomentum();
  return out;
}

std::istream& operator>>( std::istream& in, Particle& particle )
{
  std::string name;
  std::string dummy;
  FourVector p4;
  in >> name >> dummy >> p4;
  int pdg_code = ParticleInfo::Instance().getPDGCode( name );
  particle.setPDGCode( pdg_code );
  particle.setThreeMomentum( p4.getThreeVector() );
  return in;
}

double calculate_invariant_mass(const Particle& first, const Particle& second)
{
  const FourVector& p1 = first.getFourMomentum();
  const FourVector& p2 = second.getFourMomentum();
  FourVector p_tot = p1 + p2;
  return sqrt(p_tot.interval());
}

double calculate_invariant_mass(const std::vector<Particle>& particles)
{
  FourVector p_tot;
  std::vector<Particle>::const_iterator iter = particles.begin();
  const std::vector<Particle>::const_iterator end = particles.end();
  for ( ; iter != end; ++iter ) {
    p_tot += iter->getFourMomentum();
  }
  return sqrt(p_tot.interval());
}

