//
// Created by User on 23.11.2022.
//

#ifndef LAB02_Emil_MAP_H
#define LAB02_Emil_MAP_H

#include <cstdlib>

class Map {
private:
    char** field; // ASCII Map N*M
    int w, h; // Map's width and height


public:
    Map();
    Map(int _w, int _h);
    void initMap();         // Init map or generate the field with random elements
    void printMap();        // Print the field
    int getW() const;       // get Width or Height
    int getH() const;
    ~Map();
    char** &getField();     // Get ASCII Map
    void drawLine(int x, int y);
    void setCharacter(int x, int y, char ch);
};


#endif //LAB02_EASAMIGULLIN_MAP_H
