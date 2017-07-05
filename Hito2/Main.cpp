#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Greedy.h"

int main() {
	Board board = Board();

	Player playerWHITE = Player(ColorPlayer::PLAYER_WHITE);
	Player playerRED = Player(ColorPlayer::PLAYER_RED);

	Greedy greedy = Greedy();

	while (true)
	{
		board.printBoard();

		auto plays = greedy.moveDraught(board, playerWHITE);

		if (plays.moves.empty()) {
			cout << "Sorry. I can't move any longer" << endl;
			break;
		}
		else {
			while (!plays.moves.empty()) {
				auto play = plays.moves.front();
				plays.moves.pop();
				board.move(playerWHITE, plays.draught, play);
				cin.get();
				cin.get();
			}
			cout << "Kills: " << board.possibleMoves(playerWHITE, MoveStatus::MOVE_ENEMY) << endl;
			cout << "Heuristic 1: " << get<0>(plays.heuristic.variables) << endl;
			cout << "Heuristic 2: " << get<1>(plays.heuristic.variables) << endl;
		}
	}
	cin.get();
	cin.get();
	return 0;
}