// PP6MomentumCut.cpp : Implementation of PP6MomentumCut
//
#include "PP6MomentumCut.hpp"

#include <cstdlib>
#include <cmath>
#include <iostream>

#include "PP6Math.hpp"
#include "PP6Particle.hpp"
#include "PP6ThreeVector.hpp"

// The constructors set the cut type along with the value(s).
// In the case of the double-sided cut there is also a check that the arguments
// are the right way around.

MomentumCut::MomentumCut( const double lowerValue, const double upperValue ) :
    type_( Range ),
    lowerValue_( lowerValue ),
    upperValue_( upperValue )
{
  checkValidity();
}

MomentumCut::MomentumCut( const CutType type, const double value ) :
    type_( type ),
    lowerValue_( value ),
    upperValue_( value )
{
}

void MomentumCut::checkValidity()
{
  // Check that the two cut values are the right way around, if not swap them
  if ( lowerValue_ > upperValue_ ) {
    swap( lowerValue_, upperValue_ );
  }
}

bool MomentumCut::select(const Particle& input) const
{
  switch ( type_ ) {
    case Range:
      return this->rangeCut( input );
    case LessThan:
      return this->lessThanCut( input );
    case GreaterThan:
      return this->greaterThanCut( input );
    default:
      std::cerr << "Unknown cut type!" << std::endl;
      return false;
  }
}

std::vector<Particle> MomentumCut::select(const std::vector<Particle>& input) const
{
  // Construct an empty vector to hold the selected Particles
  std::vector<Particle> selected;
  selected.reserve( input.size() );

  // Loop through the input vector, checking each Particle
  // If it passes add it into the selected list
  std::vector<Particle>::const_iterator iter = input.begin();
  std::vector<Particle>::const_iterator end = input.end();
  for ( ; iter != end; ++iter ) {
    if ( this->select( (*iter) ) ) {
      selected.push_back( (*iter) );
    }
  }

  return selected;
}

bool MomentumCut::rangeCut(const Particle& input) const
{
  double mass = input.getMagMomentum();
  if ( mass > lowerValue_ && mass < upperValue_ ) {
    return true;
  } else {
    return false;
  }
}

bool MomentumCut::lessThanCut(const Particle& input) const
{
  double mass = input.getMagMomentum();
  if ( mass < upperValue_ ) {
    return true;
  } else {
    return false;
  }
}

bool MomentumCut::greaterThanCut(const Particle& input) const
{
  double mass = input.getMagMomentum();
  if ( mass > lowerValue_ ) {
    return true;
  } else {
    return false;
  }
}

