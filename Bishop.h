/*
       
    ()    
    /\    
   //\\   
  (    )  
   )__(   
  /____\  
   |  |   
   |  |   
  /____\  
 (======) 
 }======{ 
(________)

This is a header file for data class Bishop.
The implementation is in the same named file ending .cpp
The documentation of the member functions can be found in the implementation file,
above each function's defintion.
*/

#ifndef BISHOP_H
#define BISHOP_H

class Bishop : public ChessPiece {
private:
public:
    Bishop();
    bool valid_move(int c1, int r1, int c2,  int r2, ChessPiece* board[BOARD_SIZE][BOARD_SIZE]) override;
};


#endif