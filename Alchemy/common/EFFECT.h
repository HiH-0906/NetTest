#pragma once

enum class EFFECT
{
	AT_BITE,			// Šš‚Ý‚Â‚«
	HEAL,				// ‰ñ•œ
	AT_SLIME,			// ½×²Ñ
	GHOST_CHARGE,		// Á¬°¼Þ
	GHOST_SHOT,			// ’e•\Ž¦—p
	GHOST_BLAST,		// ”š”­
	DEMON_CHARGE,		// Á¬°¼Þ
	DEMON_WAR,			// Œx
	INK,				// –nUŒ‚
	FIRE,				// ‰ŠUŒ‚
	AT_BEE,				// –I‚Ì‚±‚¤‚°‚«
	SMOKE,				// ·Éº‚Ì‰ŒUŒ‚
	LANDING,			// ’…’n
	MAX
};

EFFECT begin(EFFECT);
EFFECT end(EFFECT);

EFFECT operator ++(EFFECT& effect);
EFFECT operator *(EFFECT effect);