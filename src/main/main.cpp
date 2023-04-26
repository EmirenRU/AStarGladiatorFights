#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#include "Event.h"

#include "../Map/Map.h"
#include "../Units/Player.h"
#include "../Units/Knight.h"
#include "../Units/Archer.h"

using namespace std;

// A* algorithm with Gladiatorial Fights (Knights and Archers)



int main() {

    srand(time(0));

    Map map(10, 10);
    map.initMap();
    map.printMap();

// Knight 1 and Knight 2

    Player *plKng = new Knight(map, 0, 0, 5, 9, '1');
    plKng->initStats();
    plKng->OnUserCreate();
    Node *plNodeKng = plKng->getStartNode();

    Player *botKng = new Knight(map, 5, 9, 0, 0, '2');
    botKng->initStats();
    botKng->OnUserCreate();
    Node *botNodeKng = botKng->getStartNode();

// Archer 1 and 2

    Player *plArc = new Archer(map, 0, 0, 5, 9, '1');
    plArc->initStats();
    plArc->OnUserCreate();
    Node *plNodeArc = plArc->getStartNode();

    Player *botArc = new Archer(map, 5, 9, 0, 0, '2');
    botArc->initStats();
    botArc->OnUserCreate();
    Node *botNodeArc = botArc->getStartNode();

    // to start the A* algorithm and fight

    // Knight vs Knight

    A_Star_Event(map, plKng, plNodeKng, botKng, botNodeKng);

    // Archer vs Archer

//    A_Star_Event(map, plArc, plNodeArc, botArc, botNodeArc);

    // Knight vs Archer

//        A_Star_Event(map, plKng, plNodeKng, botArc, botNodeArc);

    return 0;
}


