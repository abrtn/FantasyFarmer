#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Classes.hpp"
#include "Functions.hpp"

using std::string;
using std::cin;
using std::cout;
using std::vector;

#define NULL_ITEM getItem("Null", 0)
#define NULL_ANIMAL getAnimal("Null")
#define NULL_CROP getCrop("Null", 0)

/*
Setting up classes for use in Fantasy Farmer game
7/14/2023 by Andrew Barton
*/


//Players and enemies

//Animals
void Animal::advanceDay(Item itm){
    time++;
    timeLastFed++;
    if(itm.name != "Null"){
        timeLastFed = 0;
    }
    if(grown){
        timeLastItem++;
    }
    if(time == growTime){
        cout << name << " is grown";
        grown = 1;
    }

}

bool Animal::milk(Inventory & invnt){
    if(timeLastItem >= productionTime){
        Item tmpItem = getItem(produced.name, 1);
        invnt.items.push_back(tmpItem);
        timeLastItem = 0;
        return 1;
    }
    return 0;
}

void Animal::die(Inventory & invnt){
    if(grown == 1){
        invnt.items.push_back(onDeath);
    }
}

Animal Animal::eat(vector<Item> & animalFood){
    if(animalFood.size() > 0){
        Item & food = animalFood.at(0);
        if(food.name.at(0) == 'E' && name.at(0) != 'E'){
            Animal tmpAnimal = getAnimal("Evil_" + type);
            tmpAnimal.grown = 1;
            tmpAnimal.time = time;
            tmpAnimal.name = name;
            tmpAnimal.timeLastItem = timeLastItem;
            return tmpAnimal;
        }
        return NULL_ANIMAL;
    }
    return NULL_ANIMAL;
}


//Crops
void Crop::advanceDay(){
    timeInGround += 1 * boostMultiplier;
    if(timeInGround >= growTime){
        grown = 1;
        cout << name + " is ready to harvest";
    }
}

//Inventory

void Inventory::clearEmpty(){
    auto start = std::remove_if(items.begin(), items.end(), [](Item itm){
        return itm.count <= 0;
    });
    for(auto i = items.end() - 1; i >= start; i--){
        items.erase(i);
    }
}

bool Inventory::sell(Player & plyr){
    string name;
    int count;
    cout << "Name of item";
    cin >> name;
    cout << "Number to sell";
    cin >> count;
    for(auto i = items.begin(); i < items.end(); i++){
        if((*i).name == name){
            (*i).count -= count;
            plyr.gold += count * (*i).sellCost;
            clearEmpty();
            return 1;
        }
    }
    return 0;
}

bool Inventory::buy(Player & plyr){
    string name;
    int count;
    cout << "Name of item";
    cin >> name;
    cout << "Number to buy";
    cin >> count;
    Item itm = getItem(name, count);
    if(plyr.gold < itm.buyCost * count){
        return 0;
    }else{
        plyr.gold -= itm.buyCost * count;
        items.push_back(itm);
        return 1;
    }
    return 0;
}

//Farm

void Farm::newDay(){
    for(auto & plants : plots){
        for(auto i = plants.begin(); i < plants.end(); i++){
            (*i).advanceDay();
        }
    }
}

void Farm::plant(Inventory & invnt){                  //TODO only plant if seeds
    string cropName;
    int qty;
    int plot;
    cout << "Enter name of crop";
    cin >> cropName;
    cout << "Number to plant";
    cin >> qty;
    cout << "Plot number";
    cin >> plot;
    for(auto itr = invnt.items.begin(); itr < invnt.items.end(); itr++){
        if((*itr).name == cropName + "_Seed"){
            if(plots.at(plot).size() >= 25){
                cout << "Plot is full";
            }else{
                if((*itr).count < qty){
                    qty = (*itr).count;
                }
                plots.at(plot).push_back(getCrop(cropName, qty));
                (*itr).count -= qty;
            }
        }
    }
    invnt.clearEmpty();
}

void Farm::harvest(Inventory & invnt){
    for(auto & plants : plots){
        for(auto i = plants.begin(); i < plants.end(); i++){
            if((*i).grown){
                bool inInvnt = 0;
                string name = (*i).name;
                if((*i).evil){
                    name = "Evil_" + name;
                }
                for(Item & j : invnt.items){
                    if(name == j.name){
                        j.count += (*i).count;
                        plants.erase(i);
                        inInvnt = 1;
                        break;
                    }
                }
                if(inInvnt == 0){
                    invnt.items.push_back(getItem(name, (*i).count));
                    plants.erase(i);
                }
            }
        }
    }
}

void Farm::boost(Inventory & invnt){
    int plot;
    string fertilizer;
    bool evil = 0;
    string bst = "";
    cout << "Plot number";
    cin >> plot;
    cout << "Boost";
    cin >> fertilizer;
    int i = 0;
    for(auto itr = invnt.items.begin(); itr < invnt.items.end(); itr++){
        if((*itr).name == fertilizer + "Fertilizer"){
            while(i < 3){
                bst += fertilizer.at(i);
                i++;
            }
            if((*itr).name.at(4) == 'E'){
                evil = 1;
            }
            for(Crop & crp : plots.at(plot)){
                crp.boostMultiplier = std::stod(bst);
                crp.evil = evil;
            }
            (*itr).count -= 1;
            break;
        }
    }
    invnt.clearEmpty();
}

//Animals
bool Pen::buyAnimal(Player & plyr){
    string type;
    string name;
    if(animals.size() >= 5){
        cout << "Pen is full";
        return 0;
    }
    cout << "Type of Animal";
    cin >> type;
    cout << "Animal name";
    cin >> name;
    Animal anml = getAnimal(type);
    anml.name = name;
    if(plyr.gold < anml.buyCost){
        return 0;
    }else{
        plyr.gold -= anml.buyCost;
        animals.push_back(anml);
        return 1;
    }
    return 0;
}

bool Pen::sellAnimal(Player & plyr){
    string name;
    cout << "Name of Animal";
    cin >> name;
    for(auto i = animals.begin(); i < animals.end(); i++){
        if((*i).name == name){
            plyr.gold += (*i).sellCost;
            animals.erase(i);
            return 1;
        }
    }
    return 0;
}

bool Pen::kill(Inventory & invnt){
    string name;
    cout << "Name of Animal";
    cin >> name;
    for(auto i = animals.begin(); i < animals.end(); i++){
        if((*i).name == name){
            (*i).die(invnt);
            animals.erase(i);
            return 1;
        }
    }
    return 0;
}

void Pen::newDay(){
    for(auto i = animals.begin(); i < animals.end(); i++){
        if(food.size() > 0){
            (*i).advanceDay(food.at(0));
            if((*i).predatorRating > 2){
                Animal newAnimal = (*i).eat(food);
                if(newAnimal.name != NULL_ANIMAL.name){
                    animals.erase(i);
                    animals.insert(i, newAnimal);
                }
                food.at(0).count -= 1;
                if(food.at(0).count == 0){
                    food.erase(food.begin());
                }
            }
        }
        else{
            (*i).advanceDay(NULL_ITEM);
        }
    }
}

bool Pen::milk(Inventory & invnt){
    string name;
    cout << "Name of Animal";
    cin >> name;
    for(auto i = animals.begin(); i < animals.end(); i++){
        if((*i).name == name){
            (*i).milk(invnt);
            return 1;
        }
    }
    return 0;
}

void Pen::feed(Inventory & invnt){
    string foodName;
    int qty;
    cout << "Enter feed";
    cin >> foodName;
    cout << "How many";
    cin >> qty;
    for(auto i = invnt.items.begin(); i < invnt.items.end(); i++){
        if((*i).name == foodName){
            if((*i).count < qty){
                qty = (*i).count;
            }
            (*i).count -= qty;
            invnt.clearEmpty();
            food.push_back(getItem(foodName, qty));
        }
    }
}
