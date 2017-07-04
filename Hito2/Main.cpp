#include <iostream>
#include "Board.h"
#include "Player.h"

int main() {
	Board board = Board();
	Player playerWHITE = Player(PlayerColor::PLAYER_WHITE, board);
	Player playerRED = Player(PlayerColor::PLAYER_RED, board);
	
	/*board.printBoard();*/
	cout << "Posiciones de las Fichas Blancas:  "<<endl;
	for (auto draught : playerWHITE.draughts)
		cout << draught.point.x << " " << draught.point.y << endl;
	cout << "Posiciones de las FIchas Rojas:  " << endl;
	for (auto draught : playerRED.draughts)
		cout << draught.point.x << " " << draught.point.y << endl;

	Draught obj;
	int x, y;
	int aux;
	Move mover;
	obj = playerWHITE.getDraught(2, 6);
	board.move(playerWHITE, obj, Move::DIAGONAL_DOWN_LEFT);
	obj = playerWHITE.getDraught(3, 5);
	board.move(playerWHITE, obj, Move::DIAGONAL_DOWN_RIGHT);
	board.printBoard();
	while (true)
	{
		cout << "x:"; cin >> x; cout << "Y:"; cin >> y; cout << "Ezquierda [1], Derecha[2] :"; cin >> aux; cout << endl;
		if (aux == 1)
			mover = Move::DIAGONAL_TOP_LEFT;
		else
			mover = Move::DIAGONAL_TOP_RIGHT;
		obj = playerRED.getDraught(x, y);
		if (board.move(playerRED, obj, mover) != MoveStatus::MOVE_IMPOSSIBLE)
		{
			board.printBoard();
		}
		else
		{
			cout << "jugada incorrecta" << endl;
		}		
	}	
		
	cin.get();
	return 0;	
}