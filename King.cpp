/*
This is the implementation file for a data class King.
Documentation of each function can be found above the function's defintion.
*/

#include "ChessPiece.h"
#include "helper.h"
#include "King.h"

/* Assigns name of the chess piece during initialization of King object */
King::King() {
    name = "King";
}

/* This a overriden function which checks if it is a valid move for King. */
bool King::valid_move(int c1, int r1, int c2,  int r2, ChessPiece* board[BOARD_SIZE][BOARD_SIZE])
{
    /*
    Kings moves 1 square in any of the possible 8 directions, unless on the edge of the board.
    Here valid_move is defined as:
        1 square moved in either direction
    This function does not deal with valid_moves in terms of possible checks or checksmates.
    Other functions deal with collisions.
    */
    
    // King's code:
    if ((r1 == r2) && ((c1 - 1) == c2)) {
        return true;
    }
    else if ((r1 == r2) && ((c1 + 1) == c2)) {
        return true;
    }
    else if (((r1 - 1) == r2) && (c1 == c2)) {
        return true;
    }
    else if (((r1 + 1) == r2) && (c1 == c2)) {
        return true;
    }
    else if (((r1 - 1) == r2) && ((c1 - 1) == c2)) {
        return true;
    }
    else if (((r1 - 1) == r2) && ((c1 + 1) == c2)) {
        return true;
    }
    else if (((r1 + 1) == r2) && ((c1 - 1) == c2)) {
        return true;
    }
    else if (((r1 + 1) == r2) && ((c1 + 1) == c2)) {
        return true;
    } 
       
    return false; // else false;
}