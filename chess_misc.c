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
    };
}

metaCoordsNode* createNewMCNode(coordsNode* data) {
    metaCoordsNode* newMCNode = malloc(sizeof(data));
    newMCNode->data = data;
    newMCNode->nextMCNode = NULL;
    return newMCNode;
}

void freeAllMCNodes(metaCoordsNode* headMCNode) {
    metaCoordsNode* currentMCNode = headMCNode;
    while (currentMCNode) {
        metaCoordsNode* prevMCNode = currentMCNode;
        currentMCNode = currentMCNode->nextMCNode;

        coordsNode* data = prevMCNode->data;
        freeAllNodes(data);

        free(prevMCNode);
    }
}

void printAllMCNodes(metaCoordsNode* headMCNode) {
    metaCoordsNode* currentMCNode = headMCNode->nextMCNode;
    while (currentMCNode) {
        coordsNode* data = currentMCNode->data;
        printAllNodes(data->nextNode);
        currentMCNode = currentMCNode->nextMCNode;
    }
}