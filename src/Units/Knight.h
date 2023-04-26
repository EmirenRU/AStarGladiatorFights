//
// Created by User on 23.11.2022.
//

#ifndef LAB02_EMIL_KNIGHT_H
#define LAB02_EMIL_KNIGHT_H

#include "../Map/Map.h"
#include "Player.h"


class Knight : public virtual Player
{
public:

    Knight();
    Knight(Map& map, int _x, int _y, int _x1, int _y1, char ch);

    bool OnUserCreate();
    bool Solve_AStar();

    void initStats();

    Node* &getStartNode();
    string getClassName();
    int getHitChance();
    float getHP();
    float getArmor();
    float getDMG();
    char getCharacter();

    void setHP(float hp);
    void setStartAndEndNode(Node* &start, Node* &end);
    void setHitChances(int hitChances);

    ~Knight();
};

#endif //LAB02_EASAMIGULLIN_PLAYER_H
