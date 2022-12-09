chess: ChessMain.o ChessBoard.o ChessPiece.o Pawn.o Castle.o Knight.o Bishop.o Queen.o King.o
	g++ ChessMain.o ChessBoard.o ChessPiece.o Pawn.o Castle.o Knight.o Bishop.o Queen.o King.o -o chess
ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -g -c ChessMain.cpp
ChessBoard.o: ChessBoard.cpp ChessBoard.h helper.h ChessPiece.h Pawn.h Castle.h Knight.h Bishop.h Queen.h King.h
	g++ -Wall -g -c ChessBoard.cpp
ChessPiece.o: ChessPiece.cpp helper.h ChessPiece.h
	g++ -Wall -g -c ChessPiece.cpp
Pawn.o: Pawn.cpp helper.h ChessPiece.h Pawn.h
	g++ -Wall -g -c Pawn.cpp
Castle.o: Castle.cpp helper.h ChessPiece.h Castle.h
	g++ -Wall -g -c Castle.cpp
Knight.o: Knight.cpp helper.h ChessPiece.h Knight.h
	g++ -Wall -g -c Knight.cpp
Bishop.o: Bishop.cpp helper.h ChessPiece.h Bishop.h
	g++ -Wall -g -c Bishop.cpp
Queen.o: Queen.cpp helper.h ChessPiece.h Queen.h Castle.h Bishop.h
	g++ -Wall -g -c Queen.cpp
King.o: King.cpp helper.h ChessPiece.h King.h
	g++ -Wall -g -c King.cpp

.PHONy: clean
clean:
	rm -f ChessMain.o ChessBoard.o ChessPiece.o Pawn.o Castle.o Knight.o Bishop.o Queen.o King.o chess