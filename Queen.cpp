/*
This is the implementation file for a data class Queen.
Documentation of each function can be found above the function's defintion.
*/

#include "ChessPiece.h"
#include "helper.h"
#include "Queen.h"
#include "Castle.h"
#include "Bishop.h"

/* Assigns name of the chess piece during initialization of Queen object */
Queen::Queen() {
    name = "Queen";
}

/* This a overriden function which checks if it is a valid move for Queen. 
This function allocates and free the memory. It is self-contained.
No ownership transferred.
*/
bool Queen::valid_move(int c1, int r1, int c2,  int r2, ChessPiece* board[BOARD_SIZE][BOARD_SIZE])
{
    /*
    Queen is like Castle or Bishop. (can do both)
    => If the move is either valid in terms of diagonal movement (Bishop)
       OR verizontal/vertical movement (Castle)
       then Queen's movement: valid_move = true.
    */
    
    ChessPiece* tmp_castle = new Castle();
    ChessPiece* tmp_bishop = new Bishop();

    if (tmp_castle->valid_move(c1, r1, c2, r2, board) || tmp_bishop->valid_move(c1, r1, c2, r2, board)) 
    {   
        delete tmp_castle; 
        delete tmp_bishop;
        return true;
    }
    else {
        delete tmp_castle;
        delete tmp_bishop;        
        return false;
    }
}
