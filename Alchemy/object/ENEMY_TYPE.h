#pragma once

enum class ENEMY_TYPE
{
	SLIME = 1,		// ｽﾗｲﾑ
	BAD = 2,		// ｺｳﾓﾘ
	GHOST = 4,		// おばけ
	MUSH = 8,		// きのこ
	DAEMON = 16,	// ﾃﾞｰﾓﾝ
	BOSS = 32,		// ﾎﾞｽ
	MAX
};


ENEMY_TYPE begin(ENEMY_TYPE);
ENEMY_TYPE end(ENEMY_TYPE);

ENEMY_TYPE operator++(ENEMY_TYPE type);
ENEMY_TYPE operator*(ENEMY_TYPE type);