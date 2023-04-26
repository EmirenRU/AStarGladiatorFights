//
// Created by User on 28.11.2022.
//

#ifndef LAB02_EMIL_ARCHER_H
#define LAB02_EMIL_ARCHER_H
#include "Player.h"

class Archer : public virtual Player
{
public:
    Archer();
    Archer(Map& map, int _x, int _y, int _x1, int _y1, char ch);

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
    void setHitChances(int hitChances);
    void setStartAndEndNode(Node* &start, Node* &end);


    ~Archer();
};


#endif //LAB02_EMIL_ARCHER_H
