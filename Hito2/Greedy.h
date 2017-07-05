#pragma once
#include "MoveAlgorithm.h"

class Greedy: public MoveAlgorithm
{
public:
	Greedy()=default;
	~Greedy()=default;
	Play moveDraught(Board board, Player player);
private:
	Play recursiveMoveDraught(Board board, Player player);
};

