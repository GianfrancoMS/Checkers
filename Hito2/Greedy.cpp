#include "Greedy.h"
#include "Board.h"
#include "Player.h"
#include <vector>
#include <algorithm>
#include <functional>

Play Greedy::moveDraught(Board board, Player player)
{
	vector<Play>plays;
	recursiveMoveDraught(board, player, plays);
	Play bestPlay = *max_element(plays.begin(), plays.end(),greater<>());
	return bestPlay;
}

void Greedy::recursiveMoveDraught(Board board, Player player, vector<Play>&plays)
{
	auto draughts = board.possibleMoves(player);
	auto color = player.color;
	if (color == ColorPlayer::PLAYER_RED) {
		for (auto draught : draughts) {
			if (board.move(player, draught, Move::DIAGONAL_TOP_LEFT) == MoveStatus::MOVE_BLANK ){
				Play play;
				play.draught = draught;
				play.moves.push(Move::DIAGONAL_TOP_LEFT);
				play.heuristic.variables = make_tuple(0, board.possibleMoves(player,MoveStatus::MOVE_ENEMY));
				plays.push_back(play);
			}
			if (board.move(player, draught, Move::DIAGONAL_TOP_RIGHT) == MoveStatus::MOVE_ENEMY) {
				Play play;
				play.draught = draught;
				play.moves.push(Move::DIAGONAL_TOP_RIGHT);
				play.heuristic.variables = make_tuple(1, board.possibleMoves(player, MoveStatus::MOVE_ENEMY));
				recursiveMoveDraught(board, player, draught, play);
				plays.push_back(play);
			}
		}
	}
	else {
		for (auto draught : draughts) {
			if (board.move(player, draught, Move::DIAGONAL_DOWN_LEFT) == MoveStatus::MOVE_BLANK) {
				Play play;
				play.draught = draught;
				play.moves.push(Move::DIAGONAL_DOWN_LEFT);
				play.heuristic.variables = make_tuple(0, board.possibleMoves(player, MoveStatus::MOVE_ENEMY));
				plays.push_back(play);
			}
			if (board.move(player, draught, Move::DIAGONAL_DOWN_RIGHT) == MoveStatus::MOVE_ENEMY) {
				Play play;
				play.draught = draught;
				play.moves.push(Move::DIAGONAL_DOWN_RIGHT);
				play.heuristic.variables = make_tuple(1, board.possibleMoves(player, MoveStatus::MOVE_ENEMY));
				recursiveMoveDraught(board, player, draught, play);
				plays.push_back(play);
			}
		}
	}
}

void Greedy::recursiveMoveDraught(Board board, Player player, Draught draught, Play&play)
{
	auto color = player.color;
	if (color == ColorPlayer::PLAYER_RED) {
		if (board.move(player, draught, Move::DIAGONAL_TOP_RIGHT) == MoveStatus::MOVE_ENEMY) {
			play.moves.push(Move::DIAGONAL_TOP_RIGHT);
			get<0>(play.heuristic.variables) = get<0>(play.heuristic.variables) + 1;
			get<1>(play.heuristic.variables) = board.possibleMoves(player, MoveStatus::MOVE_ENEMY);
			recursiveMoveDraught(board, player, draught, play);
		}
	}
	else {
		if (board.move(player, draught, Move::DIAGONAL_DOWN_RIGHT) == MoveStatus::MOVE_ENEMY) {
			play.moves.push(Move::DIAGONAL_DOWN_RIGHT);
			get<0>(play.heuristic.variables) = get<0>(play.heuristic.variables) + 1;
			get<1>(play.heuristic.variables) = board.possibleMoves(player, MoveStatus::MOVE_ENEMY);
			recursiveMoveDraught(board, player, draught, play);
		}
	}
}
