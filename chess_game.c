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

// It may be worth moving appendMove into chess_misc and renaming it to appendNode/renaming "move" to "coord", etc.
coordsNode* appendMove(coordsNode* currentNode, coords move) {
    coordsNode* newNode = createNewNode(move);
    currentNode->nextNode = newNode;
    return newNode;
}

coordsNode* getMoves(chessBoard board, coords pieceCoords) {
    // Move list setup
    coordsNode* headNode = createNewNode(pieceCoords);
    coordsNode* currentNode = headNode;

    // Variable setup
    int row = pieceCoords.row;
    int col = pieceCoords.col;
    int piece = board.spaces[row][col];

    if (piece == none) {
        return NULL;
    }

    // Turn indicator setup
    // TODO: This may be need to be removed, as it has been made somewhat redundant by getAllMoves
    int turn;
    if (piece > 6) { // TODO: Consider removing hardcoding/creating a static const variable pieceTypeCount
        turn = -1; // turn = -1 <=> Black turn
    }
    else {
        turn = 1; // turn = 1 <=> White turn
    }

    // Move search logic
    switch (piece) {
        int newRow;
        int newCol;
        int otherPiece;
        case whitePawn: case blackPawn:
            // Diagonal (capture) check
            newRow = row + (1 * turn);
            for (int colInc = -1; colInc <= 1; colInc += 2) {
                newCol = col + colInc;
                if (newCol < 0 || newCol > 7) {
                    continue;
                }
                
                otherPiece = board.spaces[newRow][newCol];
                if (otherPiece != none && (piece / 7 != otherPiece / 7)) {
                    coords move = {newRow, newCol};
                    currentNode = appendMove(currentNode, move);
                }
                
                // TODO: Add En Passant logic here
            }
            // Forward check
            otherPiece = board.spaces[newRow][col];
            if (otherPiece == none) {
                coords move = {newRow, col};
                currentNode = appendMove(currentNode, move);
                
                // Double forward check
                newRow = row + (2 * turn);

                otherPiece = board.spaces[newRow][col];
                if (otherPiece == none && row == (1 + (5 * (piece / 7)))) {
                    coords move = {newRow, col};
                    currentNode = appendMove(currentNode, move);
                }
            }
        break;
        case whiteKnight: case blackKnight:
            for (int i = 0; i < 8; i++) {
                newRow = row + knightMoves[i][0];
                newCol = col + knightMoves[i][1];
                if ((newRow >= 0 && newRow < 8) && (newCol >= 0 && newCol < 8)) {
                    otherPiece = board.spaces[newRow][newCol];
                    if (otherPiece == 0 || (piece / 7 != otherPiece / 7)) {
                        coords move = {newRow, newCol};
                        currentNode = appendMove(currentNode, move);
                    }
                }
            }
        break;
        case whiteBishop: case blackBishop:
        case whiteRook: case blackRook:
        case whiteQueen: case blackQueen:
        case whiteKing: case blackKing:
            int startIndex;
            int endIndex;

            if (piece != whiteRook && piece != blackRook) {
                startIndex = 0;
            }
            else {
                startIndex = 4;
            }

            if (piece != whiteBishop && piece != blackBishop) {
                endIndex = 8;
            }
            else {
                endIndex = 4;
            }

            for (int i = startIndex; i < endIndex; i++) {
                newRow = row + dirs[i][0];
                newCol = col + dirs[i][1];
                while ((newRow >= 0 && newRow < 8) && (newCol >= 0 && newCol < 8)) {
                    otherPiece = board.spaces[newRow][newCol];
                    if (otherPiece == 0 || (piece / 7 != otherPiece / 7)) {
                        coords move = {newRow, newCol};
                        if (piece == whiteKing || piece == blackKing) {
                            // TODO: Add king vulnerability check (recursive call) here
                        }
                        currentNode = appendMove(currentNode, move);
                        if (otherPiece != 0 || (piece == whiteKing || piece == blackKing)) {
                            break;
                        }
                    }
                    else {
                        break;
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

metaCoordsNode* getAllMoves(chessBoard board, int turn) {
    metaCoordsNode* headMCNode = createNewMCNode(NULL);
    metaCoordsNode* currentMCNode = headMCNode;

    for (int row = 7; row >= 0; row--) {
        for (int col = 0; col <= 7; col++) {
            int piece = board.spaces[row][col];
            if (piece > 0 && 1 + ((piece / 6) * -2) == turn) {
                coords pieceCoords = {row, col};
                coordsNode* moves = getMoves(board, pieceCoords);
                if (moves && moves->nextNode) { // If the movelist does not solely contain the identity move (i.e. if at least one move exists)...
                    // Somehow this minor memory optimization solves what appears to be a print buffer issue.
                    // Calling this function and then subsequently printing the results via printAllMoves for both players in sequence
                    // seems to break without an explicit error.
                    metaCoordsNode* newMCNode = createNewMCNode(moves);
                    currentMCNode->nextMCNode = newMCNode;
                    currentMCNode = newMCNode;
                }
            }
        }
    }
    return headMCNode;
}

int getScore(chessBoard board, int turn) {
    int score = 0;
    for (int row = 7; row >= 0; row--) {
        for (int col = 0; col <= 7; col++) {
            int piece = board.spaces[row][col];
            if (piece > 0 && 1 + ((piece / 6) * -2) == turn) {
                // TODO: Consider using an array (piece as index)
                // or a hashmap instead of a switch
                switch (piece) {
                    case whitePawn: case blackPawn:
                        score += 1;
                    break;
                    case whiteKnight: case blackKnight: case whiteBishop: case blackBishop:
                        score += 3;
                    break;
                    case whiteRook: case blackRook:
                        score += 5;
                    break;
                    case whiteQueen: case blackQueen:
                        score += 9;
                    break;
                    // TODO: Add king value (?)
                    default:
                    break;
                }
            }
        }
    }
    return score;
}