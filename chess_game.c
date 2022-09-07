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
        }, 0, whiteTurn
    };
    return newBoard;
}

void printChessBoard(chessBoard board) {
    for (int row = 7; row >= 0; row--) {
        for (int col = 0; col <= 7; col++) {
            int piece;
            if (board.turn == whiteTurn) {
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

void printChessBoardFancy(chessBoard board) {
    for (int row = 7; row >= 0; row--) {
        if (board.turn == whiteTurn) {
            printf("%d ", row + 1);
        }
        else {
            printf("%d ", ((row - 7) * (-1)) + 1);
        }
        for (int col = 0; col <= 7; col++) {
            int piece;
            if (board.turn == whiteTurn) {
                piece = board.spaces[row][col];
            }
            else {
                piece = board.spaces[(row - 7) * (-1)][((col * (-1)) + 7)];
            }
            // printf("%s ", pieceStrsFancy[piece]);
            printf("%s ", pieceStrs[piece]);
        }
        printf("\n");
    }
    if (board.turn == whiteTurn) {
        printf("  a  b  c  d  e  f  g  h \n\n");
    }
    else {
        printf("  h  g  f  e  d  c  b  a \n\n");
    }
}

coordsNode* getMoves(chessBoard board, coords pieceCoords) {
    int row = pieceCoords.row;
    int col = pieceCoords.col;
    int piece = board.spaces[row][col];
    int turn = board.turn;
    if (piece == none || turn != 1 + ((piece / pieceCutoff) * -2)) {
        return NULL;
    }

    coordsNode* headNode = createNewNode(pieceCoords);
    coordsNode* currentNode = headNode;

    switch (piece) {
        int newRow;
        int newCol;
        int otherPiece;
        case whitePawn: case blackPawn:
            // Diagonal (capture) check:
            newRow = row + (1 * turn);
            for (int colInc = -1; colInc <= 1; colInc += 2) {
                newCol = col + colInc;
                if (newCol < 0 || newCol > 7) {
                    continue;
                }
                otherPiece = board.spaces[newRow][newCol];
                if (otherPiece != none && (piece / pieceCutoff != otherPiece / pieceCutoff)) {
                    coords move = {newRow, newCol};
                    currentNode = appendNode(currentNode, move);
                }
                // TODO: Add En Passant logic
            }
            // Forward check:
            otherPiece = board.spaces[newRow][col];
            if (otherPiece == none) {
                coords move = {newRow, col};
                currentNode = appendNode(currentNode, move);
                // Double forward check:
                newRow = row + (2 * turn);
                otherPiece = board.spaces[newRow][col];
                if (otherPiece == none && row == (1 + (5 * (piece / pieceCutoff)))) {
                    coords move = {newRow, col};
                    currentNode = appendNode(currentNode, move);
                }
            }
        break;
        case whiteKnight: case blackKnight:
            for (int i = 0; i < 8; i++) {
                newRow = row + knightMoves[i][0];
                newCol = col + knightMoves[i][1];
                if ((newRow >= 0 && newRow < 8) && (newCol >= 0 && newCol < 8)) {
                    otherPiece = board.spaces[newRow][newCol];
                    if (otherPiece == none || (piece / pieceCutoff != otherPiece / pieceCutoff)) {
                        coords move = {newRow, newCol};
                        currentNode = appendNode(currentNode, move);
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
                    if (otherPiece == none || (piece / pieceCutoff != otherPiece / pieceCutoff)) {
                        coords move = {newRow, newCol};
                        if (piece == whiteKing || piece == blackKing) {
                            // TODO: Add king vulnerability check (recursive call) here
                        }
                        currentNode = appendNode(currentNode, move);
                    }
                    else {
                        break;
                    }
                    if (piece == whiteKing || piece == blackKing) {
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

metaCoordsNode* getAllMoves(chessBoard board) {
    int turn = board.turn;

    metaCoordsNode* headMCNode = createNewMCNode(NULL);
    metaCoordsNode* currentMCNode = headMCNode;

    for (int row = 7; row >= 0; row--) {
        for (int col = 0; col <= 7; col++) {
            int piece = board.spaces[row][col];
            if (piece != none && turn == 1 + ((piece / pieceCutoff) * -2)) {
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

int getScoreManual(chessBoard board) {
    int score = 0;
    for (int row = 7; row >= 0; row--) {
        for (int col = 0; col <= 7; col++) {
            int piece = board.spaces[row][col];
            if (piece != none) {
                score += pieceValues[piece];
            }
        }
    }
    return score;
}

int isLegal(chessBoard board, coordsTuple proposedMove) {
    coords proposedOrigin = proposedMove.origin;
    coords proposedDest = proposedMove.dest;

    coordsNode* legalDest = getMoves(board, proposedOrigin);
    legalDest = legalDest->nextNode; // Skip the identity node
    while (legalDest) {
        if (legalDest->data.row == proposedDest.row && legalDest->data.col == proposedDest.col) {
            return 1;
        }
        legalDest = legalDest->nextNode;
    }
    return 0;
}

chessBoard makeMove(chessBoard board, coordsTuple proposedMove, int verifyFlag) {
    coords proposedOrigin = proposedMove.origin;
    coords proposedDest = proposedMove.dest;

    if (!verifyFlag || (verifyFlag && isLegal(board, proposedMove))) {
        int piece = board.spaces[proposedOrigin.row][proposedOrigin.col];
        int otherPiece = board.spaces[proposedDest.row][proposedDest.col];

        board.spaces[proposedOrigin.row][proposedOrigin.col] = none;
        board.spaces[proposedDest.row][proposedDest.col] = piece;

        board.score = board.score - pieceValues[otherPiece];
        board.turn = board.turn * -1;
    }

    return board;
}

int isFile(char c) {
    if (c > 96 && c < 105) {
        return 1;
    }
    return 0;
}
int isRank(char c) {
    if (c > 48 && c < 57) {
        return 1;
    }
    return 0;
}
int isPieceType(char c) {
    if (c == 66 || c == 75 || c == 78 || c == 81 || c == 82) {
        return 1;
    }
    return 0;
}
int fileToBoardCol(char algCol) {
    return ((int) algCol) - ((int) 'a');
}
int ranksToBoardRow(char algRow) {
    return ((int) algRow) - 49;
}

// TESTING ONLY (UNCHECKED BEHAVIOUR)
coordsTuple simpleNoteToMove(char* simpleNote) {
    coordsTuple proposedMove;
    proposedMove.origin.col = fileToBoardCol(simpleNote[0]);
    proposedMove.origin.row = ranksToBoardRow(simpleNote[1]);
    proposedMove.dest.col = fileToBoardCol(simpleNote[2]);
    proposedMove.dest.row = ranksToBoardRow(simpleNote[3]);
    return proposedMove;
}
// TESTING ONLY (UNCHECKED BEHAVIOUR)

// WORK IN PROGRESS
coordsTuple algNoteToMove(char* algNote) {
    // int pieces[2];
    // int captureFlag = 0;

    // char currentChar = algNote[0];
    // if (isPieceType(currentChar)) {
    //     switch (currentChar) {
    //         case 66:
    //             pieces[0] = whiteBishop;
    //             pieces[1] = blackBishop;
    //         break;
    //         case 75:
    //             pieces[0] = whiteKing;
    //             pieces[1] = blackKing;
    //         break;
    //         case 78:
    //             pieces[0] = whiteKnight;
    //             pieces[1] = blackKnight;
    //         break;
    //         case 81:
    //             pieces[0] = whiteQueen;
    //             pieces[1] = blackQueen;
    //         break;
    //         case 82:
    //             pieces[0] = whiteRook;
    //             pieces[1] = blackRook;
    //         break;
    //         default:
    //         break;
    //     }
    //     currentChar = algNote[1];
    // }
    // else {
    //     pieces[0] = whitePawn;
    //     pieces[1] = blackPawn;
    // }

    // if (currentChar == 'x') {
    //     captureFlag = 1;
    //     currentChar = algNote[2];
    // }
}
// WORK IN PROGRESS