#include "chess_game.h"

void main(int argc, char *argv[]) {
    chessBoard board = getNewChessBoard();
    printChessBoard(board, whiteTurn);
    printf("\n");
    printChessBoard(board, blackTurn);

    printf("\nPAWN WHITE:");

    coords testCoords = {1, 1};
    coordsNode* headNode = getMoves(board, testCoords);
    printAllNodes(headNode);
    freeAllNodes(headNode);

    printf("\nPAWN BLACK:");

    testCoords.row = 6; testCoords.col = 6;
    headNode = getMoves(board, testCoords);
    printAllNodes(headNode);
    freeAllNodes(headNode);

    printf("\nKNIGHT WHITE:");

    testCoords.row = 0; testCoords.col = 1;
    headNode = getMoves(board, testCoords);
    printAllNodes(headNode);
    freeAllNodes(headNode);

    printf("\nKNIGHT BLACK:");

    testCoords.row = 7; testCoords.col = 6;
    headNode = getMoves(board, testCoords);
    printAllNodes(headNode);
    freeAllNodes(headNode);

    // for (int i = 0; i < 8; i++) {
    //     board.spaces[1][i] = none;
    //     board.spaces[6][i] = none;
    // }

    // printf("\n\nPAWNS REMOVED");

    // printf("\n\nBISHOP WHITE");

    // testCoords.row = 0; testCoords.col = 2;
    // headNode = getMoves(board, testCoords);
    // printAllNodes(headNode);
    // freeAllNodes(headNode);

    // printf("\nBISHOP BLACK");

    // testCoords.row = 7; testCoords.col = 5;
    // headNode = getMoves(board, testCoords);
    // printAllNodes(headNode);
    // freeAllNodes(headNode);

    // printf("\nROOK WHITE:");

    // testCoords.row = 0; testCoords.col = 0;
    // headNode = getMoves(board, testCoords);
    // printAllNodes(headNode);
    // freeAllNodes(headNode);

    // printf("\nROOK BLACK:");

    // testCoords.row = 7; testCoords.col = 7;
    // headNode = getMoves(board, testCoords);
    // printAllNodes(headNode);
    // freeAllNodes(headNode);

    // printf("\nQUEEN WHITE:");

    // testCoords.row = 0; testCoords.col = 3;
    // headNode = getMoves(board, testCoords);
    // printAllNodes(headNode);
    // freeAllNodes(headNode);

    // printf("\nQUEEN BLACK:");

    // testCoords.row = 7; testCoords.col = 3;
    // headNode = getMoves(board, testCoords);
    // printAllNodes(headNode);
    // freeAllNodes(headNode);

    // printf("\nKING WHITE:");

    // testCoords.row = 0; testCoords.col = 4;
    // headNode = getMoves(board, testCoords);
    // printAllNodes(headNode);
    // freeAllNodes(headNode);

    // printf("\nKING BLACK:");

    // testCoords.row = 7; testCoords.col = 4;
    // headNode = getMoves(board, testCoords);
    // printAllNodes(headNode);
    // freeAllNodes(headNode);

    printf("\n\nALL MOVES (WHITE):");

    metaCoordsNode* headMCNode = getAllMoves(board, 1);
    printAllMCNodes(headMCNode);
}