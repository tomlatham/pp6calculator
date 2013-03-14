// PP6FourVector.cpp : Implementation of PP6FourVector
#include "PP6ThreeBodyGenerator.hpp"
#include "PP6ThreeBodyKinematics.hpp"

#include <cstdlib>
#include <cmath>
#include <iostream>

#include "PP6Particle.hpp"
#include "PP6ParticleInfo.hpp"
#include "PP6ThreeVector.hpp"
// The constructors create the template particles (with 0 3-momentum) from 
// either the PDG code or particle name.
// Then they check that the decay is valid and if so create the 3-body 
// kinematics object.

ThreeBodyGenerator::ThreeBodyGenerator(const int mother_code, const int daughter1_code, const int daughter2_code, const int daughter3_code) :
    mother_( mother_code ),
    daughter1_( daughter1_code ),
    daughter2_( daughter2_code ),
    daughter3_( daughter3_code ),
    valid_(false),
    kinematics_(0)
{
  checkValidity();
  if ( valid_ ) {
    kinematics_ = new ThreeBodyKinematics( daughter1_.getMassGeV(), daughter2_.getMassGeV(), daughter3_.getMassGeV(), mother_.getMassGeV() );
  }
}

ThreeBodyGenerator::ThreeBodyGenerator(const std::string& mother, const std::string& daughter1, const std::string& daughter2, const std::string& daughter3) :
    mother_( mother ),
    daughter1_( daughter1 ),
    daughter2_( daughter2 ),
    daughter3_( daughter3 ),
    valid_(false),
    kinematics_(0)
{
  checkValidity();
  if ( valid_ ) {
    kinematics_ = new ThreeBodyKinematics( daughter1_.getMassGeV(), daughter2_.getMassGeV(), daughter3_.getMassGeV(), mother_.getMassGeV() );
  }
}

// The destructor must free up the resources allocated during the constructor
ThreeBodyGenerator::~ThreeBodyGenerator()
{
  delete kinematics_;  kinematics_ = 0;
  std::cout << "ThreeBodyGenerator::~ThreeBodyGenerator(" << this << ")" << std::endl;
}

void ThreeBodyGenerator::checkValidity()
{
  // Some simple validity checks
  // The daughter charges should sum to that of the mother
  if ( (daughter1_.getCharge() + daughter2_.getCharge() + daughter3_.getCharge()) != mother_.getCharge() ) {
    return;
  }
  // The mother mass should be greater than the sum of the daughter masses
  if ( (daughter1_.getMassGeV() + daughter2_.getMassGeV() + daughter3_.getMassGeV()) > mother_.getMassGeV() ) {
    return;
  }
  valid_ = true;
}

std::vector<Particle> ThreeBodyGenerator::generate( const double mother_beta_z ) const
{
  // If the decay is not valid we can't do anything, so just return an empty vector
  if ( ! valid_ ) {
    return std::vector<Particle>();
  }

  // Generate a point in 3-body phase space and find the momenta of the 3
  // particles and their relative orientation (initially in the x-z plane)
  kinematics_->genFlatPhaseSpace();

  const double p1 = kinematics_->getp1_B();
  const double p2 = kinematics_->getp2_B();
  const double p3 = kinematics_->getp3_B();

  // Since acos only returns angles in [0,pi] we need to negate one of them
  const double theta12 =  acos((p3*p3 - p1*p1 - p2*p2)/(2*p1*p2));
  const double theta13 = -acos((p2*p2 - p1*p1 - p3*p3)/(2*p1*p3));

  // Initially define the momenta in the x-y plane with p1 along y-axis
  ThreeVector daughter1_momentum( 0.0            , p1             , 0.0 );
  ThreeVector daughter2_momentum( p2*sin(theta12), p2*cos(theta12), 0.0 );
  ThreeVector daughter3_momentum( p3*sin(theta13), p3*cos(theta13), 0.0 );

  // Get random values of the angles that:
  // - define a rotation about the normal to the plane (the z-axis)
  // - then set the theta and phi of the normal to the plane
  //   (in this special case that the normal is initially the z-axis,
  //   setting theta is the same as a negative rotation about the x-axis)
  const double rot_in_plane = rand()*2.0*acos(-1.0)/RAND_MAX;
  daughter1_momentum.rotateZ( rot_in_plane );
  daughter2_momentum.rotateZ( rot_in_plane );
  daughter3_momentum.rotateZ( rot_in_plane );

  const double theta = acos(2.0*rand()/RAND_MAX-1.0);
  daughter1_momentum.rotateX( -theta );
  daughter2_momentum.rotateX( -theta );
  daughter3_momentum.rotateX( -theta );

  const double phi = rand()*2.0*acos(-1.0)/RAND_MAX;
  daughter1_momentum.rotateZ( phi );
  daughter2_momentum.rotateZ( phi );
  daughter3_momentum.rotateZ( phi );

  // Construct the three Particle objects from the templates, give them
  // the calculated 3-momenta and boost them into the lab frame
  Particle daug1( daughter1_ );
  daug1.setThreeMomentum( daughter1_momentum );
  daug1.boost_z( mother_beta_z );

  Particle daug2( daughter2_ );
  daug2.setThreeMomentum( daughter2_momentum );
  daug2.boost_z( mother_beta_z );

  Particle daug3( daughter3_ );
  daug3.setThreeMomentum( daughter3_momentum );
  daug3.boost_z( mother_beta_z );

  // Return a vector of the particles
  std::vector<Particle> particles;
  particles.push_back( daug1 );
  particles.push_back( daug2 );
  particles.push_back( daug3 );

  return particles;
}


