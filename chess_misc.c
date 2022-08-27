#include "chess_misc.h"

coordsNode* createNewNode(coords data) {
    coordsNode* newNode = malloc(sizeof(coordsNode));
    newNode->data = data;
    newNode->nextNode = NULL;
    return newNode;
}

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
    if (headMCNode) { // Should prevent undefined behaviour
    metaCoordsNode* currentMCNode = headMCNode->nextMCNode; // The headMCNode's data is always NULL
        while (currentMCNode) {
            coordsNode* data = currentMCNode->data;
            printAllNodes(data->nextNode); // Skips the headNode as it contains the identity move (when a linked list of coordsNodes is used to hold chess moves)
            // This may need to be changed as this makes the function non-generic and its name misleading
            currentMCNode = currentMCNode->nextMCNode;
        }
    }
}