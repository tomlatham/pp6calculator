// Standard Library
#include <iostream>
#include <limits>

// This Project
#include "PP6Day1Menu.hpp"
#include "PP6Day2Menu.hpp"
#include "PP6Day3Menu.hpp"

//----------------------------------------------------------------------
// Main program
//
int main() 
{
  // Menu operation
  char item('\0');

  while (true)
  {
    // Ask the user to select a submenu or quit
    std::cout << "PP6Calculator - Main Menu" << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << "Choose the operation you would like to perform:" << std::endl;
    std::cout << "1)  Basic Mathematics from Day 1" << std::endl;
    std::cout << "2)  Array Operations from Day 2" << std::endl;
    std::cout << "3)  FourVector Operations from Day 3" << std::endl;
    std::cout << "q)  Quit" << std::endl;
    std::cout << ">> ";

    std::cin >> item;

    // check for bad input
    if(!std::cin)
    {
      std::cerr << "[error] Error in input" << std::endl;
    
      // clear the buffer
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    // Handle menu operation
    if (item == 'q')
    {
      break;
    }
    else if (item == '1')
    {
      pp6day1_menu();
    }
    else if (item == '2')
    {
      pp6day2_menu();
    }
    else if (item == '3')
    {
      pp6day3_menu();
    }
    else
    {
      std::cerr << "[error] Operation '" << item << "' not recognised."
                << std::endl;
      continue;
    }
  }
 
  std::cout << "Thank you for using pp6calculator!" << std::endl;
  return 0;
}

