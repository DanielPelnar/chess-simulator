/*
       
    ????   
  ?|????|? 
  |      | 
   |????|  
    ?||?  
    |  |   
    |??|   
   |    |  
  ???????? 
 ??????????
 |????????|

This is an abstract data class and hence the question mark ASCII used to 
draw this picture. Who knows what piece this chess piece is.

This is a header file for abstract data class ChessPiece.
The implementation is in the same named file ending .cpp
The documentation of the member functions can be found in the implementation file,
above each function's defintion.
*/

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "helper.h"
#include <string>

class ChessPiece {
protected:
    Colour colour;
    std::string name;
public:
    virtual ~ChessPiece(); 
    void set_colour(Colour c);
    Colour const get_colour() const;
    std::string const get_name() const;
    virtual bool valid_move(int c1, int r1, 
                            int c2,  int r2, 
                            ChessPiece* board[BOARD_SIZE][BOARD_SIZE]) = 0; 
};

#endif