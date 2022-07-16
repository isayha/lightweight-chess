#include "chess_game.h"

void main(int argc, char *argv[]) {
    chessBoard board = getNewChessBoard();
    printChessBoard(board, whiteTurn);
    printChessBoard(board, blackTurn);

    coords testCoords = {1, 1};
    coordsNode* headNode = getMoves(board, testCoords);
    printAllNodes(headNode);
    freeAllNodes(headNode);

    printf("\n");

    testCoords.row = 6; testCoords.col = 6;
    headNode = getMoves(board, testCoords);
    printAllNodes(headNode);
    freeAllNodes(headNode);

    printf("\n");

    testCoords.row = 0; testCoords.col = 1;
    headNode = getMoves(board, testCoords);
    printAllNodes(headNode);
    freeAllNodes(headNode);

    printf("\n");

    testCoords.row = 7; testCoords.col = 6;
    headNode = getMoves(board, testCoords);
    printAllNodes(headNode);
    freeAllNodes(headNode);
}