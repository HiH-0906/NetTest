#pragma once

enum class ENEMY_TYPE
{
	SLIME,		// ｽﾗｲﾑ
	BAD,		// ｺｳﾓﾘ
	DAEMON,		// ﾃﾞｰﾓﾝ
	GHOST,		// おばけ
	MUSH,		// きのこ
	MAX
};


ENEMY_TYPE begin(ENEMY_TYPE);
ENEMY_TYPE end(ENEMY_TYPE);

ENEMY_TYPE operator++(ENEMY_TYPE type);
ENEMY_TYPE operator*(ENEMY_TYPE type);