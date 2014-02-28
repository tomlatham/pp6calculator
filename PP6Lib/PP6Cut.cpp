// PP6Cut.cpp : Implementation of PP6Cut
//
#include "PP6Cut.hpp"

std::istream& operator>>( std::istream& in, Cut::CutType& type )
{
  std::string type_str;
  in >> type_str;
  if ( type_str == "Range" ) {
    type = Cut::Range;
  } else if ( type_str == "GreaterThan" ) {
    type = Cut::GreaterThan;
  } else if ( type_str == "LessThan" ) {
    type = Cut::LessThan;
  }
  return in;
}

