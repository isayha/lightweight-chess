#include "chess_game.h"

void main(int argc, char *argv[]) {
    chessBoard board = getNewChessBoard();
    printChessBoard(board, whiteTurn);
    printChessBoard(board, blackTurn);
}