#pragma once
#include <set>
#include "Utils.h"

using namespace std;

struct Draught;
class Board;

class Player
{
public:
	Player(PlayerColor color, Board board);
	~Player()=default;

	PlayerColor color;

	void removeDraught(Draught C);
	void upgradeToQueen(Draught draught);
	void updatePosition(Draught draught, int x, int y);
	Draught getDraught(int x, int y);
	
	set<Draught> draughts;
};

