#ifndef CHESS_MISC_H
#define CHESS_MISC_H

#include <stdio.h>
#include <stdlib.h>

typedef struct coords {
    int row;
    int col;
} coords;

static const coords nullCoords = {-1, -1};

typedef struct coordsNode {
    coords data;
    struct coordsNode* nextNode;
} coordsNode;

coordsNode* createNewNode(coords);
// void appendNode(coordsNode*, coordsNode*); // Unused
void freeAllNodes(coordsNode*);
void printAllNodes(coordsNode*);

typedef struct metaCoordsNode {
    coordsNode* data;
    struct metaCoordsNode* nextMCNode;
} metaCoordsNode;

metaCoordsNode* createNewMCNode(coordsNode*);
void freeAllMCNodes(metaCoordsNode*);
void printAllMCNodes(metaCoordsNode*);

#endif