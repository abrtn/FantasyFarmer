#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

using std::string;
using std::cin;
using std::cout;
using std::vector;

/*
Setting up classes for use in Fantasy Farmer game
7/14/2023 by Andrew Barton
*/


//Players and enemies
struct Player{
    string name;
    int defense = 5;
    int health = 100;
    int gold = 50;

    friend std::ostream & operator<<(std::ostream & out, Player plyr){
        out << plyr.name << ": " << std::to_string(plyr.gold);
        return out;
    }
};

//Items
struct Item{
    string name;
    int count;
    int buyCost;
    int sellCost;
    string type;
};

//Knights
struct Knight{
    string name;
    int level;
    vector<Item> need = {};
    bool needMet = true;
};


//Characters
struct Character{
    string name;
    vector<string> likes;
    vector<string> randomDialog;
    vector<string> orderedDialog;
    bool diagReady;

    friend std::ostream & operator<<(std::ostream & out, Character & chctr){
        if(chctr.diagReady){
            for(string i : chctr.orderedDialog){
                out << i << "\n";
            }
            chctr.orderedDialog = {};
            chctr.diagReady = 0;
            return out;
        }
        if(chctr.randomDialog.size() > 0){
            std::random_shuffle(chctr.randomDialog.begin(), chctr.randomDialog.end());
            out << *(chctr.randomDialog.begin());
            return out;
        }
        out << "...";
        return out;
    }
};

//Crops
struct Crop{
    string name;
    int count;
    int growTime;
    double timeInGround = 0;
    double boostMultiplier = 1;
    bool grown = 0;
    bool evil = 0;

    void advanceDay();
};

//Inventory
class Inventory{
    public:
    vector<Item> items = {};

    void clearEmpty();

    bool sell(Player &);

    bool buy(Player &);

    friend std::ostream & operator<<(std::ostream & out, Inventory invnt){
        out << "Inventory:\nItems:";
        for(Item & itm : invnt.items){
            out << itm.name << itm.count << ", ";
        }
        return out;
    }
};

//Farm
class Farm{
    public:
    //vector<Crop> plants = {};
    vector<vector<Crop>> plots = {{}};

    void newDay();

    void plant(Inventory &);

    void harvest(Inventory &);

    void boost(Inventory &);

    friend std::ostream & operator<<(std::ostream & out, Farm frm){
        for(auto i : frm.plots){
            for(Crop & crp : i){
                out << crp.name << " " << std::to_string(crp.count) << " " << std::to_string(crp.timeInGround) << "\n";
            }
            out << "\n";
        }
        return out;
    }
};

//Animals
struct Animal{
    string type;
    int buyCost;
    int sellCost;
    Item produced;
    int productionTime;
    Item onDeath;
    int growTime;
    string name;
    int predatorRating;
    bool grown = 0;
    int timeLastItem = 0;
    int timeLastFed = 0;
    int time = 0;
    bool evil = 0;

    void advanceDay(Item);
    bool milk(Inventory &);
    void die(Inventory &);
    Animal eat(vector<Item> &);
};

struct Pen{
    vector<Animal> animals = {};
    vector<Item> food = {};

    bool buyAnimal(Player &);
    bool sellAnimal(Player &);
    bool kill(Inventory &);
    void newDay();
    bool milk(Inventory &);
    void feed(Inventory &);

    friend std::ostream & operator<<(std::ostream & out, Pen pn){
        out << "Animals: ";
        for(Item & fd : pn.food){
            out << fd.name << fd.count << " ";
        }
        out << " | ";
        for(Animal & anml : pn.animals){
            out << anml.name << " " << anml.type << " " << anml.timeLastFed << ", ";
        }
        return out;
    }
};
