/*

 |'-'-'| 
 |_____| 
  |===|  
  |   |  
  |   |  
  )___(  
 (=====) 
 }====={ 
(_______)

This is a header file for data class Castle.
The implementation is in the same named file ending .cpp
The documentation of the member functions can be found in the implementation file,
above each function's defintion.
*/

#ifndef CASTLE_H
#define CASTLE_H

class Castle : public ChessPiece {
private:
public:
    Castle();
    bool valid_move(int c1, int r1, int c2,  int r2, ChessPiece* board[BOARD_SIZE][BOARD_SIZE]) override;
};

#endif