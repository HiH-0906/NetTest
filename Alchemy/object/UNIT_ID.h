#pragma once

// オブジェクトの種別
enum class UNIT_ID
{
	NON,
	PLAYER,
	ENEMY,
	POT,
	FOLLOWER
};

UNIT_ID bigin(UNIT_ID());
UNIT_ID end(UNIT_ID());
UNIT_ID operator*(UNIT_ID key);
UNIT_ID operator++(UNIT_ID& key);

