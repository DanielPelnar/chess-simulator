/*
This is the implementation file for a data class ChessBoard.
Documentation of each function can be found above the function's defintion.
*/

#include <iostream>
#include <string>
#include "ChessBoard.h"
#include "helper.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "Castle.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
using namespace std;

/* Initialize the board and paint the chess pieces. */
ChessBoard::ChessBoard() {
    init_board(); 
}

/* This destructor calls a function that deallocates memory that has not been freed yet. */
ChessBoard::~ChessBoard() { 
    free_memory();
}

/* Goes through the whole board and deallocates memory from the squares that are not empty. */
void ChessBoard::free_memory() {
    // Deallocates the memory of the remaining pieces on the board:
    for (int row_index = 0; row_index < BOARD_SIZE; row_index++) {
        for (int column_index = 0; column_index < BOARD_SIZE; column_index++) {
            if (board[row_index][column_index] != nullptr) {
                delete board[row_index][column_index];
            }
        }
    }    
}

/* Initializes the board, which includes allocating memory for all pieces and painting them. */
void ChessBoard::init_board() {
    // Initialising a variable that holds the state about who is next to play:
    whose_turn_is_it = white;
    // Initialize a variable that holds info about if a given king is in "check":
    already_checked = false;
    // Printing this msg per instructions:
    cout << "A new chess game is started!" << endl;

    // Putting all chess pieces on the chess board. Note, it's quicker than in real life ;)
    for (int row_index = 0; row_index < BOARD_SIZE; row_index++) {
        for (int column_index = 0; column_index < BOARD_SIZE; column_index++) {
            // 16 Pawns:
            if (row_index == 1 || row_index == 6) {
                board[row_index][column_index] = new Pawn();
            }
            // 32 nullptrs:
            // Those represent the empty squares:
            if (row_index > 1 && row_index < 6) {
                board[row_index][column_index] = nullptr;
            }
            // 4 Castles:
            if ((row_index == 0 || row_index == 7) && (column_index == 0 || column_index == 7)) {
                board[row_index][column_index] = new Castle();
            }
            // 4 Knights:
            if ((row_index == 0 || row_index == 7) && (column_index == 1 || column_index == 6 )) {
                board[row_index][column_index] = new Knight();
            }
            // 4 Bishops:
            if ((row_index == 0 || row_index == 7) && (column_index == 2 || column_index == 5 )) {
                board[row_index][column_index] = new Bishop();
            }
            // 2 Queens:
            if ((row_index == 0 || row_index == 7) && (column_index == 3)) {
                board[row_index][column_index] = new Queen();
            }  
            // 2 Kings:
            if ((row_index == 0 || row_index == 7) && (column_index == 4)) {
                board[row_index][column_index] = new King();
            }           
        }
    }

    // "Colouring" the chess pieces to white and black colour. Before that, they didn't have any colour.
    // This could have been done in previous loop. I decided to sacrify a bit of performance for readability:
    for (int row_index = 0; row_index < BOARD_SIZE; row_index++) {
        for (int column_index = 0; column_index < BOARD_SIZE; column_index++) {
            // Black's chess pieces:
            if (row_index == 0 || row_index == 1) {
                board[row_index][column_index]->set_colour(black);
            }
            // White's chess pieces:
            if (row_index == 6 || row_index == 7) {
                board[row_index][column_index]->set_colour(white);
            }
        }
    }   
}

/* A new game? First free the old board and then itialize a new one from the beginning. */
void ChessBoard::resetBoard() {
    free_memory(); // old board needs to be cleaned up.
    init_board(); // Initialize the board like it was at the beginning.
}

/* Submits a move. Inputs are source and destination locations as string (file and rank) */
void ChessBoard::submitMove(std::string initial_location, std::string end_location) {
    /*
    In order to make it more readable, I had to shorten my varibale names to:
    initial_column_position is c1
    end_column_position is c2
    initial_row_position is r1
    end_row_position is r2
    */    
    string initial_index = file_and_rank_to_index(initial_location); 
    int c1 = (initial_index[0] - '0'); 
    int r1 = (initial_index[1] - '0');
    /*
    Summary with example: 
        initial_location = "C5"
        initial_index = "23"
        c1 = 2
        r1 = 3
    */
    string end_index = file_and_rank_to_index(end_location); 
    int c2 = (end_index[0] - '0'); 
    int r2 = (end_index[1] - '0');
    /*
    Summary with example: 
        end_location = "A7"
        end_index = "01"
        c2 = 0
        r2 = 1
    */

    // if guard: illegal move - "no chess piece at the initial location"
    if (board[r1][c1] == nullptr) {
        cout << "There is no piece at position " << initial_location << "!"
             << endl;
        return;
    }

    // If guard: illegal move - "not a player's turn":
    if (whose_turn_is_it != board[r1][c1]->get_colour()) {
        if (board[r1][c1]->get_colour() == white) {
            cout << "It is not White's turn to move!"
                 << endl;
            return;
        }
        else {
            cout << "It is not Black's turn to move!"
                 << endl;
            return;
        }
    }

    // If guard: illegal move - "trying to take your own piece":
        // Please note that I used 2 nested IFs 
        // because the second condition can get seg fault if all in one line as && && &&.
    if (board[r1][c1]->valid_move(c1, r1, c2, r2, board)) { // It is valid move. But ...
        if (board[r2][c2] != nullptr) { // piece is present 
            if ((board[r2][c2]->get_colour() == whose_turn_is_it)) { // and it is the same player's piece.
                cout << colour_to_string(board[r1][c1]->get_colour())
                    << "'s " << board[r1][c1]->get_name()
                    << " cannot move to "
                    << end_location 
                    << "!"
                    << "The reason: a player cannot take its own piece."
                    << endl;                
                return;
            }
        }
    }   

    // Stores king's position of a player whose is about to make a move:
    int tmp_king_position[2]; 

    // Check for Stalemate:
    bool is_stalemate = stalemate();
    if (is_stalemate == true) {
        cout << "This is Stalemate!"
             << endl;
        return;
    }

    // FOR ALL CHESS PIECES:
    if (board[r1][c1]->valid_move(c1, r1, c2, r2, board)) {
        // For destination square being empty:
        if (board[r2][c2] == nullptr) {  
            // Move the piece to the destination square:
            board[r2][c2] = board[r1][c1];
            // Let source square be empty:
            board[r1][c1] = nullptr;
            // Print msg:
            // e.g X's Y moves from Z to W
            cout << colour_to_string(board[r2][c2]->get_colour()) // !
                 << "'s " << board[r2][c2]->get_name() // !
                 << " moves from "
                 << initial_location
                 << " to "
                 << end_location
                 << endl;
        } 
        // For destination square containing a piece:
        else {  
            // Check if it is opponent's piece:
            if (board[r2][c2]->get_colour() != whose_turn_is_it) {
                // Print msg:
                // eg. X's Y moves from Z to W taking X^'s G
                cout << colour_to_string(board[r1][c1]->get_colour())
                    << "'s " << board[r1][c1]->get_name()
                    << " moves from "
                    << initial_location
                    << " to "
                    << end_location
                    << " taking "
                    << colour_to_string(board[r2][c2]->get_colour())
                    << "'s " << board[r2][c2]->get_name()
                    << endl;               
                // The piece at destination square is ready to be taken.
                // Free its memory:
                delete board[r2][c2];
                // Move your piece to the new location:
                board[r2][c2] = board[r1][c1];
                // empty old square:
                board[r1][c1] = nullptr;
            }
        }
        // After successful move, swap colours - The other player's turn:
        if (whose_turn_is_it == white) {
            whose_turn_is_it = black;
        }
        else {
            whose_turn_is_it = white;   
        }
        // Find Current's player king's position (The player who is about to make a move):
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] != nullptr) {
                    if ((board[i][j]->get_name() == "King") && (board[i][j]->get_colour() == whose_turn_is_it)) { 
                        tmp_king_position[0] = i;
                        tmp_king_position[1] = j;
                    }
                }
            }
        }
        // Check if the player who've just made his move put the current player's king in check:
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] != nullptr) { // only iterating over chess pieces
                    if ((board[i][j]->valid_move(j, i, tmp_king_position[1], tmp_king_position[0], board)) 
                    && (board[i][j]->get_colour() != whose_turn_is_it)) 
                    {
                        // Is it checkmate:
                        if (checkmate(tmp_king_position[0], tmp_king_position[1], board, i, j)) {
                            cout << colour_to_string(whose_turn_is_it)
                                << " is in checkmate" 
                                << endl;
                            return;  
                        }    

                        // Not checkmate? then print check:
                        cout << colour_to_string(whose_turn_is_it)
                            << " is in check" 
                            << endl;

                        already_checked = true; 

                        // Once I get ONE check, I need to break both inner and outer loop:
                        // I didn't want to use Go-To statement, instead, I am using this:
                        // There 64 squares on the board, hence this constant is succifiently 
                        // large to get me out of outer loop:
                        i = j = N; 
                        break;                                                
                        // return; // Break for both loops needs to be here.
                                // you might get this iteration more than once
                                // if more than
                                // one piece is "checking" the king at one time.
                                /*
                                This does not happen that often, but it is possible.
                                For example, a bishop lines up on the 
                                same diagonal as the king with 
                                a castle or knight in the way blocking the check. 
                                The rook or knight moves giving check to the king 
                                and also uncovering the check from the bishop.    
                                */
                    }
                }
            }
        }
    }
    else {
        // Print msg:
        // e.g X's Y cannot move to Z!
        cout << colour_to_string(board[r1][c1]->get_colour())
            << "'s " << board[r1][c1]->get_name()
            << " cannot move to "
            << end_location 
            << "!"
            << endl;
        return;
    }
}

/*
A helper function that does the following.
Input: string like "D7" or "A8" which represents "file" and "rank" on the board.
Returns: string like "31" or "00" which represents column index and row index on the board.
The following diagram illustrates this:
BEFORE:
 	   A B C D E F G H
	8 |_|#|_|#|_|#|_|#|
	7 |#|_|#|_|#|_|#|_|
	6 |_|#|_|#|_|#|_|#|
	5 |#|_|#|_|#|_|#|_|
	4 |_|#|_|#|_|#|_|#|
	3 |#|_|#|_|#|_|#|_|
	2 |_|#|_|#|_|#|_|#|
	1 |#|_|#|_|#|_|#|_|

AFTER:
 	   0 1 2 3 4 5 6 7
	0 |_|#|_|#|_|#|_|#|
	1 |#|_|#|_|#|_|#|_|
	2 |_|#|_|#|_|#|_|#|
	3 |#|_|#|_|#|_|#|_|
	4 |_|#|_|#|_|#|_|#|
	5 |#|_|#|_|#|_|#|_|
	6 |_|#|_|#|_|#|_|#|
	7 |#|_|#|_|#|_|#|_|     
*/
std::string ChessBoard::file_and_rank_to_index(std::string file_and_rank) {
    // A -> 65 ASCII, B -> 66 ASCII, etc.
    // 0 -> 48 ASCII, 1 -> 49 ASCII, etc.
    // 65 - 48 = 17
    // => if I want to convert A to 0, I shifted by 17
    // => if I want to convert B to 1, I shifted by 17
    // etc.
    // LETTER_TO_DIGIT_SHIFTER is 17
    // If I want to convert 8 to 0, I can do 8 - 8 = 0
    // If I want to convert 7 to 1, I can do 8 - 7 = 1
    // Pattern: BOARD_SIZE - x = y; where BOARD_SIZE is constant.
    const int LETTER_TO_DIGIT_SHIFTER = 17;
    const int DIGIT_SHIFTER = 48;

    string result = "";
    result += static_cast<char>(file_and_rank[0] - LETTER_TO_DIGIT_SHIFTER);
    result += to_string(((DIGIT_SHIFTER + BOARD_SIZE) - static_cast<int>(file_and_rank[1])));
    return result;
}

/*
A helper function which is the exact opposite of file_and_rank_to_index.
Input: string like "31" or "00" which represents column index and row index on the board.
Returns: string like "D7" or "A8" which represents "file" and "rank" on the board.
The following diagram illustrates this:
BEFORE:
 	   0 1 2 3 4 5 6 7
	0 |_|#|_|#|_|#|_|#|
	1 |#|_|#|_|#|_|#|_|
	2 |_|#|_|#|_|#|_|#|
	3 |#|_|#|_|#|_|#|_|
	4 |_|#|_|#|_|#|_|#|
	5 |#|_|#|_|#|_|#|_|
	6 |_|#|_|#|_|#|_|#|
	7 |#|_|#|_|#|_|#|_|  

AFTER:
 	   A B C D E F G H
	8 |_|#|_|#|_|#|_|#|
	7 |#|_|#|_|#|_|#|_|
	6 |_|#|_|#|_|#|_|#|
	5 |#|_|#|_|#|_|#|_|
	4 |_|#|_|#|_|#|_|#|
	3 |#|_|#|_|#|_|#|_|
	2 |_|#|_|#|_|#|_|#|
	1 |#|_|#|_|#|_|#|_|   
*/
std::string ChessBoard::index_to_file_and_rank(std::string double_index) {
    const int LETTER_TO_DIGIT_SHIFTER = 17;
    const int DIGIT_SHIFTER = 48;    
    string result = "";

    result += static_cast<char>(double_index[0] + LETTER_TO_DIGIT_SHIFTER);
    result += to_string(((DIGIT_SHIFTER + BOARD_SIZE) - static_cast<int>(double_index[1])));
    return result;
}

/* If 0, then "White.". If 1, then "Black" */
std::string ChessBoard::colour_to_string(Colour c) {
    if (c == white) {
        return "White";
    }
    else { // black
        return "Black";
    }
}

/* Helper function that returns true if stalemate and false otherwise. */
bool ChessBoard::stalemate() {
    int count_possible_moves = 0;
    bool is_stalemate;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            for (int l = 0; l < BOARD_SIZE; l++) {
                for (int k = 0; k < BOARD_SIZE; k++) {
                    if ((board[i][j] != nullptr)
                        && ((i != l) && (j != k)) 
                        && (board[i][j]->valid_move(j, i, k, l, board))) {
                            count_possible_moves ++;
                    }
                }
            }
        }
    }
    if (count_possible_moves == 0) {
        is_stalemate = true;
    }
    else {
        is_stalemate = false;
    }
    return is_stalemate;
}

/* A helper function that returns true of checkmate and false otherwise. 
Three checkmate conditions are checked:
    1] Capturing the attacking piece
    2] Moving the king where it is not under attack
    3] Interposing (blocking) the attacking piece (can't be attacking knight)
*/
bool ChessBoard::checkmate(int king_position_row,
                           int king_position_col,
                           ChessPiece* board[BOARD_SIZE][BOARD_SIZE],
                           int attacking_row, 
                           int attacking_col) {
    // 1] Capturing the attacking piece:
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != nullptr) { // only iterating over chess pieces
                if ((board[i][j]->valid_move(j, i, attacking_col, attacking_row, board)) 
                && (board[i][j]->get_colour() == whose_turn_is_it)) {
                    return false;
                }

            } 

        }
    }  

    // 2] Moving the king where it is not under attack:
    int new_tmp_j;
    int new_tmp_i;
    int safe_counter;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[king_position_row][king_position_col]->valid_move(king_position_col, 
                                                                        king_position_row,
                                                                        j, i, 
                                                                        board)
                                                            && (board[i][j] == nullptr)) {
                new_tmp_j = j;
                new_tmp_i = i;
                safe_counter = 0;
                // Iterating over oppotents pieces to see if they can check the king in the new pos:
                for (int l = 0; l < BOARD_SIZE; l++) {
                    for (int k = 0; k < BOARD_SIZE; k++) {
                        if (board[l][k] != nullptr) { // only iterating over chess pieces
                            if ((board[l][k]->valid_move(k, l, new_tmp_j, new_tmp_i, board)) 
                                && (board[l][k]->get_colour() != whose_turn_is_it)) {
                                    safe_counter ++; 
                            }
                        }
                    }
                }
                if (safe_counter == 0) {
                    return false; // king has managed to get to a safe position 
                }
            }
        }
    }

    // 3] Interposing (blocking) the attacking piece (can't be attacking knight):
    int row_block;
    int col_block;
    // Pieces that can potentially block:
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // Where those pieces can go:
            for (int l = 0; l < BOARD_SIZE; l++) {
                for (int k = 0; k < BOARD_SIZE; k++) {
                    if (board[i][j] != nullptr) { // only iterating over chess pieces
                        if ((board[i][j]->valid_move(j, i, k, l, board)) 
                        && (board[i][j]->get_colour() == whose_turn_is_it) 
                        && (board[i][j]->get_name() != "King")
                        && (board[l][k] != nullptr && board[l][k]->get_name() != "King")
                        && ((i != l) && (j != k))) { 
                            // Check if moving to that location 
                            // blocks the trajectory of the attacking piece.
                            // It is implemented by:
                            // if the attacking piece has now valid move
                            // to take the blocking piece as a sacrifice:
                            row_block = l;
                            col_block = k;
                            if ((board[attacking_row][attacking_col]->valid_move(attacking_col, attacking_row, 
                                                                                 col_block, row_block, board)) 
                                && (board[attacking_row][attacking_col]->get_colour() != whose_turn_is_it)
                                && (board[attacking_row][attacking_col]->get_name() != "Knight")) {
                                    // A piece would be sacrifised but was it in the correct trajectory:
                                    if ( (abs(king_position_row - row_block) < 
                                          abs(king_position_row - attacking_row)
                                          &&
                                          abs(king_position_col - col_block) < 
                                          abs(king_position_col - attacking_col) 
                                         )
                                        ) {
                                        return false; // correct piece was sacrified for the King!
                                    }
                            }
                        }
                    } 
                }
            }
        }
    }  

    return true;  // If neither of the 3 conditions returned false, then it is checkmate.   
}

