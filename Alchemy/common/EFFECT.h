#pragma once

enum class EFFECT
{
	DASH,
	ATTACK_BITE,
	MAX
};

EFFECT begin(EFFECT);
EFFECT end(EFFECT);

EFFECT operator ++(EFFECT& effect);
EFFECT operator *(EFFECT effect);