/*
This is the implementation file for a data class Pawn.
Documentation of each function can be found above the function's defintion.
*/

#include "ChessPiece.h"
#include "helper.h"
#include "Pawn.h"

/* Assigns name of the chess piece during initialization of Pawn object */
Pawn::Pawn() {
    name = "Pawn";
}

/* This a overriden function which checks if it is a valid move for Pawn. */
bool Pawn::valid_move(int c1, int r1, int c2,  int r2, ChessPiece* board[BOARD_SIZE][BOARD_SIZE])
{
    // double square if initial position (1. row for back and row 6. row for white)
    
    // DOUBLE MOVE for black pawns:
    if ((board[r1][c1]->get_colour() == black) && r1 == 1) { // colour and correct row
        if (r2 == 3 && c1 == c2) { // correct destination row and column
            // Are some pieces in the way:
            for (int i = r1 + 1; i <= r2; i++) { 
                if (board[i][c1] != nullptr) { // horizontal mv -> column fixed
                    return false; // a different piece is in the trajectory
                }
            }
            return true; // valid move: black Pawns double intial move to an empty square 
                         // and no piece in the trajectory.
        }
    }

    // DOUBLE MOVE for white pawns:
    if ((board[r1][c1]->get_colour() == white) && r1 == 6) { // colour and correct row
        if (r2 == 4 && c1 == c2) { // correct destination row and column
            // Are some pieces in the way:
            for (int i = r1 - 1; i >= r2; i--) { 
                if (board[i][c1] != nullptr) { // horizontal mv -> column fixed
                    return false; // a different piece is in the trajectory
                }
            }
            return true; // valid move: white Pawns double intial move to an empty square 
                         // and no piece in the trajectory.
        }
    }

    // Check for Moving one vertically if empty:
    if (board[r1][c1]->get_colour() == black) { // for black pawns
        if (((r1 + 1) == r2) && (c1 == c2) && board[r2][c2] == nullptr) {
            return true;
        }
        else if (((r1 + 1) == r2) && (c1 == c2) && board[r2][c2] != nullptr) {
            return false;
        }
    }
    else { // for white pawns
        if (((r1 - 1) == r2) && (c1 == c2) && board[r2][c2] == nullptr) {
            return true;
        }
        else if (((r1 - 1) == r2) && (c1 == c2) && board[r2][c2] != nullptr) {
            return false;
        }        
    }

    // Checking for Moving one block diagonally if not empty:
    if (board[r1][c1]->get_colour() == black) { // for black pawns
        if (((r1 + 1) == r2) && ((c1 - 1) == c2) && board[r2][c2] != nullptr) { // left check
            return true;
        }
        else if (((r1 + 1) == r2) && ((c1 + 1) == c2) && board[r2][c2] != nullptr) { // right check
            return true;
        }
        else {
            return false;
        }
    }
    else { // for white pawns
        if (((r1 - 1) == r2) && ((c1 - 1) == c2) && board[r2][c2] != nullptr) { // left check
            return true;
        }
        else if (((r1 - 1) == r2) && ((c1 + 1) == c2) && board[r2][c2] != nullptr) { // right check
            return true;
        }
        else {
            return false; 
        }    
    }  

    return false; // the rest cases are invalid moves -> false
}
