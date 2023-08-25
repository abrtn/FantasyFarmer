#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <cstdlib>
#include "Classes.hpp"
#include "Functions.hpp"
#include "Events.hpp"

using std::string;
using std::cin;
using std::cout;
using std::vector;

/*
Main program for use in Fantasy Farmer game
7/15/2023 by Andrew Barton
*/

int main(){
    srand((unsigned) time(NULL));

    int days = 0;
    string name;
    char pick;
    cin >> name;
    Player plyr = {name};
    Farm myFarm;
    Inventory myInvnt;
    myInvnt.items.push_back(getItem("Evil_Turnip", 1));
    myInvnt.items.push_back(getItem("Turnip", 1));
    Inventory chest;
    vector<Pen> myPens = {};
    Pen p1;
    Pen p2;
    Character crier = {"Crier", {}, {"Hear Hear what I say say", "..."}, {}, 0};
    Knight sire = {"Lancelot", 0};
    myPens.push_back(p1);
    myPens.push_back(p2);
    string choice;
    //Pen myPen;
    bool a = 1;
    plyr.gold += 10000000;
    while(a){
        cout << "Enter choice: ";
        cin >> pick;
        switch(pick){
            case '>':
                myFarm.newDay();
                for(Pen & i : myPens){
                    i.newDay();
                }
                checkCompatibility(myPens, days);
                tutorialEvents(crier, sire, days);
                days++;
                break;
            case 'h':
                myFarm.harvest(myInvnt);
                break;
            case 's':
                myInvnt.sell(plyr);
                break;
            case 'p':
                myFarm.plant(myInvnt);
                break;
            case 'f':
                myFarm.boost(myInvnt);
                break;
            case 'd':
                cout << plyr << "\n";
                cout << myInvnt << "\n";
                cout << myFarm << "\n";
                for(Pen i : myPens){
                    cout << i << "\n";
                }
                break;
            case 'b':
                myInvnt.buy(plyr);
                break;
            case 'a':
                cout << "Enter choice: ";
                char pickA;
                cin >> pickA;
                switch (pickA)
                {
                case 'b':
                    if(myPens.size() > 0){
                        int pen;
                        cout << "Pen number";
                        cin >> pen;
                        myPens.at(pen).buyAnimal(plyr);
                    }
                    break;
                case 's':
                    if(myPens.size() > 0){
                        int pen;
                        cout << "Pen number";
                        cin >> pen;
                        myPens.at(pen).sellAnimal(plyr);
                    }
                    break;
                case 'k':
                    if(myPens.size() > 0){
                        int pen;
                        cout << "Pen number";
                        cin >> pen;
                        myPens.at(pen).kill(myInvnt);
                    }
                    break;
                case 'm':
                    if(myPens.size() > 0){
                        int pen;
                        cout << "Pen number";
                        cin >> pen;
                        myPens.at(pen).milk(myInvnt);
                    }
                    break;
                case 't':
                    transportAnimal(myPens);
                    break;
                case 'f':
                    if(myPens.size() > 0){
                        int pen;
                        cout << "Pen number";
                        cin >> pen;
                        myPens.at(pen).feed(myInvnt);
                    }
                    break;
                case 'e':
                    break;
                }
                break;
            case 'c':
                cout << "Pen or plot?";
                cin >> choice;
                if(choice == "pen"){
                    if(plyr.gold > 10000){
                        plyr.gold -= 10000;
                        Pen tmpPen;
                        myPens.push_back(tmpPen);
                    }else{
                        break;
                    }
                }else{
                    if(plyr.gold > 1000){
                        plyr.gold -= 1000;
                        vector<Crop> tmpPlot = {};
                        myFarm.plots.push_back(tmpPlot);
                    }else{
                        break;
                    }
                }
                break;
            case 't':
                cout << crier;
                break;
            case 'q':
               a = 0; 
               break;
        }
    }

    return 0;
}
