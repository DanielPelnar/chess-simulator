#include "ChessBoard.h"
#include <iostream>
using std::cout;

int main() {

	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";

	ChessBoard cb; // A new chess game is started!
	cout << '\n';

	cb.submitMove("D7", "D6"); // It is not Black’s turn to move!
	cout << '\n';

	cb.submitMove("D4", "H6"); // There is no piece at position D4!
	cout << '\n';

	cb.submitMove("D2", "D4"); // White’s Pawn moves from D2 to D4
	cout << '\n';

	cb.submitMove("F8", "B4"); // Black’s Bishop cannot move to B4!
	cout << '\n';

	cout << "=========================\n";
	cout << "Alekhine vs. Vasic (1931)\n";
	cout << "=========================\n\n";

	cb.resetBoard(); // A new chess game is started!
	cout << '\n';

	cb.submitMove("E2", "E4"); // White’s Pawn moves from E2 to E4
	cb.submitMove("E7", "E6"); // Black’s Pawn moves from E7 to E6
	cout << '\n';

	cb.submitMove("D2", "D4"); // White’s Pawn moves from D2 to D4
	cb.submitMove("D7", "D5"); // Black’s Pawn moves from D7 to D5
	cout << '\n';

	cb.submitMove("B1", "C3"); // White’s Knight moves from B1 to C3
	cb.submitMove("F8", "B4"); // Black’s Bishop moves from F8 to B4   
	cout << '\n';

	cb.submitMove("F1", "D3"); // White’s Bishop moves from F1 to D3
	cb.submitMove("B4", "C3"); // Black’s Bishop moves from B4 to C3 taking White’s Knight
	cout << '\n';              // White is in check 

	cb.submitMove("B2", "C3"); // White’s Pawn moves from B2 to C3 taking Black’s Bishop 
	cb.submitMove("H7", "H6"); // Black’s Pawn moves from H7 to H6
	cout << '\n';

	cb.submitMove("C1", "A3"); // White’s Bishop moves from C1 to A3
	cb.submitMove("B8", "D7"); // Black’s Knight moves from B8 to D7
	cout << '\n';

	cb.submitMove("D1", "E2"); // White’s Queen moves from D1 to E2
	cb.submitMove("D5", "E4"); // Black’s Pawn moves from D5 to E4 taking White’s Pawn
	cout << '\n';

	cb.submitMove("D3", "E4"); // White’s Bishop moves from D3 to E4 taking Black’s Pawn
	cb.submitMove("G8", "F6"); // Black’s Knight moves from G8 to F6
	cout << '\n';

	cb.submitMove("E4", "D3"); // White’s Bishop moves from E4 to D3
	cb.submitMove("B7", "B6"); // Black’s Pawn moves from B7 to B6
	cout << '\n';

	cb.submitMove("E2", "E6"); 
	cb.submitMove("F7", "E6"); 
	cout << '\n';

		// White’s Queen moves from E2 to E6 taking Black’s Pawn
		// Black is in check  
		// Black’s Pawn moves from F7 to E6 taking White’s Queen

	cb.submitMove("D3", "G6"); 
	cout << '\n';              
	
		// White’s Bishop moves from D3 to G6
		// Black is in checkmate

	return 0;
}
