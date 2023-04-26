//
// Created by User on 23.11.2022.
//

#ifndef LAB02_Emil_PLAYER_H
#define LAB02_Emil_PLAYER_H

#include <iostream>
#include <cmath>
#include <list>
#include <algorithm>
#include <string>

#include "../Map/Map.h"
#include "../Node/Node.h"

using namespace std;


class Player{
protected:
    Map map;

    Node** nodes = nullptr;
    Node* start = nullptr;
    Node* end = nullptr;

    int xStart, yStart; // Player's coordinates
    int xEnd, yEnd;     // Enemy's coordinates

    int mapWidth, mapHeight; // Map's width and height

    float HP, DMG, Armor;
    int HitChance;
    char ch;            // Character for Player or Bot;

public:
    virtual bool OnUserCreate() = 0;        // Creating Nodes and Connections
    virtual bool Solve_AStar() = 0;         // Solve A*
    virtual void initStats() = 0;           // Stats for Gladiators;
    virtual Node* &getStartNode() = 0;
    virtual string getClassName() = 0;      // Knight or Archer or Mage;
    virtual int getHitChance() = 0;
    virtual float getHP() = 0;
    virtual void setHP(float hp) = 0;
    virtual float getDMG() = 0;
    virtual float getArmor() = 0;
    virtual char getCharacter() = 0;
    virtual void setStartAndEndNode(Node* &start, Node* &end) = 0;
    virtual void setHitChances(int hitChances) = 0;


    ~Player()
    {
        map.~Map();
        delete nodes;
        delete start;
        delete end;
        mapWidth = 0, mapHeight = 0;
        xEnd = 0, yEnd = 0;
        xStart = 0, yStart = 0;
        HP = 0, Armor = 0, DMG = 0;
        HitChance = 0;
        ch = 0;

    }
};

#endif //LAB02_EASAMIGULLIN_PLAYER_H
