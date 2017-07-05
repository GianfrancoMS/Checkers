#pragma once
#include "MoveAlgorithm.h"
#include <vector>

struct Play;
struct Draught;

class Greedy: public MoveAlgorithm
{
public:
	Greedy()=default;
	~Greedy()=default;
	Play moveDraught(Board board, const Player& player);
private:
	void recursiveMoveDraught(Board board, const Player& player,vector<Play>&plays);
	void recursiveMoveDraught(Board& board, const Player& player, Draught&draught, Play&play);
};

