// PP6MassCut.cpp : Implementation of PP6MassCut
//
#include "PP6MassCut.hpp"

#include <cstdlib>
#include <cmath>
#include <iostream>

#include "PP6Math.hpp"
#include "PP6Particle.hpp"
#include "PP6ThreeVector.hpp"

// The constructors set the cut type along with the value(s).
// In the case of the double-sided cut there is also a check that the arguments
// are the right way around.

MassCut::MassCut( const double lowerValue, const double upperValue ) :
    type_( Range ),
    lowerValue_( lowerValue ),
    upperValue_( upperValue )
{
  checkValidity();
}

MassCut::MassCut( const CutType type, const double value ) :
    type_( type ),
    lowerValue_( value ),
    upperValue_( value )
{
}

void MassCut::checkValidity()
{
  // Check that the two cut values are the right way around, if not swap them
  if ( lowerValue_ > upperValue_ ) {
    swap( lowerValue_, upperValue_ );
  }
}

bool MassCut::select(const Particle& input) const
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

std::vector<Particle> MassCut::select(const std::vector<Particle>& input) const
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

bool MassCut::rangeCut(const Particle& input) const
{
  double mass = input.getMassGeV();
  if ( mass > lowerValue_ && mass < upperValue_ ) {
    return true;
  } else {
    return false;
  }
}

bool MassCut::lessThanCut(const Particle& input) const
{
  double mass = input.getMassGeV();
  if ( mass < upperValue_ ) {
    return true;
  } else {
    return false;
  }
}

bool MassCut::greaterThanCut(const Particle& input) const
{
  double mass = input.getMassGeV();
  if ( mass > lowerValue_ ) {
    return true;
  } else {
    return false;
  }
}

