/*

    _:_
   '-.-'
  __.'.__
 |_______|
  \=====/
   )___(
  /_____\
   |   |
   |   |
   |   |
   |   |
   |   |
  /_____\
 (=======)
 }======={
(_________)

This is a header file for data class King.
The implementation is in the same named file ending .cpp
The documentation of the member functions can be found in the implementation file,
above each function's defintion.
*/

#ifndef KING_H
#define KING_H

class King : public ChessPiece {
private:
public:
    King();
    bool valid_move(int c1, int r1, int c2,  int r2, ChessPiece* board[BOARD_SIZE][BOARD_SIZE]) override;
};

#endif
