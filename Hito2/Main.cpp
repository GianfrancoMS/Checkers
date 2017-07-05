#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Greedy.h"

int main() {
	Board board = Board();

	Player playerWHITE = Player(ColorPlayer::PLAYER_WHITE);
	Player playerRED = Player(ColorPlayer::PLAYER_RED);

	Draught draught;

	draught = board.getDraught(playerWHITE.color, 2, 6);
	board.move(playerWHITE, draught, Move::DIAGONAL_DOWN_LEFT);

	draught = board.getDraught(playerWHITE.color, 3, 5);
	board.move(playerWHITE, draught, Move::DIAGONAL_DOWN_RIGHT);

	Greedy greedy = Greedy();

	while (true)
	{
		board.printBoard();

		auto plays = greedy.moveDraught(board, playerRED);

		if (plays.moves.empty()) {
			cout << "Sorry. I can't move any longer" << endl;
			break;
		}
		else {
			cin.get();
			cout << "Kills: " << board.possibleMoves(playerRED, MoveStatus::MOVE_ENEMY) << endl;
			cout << "Heuristic 1: " << plays.heuristic.variable << endl;
			while (!plays.moves.empty()) {
				auto play = plays.moves.front();
				plays.moves.pop();
				board.move(playerRED, plays.draught, play);
				cin.get();
			}
		}
	}

	cin.get();
	cin.get();
	return 0;
}