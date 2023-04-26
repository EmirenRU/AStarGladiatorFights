//
// Created by User on 23.11.2022.
//

#ifndef LAB02_Emil_NODE_H
#define LAB02_Emil_NODE_H

#include <vector>


struct Node
{
    bool bObstacle = false;                 // Is the node an obstruction?
    bool bVisited = false;                  // Have we searched this node before?
    float fGlobalGoal;                      // Distance to goal so far
    float fLocalGoal;                       // Distance to goal if we take alternative route
    float fMultiplier;                      // Multiplier of element
    int x;                                  // Node's position in 2D space
    int y;
    std::vector<Node*> vecNeighbours;       // Connections to neighbours
    Node* parent;                           // Node connecting to this node that offers the shortest parent;
};

#endif //LAB02_Emil_NODE_H
