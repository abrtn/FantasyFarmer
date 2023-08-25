#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iterator>
#include "Classes.hpp"

using std::string;
using std::cin;
using std::cout;
using std::vector;

/*
Setting up miscalleneous funcions for use in Fantasy Farmer game
8/1/2023 by Andrew Barton
*/

int random(int lower, int upper);

bool storage(Inventory & to, Inventory & from);

Crop getCrop(string name, int num);

Item getItem(string name, int num);

Animal getAnimal(string name);

void transportAnimal(vector<Pen> &);

void checkCompatibility(vector<Pen> &, const int &);

