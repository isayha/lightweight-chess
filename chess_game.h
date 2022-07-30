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
    blackTurn = -1,
    whiteTurn = 1
};

static const char pieceStrs[13][3] = {
    {'X', 'X', '\0'},
    {'W', 'P', '\0'}, {'W', 'N', '\0'}, {'W', 'B', '\0'}, {'W', 'R', '\0'}, {'W', 'Q', '\0'}, {'W', 'K', '\0'},
    {'B', 'P', '\0'}, {'B', 'N', '\0'}, {'B', 'B', '\0'}, {'B', 'R', '\0'}, {'B', 'Q', '\0'}, {'B', 'K', '\0'}
};

static const int knightMoves[8][2] = {
    {-2, -1},
    {-2, 1},
    {-1, -2},
    {-1, 2},
    {1, -2},
    {1, 2},
    {2, -1},
    {2, 1}
};

static const int dirs[8][2] = {
    //BISHOP
    {1, 1},
    {1, -1},
    {-1, 1},
    {-1, -1},
    //ROOK
    {0, -1},
    {-1, 0},
    {0, 1},
    {1, 0}
};

// Using the Unicode chess pieces will require some tomfoolery
// static char pieceStrsAdv[13][2] = {
//     "☐",
//     "♙", "♘", "♗", "♖", "♕", "♔",
//     "♟" , "♞", "♝", "♜", "♛", "♚"
// };

chessBoard getNewChessBoard();
void printChessBoard(chessBoard, int);
coordsNode* appendMove(coordsNode*, coords);
coordsNode* getMoves(chessBoard, coords);

#endif