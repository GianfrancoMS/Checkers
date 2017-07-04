#pragma once

using namespace std;

class Player
{
public:
	Player(PlayerColor color);
	~Player()=default;
	PlayerColor color;
};

