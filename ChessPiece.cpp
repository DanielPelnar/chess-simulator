/*
This is the implementation file for an abstract data class ChessPiece.
Documentation of each function can be found above the function's defintion.
*/

#include <string>
#include "ChessPiece.h"
#include "helper.h"
using namespace std;

/* Sets colour, namely white or black */
void ChessPiece::set_colour(Colour c) {
    colour = c;
}

/* Gets colour to either black or white */
Colour const ChessPiece::get_colour() const {
    return colour;
}

/* Gets name of the chess piece */
std::string const ChessPiece::get_name() const {
    return name;
}

/* It was added to get rid of the warning regarding pure virtual function 
And having non-virtual destructor.  */
ChessPiece::~ChessPiece() {
    ;  
}