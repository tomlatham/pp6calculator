//! \file   PP6EnergyCut.hpp
//! \author Tom Latham
//! \brief  Declaration of PP6EnergyCut concrete class
#ifndef PP6ENERGYCUT_HPP
#define PP6ENERGYCUT_HPP

#include <string>
#include <vector>

#include "PP6Cut.hpp"
#include "PP6Particle.hpp"

class EnergyCut : public Cut {
 public:
  // Constructors
  EnergyCut( const double lowerValue, const double upperValue );
  EnergyCut( const CutType type, const double value );

  virtual ~EnergyCut() {
    std::cout << "EnergyCut::~EnergyCut(" << this << ")" << std::endl;
  }

  // Member functions
  virtual bool select(const Particle& input) const;
  virtual std::vector<Particle> select(const std::vector<Particle>& input) const;

 private:
  void checkValidity();

  bool rangeCut(const Particle& input) const;
  bool lessThanCut(const Particle& input) const;
  bool greaterThanCut(const Particle& input) const;

  CutType type_;

  double lowerValue_;
  double upperValue_;
};

#endif // PP6ENERGYCUT_HPP
