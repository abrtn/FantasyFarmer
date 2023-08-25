#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iterator>
#include "Classes.hpp"
#include "Functions.hpp"

using std::string;
using std::cin;
using std::cout;
using std::vector;

/*
Setting up event funcions for use in Fantasy Farmer game
8/12/2023 by Andrew Barton
*/

//Events guaranteed to happen on specific day
void tutorialEvents(Character &, Knight &, const int &);

//void randomEvents(Character &, Knight &, const int &);
