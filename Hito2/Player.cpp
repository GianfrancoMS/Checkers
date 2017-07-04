#include "Player.h"
#include "Utils.h"

Player::Player(PlayerColor color)
{
	this->color = color;
}

//void Player::removeDraught(Draught draught)
//{
//	for each (Draught obj in draughts)
//	{
//		if (obj.point.x == draught.point.x && obj.point.y == draught.point.y)
//		{
//			draught = obj;
//		}
//	}
//	draughts.erase(draught);
//}
//
//void Player::upgradeToQueen(Draught  draught)
//{
//	auto queen = *draughts.find(draught);
//	queen.draughtType = DraughtType::QUEEN;
//	removeDraught(draught);
//	draughts.insert(queen);
//}
//
//void Player::updatePosition(Draught draught, int x, int y)
//{
//	auto newDraught = *draughts.find(draught);
//	newDraught.point.x = x;
//	newDraught.point.y = y;
//	removeDraught(draught);
//	if (newDraught.playerColor == PlayerColor::PLAYER_RED && newDraught.point.x == 0)
//	{
//		upgradeToQueen(newDraught);
//	}
//	else if (newDraught.playerColor == PlayerColor::PLAYER_WHITE && newDraught.point.x == 7)
//	{
//		upgradeToQueen(newDraught);
//	}
//	else
//	{
//		draughts.insert(newDraught);
//	}
//}
//
//Draught Player::getDraught(int x, int y)
//{
//	Draught draught;
//	for each (Draught obj in draughts)
//	{
//		if (obj.point.x == x && obj.point.y == y)
//		{
//			draught = obj;
//		}
//	}
//	return draught;
//}
