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

#define NULL_ITEM = getItem("Null");
#define NULL_ANIMAL = getAnimal("Null");
#define NULL_CROP = getCrop("Null");

/*
Setting up miscalleneous funcions for use in Fantasy Farmer game
8/1/2023 by Andrew Barton
*/

int random(int lower, int upper){
    return lower + (rand() % upper);
}

bool storage(Inventory & to, Inventory & from){
    Item itm;
    string name;
    cout << "Name of item:";
    cin >> name;
    for(auto i = from.items.begin(); i < from.items.end(); i++){
        if(name == (*i).name){
            to.items.push_back(*i);
            from.items.erase(i);
            return 1;
        }
    }
    return 0;
}

Crop getCrop(string name, int num){
    Crop tmpCrop = {"Null", 0, 0};
    string cropData;
    string tmp;
    std::ifstream cropFile("Crops.txt");
    while(getline(cropFile, cropData)){
        std::stringstream s(cropData);
        s >> tmp;
        if(tmp.at(0) == '-' || tmp == "Name"){
            continue;
        }
        if(tmp == name){
            Crop tmpCrop;
            tmpCrop.name = name;
            tmp = "";
            tmpCrop.count = num;
            s >> tmp;
            tmpCrop.growTime = std::stoi(tmp);
            cropFile.close();
            return tmpCrop;
        }
    }
    cropFile.close();
    return tmpCrop;
}

Item getItem(string name, int num){
    Item tmpItem = {"Null", 0, 0, 0, "-"};
    string itemData;
    string tmp;
    std::ifstream itemFile("Items.txt");
    while(getline(itemFile, itemData)){
        std::stringstream s(itemData);
        s >> tmp;
        if(tmp.at(0) == '-' || tmp == "Name"){
            continue;
        }
        if(tmp == name){
            tmpItem.name = name;
            tmp = "";
            tmpItem.count = num;
            s >> tmp;
            tmpItem.buyCost = std::stoi(tmp);
            s >> tmp;
            tmpItem.sellCost = std::stoi(tmp);
            s >> tmp;
            tmpItem.type = tmp;
            itemFile.close();
            return tmpItem;
        }
    }
    itemFile.close();
    return tmpItem;
}

Animal getAnimal(string type){
    Animal tmpAnimal = {"Null", 0, 0, getItem("-", 0), 0, getItem("-", 0), 0, "", 4};
    string animalData;
    string tmp;
    std::ifstream animalFile("Animals.txt");
    while(getline(animalFile, animalData)){
        std::stringstream s(animalData);
        s >> tmp;
        if(tmp.at(0) == '-' || tmp == "Name"){
            continue;
        }
        if(tmp == type){
            tmpAnimal.type = type;
            tmp = "";
            s >> tmp;
            tmpAnimal.buyCost = std::stoi(tmp);
            s >> tmp;
            tmpAnimal.sellCost = std::stoi(tmp);
            s >> tmp;
            tmpAnimal.produced = getItem(tmp, 1);
            s >> tmp;
            tmpAnimal.productionTime = std::stoi(tmp);
            s >> tmp;
            tmpAnimal.onDeath = getItem(tmp, 1);
            s >> tmp;
            tmpAnimal.growTime = std::stoi(tmp);
            s >> tmp;
            tmpAnimal.predatorRating = std::stoi(tmp);
            animalFile.close();
            return tmpAnimal;
        }
    }
    animalFile.close();
    return tmpAnimal;
}

void transportAnimal(vector<Pen> & pens){
    string name;
    int pen;
    Animal anml;
    cout << "Name of animal to move";
    cin >> name;
    cout << "Pen number to move to";
    cin >> pen;
    for(auto i = pens.begin(); i < pens.end(); i++){
        for(auto j = (*i).animals.begin(); j < (*i).animals.end(); j++){
            if((*j).name == name){
                anml = *j;
                (*i).animals.erase(j);
                break;
            }
        }
    }
    pens.at(pen).animals.push_back(anml);
}

void checkCompatibility(vector<Pen> & pens, const int & day){
    bool evilPred = 0;
    bool evilPrey = 0;
    for(auto i = pens.begin(); i < pens.end(); i++){
        if((*i).animals.size() > 0){
            vector<Animal> prey;
            bool hasPredator = 0;
            for(auto j = (*i).animals.begin(); j < (*i).animals.end(); j++){
                if((*j).predatorRating == 2){
                    if((*j).type.at(0) == 'E'){
                        evilPred = 1;
                    }
                    hasPredator = 1;
                    break;
                }
            }
            if(hasPredator && day % 3 == 0){
                for(auto j = (*i).animals.begin(); j < (*i).animals.end(); j++){
                    if((*j).predatorRating == 0){
                        if((*j).type.at(0) == 'E'){
                            evilPrey = 1;
                        }
                        cout << (*j).name + " was eaten";
                        (*i).animals.erase(j);
                        break;
                    }
                }
                for(auto j = (*i).animals.begin(); j < (*i).animals.end(); j++){
                    if((*j).predatorRating == 2){
                        if(evilPrey && !evilPred){
                            Animal newAnimal = getAnimal("Evil_" + (*j).type);
                            newAnimal.grown = 1;
                            newAnimal.time = (*j).time;
                            newAnimal.name = (*j).name;
                            newAnimal.timeLastFed = 0;
                            newAnimal.timeLastItem = (*j).timeLastItem;
                            (*i).animals.erase(j);
                            (*i).animals.insert(j, newAnimal);
                        }else{
                            (*j).timeLastFed = 0;
                        }
                    }
                }
            }
        }
    }
}
