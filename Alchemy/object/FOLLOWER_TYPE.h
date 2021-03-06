#pragma once

enum class FOLLOWER_TYPE
{
	OCTOPUS = 1,		// たこ
	BEE = 2,		// はち
	GHOST = 4,		// おばけ
	MUSH = 8,		// きのこ
	DAEMON = 16,		// ﾃﾞｰﾓﾝ
	POT = 32,			// ﾊﾘｰ
	MAX
};


FOLLOWER_TYPE begin(FOLLOWER_TYPE);
FOLLOWER_TYPE end(FOLLOWER_TYPE);

FOLLOWER_TYPE operator++(FOLLOWER_TYPE type);
FOLLOWER_TYPE operator*(FOLLOWER_TYPE type);
