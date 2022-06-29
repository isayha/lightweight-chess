#ifndef CHESS_MISC_H
#define CHESS_MISC_H

#include <stdio.h>

typedef struct coords {
    int row;
    int col;
} coords;

const coords nullCoords = {-1, -1};

typedef struct coordsNode {
    coords data;
    coordsNode *nextNode;
} coordsNode;

coordsNode * createNewNode(coords);
void appendNode(coordsNode*, coordsNode*);

#endif