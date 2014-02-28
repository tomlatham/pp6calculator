//! \file   PP6Cut.hpp
//! \author Tom Latham
//! \brief  Declaration of PP6Cut Pure Abstract Class
#ifndef PP6CUT_HPP
#define PP6CUT_HPP

#include "PP6Particle.hpp"
#include <vector>
#include <iostream>

class Cut {
 public:
  enum CutType { LessThan, GreaterThan, Range };

  virtual ~Cut() {
    std::cout << "Cut::~Cut(" << this << ")" << std::endl;
  }

  virtual bool select(const Particle& input) const = 0;
  virtual std::vector<Particle> select(const std::vector<Particle>& input) const = 0;
};

std::istream& operator>>( std::istream& in, Cut::CutType& type );

#endif // PP6CUT_HPP
