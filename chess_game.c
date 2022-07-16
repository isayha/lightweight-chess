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
}

coordsNode* getMoves(chessBoard board, coords pieceCoords) {
    coordsNode* headNode = createNewNode(pieceCoords);
    coordsNode* currentNode = headNode;
    int row = pieceCoords.row;
    int col = pieceCoords.col;
    int piece = board.spaces[row][col];

    if (piece == none) {
        return headNode;
    }

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
            if (col > 0) {
                // Diagonal Check (Left relative to White)
                int otherPiece = board.spaces[row + (1 * turn)][col - 1];
                if (otherPiece != 0 && (piece / 7 != otherPiece / 7)) {
                    coords move = {row + (1 * turn), col - 1};
                    coordsNode* newNode = createNewNode(move);
                    currentNode->nextNode = newNode;
                    currentNode = newNode;
                }
            }
            if (col < 7) {
                // Diagonal Check (Right relative to White)
                int otherPiece = board.spaces[row + (1 * turn)][col + 1];
                if (otherPiece != 0 && (piece / 7 != otherPiece / 7)) {
                    coords move = {row + (1 * turn), col + 1};
                    coordsNode* newNode = createNewNode(move);
                    currentNode->nextNode = newNode;
                    currentNode = newNode;
                }
            }
            // Forward Check
            if (board.spaces[row + (1 * turn)][col] == none) {
                coords move = {row + (1 * turn), col};
                coordsNode* newNode = createNewNode(move);
                currentNode->nextNode = newNode;
                currentNode = newNode;
                // Double Forward Check
                if (row == (1 + (5 * (piece / 7))) && board.spaces[row + (2 * turn)][col] == none) {
                    coords move = {row + (2 * turn), col};
                    coordsNode* newNode = createNewNode(move);
                    currentNode->nextNode = newNode;
                    currentNode = newNode;
                }
            }
        break;
        case whiteKnight: case blackKnight:
            for (int i = 0; i < 8; i++) {
                int newRow = row + knightMoves[i][0];
                int newCol = col + knightMoves[i][1];
                if ((newRow >= 0 && newRow < 8) && (newCol >= 0 && newCol < 8)) {
                    int otherPiece = board.spaces[newRow][newCol];
                    if (otherPiece == 0 || (piece / 7 != otherPiece / 7)) {
                        coords move = {newRow, newCol};
                        coordsNode* newNode = createNewNode(move);
                        currentNode->nextNode = newNode;
                        currentNode = newNode;
                    }
                }
            }
        break;
        case whiteBishop: case blackBishop:
        case whiteRook: case blackRook:
        case whiteQueen: case blackQueen:
        case whiteKing: case blackKing:
            int i_start;
            int i_end;

            if (piece != whiteRook && piece != blackRook) {
                i_start = 0;
            }
            else {
                i_start = 4;
            }

            if (piece != whiteBishop && piece != blackBishop) {
                i_end = 8;
            }
            else {
                i_end = 4;
            }

            for (int i = i_start; i < i_end; i++) {
                int newRow = row + dirs[i][0];
                int newCol = col + dirs[i][1];
                int endFlag = 0;
                while (!endFlag && (newRow >= 0 && newRow < 8) && (newCol >= 0 && newCol < 8)) {
                    int otherPiece = board.spaces[newRow][newCol];
                    if (otherPiece == 0 || (piece / 7 != otherPiece / 7)) {
                        coords move = {newRow, newCol};
                        coordsNode* newNode = createNewNode(move);
                        currentNode->nextNode = newNode;
                        currentNode = newNode;
                        if (otherPiece != 0) {
                            endFlag = 1;
                        }
                    }
                    else {
                        endFlag = 1;
                    }
                    newRow += dirs[i][0];
                    newCol += dirs[i][1];
                }
            }
        break;
        default:
        break;
    }
    return headNode;
}