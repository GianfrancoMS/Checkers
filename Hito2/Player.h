#pragma once
#include "Utils.h"
#include <memory>
#include "MoveAlgorithm.h"

using namespace std;

class Player
{
public:
	Player(ColorPlayer color);
	~Player() = default;
	ColorPlayer color;
private:

};

