#pragma once
#include <vector>
#include <tuple>
#include <set>
#include <queue>
#include "Utils.h"
#include "Player.h"

using namespace std;

struct Point
{
	int x;
	int y;

	bool operator < (const Point& point) const {
		return tie(this->x, this->y) < tie(point.x, point.y);
	}

	bool operator > (const Point& point) const {
		return tie(this->x, this->y) > tie(point.x, point.y);
	}
};

struct Draught
{
	Point point;
	DraughtType type;
	ColorPlayer color;

	bool operator < (const Draught& draught) const {
		return this->point < draught.point;
	}

	bool operator > (const Draught& draught) const {
		return this->point > draught.point;
	}
};

template<typename ...Types>
struct Heuristic {

	tuple<Types...> variables;

	bool operator > (const Heuristic& heuristic) const {
		return tie(variables) > tie(heuristic.variables);
	}

	bool operator == (const Heuristic& heuristic) const {
		return tie(variables) == tie(heuristic.variables);
	}

	bool operator < (const Heuristic& heuristic) const {
		return tie(variables) < tie(heuristic.variables);
	}
};

struct Play {
	Draught draught;
	queue<Move> moves;
	Heuristic<int, int>heuristic;

	bool operator > (const Play& play) const {
		return heuristic > play.heuristic;
	}

	bool operator == (const Play& play) const {
		return heuristic == play.heuristic;
	}

	bool operator < (const Play& play) const {
		return heuristic < play.heuristic;
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

	set<Draught,greater<Draught>() > possibleMovesWhite(const Player& player);
	set<Draught, less<Draught>() > possibleMovesRed(const Player& player);

	int possibleMoves(const Player& player, MoveStatus status);

	Draught getDraught(ColorPlayer color, int x ,int y);

	MoveStatus move(const Player& player, Draught draught, Move move);

	set<Draught> whiteDraughts;
	set<Draught> redDraughts;

private:

	static const char NORMAL_PIECE = '@';
	static const char QUEEN_PIECE = '#';

	void updateBoard(int x, int y, const Player& player);
	void updateBoard(int x, int y, int color);

	bool isSameColor(int x, int y, Draught draught);
	bool isInLimits(int x, int y);

	void removeDraught(ColorPlayer color, Draught draught);
	void updateToQueen(ColorPlayer color, Draught draught);
	void updatePosition(ColorPlayer color, Draught draught, int newX, int newY);

	void fillDraughts();
	void fillBoard();

	MoveStatus move(Draught draught, Move move);

	vector<vector<int>>board;
};

