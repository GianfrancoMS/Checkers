#pragma once
#include <vector>
#include <tuple>
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
	DraughtType draughtType;
	PlayerColor playerColor;
	bool destroyed = false;

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

	/*MoveStatus remove(Player &player, int x , int y);*/
	MoveStatus move(Player &player, Draught&draught, Move move);

	void printBoard();

private:

	static const char PIECE = '@';

	void initializeBoard();
	void updateBoard(int x, int y,PlayerColor color);

	bool isSameColor(int x, int y, Draught draught);
	bool isInLimits(int x, int y);
	//bool isFree(int x, int y);

	vector<vector<int>>board;
};

