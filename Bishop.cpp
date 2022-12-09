/*
This is the implementation file for a data class Bishop.
Documentation of each function can be found above the function's defintion.
*/

#include "ChessPiece.h"
#include "helper.h"
#include "Bishop.h"

/* Assigns name of the chess piece during initialization of Bishop object */
Bishop::Bishop() {
    name = "Bishop";
}

/* This a overriden function which checks if it is a valid move for Bishop. */
bool Bishop::valid_move(int c1, int r1, int c2,  int r2, ChessPiece* board[BOARD_SIZE][BOARD_SIZE])
{
    // Check if same diagonal:
    int col_change = abs(c1 - c2);
    int row_change = abs(r1 - r2);
    // Same diagonal iff the change in column is equal to the change in row:
    bool same_diagonal = (col_change == row_change); 

    // If it is a valid_move, the destination square can be in 4 different diagonal directions
    // from the source. That is either left_up, left_down, right_up, right_down.
    // Once we know, we can "loop over diagonally" by substracting and adding rows and columns
    // appropriately.
    // When checking for no piece in the trajectory. The loops can be done both ways.
    // Why? Because we are just checking collision along the trajectory, excluding
    // the first item (can be the piece itself) and the last item (the opponents piece), 
    // or vice versa. Other functions are dealing with the rest. 

    bool left_up = false;
    bool left_down = false;
    bool right_up = false;
    bool right_down = false;

    // Which direction:
    if ((r2 < r1) && (c2 < c1)) {
        left_up = true;
    }
    else if ((r2 > r1) && (c2 < c1)) {
        left_down = true;
    }
    else if ((r2 < r1) && (c2 > c1)) {
        right_up = true;
    }
    else if ((r2 > r1) && (c2 > c1)) {
        right_down = true;
    }

    // Each 4 cases in turn:

    // Towards right_down:
    int count_rows1 = 0;
    if (right_down) {
        for (int i = r1 + 1; i < r2; i++) {
            count_rows1 ++;
            for (int j = c1 + count_rows1; j < c2; j++) {
                if (board[i][j] != nullptr) {
                    return false; // there is a piece in the trajectory
                }
                break;
            }
        }
    }

    // Towards left_up:
    int count_rows2 = 0;
    if (left_up) {
        for (int i = r2 + 1; i < r1; i++) {
            count_rows2++;
            for (int j = c2 + count_rows2; j < c1; j++) {
                if (board[i][j] != nullptr) {
                    return false; // there is a piece in the trajectory
                }
                break;
            }
        }
    }

    // Towards right_up:
    int count_rows3 = 0;
    if (right_up) {
        for (int i = r1 - 1; i > r2; i--) {
            count_rows3 ++;
            for (int j = c1 + count_rows3; j < c2; j++) {
                if (board[i][j] != nullptr) {
                    return false; // there is a piece in the trajectory
                }
                break;
            }
        }
    }

    // Towards left_down:
    int count_rows4 = 0;
    if (left_down) {
        for (int i = r2 - 1; i > r1; i--) {
            count_rows4 ++;
            for (int j = c2 + count_rows4; j < c1; j++) { 
                if (board[i][j] != nullptr) {
                    return false; // there is a piece in the trajectory
                }
                break;
            }
        }
    }

    return same_diagonal;  // if false hasn't been returned by now, then true if diagonal.

}
