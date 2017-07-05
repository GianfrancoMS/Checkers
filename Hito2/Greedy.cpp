#include "Greedy.h"
#include "Board.h"
#include <vector>
#include <functional>

Play Greedy::moveDraught(Board board, const Player& player)
{
	vector<Play>plays;
	recursiveMoveDraught(board, player, plays);
	return plays.empty() ? Play() : *max_element(plays.begin(), plays.end(), less<>());
}

void Greedy::recursiveMoveDraught(Board board, const Player& player, vector<Play>&plays)
{
	auto draughts = board.possibleMoves(player);
	auto color = player.color;
	if (color == ColorPlayer::PLAYER_RED) {
		for (auto draught : draughts) {
			auto tempBoard = board;
			if (tempBoard.move(player, draught, Move::DIAGONAL_TOP_LEFT) == MoveStatus::MOVE_BLANK ){
				Play play;
				play.draught = draught;
				play.moves.push(Move::DIAGONAL_TOP_LEFT);
				play.heuristic.variable = 0;
				plays.push_back(play);
			}
			tempBoard = board;
			if (tempBoard.move(player, draught, Move::DIAGONAL_TOP_LEFT) == MoveStatus::MOVE_ENEMY) {
				Play play;
				play.draught = draught;
				play.moves.push(Move::DIAGONAL_TOP_LEFT);
				play.heuristic.variable = 1;
				recursiveMoveDraught(tempBoard, player, draught, play);
				plays.push_back(play);
			}
			tempBoard = board;
			if (tempBoard.move(player, draught, Move::DIAGONAL_TOP_RIGHT) == MoveStatus::MOVE_BLANK) {
				Play play;
				play.draught = draught;
				play.moves.push(Move::DIAGONAL_TOP_RIGHT);
				play.heuristic.variable = 0;
				plays.push_back(play);
			}
			tempBoard = board;
			if (tempBoard.move(player, draught, Move::DIAGONAL_TOP_RIGHT) == MoveStatus::MOVE_ENEMY) {
				Play play;
				play.draught = draught;
				play.moves.push(Move::DIAGONAL_TOP_RIGHT);
				play.heuristic.variable = 1;
				recursiveMoveDraught(tempBoard, player, draught, play);
				plays.push_back(play);
			}
		}
	}
	else {
		for (auto draught : draughts) {
			auto tempBoard = board;
			if (tempBoard.move(player, draught, Move::DIAGONAL_DOWN_LEFT) == MoveStatus::MOVE_BLANK) {
				Play play;
				play.draught = draught;
				play.moves.push(Move::DIAGONAL_DOWN_LEFT);
				play.heuristic.variable = 0;
				plays.push_back(play);
			}
			tempBoard = board;
			if (tempBoard.move(player, draught, Move::DIAGONAL_DOWN_LEFT) == MoveStatus::MOVE_ENEMY) {
				Play play;
				play.draught = draught;
				play.moves.push(Move::DIAGONAL_DOWN_LEFT);
				play.heuristic.variable = 1;
				recursiveMoveDraught(tempBoard, player, draught, play);
				plays.push_back(play);
			}
			tempBoard = board;
			if (tempBoard.move(player, draught, Move::DIAGONAL_DOWN_RIGHT) == MoveStatus::MOVE_BLANK) {
				Play play;
				play.draught = draught;
				play.moves.push(Move::DIAGONAL_DOWN_RIGHT);
				play.heuristic.variable = 0;
				plays.push_back(play);
			}
			tempBoard = board;
			if (tempBoard.move(player, draught, Move::DIAGONAL_DOWN_RIGHT) == MoveStatus::MOVE_ENEMY) {
				Play play;
				play.draught = draught;
				play.moves.push(Move::DIAGONAL_DOWN_RIGHT);
				play.heuristic.variable = 1;
				recursiveMoveDraught(tempBoard, player, draught, play);
				plays.push_back(play);
			}
		}
	}
}

void Greedy::recursiveMoveDraught(Board board, const Player& player, Draught&draught, Play&play)
{
	auto color = player.color;
	if (color == ColorPlayer::PLAYER_RED) {
		if (board.move(player, draught, Move::DIAGONAL_TOP_RIGHT) == MoveStatus::MOVE_ENEMY) {
			play.moves.push(Move::DIAGONAL_TOP_RIGHT);
			play.heuristic.variable += 1;
			recursiveMoveDraught(board, player, draught, play);
		}
		if (board.move(player, draught, Move::DIAGONAL_TOP_LEFT) == MoveStatus::MOVE_ENEMY) {
			play.moves.push(Move::DIAGONAL_TOP_LEFT);
			play.heuristic.variable += 1;
			recursiveMoveDraught(board, player, draught, play);
		}
	}
	else {
		auto tempBoard = board;
		if (tempBoard.move(player, draught, Move::DIAGONAL_DOWN_RIGHT) == MoveStatus::MOVE_ENEMY) {
			play.moves.push(Move::DIAGONAL_DOWN_RIGHT);
			play.heuristic.variable += 1;
			recursiveMoveDraught(tempBoard, player, draught, play);
		}
		if (tempBoard.move(player, draught, Move::DIAGONAL_DOWN_LEFT) == MoveStatus::MOVE_ENEMY) {
			play.moves.push(Move::DIAGONAL_DOWN_LEFT);
			play.heuristic.variable += 1;
			recursiveMoveDraught(tempBoard, player, draught, play);
		}
	}
}
