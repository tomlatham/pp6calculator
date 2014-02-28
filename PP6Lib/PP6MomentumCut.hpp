//! \file   PP6MomentumCut.hpp
//! \author Tom Latham
//! \brief  Declaration of PP6MomentumCut concrete class
#ifndef PP6MOMENTUMCUT_HPP
#define PP6MOMENTUMCUT_HPP

#include <string>
#include <vector>

#include "PP6Cut.hpp"
#include "PP6Particle.hpp"

class MomentumCut : public Cut {
 public:
  // Constructors
  MomentumCut( const double lowerValue, const double upperValue );
  MomentumCut( const CutType type, const double value );

  virtual ~MomentumCut() {
    std::cout << "MomentumCut::~MomentumCut(" << this << ")" << std::endl;
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

#endif // PP6MOMENTUMCUT_HPP
