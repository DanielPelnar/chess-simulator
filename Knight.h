/*
       
  (\=,   
 //  .\  
(( \_  \ 
 ))  `\_)
(/     \ 
 | _.-'| 
  )___(  
 (=====) 
 }====={ 
(_______)

This is a header file for data class Knight.
The implementation is in the same named file ending .cpp
The documentation of the member functions can be found in the implementation file,
above each function's defintion.
*/

#ifndef KNIGHT_H
#define KNIGHT_H

class Knight : public ChessPiece {
private:
public:
    Knight();
    bool valid_move(int c1, int r1, int c2,  int r2, ChessPiece* board[BOARD_SIZE][BOARD_SIZE]) override;
};

#endif 
