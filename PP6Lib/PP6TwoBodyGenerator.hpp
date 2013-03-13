//! \file   PP6TwoBodyGenerator.hpp
//! \author Ben Morgan
//! \brief  Declaration of PP6TwoBodyGenerator concrete class
#ifndef PP6TWOBODYGENERATOR_HPP
#define PP6TWOBODYGENERATOR_HPP

#include <string>
#include <vector>

#include "PP6EventGenerator.hpp"
#include "PP6Particle.hpp"

class TwoBodyGenerator : public EventGenerator {
 public:
  // Constructors
  TwoBodyGenerator(const std::string& mother, const std::string& daughter1, 
                   const std::string& daughter2);
  TwoBodyGenerator(const int mother_code, const int daughter1_code, 
                   const int daughter2_code);

  virtual ~TwoBodyGenerator() {}

  // Member function
  virtual std::vector<Particle> generate( const double mother_beta_z ) const;

 private:
  void checkValidity();
  void calculateQ();

  Particle mother_;
  Particle daughter1_;
  Particle daughter2_;

  double qvalue_;

  bool valid_;
};

#endif // PP6TWOBODYGENERATOR_HPP
