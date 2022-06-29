#include <stdio.h>

typedef struct Coords {
    int row;
    int col;
} coords;

enum chessPiece {
    none,
    whitePawn,
    whiteKnight,
    whiteBishop,
    whiteRook,
    whiteQueen,
    whiteKing,
    blackPawn,
    blackKnight,
    blackBishop,
    blackRook,
    blackQueen,
    blackKing,
};

enum orientBoard {
    orientWhite,
    orientBlack
};

char chessPieceStr[13][3] = {
    {'X', 'X', '\0'},
    {'W', 'P', '\0'},
    {'W', 'K', '\0'},
    {'W', 'B', '\0'},
    {'W', 'R', '\0'},
    {'W', 'Q', '\0'},
    {'W', 'K', '\0'},
    {'B', 'P', '\0'},
    {'B', 'K', '\0'},
    {'B', 'B', '\0'},
    {'B', 'R', '\0'},
    {'B', 'Q', '\0'},
    {'B', 'K', '\0'}
};

int chessBoard[8][8] = {
    {whiteRook, whiteKnight, whiteBishop, whiteQueen, whiteKing, whiteBishop, whiteKnight, whiteRook},
    {whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn, whitePawn},
    {none, none, none, none, none, none, none, none},
    {none, none, none, none, none, none, none, none},
    {none, none, none, none, none, none, none, none},
    {none, none, none, none, none, none, none, none},
    {blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn, blackPawn},
    {blackRook, blackKnight, blackBishop, blackQueen, blackKing, blackBishop, blackKnight, blackRook}
};

void printChessBoard(int chessBoard[8][8], int orientation) {
    for (int row = 7; row >= 0; row--) {
        for (int col = 0; col < 8; col++) {
            int chessPiece;
            if (orientation == orientWhite) {
                chessPiece = chessBoard[row][col];
            }
            else {
                chessPiece = chessBoard[(row - 7) * (-1)][((col * (-1)) + 7)];
            }
            printf("%s ", chessPieceStr[chessPiece]);
        }
        printf("\n");
    }
    printf("\n");
}

coords getMoves(int chessBoard[8][8], coords pieceCoords) {
    int chessPiece = chessBoard[pieceCoords.row][pieceCoords.col];

    if (chessPiece == none) {

    }

    coords *moves = NULL;

    int orientation = chessPiece / 7;

    switch (chessPiece) {
        case whitePawn: case blackPawn:
            if (orientation == 0) {
                // Capture Check
                if (pieceCoords.col > 0) {
                    // Left Diagonal Check
                }
                if (pieceCoords.col < 7) {
                    // Right Diagonal Check
                }

                // Forward Check
                if (chessBoard[pieceCoords.row + 1] == none) {

                    // Double Forward Check
                    if (pieceCoords.row == 1 && chessBoard[pieceCoords.row + 2] == none) {
                        
                    }
                }
            }
            if (orientation == 1) {

            }
            break;
        case whiteKnight: case blackKnight:
            if (orientation == 0) {

            }
            if (orientation == 1) {
                
            }
            break;
        case whiteBishop: case blackBishop:
            if (orientation == 0) {

            }
            if (orientation == 1) {
                
            }
            break;
        case whiteRook: case blackRook:
            if (orientation == 0) {

            }
            if (orientation == 1) {
                
            }
            break;
        case whiteQueen: case blackQueen:
            if (orientation == 0) {

            }
            if (orientation == 1) {
                
            }
            break;
        case whiteKing: case blackKing:
            if (orientation == 0) {

            }
            if (orientation == 1) {
                
            }
            break;
        default:
            break;
    }
}

void main(int argc, char *argv[]) {
    printChessBoard(chessBoard, orientWhite);
    printChessBoard(chessBoard, orientBlack);
}



