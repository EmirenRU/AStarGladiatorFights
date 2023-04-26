//
// Created by User on 23.11.2022.
//

#include "Knight.h"

Knight::Knight() {}

Knight::Knight(Map& map, int _x, int _y, int _x1, int _y1, char ch)
{
    this->map = map;
    mapHeight = map.getH();
    mapWidth = map.getW();
    xStart = _x, yStart = _y;
    xEnd = _x1, yEnd = _y1;
    this->ch = ch;
}


bool Knight::OnUserCreate()
{
    nodes = new Node*[mapHeight];

    for (int i = 0; i < mapWidth; i++)
        nodes[i] = new Node[mapWidth];

    for (int x = 0; x < mapWidth; x++)
        for (int y = 0; y < mapHeight; y++)
        {
            nodes[y][x].x = x;
            nodes[y][x].y = y;
            nodes[y][x].bObstacle    = false;
            nodes[y][x].parent       = nullptr;
            nodes[y][x].bVisited     = false;
            nodes[y][x].fMultiplier  = 1;

        }


    for (int x = 0; x < mapWidth; x++)
    {
        for (int y = 0; y < mapHeight; y++)
        {
            if ( y > 0 )
                nodes[y][x].vecNeighbours.push_back(&nodes[ y - 1 ][ x ]);

            if ( y < mapHeight - 1 )
                nodes[y][x].vecNeighbours.push_back(&nodes[ y + 1 ] [ x ]);

            if ( x > 0 )
                nodes[y][x].vecNeighbours.push_back(&nodes[ y ][ x - 1 ]);

            if ( x < mapWidth - 1)
                nodes[y][x].vecNeighbours.push_back(&nodes[ y ][ x + 1 ]);

            if ( y > 0 && x > 0)
                nodes[y][x].vecNeighbours.push_back(&nodes[ y - 1 ][ x - 1 ]);

            if ( y < mapHeight - 1 && x > 0)
                nodes[y][x].vecNeighbours.push_back(&nodes[ y + 1 ][ x - 1 ]);

            if ( y > 0 && x < mapWidth - 1)
                nodes[y][x].vecNeighbours.push_back(&nodes[ ( y - 1 )][( x + 1 ) ]);

            if ( y < mapHeight - 1 && x < mapWidth - 1)
                nodes[y][x].vecNeighbours.push_back(&nodes[ ( y + 1 )][( x + 1 ) ]);
        }
    }

    start = &nodes[yStart][xStart];
    end = &nodes[yEnd][xEnd];

    Solve_AStar();
    return true;
}

bool Knight::Solve_AStar()
{
    auto distance = [](const Node* a, const Node* b)
    {
        return sqrtf( ( a->x - b->x ) * ( a->x - b->x ) + ( a->y - b->y ) * ( a->y - b->y ));
    };

    for (int x = 0; x < mapWidth; x++)
        for (int y = 0; y < mapHeight; y++)
        {
            nodes[y][x].bVisited    = false;
            nodes[y][x].fGlobalGoal = INFINITY;
            nodes[y][x].fLocalGoal  = INFINITY;
            nodes[y][x].parent      = nullptr;

            if (map.getField()[y][x] == 'o')
            {
                nodes[y][x].bObstacle = true;
                nodes[y][x].fMultiplier = INFINITY;
            }
            if (map.getField()[y][x] == '$')
                nodes[y][x].fMultiplier = 0;
            if (map.getField()[y][x] == '*')
                nodes[y][x].fMultiplier = 10;
            if (map.getField()[y][x] != '*' && map.getField()[y][x] != '$')
                nodes[y][x].fMultiplier = 1;

        }

    Node* nodeCurrent = end;
    end->fLocalGoal = 0.0f;
    end->fGlobalGoal = distance(start, end);
    end->fMultiplier = 0.0f;

    list<Node*> listNotTestedNodes;
    listNotTestedNodes.push_back(end);

    while (!listNotTestedNodes.empty() && nodeCurrent != start)
    {
        listNotTestedNodes.sort([](const Node* l, const Node* r) { return l->fGlobalGoal < r->fGlobalGoal; });

        while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
            listNotTestedNodes.pop_front();

        if (listNotTestedNodes.empty())
            break;


        nodeCurrent = listNotTestedNodes.front();
        nodeCurrent->bVisited = true;

        for (auto nodeNeighbour : nodeCurrent -> vecNeighbours)
        {
            if (!nodeNeighbour->bVisited && !nodeNeighbour->bObstacle)
                listNotTestedNodes.push_back(nodeNeighbour);

            float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + (distance(nodeCurrent, nodeNeighbour) * nodeNeighbour->fMultiplier );

            if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
            {
                nodeNeighbour->parent = nodeCurrent;
                nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;

                nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + distance(nodeNeighbour, start);
            }
        }
    }

    return true;
}

void Knight::initStats()
{
    HP = 100.f;
    DMG = 10.f;
    Armor = 75.f;
    HitChance = 50;
}

Node* &Knight::getStartNode() { return start; }
string Knight::getClassName() { return "Knight"; }

int Knight::getHitChance() { return HitChance; }
float Knight::getHP() { return HP; }
float Knight::getArmor() { return Armor; }
float Knight::getDMG() { return DMG; }
char Knight::getCharacter() { return this->ch; }
void Knight::setHP(float hp) { this->HP = hp; }
void Knight::setHitChances(int hitChances) { this->HitChance = hitChances; }
void Knight::setStartAndEndNode(Node *&start, Node *&end)
{
    this->start = start;
    this->end   = end;
}

Knight::~Knight()
{
    Player::~Player();
}