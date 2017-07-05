#pragma once
#include "Utils.h"

using namespace std;

class Player
{
public:
	Player(ColorPlayer color);
	~Player()=default;
	ColorPlayer color;
};

