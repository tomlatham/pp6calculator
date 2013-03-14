//! \file   PP6EventGenerator.hpp
//! \author Ben Morgan
//! \brief  Declaration of PP6EventGenerator Pure Abstract Class
#ifndef PP6EVENTGENERATOR_HPP
#define PP6EVENTGENERATOR_HPP

#include "PP6Particle.hpp"
#include <vector>
#include <iostream>

class EventGenerator {
 public:
  virtual ~EventGenerator() {
    std::cout << "EventGenerator::~EventGenerator(" << this << ")" << std::endl;
  }
  virtual std::vector<Particle> generate(const double mother_pz) const = 0;
};

#endif // PP6EVENTGENERATOR_HPP
