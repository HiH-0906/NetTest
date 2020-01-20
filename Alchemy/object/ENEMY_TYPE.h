#pragma once

enum class ENEMY_TYPE
{
	SLIME,		// ½×²Ñ
	BAD,		// º³ÓØ
	DAEMON,		// ÃÞ°ÓÝ
	GHOST,		// ‚¨‚Î‚¯
	MUSH,		// ‚«‚Ì‚±
	MAX
};


ENEMY_TYPE begin(ENEMY_TYPE);
ENEMY_TYPE end(ENEMY_TYPE);

ENEMY_TYPE operator++(ENEMY_TYPE type);
ENEMY_TYPE operator*(ENEMY_TYPE type);