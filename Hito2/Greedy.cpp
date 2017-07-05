#include "Greedy.h"
#include "Board.h"
#include "Player.h"


Play Greedy::moveDraught(Board board, Player player)
{
	return recursiveMoveDraught(board, player);
}

Play Greedy::recursiveMoveDraught(Board board, Player player)
{
	return Play();
}
