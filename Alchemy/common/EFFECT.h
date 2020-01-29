#pragma once

enum class EFFECT
{
	AT_BITE,			// 噛みつき
	HEAL,				// 回復
	AT_SLIME,			// ｽﾗｲﾑ
	GHOST_CHARGE,		// ﾁｬｰｼﾞ
	GHOST_SHOT,			// 弾表示用
	GHOST_BLAST,		// 爆発
	DEMON_CHARGE,
	DEMON_WAR,			// 警告
	DEMON_BLAST,
	INK,				// 墨攻撃
	FIRE,				// 炎攻撃
	AT_BEE,				// 蜂のこうげき
	SMOKE,				// ｷﾉｺの煙攻撃
	MAX
};

EFFECT begin(EFFECT);
EFFECT end(EFFECT);

EFFECT operator ++(EFFECT& effect);
EFFECT operator *(EFFECT effect);