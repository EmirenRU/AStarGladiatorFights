//
// Created by User on 29.11.2022.
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#include "../Map/Map.h"
#include "../Units/Player.h"
using namespace std;

#ifndef DOEVENT
#define DOEVENT

#define DEBUG

bool flag1 = false;
bool flag2 = false;

Player *kng;
Node* kngNode;
Player *arc;
Node* arcNode;


void A_Star_Event(Map &map, Player* &pl, Node* &plNode, Player* &bot, Node* &botNode ) {

    auto distance = [](Node* a, Node* b)
    {
        return sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
    };

    if (botNode != nullptr && plNode != nullptr && botNode->parent != nullptr && plNode->parent != nullptr)
    {
        while (true)
        {
            // Knight vs Knight
            if (pl->getClassName() == "Knight" && bot->getClassName() == "Knight")
            {

                map.setCharacter(plNode->x, plNode->y, '1');
                map.setCharacter(botNode->x, botNode->y, '2');

                pl->setStartAndEndNode(plNode, botNode);
                bot->setStartAndEndNode(botNode, plNode);

                pl->OnUserCreate();
                bot->OnUserCreate();

                pl->Solve_AStar();
                bot->Solve_AStar();

                if ( distance(plNode, botNode) > 1)
                {
                    botNode = botNode->parent;
                    plNode = plNode->parent;
                }

                else if (distance(botNode, plNode)  == 0 )
                {
                    map.printMap();
                    cout << "They have contacted" << std::endl;

                    while (true)
                    {
                        if (rand() % 100 < pl->getHitChance())
                        {
                            bot->setHP(bot->getHP() - ((bot->getArmor() / 100.f) * pl->getDMG()));
                        }

                        if (rand() % 100 < bot->getHitChance())
                        {
                            pl->setHP(pl->getHP() - ((pl->getArmor() / 100) * bot->getDMG()));
                        }
#ifdef DEBUG
                        cout << "\t\t\tKnight 1 has " << pl->getHP() << " HP " << endl;
                       cout << "\t\t\tKnight 2 has " << bot->getHP() << " HP " << endl;
#endif

                        if (pl->getHP() <= 0 && bot->getHP() > 0)
                        {
                            cout << "Knight 2 has won the battle... " << endl;
#ifdef DEBUG
                            cout << "\t\t\tKnight 1 has " << pl->getHP() << " HP " << endl;
                            cout << "\t\t\tKnight 2 has " << bot->getHP() << " HP " << endl;
#endif
                            break;
                        } else if (pl->getHP() > 0 && bot->getHP() <= 0)
                        {
                            cout << "Knight 1 has won the battle... " << endl;
#ifdef DEBUG
                            cout << "\t\t\tKnight 1 has " << pl->getHP() << " HP " << endl;
                            cout << "\t\t\tKnight 2 has " << bot->getHP() << " HP " << endl;
#endif
                            break;
                        } else if (pl->getHP() <= 0 && bot->getHP() <= 0)
                        {
                            cout << "Knight 1 and 2 have lost their life... " << endl;
#ifdef DEBUG

                            cout << "\t\t\tKnight 1 has " << pl->getHP() << " HP " << endl;
                            cout << "\t\t\tKnight 2 has " << bot->getHP() << " HP " << endl;
#endif
                            break;
                        }
                    }


                    break;
                }



            }

            // Archer vs Archer
            if (pl->getClassName() == "Archer" && bot->getClassName() == "Archer")
            {
                int firstRandomNumber = rand() % 100;
                int secondRandomNumber = rand() % 100;
                // if x < 30 then step else shoot;
                // Archer 1
                if (firstRandomNumber < 25 && distance(plNode,botNode) > 0) {

                    map.setCharacter(plNode->x, plNode->y, '1');

                    plNode = plNode->parent;

                    pl->setStartAndEndNode(plNode, botNode);
                    pl->OnUserCreate();
                    pl->Solve_AStar();
                    pl->setHitChances(pl->getHitChance() + 5);

                    map.printMap();
                }
                    // The Attack
                else if (firstRandomNumber <= 100) {
                    if ((rand() % 100) < pl->getHitChance()) {
                        bot->setHP(bot->getHP() - (pl->getDMG() * (bot->getArmor() / 100)));
                    }
                    if (pl->getHP() <= 0 && bot->getHP() > 0) {
                        cout << "Archer 2 has won the battle... " << endl;
#ifdef DEBUG
                        cout << "\t\t\tKnight 1 has " << pl->getHP() << " HP " << endl;
                        cout << "\t\t\tKnight 2 has " << bot->getHP() << " HP " << endl;
#endif
                        break;
                    } else if (pl->getHP() > 0 && bot->getHP() <= 0) {
                        cout << "Archer 1 has won the battle... " << endl;
#ifdef DEBUG
                        cout << "\t\t\tKnight 1 has " << pl->getHP() << " HP " << endl;
                        cout << "\t\t\tKnight 2 has " << bot->getHP() << " HP " << endl;
#endif
                        break;
                    } else if (pl->getHP() <= 0 && bot->getHP() <= 0) {
                        cout << "Archer 1 and 2 have lost their life... " << endl;
#ifdef DEBUG

                        cout << "\t\t\tKnight 1 has " << pl->getHP() << " HP " << endl;
                        cout << "\t\t\tKnight 2 has " << bot->getHP() << " HP " << endl;
#endif
                        break;
                    }
                }
                // Archer 2
                if (secondRandomNumber < 25 && distance(plNode, botNode) > 0) {
                    map.setCharacter(botNode->x, botNode->y, '2');
                    botNode = botNode->parent;
                    bot->setStartAndEndNode(botNode, plNode);
                    bot->OnUserCreate();
                    bot->Solve_AStar();
                    bot->setHitChances(bot->getHitChance() + 5);
                    map.printMap();
                }
                // The Attack
                if (secondRandomNumber <= 100) {
                    if (rand() % 100 < bot->getHitChance()) {
                        pl->setHP(pl->getHP() - (bot->getDMG() * (pl->getArmor() / 100)));
                    }

                }

                if (pl->getHP() <= 0 && bot->getHP() > 0) {
                    cout << "Archer 2 has won the battle... " << endl;
#ifdef DEBUG
                    cout << "\t\t\tKnight 1 has " << pl->getHP() << " HP " << endl;
                    cout << "\t\t\tKnight 2 has " << bot->getHP() << " HP " << endl;
#endif
                    break;
                } else if (pl->getHP() > 0 && bot->getHP() <= 0) {
                    cout << "Archer 1 has won the battle... " << endl;
#ifdef DEBUG
                    cout << "\t\t\tKnight 1 has " << pl->getHP() << " HP " << endl;
                    cout << "\t\t\tKnight 2 has " << bot->getHP() << " HP " << endl;
#endif
                    break;
                } else if (pl->getHP() <= 0 && bot->getHP() <= 0) {
                    cout << "Archer 1 and 2 have lost their life... " << endl;
#ifdef DEBUG

                    cout << "\t\t\tKnight 1 has " << pl->getHP() << " HP " << endl;
                    cout << "\t\t\tKnight 2 has " << bot->getHP() << " HP " << endl;
#endif
                    break;
                }
            }

            // Knight vs Archer

            if (pl->getClassName() == "Knight" && bot->getClassName() == "Archer" || pl->getClassName() == "Archer" && bot->getClassName() == "Knight")
            {
                int randomNumber = rand() % 100;
                if (pl->getClassName() == "Knight" && !flag1)
                {
                    kng = pl;
                    kngNode = plNode;
                    arc = bot;
                    arcNode = botNode;
                    flag1 = true;
                }
                if (pl->getClassName() == "Archer" && !flag2)
                {
                    kng = bot;
                    kngNode = botNode;
                    arc = pl;
                    arcNode = plNode;
                    flag2 = true;

                }

                map.setCharacter(kngNode->x, kngNode->y, kng->getCharacter());
                kng->setStartAndEndNode(plNode, botNode);
                kng->OnUserCreate();
                kng->Solve_AStar();

                arc->setStartAndEndNode(arcNode, kngNode);
                arc->OnUserCreate();
                arc->Solve_AStar();
                map.setCharacter(arcNode->x, arcNode->y, arc->getCharacter());

                // Knight
                if ( distance(kngNode, arcNode)  > 0)
                {
                    kngNode = kngNode->parent;

                    map.printMap();
                }
                else if (distance(kngNode, arcNode) <= 1)
                {
                    int ranNumAtt = rand() % 100;
                    if (ranNumAtt < kng->getHitChance())
                    {
                        arc->setHP(arc->getHP() - (kng->getDMG() * (1 - arc->getArmor() / 100)));
                    }
                }
                if (randomNumber < 50 && distance(arcNode, kngNode) > 1)
                {
                    arcNode = arcNode->parent;

                    arc->setHitChances(arc->getHitChance() + 15);

                    map.printMap();
                }
                else if (randomNumber <= 100)
                {
                    kng->setHP( kng->getHP() - ( arc->getDMG() * (1 -  kng->getArmor() / 100 ) ));
                }



                if (kng->getHP() <= 0 && arc->getHP() > 0) {
                    cout << "Archer has won the battle... " << endl;
#ifdef DEBUG
                    cout << "\t\t\tKnight has " << pl->getHP() << " HP " << endl;
                    cout << "\t\t\tArcher has " << bot->getHP() << " HP " << endl;
#endif
                    break;
                } else if (kng->getHP() > 0 && arc->getHP() <= 0) {
                    cout << "Knight has won the battle... " << endl;
#ifdef DEBUG
                    cout << "\t\t\tKnight has " << pl->getHP() << " HP " << endl;
                    cout << "\t\t\tArcher has " << bot->getHP() << " HP " << endl;
#endif
                    break;
                } else if (kng->getHP() <= 0 && arc->getHP() <= 0) {
                    cout << "Knight and Archer have lost their life... " << endl;
#ifdef DEBUG

                    cout << "\t\t\tKnight has " << pl->getHP() << " HP " << endl;
                    cout << "\t\t\tArcher has " << bot->getHP() << " HP " << endl;
#endif
                    break;
                }
            }

            map.printMap();
            cout << "\t\t\t\t There is a fight, so be careful :) \t\t\t\t" << endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
        }

    } else {
        std::cout << "There is no A* connection between Player and Bot..." << std::endl;
    }
}


#endif //DOEVENT