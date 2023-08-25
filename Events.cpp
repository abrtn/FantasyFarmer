#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iterator>
#include "Classes.hpp"
#include "Functions.hpp"
#include "Events.hpp"

using std::string;
using std::cin;
using std::cout;
using std::vector;

/*
Setting up event funcions for use in Fantasy Farmer game
8/12/2023 by Andrew Barton
*/

void tutorialEvents(Character & crier, Knight & sir, const int & day){
    string dialog;
    switch(day){
        case 3:
            dialog = "The great King was found dead this morning. He will be succeded by his oldest son, Remus II";
            crier.orderedDialog.push_back(dialog);
            crier.diagReady = 1;
            break;
        case 5:
            sir.need.push_back(getItem("Turnip", 3));
            sir.needMet = 0;
            break;
        case 7:
            dialog = "It has come to the court's attention that Remus I was poisoned by Remus II. Remus II has been arrested.\
            Romus, the youngest son of Remus I will ascend to the throne";
            crier.orderedDialog.push_back(dialog);
            crier.diagReady = 1;
            break;
        case 8:
            dialog = "Remus II has been put to death for treason and conspiracy";
            crier.orderedDialog.push_back(dialog);
            crier.diagReady = 1;
            break;
        case 12:
            dialog = "King Romus I has admitted he poisoned the king and framed his brother to get the throne. \
            Since Romus is the last male of the line of Remus I, nothing is to be done with this information. \
            Long live King Romus";
            crier.orderedDialog.push_back(dialog);
            crier.diagReady = 1;
            break;
    }
}
