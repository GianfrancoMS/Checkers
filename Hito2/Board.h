#pragma once
#include <vector>
#include <tuple>
#include <set>
#include "Utils.h"

using namespace std;

class Player;

struct Point
{
	int x;
	int y;
	bool operator == (const Point& point) const {
		return tie(this->x, this->y) == tie(point.x, point.y);
	}

	bool operator < (const Point& point) const {
		return tie(this->x, this->y) < tie(point.x, point.y);
	}
};

struct Draught
{
	Point point;
	DraughtType type;
	PlayerColor color;

	bool operator == (const Draught& draught) const {
		return this->point == draught.point;
	}

	bool operator < (const Draught& draught) const {
		return this->point < draught.point;
	}
};

class Board
{
public:

	Board();
	~Board() = default;

	static const int ROWS = 8;
	static const int COLUMNS = 8;

	static const int EMPTY = 0;
	static const int WHITE = 1;
	static const int RED = 2;

	bool isInLimits(Draught draught, Move move);

	void printBoard();

	set<Draught> possibleMoves(Player player);

	MoveStatus move(Player player, Draught draught, Move move);

	set<Draught> whiteDraughts;
	set<Draught> redDraughts;
private:

	static const char NORMAL_PIECE = '@';
	static const char QUEEN_PIECE = '#';

	void updateBoard(int x, int y, Player player);
	void updateBoard(int x, int y, int color);

	bool isSameColor(int x, int y, Draught draught);
	bool isInLimits(int x, int y);

	void removeDraught(Player player, Draught draught);
	void updateToQueen(Player player, Draught draught);
	void updatePosition(Player player, Draught draught, int newX, int newY);

	void fillDraughts();
	void fillBoard();

	MoveStatus move(Draught&draught, Move move);

	vector<vector<int>>board;
};

