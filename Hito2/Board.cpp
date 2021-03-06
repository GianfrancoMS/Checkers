#include "Board.h"
#include "rlutil.h"
#include <functional>

Board::Board()
{
	fillBoard();
	fillDraughts();
}

void Board::fillDraughts()
{
	for (auto i = 0; i < 3; ++i) {
		int x = i;
		for (auto j = i % 2 == 0 ? 0 : 1; j < COLUMNS; j += 2) {
			Draught draught;
			draught.point.x = x;
			draught.point.y = j;
			draught.type = DraughtType::NORMAL;
			draught.color = ColorPlayer::PLAYER_WHITE;
			whiteDraughts.insert(draught);
		}
	}
	for (auto i = 5; i < 8; ++i) {
		int x = i;
		for (auto j = i % 2 == 0 ? 0 : 1; j < COLUMNS; j += 2) {
			Draught draught;
			draught.point.x = x;
			draught.point.y = j;
			draught.type = DraughtType::NORMAL;
			draught.color = ColorPlayer::PLAYER_RED;
			redDraughts.insert(draught);
		}
	}
}

void Board::fillBoard()
{
	board = {
		{ WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY },
		{ EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE },
		{ WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY, WHITE, EMPTY },
		{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
		{ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
		{ EMPTY, RED  , EMPTY, RED  , EMPTY, RED  , EMPTY, RED },
		{ RED  , EMPTY, RED  , EMPTY, RED  , EMPTY, RED  , EMPTY },
		{ EMPTY, RED  , EMPTY, RED  , EMPTY, RED  , EMPTY, RED }
	};
}

void Board::printBoard() {
	cout << "+";
	for (auto i = 0; i < ROWS; ++i)
		cout << "---+";
	cout << endl;
	for (auto i = 0; i < ROWS; ++i) {
		cout << "|";
		for (auto j = 0; j < COLUMNS; ++j) {
			switch (board[i][j]) {
			case EMPTY:
				cout << "   |";
				break;
			case WHITE:
				rlutil::setColor(15);
				cout << " " << NORMAL_PIECE << " |";
				break;
			case RED:
				rlutil::setColor(4);
				cout << " " << NORMAL_PIECE;
				rlutil::setColor(15);
				cout << " |";
				break;
			}
		}
		rlutil::setColor(15);
		cout << endl;
		cout << "+";
		for (auto j = 0; j < ROWS; ++j)
			cout << "---+";
		cout << endl;
	}
}

set<Draught> Board::possibleMoves(const Player& player)
{
	set<Draught>possibleMoves;
	if (player.color == ColorPlayer::PLAYER_WHITE) {
		for (auto draught : whiteDraughts) {
			if (move(draught, Move::DIAGONAL_DOWN_LEFT) != MoveStatus::MOVE_IMPOSSIBLE || move(draught, Move::DIAGONAL_DOWN_RIGHT) != MoveStatus::MOVE_IMPOSSIBLE) {
				possibleMoves.insert(draught);
				continue;
			}

			if (draught.type == DraughtType::QUEEN)
				if (move(draught, Move::DIAGONAL_TOP_LEFT) != MoveStatus::MOVE_IMPOSSIBLE || move(draught, Move::DIAGONAL_TOP_RIGHT) != MoveStatus::MOVE_IMPOSSIBLE) {
					possibleMoves.insert(draught);
					continue;
				}
		}
	}
	else {
		for (auto draught : redDraughts) {
			if (move(draught, Move::DIAGONAL_TOP_LEFT) != MoveStatus::MOVE_IMPOSSIBLE || move(draught, Move::DIAGONAL_TOP_RIGHT) != MoveStatus::MOVE_IMPOSSIBLE) {
				possibleMoves.insert(draught);
				continue;
			}

			if (draught.type == DraughtType::QUEEN)
				if (move(draught, Move::DIAGONAL_DOWN_LEFT) != MoveStatus::MOVE_IMPOSSIBLE || move(draught, Move::DIAGONAL_DOWN_RIGHT) != MoveStatus::MOVE_IMPOSSIBLE) {
					possibleMoves.insert(draught);
					continue;
				}
		}
	}
	return possibleMoves;
}



int Board::possibleMoves(const Player& player, MoveStatus status)
{
	int moves = 0;
	if (player.color == ColorPlayer::PLAYER_WHITE) {
		for (auto draught : whiteDraughts) {
			if (move(draught, Move::DIAGONAL_DOWN_LEFT) == status)
				++moves;

			if (move(draught, Move::DIAGONAL_DOWN_RIGHT) == status)
				++moves;

			if (draught.type == DraughtType::QUEEN) {
				if (move(draught, Move::DIAGONAL_TOP_LEFT) == status)
					++moves;
				if (move(draught, Move::DIAGONAL_TOP_RIGHT) == status)
					++moves;
			}
		}
	}
	else {
		for (auto draught : redDraughts) {
			if (move(draught, Move::DIAGONAL_TOP_LEFT) == status)
				++moves;

			if (move(draught, Move::DIAGONAL_TOP_RIGHT) == status)
				++moves;

			if (draught.type == DraughtType::QUEEN) {
				if (move(draught, Move::DIAGONAL_DOWN_LEFT) == status)
					++moves;
				if (move(draught, Move::DIAGONAL_DOWN_RIGHT) == status)
					++moves;
			}
		}
	}
	return moves;
}

Draught Board::getDraught(ColorPlayer color, int x, int y)
{
	Draught draught;
	draught.point.x = x;
	draught.point.y = y;
	return  (color == ColorPlayer::PLAYER_RED) ?
		*redDraughts.find(draught) : *whiteDraughts.find(draught);
}

bool Board::isSameColor(int x, int y, Draught draught)
{
	if (board[x][y] == RED && draught.color == ColorPlayer::PLAYER_RED)
		return true;
	else if (board[x][y] == WHITE && draught.color == ColorPlayer::PLAYER_WHITE)
		return true;
	else
		return false;
}

bool Board::isInLimits(int x, int y)
{
	if (x <= -1 || x >= ROWS || y <= -1 || y >= COLUMNS)
		return false;
	return true;
}

bool Board::isInLimits(Draught draught, Move move)
{
	int draughtX = draught.point.x;
	int draughtY = draught.point.y;
	switch (move) {
	case Move::DIAGONAL_TOP_LEFT: {
		int x = draughtX - 1;
		int y = draughtY - 1;
		return isInLimits(x, y);
	}
	case Move::DIAGONAL_TOP_RIGHT: {
		int x = draughtX - 1;
		int y = draughtY + 1;
		return isInLimits(x, y);
	}
	case Move::DIAGONAL_DOWN_LEFT: {
		int x = draughtX + 1;
		int y = draughtY - 1;
		return isInLimits(x, y);
	}
	case Move::DIAGONAL_DOWN_RIGHT: {
		int x = draughtX + 1;
		int y = draughtY + 1;
		return isInLimits(x, y);
	}
	}
	return false;
}

void Board::updateBoard(int x, int y, const Player& player)
{
	player.color == ColorPlayer::PLAYER_WHITE ? board[x][y] = WHITE : board[x][y] = RED;
}

void Board::updateBoard(int x, int y, int color)
{
	board[x][y] = color;
}

void Board::updateToQueen(ColorPlayer color, Draught draught) {
	Draught queen = draught;
	queen.type = DraughtType::QUEEN;
	redDraughts.erase(draught);
	color == ColorPlayer::PLAYER_RED ? redDraughts.insert(queen) : whiteDraughts.insert(queen);
}

void Board::removeDraught(ColorPlayer color, Draught draught) {
	color == ColorPlayer::PLAYER_WHITE ? whiteDraughts.erase(draught) : redDraughts.erase(draught);
	updateBoard(draught.point.x, draught.point.y, EMPTY);
}

void Board::updatePosition(ColorPlayer color, Draught draught, int newX, int newY) {
	Draught newDraught = draught;
	newDraught.point.x = newX;
	newDraught.point.y = newY;
	removeDraught(color, draught);
	if (color == ColorPlayer::PLAYER_RED) {
		redDraughts.insert(newDraught);
		updateBoard(newX, newY, RED);
		if (newDraught.point.x == 0)
			updateToQueen(color, newDraught);
	}
	else {
		whiteDraughts.insert(newDraught);
		updateBoard(newX, newY, WHITE);
		if (newDraught.point.x == 7)
			updateToQueen(color, newDraught);
	}
}

MoveStatus Board::move(Draught draught, Move move)
{
	int draughtX = draught.point.x;
	int draughtY = draught.point.y;

	switch (move) {
	case Move::DIAGONAL_TOP_LEFT: {
		if (isInLimits(draught, move)) {
			int x = draughtX - 1;
			int y = draughtY - 1;
			if (board[x][y] == EMPTY)
				return MoveStatus::MOVE_BLANK;
			else if (isSameColor(x, y, draught))
				return MoveStatus::MOVE_IMPOSSIBLE;
			else {
				int tempX = x - 1;
				int tempY = y - 1;
				if (isInLimits(tempX, tempY) && board[tempX][tempY] == EMPTY)
					return MoveStatus::MOVE_ENEMY;
			}
		}
		break;
	}

	case Move::DIAGONAL_TOP_RIGHT: {
		if (isInLimits(draught, move)) {
			int x = draughtX - 1;
			int y = draughtY + 1;
			if (board[x][y] == EMPTY)
				return MoveStatus::MOVE_BLANK;
			else if (isSameColor(x, y, draught))
				return MoveStatus::MOVE_IMPOSSIBLE;
			else {
				int tempX = x - 1;
				int tempY = y + 1;
				if (isInLimits(tempX, tempY) && board[tempX][tempY] == EMPTY)
					return MoveStatus::MOVE_ENEMY;
			}
		}
		break;
	}

	case Move::DIAGONAL_DOWN_LEFT: {
		if (isInLimits(draught, move)) {
			int x = draughtX + 1;
			int y = draughtY - 1;
			if (board[x][y] == EMPTY)
				return MoveStatus::MOVE_BLANK;
			else if (isSameColor(x, y, draught))
				return MoveStatus::MOVE_IMPOSSIBLE;
			else {
				int tempX = x + 1;
				int tempY = y - 1;
				if (isInLimits(tempX, tempY) && board[tempX][tempY] == EMPTY)
					return MoveStatus::MOVE_ENEMY;
			}
		}
		break;
	}

	case Move::DIAGONAL_DOWN_RIGHT: {
		if (isInLimits(draught, move)) {
			int x = draughtX + 1;
			int y = draughtY + 1;
			if (board[x][y] == EMPTY) {
				return MoveStatus::MOVE_BLANK;
			}
			else if (isSameColor(x, y, draught))
				return MoveStatus::MOVE_IMPOSSIBLE;
			else {
				int tempX = x + 1;
				int tempY = y + 1;
				if (isInLimits(tempX, tempY) && board[tempX][tempY] == EMPTY)
					return MoveStatus::MOVE_ENEMY;
			}
		}
		break;
	}
	}
	return MoveStatus::MOVE_IMPOSSIBLE;
}

MoveStatus Board::move(const Player& player, Draught draught, Move move) {
	int draughtX = draught.point.x;
	int draughtY = draught.point.y;

	MoveStatus draughtMove = this->move(draught, move);
	ColorPlayer enemyColor = (player.color == ColorPlayer::PLAYER_RED) ? ColorPlayer::PLAYER_WHITE : ColorPlayer::PLAYER_RED;

	if (draughtMove == MoveStatus::MOVE_IMPOSSIBLE)
		return MoveStatus::MOVE_IMPOSSIBLE;
	else {
		switch (move) {
		case Move::DIAGONAL_TOP_LEFT: {
			int newX = draughtX - 1;
			int newY = draughtY - 1;
			if (draughtMove == MoveStatus::MOVE_BLANK) {
				updatePosition(player.color, draught, newX, newY);
				return MoveStatus::MOVE_BLANK;
			}
			else {
				int tempX = newX - 1;
				int tempY = newY - 1;

				Draught deletedDraught = getDraught(enemyColor, newX, newY);
				removeDraught(enemyColor, deletedDraught);

				updatePosition(player.color, draught, tempX, tempY);

				return MoveStatus::MOVE_ENEMY;
			}
			break;
		}
		case Move::DIAGONAL_TOP_RIGHT: {
			int newX = draughtX - 1;
			int newY = draughtY + 1;
			if (draughtMove == MoveStatus::MOVE_BLANK) {
				updatePosition(player.color, draught, newX, newY);
				return MoveStatus::MOVE_BLANK;
			}
			else {
				int tempX = newX - 1;
				int tempY = newY + 1;

				Draught deletedDraught = getDraught(enemyColor, newX, newY);
				removeDraught(enemyColor, deletedDraught);

				updatePosition(player.color, draught, tempX, tempY);

				return MoveStatus::MOVE_ENEMY;
			}
			break;
		}
		case Move::DIAGONAL_DOWN_LEFT: {
			int newX = draughtX + 1;
			int newY = draughtY - 1;
			if (draughtMove == MoveStatus::MOVE_BLANK) {
				updatePosition(player.color, draught, newX, newY);
				return MoveStatus::MOVE_BLANK;
			}
			else {
				int tempX = newX + 1;
				int tempY = newY - 1;

				Draught deletedDraught = getDraught(enemyColor, newX, newY);
				removeDraught(enemyColor, deletedDraught);

				updatePosition(player.color, draught, tempX, tempY);

				return MoveStatus::MOVE_ENEMY;
			}
			break;
		}
		case Move::DIAGONAL_DOWN_RIGHT: {
			int newX = draughtX + 1;
			int newY = draughtY + 1;
			if (draughtMove == MoveStatus::MOVE_BLANK) {
				updatePosition(player.color, draught, newX, newY);
				return MoveStatus::MOVE_BLANK;
			}
			else {
				int tempX = newX + 1;
				int tempY = newY + 1;

				Draught deletedDraught = getDraught(enemyColor, newX, newY);
				removeDraught(enemyColor, deletedDraught);

				updatePosition(player.color, draught, tempX, tempY);

				return MoveStatus::MOVE_ENEMY;
			}
			break;
		}
		}
		return MoveStatus::MOVE_IMPOSSIBLE;
	}
}
