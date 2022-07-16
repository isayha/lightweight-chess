#include "chess_misc.h"

coordsNode* createNewNode(coords data) {
    coordsNode* newNode = malloc(sizeof(coordsNode));
    newNode->data = data;
    newNode->nextNode = NULL;
    return newNode;
}

// Unused
// void appendNode(coordsNode* headNode, coordsNode* tailNode) {
//     headNode->nextNode = tailNode;
// }

void freeAllNodes(coordsNode* headNode) {
    coordsNode* currentNode = headNode;
    while (currentNode) {
        coordsNode* prevNode = currentNode;
        currentNode = currentNode->nextNode;
        free(prevNode);
    }
}

void printAllNodes(coordsNode* headNode) {
    coordsNode* currentNode = headNode;
    while (currentNode) {
        printf("\ncurrentNode->data: {%d, %d}", currentNode->data.row, currentNode->data.col);
        currentNode = currentNode->nextNode;
    }
}