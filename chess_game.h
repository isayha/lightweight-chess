#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "chess_misc.h"

#include <stdio.h>

typedef struct chessBoard {
    int spaces[8][8];
    int score;
    int turn; // TODO: Use internal board turn variable instead of passing turn variable separately
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

static const int pieceCutoff = 7;

static const int pieceValues[13] = {
    0,
    1, 3, 3, 5, 9, 0,
    -1, -3, -3, -5, -9, 0
};

static const char pieceStrs[13][3] = {
    {'-', '-', '\0'},
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
    // BISHOP
    {1, 1},
    {1, -1},
    {-1, 1},
    {-1, -1},
    // ROOK
    {0, -1},
    {-1, 0},
    {0, 1},
    {1, 0}
};

// Using the Unicode chess pieces will require some tomfoolery
// static char* pieceStrsFancy[13][5] = {
//     "☐",
//     "♙", "♘", "♗", "♖", "♕", "♔",
//     "♟" , "♞", "♝", "♜", "♛", "♚"
// };

chessBoard getNewChessBoard();
void printChessBoard(chessBoard);
void printChessBoardFancy(chessBoard);
coordsNode* getMoves(chessBoard, coords);
metaCoordsNode* getAllMoves(chessBoard);

int getScoreManual(chessBoard);

chessBoard makeMove(chessBoard, coordsTuple, int);

int isFile(char);
int isRank(char);
int fileToBoardCol(char);
int rankToBoardRow(char);

coordsTuple simpleNoteToMove(char*);
coordsTuple algNoteToMove(char*);

#endif