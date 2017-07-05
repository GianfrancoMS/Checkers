#pragma once

struct Play;
class Board;

class MoveAlgorithm
{
public:
	MoveAlgorithm() = default;
	virtual ~MoveAlgorithm() = 0;
	virtual Play moveDraught(Board board) = 0;
};

