#pragma once
#include <tuple>

struct Play;
class Board;
class Player;

using namespace std;

template<typename ...Types> 
struct Heuristic {

	tuple<Types...> variables;

	bool operator > (const Heuristic& heuristic) const {
		return tie(variables) > tie(heuristic.variables);
	}

	bool operator == (const Heuristic& heuristic) const {
		return tie(variables) = tie(heuristic.variables);
	}

	bool operator < (const Heuristic& heuristic) const {
		return tie(variables) < tie(heuristic.variables);
	}
};

class MoveAlgorithm
{
public:
	MoveAlgorithm() = default;
	virtual ~MoveAlgorithm() = 0;
	virtual Play moveDraught(Board board, Player player) = 0;
};

