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

    int turn;
    if (piece > 6) {
        turn = -1;
    }
    else {
        turn = 1;
    }

    switch (piece) {
        case whitePawn: case blackPawn:
            // Capture Check (excl. en passant)
            if (pieceCoords.col > 0) {
                int otherPiece = board.spaces[pieceCoords.row + (1 * turn)][pieceCoords.col - 1];
                if (otherPiece != 0 && (piece / 7 != otherPiece / 7)) {
                    
                }
            }
            if (pieceCoords.col < 7) {
                int otherPiece = board.spaces[pieceCoords.row + (1 * turn)][pieceCoords.col + 1];
                if (otherPiece != 0 && (piece / 7 != otherPiece / 7)) {
                    
                }
            }
            // Forward Check
            if (board.spaces[pieceCoords.row + (1 * turn)] == none) {
                // Double Forward Check
                if (pieceCoords.row == (1 + (5 * (piece / 7))) && board.spaces[pieceCoords.row + (2 * turn)] == none) {
                    
                }
            }
        break;
        case whiteKnight: case blackKnight:
        
        break;
        case whiteBishop: case blackBishop:

        break;
        case whiteRook: case blackRook:
            for (int newRow = pieceCoords.row; (newRow < 8); newRow++) {
                int otherPiece = board.spaces[newRow][pieceCoords.col];
                if (otherPiece != 0) {
                    if (piece / 7 != otherPiece / 7) {

                    }
                    else {

                    }
                }
            }
            for (int newRow = pieceCoords.row; (newRow >= 0); newRow--) {
                int otherPiece = board.spaces[newRow][pieceCoords.col];
                if (otherPiece != 0) {
                    if (piece / 7 != otherPiece / 7) {

                    }
                    else {
                        
                    }
                }
            }
            for (int newCol = pieceCoords.col; (newCol < 8); newCol++) {
                int otherPiece = board.spaces[pieceCoords.row][newCol];
                if (otherPiece != 0) {
                    if (piece / 7 != otherPiece / 7) {

                    }
                    else {
                        
                    }
                }
            }
            for (int newCol = pieceCoords.col; (newCol >= 0); newCol--) {
                int otherPiece = board.spaces[pieceCoords.row][newCol];
                if (otherPiece != 0) {
                    if (piece / 7 != otherPiece / 7) {

                    }
                    else {
                        
                    }
                }
            }
        break;
        default:
        break;
    }
}