// PP6TwoBodyGenerator.cpp : Implementation of PP6TwoBodyGenerator
//
#include "PP6TwoBodyGenerator.hpp"

#include <cstdlib>
#include <cmath>

#include "PP6Particle.hpp"
#include "PP6ThreeVector.hpp"

// The constructors create the template particles (with 0 3-momentum) 
// from either the PDG code or particle name.
// Then they check that the decay is valid and if so calculate the 
// breakup momentum.

TwoBodyGenerator::TwoBodyGenerator(const int mother_code, const int daughter1_code, const int daughter2_code) :
    mother_( mother_code ),
    daughter1_( daughter1_code ),
    daughter2_( daughter2_code ),
    qvalue_(0.0),
    valid_(false)
{
  checkValidity();
  if ( valid_ ) {
    calculateQ();
  }
}

TwoBodyGenerator::TwoBodyGenerator(const std::string& mother, const std::string& daughter1, const std::string& daughter2) :
    mother_( mother ),
    daughter1_( daughter1 ),
    daughter2_( daughter2 ),
    qvalue_(0.0),
    valid_(false)
{
  checkValidity();
  if ( valid_ ) {
    calculateQ();
  }
}

void TwoBodyGenerator::checkValidity()
{
  // Some simple validity checks
  // The daughter charges should sum to that of the mother
  if ( (daughter1_.getCharge() + daughter2_.getCharge()) != mother_.getCharge() ) {
    return;
  }
  // The mother mass should be greater than the sum of the daughter masses
  if ( (daughter1_.getMassGeV() + daughter2_.getMassGeV()) > mother_.getMassGeV() ) {
    return;
  }
  valid_ = true;
}

void TwoBodyGenerator::calculateQ()
{
  // Calculate the squares and 4th powers of the masses
  const double mM2 = mother_.getMassGeV()*mother_.getMassGeV();
  const double d1M2 = daughter1_.getMassGeV()*daughter1_.getMassGeV();
  const double d2M2 = daughter2_.getMassGeV()*daughter2_.getMassGeV();

  const double mM4 = mM2*mM2;
  const double d1M4 = d1M2*d1M2;
  const double d2M4 = d2M2*d2M2;

  // Use those to calculate the magnitude of the momentum of each daughter particle
  qvalue_ = sqrt( d1M4 - 2*d1M2*d2M2 - 2*d1M2*mM2 + d2M4 - 2*d2M2*mM2 + mM4 ) / ( 2*mother_.getMassGeV() );
}

std::vector<Particle> TwoBodyGenerator::generate( const double mother_beta_z ) const
{
  // If the decay is not valid we can't do anything, so just return an empty vector
  if ( ! valid_ ) {
    return std::vector<Particle>();
  }

  // Get random values of the angles
  double theta = acos(2.0*rand()/RAND_MAX-1.0);
  double phi = rand()*2.0*acos(-1.0)/RAND_MAX;

  // Formulate the 3-momentum of the 1st daughter
  // NB theta must be set before phi!
  ThreeVector daughter1_momentum( 0.0, 0.0, qvalue_ );
  daughter1_momentum.setTheta( theta );
  daughter1_momentum.setPhi( phi );

  // The 3-momentum of the 2nd daughter is -1 * that of the 1st
  ThreeVector daughter2_momentum( -daughter1_momentum );

  // Construct the two Particle objects from the templates, give them the
  // calculated 3-momenta and boost them into the lab frame
  Particle daug1( daughter1_ );
  daug1.setThreeMomentum( daughter1_momentum );
  daug1.boost_z( mother_beta_z );

  Particle daug2( daughter2_ );
  daug2.setThreeMomentum( daughter2_momentum );
  daug2.boost_z( mother_beta_z );

  // Return a vector of the particles
  std::vector<Particle> particles;
  particles.push_back( daug1 );
  particles.push_back( daug2 );

  return particles;
}


