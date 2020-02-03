#pragma once

enum class FOLLOWER_TYPE
{
	OCTOPUS = 1,		// ‚½‚±
	BEE = 2,		// ‚Í‚¿
	GHOST = 4,		// ‚¨‚Î‚¯
	MUSH = 8,		// ‚«‚Ì‚±
	DAEMON = 16,		// ÃÞ°ÓÝ
	POT = 32,			// ÊØ°
	MAX
};


FOLLOWER_TYPE begin(FOLLOWER_TYPE);
FOLLOWER_TYPE end(FOLLOWER_TYPE);

FOLLOWER_TYPE operator++(FOLLOWER_TYPE type);
FOLLOWER_TYPE operator*(FOLLOWER_TYPE type);
