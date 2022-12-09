/*
   __   
  /  \  
  \__/  
 /____\ 
  |  |  
  |__|  
 (====) 
 }===={ 
(______)

This is a header file for data class Pawn.
The implementation is in the same named file ending .cpp  
The documentation of the member functions can be found in the implementation file,
above each function's defintion.
*/

#ifndef PAWN_H
#define PAWN_H

class Pawn : public ChessPiece {
private:
public:
    Pawn();
    bool valid_move(int c1, int r1, int c2,  int r2, ChessPiece* board[BOARD_SIZE][BOARD_SIZE]) override;
};

#endif