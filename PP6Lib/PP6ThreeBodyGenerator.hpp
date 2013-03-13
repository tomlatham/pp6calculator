//! \file   PP6ThreeBodyGenerator.hpp
//! \author Ben Morgan
//! \brief  Declaration of ThreeBodyGenerator class
#ifndef PP6THREEBODYGENERATOR_HPP
#define PP6THREEBODYGENERATOR_HPP

#include <string>
#include <vector>

#include "PP6EventGenerator.hpp"
#include "PP6Particle.hpp"

// We forward declare the internal kinematics class
// Like we saw on Day 3 with structs, this uses the Opaque Pointer pattern
class ThreeBodyKinematics;

class ThreeBodyGenerator : public EventGenerator {
 public:
  // Constructors
  ThreeBodyGenerator(const std::string& mother, const std::string& daughter1, const std::string& daughter2, const std::string& daughter3);
  ThreeBodyGenerator(const int mother_code, const int daughter1_code, const int daughter2_code, const int daughter3_code);

  // Destructor
  virtual ~ThreeBodyGenerator();

  // Member function
  virtual std::vector<Particle> generate( const double mother_beta_z ) const;

 private:
  void checkValidity();

  Particle mother_;
  Particle daughter1_;
  Particle daughter2_;
  Particle daughter3_;

  bool valid_;

  ThreeBodyKinematics* kinematics_;
};

#endif
