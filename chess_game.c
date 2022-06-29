#include "chess_game.h"

chessBoard getNewChessBoard() {
    chessBoard newBoard = {{
            {whiteRook, whiteKnight, whiteBishop, whiteQueen, whiteKing, whiteBishop, whiteKnight, whiteRook},
            {whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn},
            {none, none, none, none, none, none, none, none},
            {none, none, none, none, none, none, none, none},
            {none, none, none, none, none, none, none, none},
            {none, none, none, none, none, none, none, none},
            {blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn},
            {blackRook, blackKnight, blackBishop, blackQueen, blackKing, blackBishop, blackKnight, blackRook}
        }
    };
    return newBoard;
}

void printChessBoard(chessBoard board, int turn) {
    for (int row = 7; row >= 0; row--) {
        for (int col = 0; col <= 7; col++) {
            int piece;
            if (turn == whiteTurn) {
                piece = board.spaces[row][col];
            }
            else {
                piece = board.spaces[(row - 7) * (-1)][((col * (-1)) + 7)];
            }
            printf("%s ", pieceStrs[piece]);
        }
        printf("\n");
    }
    printf("\n");
}

coords * getMoves(chessBoard board, coords pieceCoords) {
    int piece = board.spaces[pieceCoords.row][pieceCoords.col];

    if (piece == none) {
        
    }

    coords *moves = NULL;

    int turn = piece / 7;

    switch (piece) {
        case whitePawn: case blackPawn:
            if (turn == 0) {
                // Capture Check
                if (pieceCoords.col > 0) {
                    // Left Diagonal Check
                }
                if (pieceCoords.col < 7) {
                    // Right Diagonal Check
                }

                // Forward Check
                if (board.spaces[pieceCoords.row + 1] == none) {
                    // Double Forward Check
                    if (pieceCoords.row == 1 && board.spaces[pieceCoords.row + 2] == none) {
                        
                    }
                }
            }
            if (turn == 1) {

            }
            break;
        case whiteKnight: case blackKnight:
            if (turn == 0) {

            }
            if (turn == 1) {
                
            }
            break;
        case whiteBishop: case blackBishop:
            if (turn == 0) {

            }
            if (turn == 1) {
                
            }
            break;
        case whiteRook: case blackRook:
            if (turn == 0) {

            }
            if (turn == 1) {
                
            }
            break;
        case whiteQueen: case blackQueen:
            if (turn == 0) {

            }
            if (turn == 1) {
                
            }
            break;
        case whiteKing: case blackKing:
            if (turn == 0) {

            }
            if (turn == 1) {
                
            }
            break;
        default:
            break;
    }
}