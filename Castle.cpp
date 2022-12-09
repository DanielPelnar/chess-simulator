/*
This is the implementation file for a data class Castle.
Documentation of each function can be found above the function's defintion.
*/

#include "ChessPiece.h"
#include "helper.h"
#include "Castle.h"

/* Assigns name of the chess piece during initialization of Castle object */
Castle::Castle() {
    name = "Castle";
}

/* This a overriden function which checks if it is a valid move for Castle. */
bool Castle::valid_move(int c1, int r1, int c2,  int r2, ChessPiece* board[BOARD_SIZE][BOARD_SIZE])
{
    // Check if on the same column or row:
    if (c1 == c2 || r1 == r2) {
        // Same column case (fix column):
        if (c1 == c2) {
            // Depending on which larger:
            if (r1 < r2) {
                for (int i = r1 + 1; i < r2; i++) {
                    if (board[i][c1] != nullptr) {
                        return false; // Some piece is in the trajectory
                    }
                }
            }
            else if (r1 > r2) {
                for (int i = r2 + 1; i < r1; i++) {
                    if (board[i][c1] != nullptr) { 
                        return false;
                    }
                }
            }
        }
        // Same row case (fix row):
        else if (r1 == r2) { 
            // Depending on which larger:
            if (c1 < c2) {
              for (int i = c1 + 1; i < c2; i++) {
                  if (board[r1][i] != nullptr) {
                      return false; // Some piece in the trajectory
                  }
              } 
            }
            else if (c1 > c2) {
                for (int i = c2 + 1; i < c1; i++) {
                    if (board[r1][i] != nullptr) {
                        return false;
                    }
                }
            }
        }
    }
    else { 
        return false; // if not on the same column or row => not valid move.
    }

    // The destionation square is on the same row or column and no pieces in trajectory => valid move:
    return true; 
}
