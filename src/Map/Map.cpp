//
// Created by User on 23.11.2022.
//

#include <iostream>

#include "Map.h"
using namespace std;

Map::Map() {
    field = nullptr;
    w = 0, h = 0;

}

Map::Map(int _w, int _h)
{
    w = _w, h = _h;
    field = new char* [_h];
    for (int i = 0; i < h; ++i) {
        field[i] = new char[_w];
    }
//    for (int i = 0; i < 2; i++) {
//        elements[i]->x = 0;
//        elements[i]->y = 0;
//        elements[i]->element = '0';
//    }
}

void Map::initMap()
{
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j)
        {
            int randomNumber = (rand() % 100) + 1;
            if (randomNumber < 50) {
                field[i][j] = '_';
            }
            else if (randomNumber < 70) {
                field[i][j] = 'o';
            }
            else if (randomNumber < 85) {
                field[i][j] = '$';
            }
            else if (randomNumber < 100) {
                field[i][j] = '*';
            }
        }
    }
}

void Map::printMap()
{
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            std::cout << field[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int Map::getW() const { return this->w; }
int Map::getH() const { return this->h; }
char** &Map::getField() { return this->field; }

void Map::drawLine(int x, int y)
{
    field[y][x] = '&';
}

void Map::setCharacter(int x, int y, char ch)
{
//    if (ch == '1')
//    {
//        field[elements[0]->y][elements[0]->x] = elements[0]->element;
//        elements[0]->x = x;
//        elements[0]->y = y;
//        elements[0]->element = field[y][x];
//    }
//
//    if (ch == '2')
//    {
//        field[elements[1]->y][elements[1]->x] = elements[1]->element;
//        elements[1]->x = x;
//        elements[1]->y = y;
//        elements[1]->element = field[y][x];
//    }

    field[y][x] = ch;
}

Map::~Map()
{
    delete[] field;
    w = 0, h = 0;
}