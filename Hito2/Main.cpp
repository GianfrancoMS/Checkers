#include <iostream>
#include "Board.h"
#include "Player.h"

int main() {
	Board board = Board();

	Player playerWHITE = Player(PlayerColor::PLAYER_WHITE);
	Player playerRED = Player(PlayerColor::PLAYER_RED);

	Draught draught;
	int x = 0; 
	int y = 0;
	int aux = 0;
	Move move;

	draught = board.getDraught(playerWHITE.color, 2 ,6);
	board.move(playerWHITE, draught, Move::DIAGONAL_DOWN_LEFT);

	draught = board.getDraught(playerWHITE.color, 3, 5);
	board.move(playerWHITE, draught, Move::DIAGONAL_DOWN_RIGHT);

	board.printBoard();

	while (true)
	{
		auto possiblePlaysWhite = board.possibleMoves(playerWHITE);
		auto possiblePlaysRed = board.possibleMoves(playerRED);

		cout << "White moves: " << endl;
		for (auto draught : possiblePlaysWhite)
			cout << draught.point.x << " " << draught.point.y << endl;

		cout << "Red moves: " << endl;
		for (auto draught : possiblePlaysRed)
			cout << draught.point.x << " " << draught.point.y << endl;

		cout << "X:"; 
		cin >> x; 
		cout << "Y:"; 
		cin >> y; 
		cout << "Izquierda [1], Derecha[2] :"; 
		cin >> aux; 
		cout << endl;
		if (aux == 1)
			move = Move::DIAGONAL_TOP_LEFT;
		else
			move = Move::DIAGONAL_TOP_RIGHT;
		draught = board.getDraught(playerRED.color,x,y);
		if (board.move(playerRED, draught, move) != MoveStatus::MOVE_IMPOSSIBLE)
		{
			board.printBoard();
			cout << "White draughts: " << endl;
			for (auto draught : board.whiteDraughts)
				cout << draught.point.x << " " << draught.point.y << endl;
		}
		else
			cout << "jugada incorrecta" << endl;
	}

	cin.get();
	return 0;
}