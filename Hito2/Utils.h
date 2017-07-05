#pragma once

enum class Move
{
	DIAGONAL_TOP_LEFT, DIAGONAL_TOP_RIGHT, DIAGONAL_DOWN_LEFT, DIAGONAL_DOWN_RIGHT
};

enum class MoveStatus	
{
	MOVE_BLANK, MOVE_IMPOSSIBLE, MOVE_ENEMY
};

enum class DraughtType {
	NORMAL, QUEEN
};

enum class ColorPlayer {
	PLAYER_WHITE, PLAYER_RED
};