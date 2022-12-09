/*
This is a header file for data class ChessBoard.
The implementation is in the same named file ending .cpp
The documentation of the member functions can be found in the implementation file,
above each function's defintion.

There are various chess pieces drawings in the header files to make them more beautiful.
Source of the drawings: https://www.asciiart.eu/sports-and-outdoors/chess
Drawn by: Joan G. Stark
*/

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "helper.h"
#include "ChessPiece.h"
#include <string>

class ChessBoard {
private:
    ChessPiece* board[BOARD_SIZE][BOARD_SIZE]; 
    Colour whose_turn_is_it;
    bool already_checked; 
    std::string file_and_rank_to_index(std::string file_and_rank);
    std::string index_to_file_and_rank(std::string double_index);
    std::string colour_to_string(Colour c);
    bool stalemate();
    bool checkmate(int king_position_row,
                   int king_position_col,
                   ChessPiece* board[BOARD_SIZE][BOARD_SIZE],
                   int attacking_row, 
                   int attacking_col);
public:
    ChessBoard();
    ~ChessBoard();
    void free_memory();
    void init_board(); 
    void resetBoard();
    void submitMove(std::string initial_location, std::string end_location);

};

#endif


