#include "chess_game.h"

void testGameSimpleNote(chessBoard board) {
    while (1) {
        int prevTurn = board.turn;
        printf("Score: %d\n", board.score);
        printChessBoardFancy(board);
        printf("Propose a move (Simple Notation): ");
        char moveStr[6]; // 16 bytes is an arbitrary choice
        scanf("%s", &moveStr);
        coordsTuple moveCT = simpleNoteToMove(moveStr);
        // printf("Proposed Origin Row: %d\n", moveCT.origin.row);
        // printf("Proposed Origin Col: %d\n", moveCT.origin.col);
        // printf("Proposed Dest. Row: %d\n", moveCT.dest.row);
        // printf("Proposed Dest. Col: %d\n\n", moveCT.dest.col);
        board = makeMove(board, moveCT, 1);
        if (board.turn == prevTurn) {
            printf("\nERROR: The move you have proposed is illegal. Please try again.\n\n");
        }
    }
}

void main(int argc, char *argv[]) {
    chessBoard board = getNewChessBoard();
    testGameSimpleNote(board);
}