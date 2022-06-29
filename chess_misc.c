#include "chess_misc.h"

coordsNode * createNewNode(coords data) {
    coordsNode node = {.data = nullCoords, .nextNode = NULL};
    coordsNode *newNode = &node;
}

void appendNode(coordsNode* headNode, coordsNode* tailNode) {
    headNode->nextNode = tailNode;
}
