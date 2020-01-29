#pragma once

enum class ENEMY_TYPE
{
	SLIME = 1,		// ½×²Ñ
	BAD = 2,		// º³ÓØ
	GHOST = 4,		// ‚¨‚Î‚¯
	MUSH = 8,		// ‚«‚Ì‚±
	DAEMON = 16,		// ÃÞ°ÓÝ
	MAX
};


ENEMY_TYPE begin(ENEMY_TYPE);
ENEMY_TYPE end(ENEMY_TYPE);

ENEMY_TYPE operator++(ENEMY_TYPE type);
ENEMY_TYPE operator*(ENEMY_TYPE type);