/*
This is the implementation file for a data class Castle.
Documentation of each function can be found above the function's defintion.
*/

#include "ChessPiece.h"
#include "helper.h"
#include "Knight.h"

/* Assigns name of the chess piece during initialization of Knight object */
Knight::Knight() {
    name = "Knight";
}

/* This a overriden function which checks if it is a valid move for Knight. */
bool Knight::valid_move(int c1, int r1, int c2,  int r2, ChessPiece* board[BOARD_SIZE][BOARD_SIZE])
{
    /*
    Knights jump -> no blockage.
    There are only up to only 8 possible legal moves.
    It can be less, if the knight is around the edge.
    */
    if (((r1 + 2) == r2) && ((c1 + 1) == c2)) {
        return true;
    }
    else if (((r1 + 2) == r2) && ((c1 - 1) == c2)) {
        return true;
    }
    else if (((r1 + 1) == r2) && ((c1 - 2) == c2)) {
        return true;
    }
    else if (((r1 - 1) == r2) && ((c1 - 2) == c2)) {
        return true;
    }
    else if (((r1 - 2) == r2) && ((c1 - 1) == c2)) {
        return true;
    }
    else if (((r1 - 2) == r2) && ((c1 + 1) == c2)) {
        return true;
    }
    else if (((r1 - 1) == r2) && ((c1 + 2) == c2)) {
        return true;
    }
    else if (((r1 + 1) == r2) && ((c1 + 2) == c2)) {
        return true;
    }
    // The good things about this is that, we don't have to worry about out of index.
    // This is bounded by the destination. 
    // If neither of the 8 case conditions are true, then invalid move:
    return false;
}
