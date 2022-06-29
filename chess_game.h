#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "chess_misc.h"

#include <stdio.h>

typedef struct chessBoard {
    int spaces[8][8];
} chessBoard;

enum chessPiece {
    none,
    whitePawn, whiteKnight, whiteBishop, whiteRook, whiteQueen, whiteKing,
    blackPawn, blackKnight, blackBishop, blackRook, blackQueen, blackKing
};

enum turn {
    whiteTurn,
    blackTurn
};

char pieceStrs[13][3] = {
    {'X', 'X', '\0'},
    {'W', 'P', '\0'}, {'W', 'K', '\0'}, {'W', 'B', '\0'}, {'W', 'R', '\0'}, {'W', 'Q', '\0'}, {'W', 'K', '\0'},
    {'B', 'P', '\0'}, {'B', 'K', '\0'}, {'B', 'B', '\0'}, {'B', 'R', '\0'}, {'B', 'Q', '\0'}, {'B', 'K', '\0'}
};

chessBoard getNewChessBoard();
void printChessBoard(chessBoard, int);
coords * getMoves(chessBoard, coords);

#endif