#pragma once
#include <vector>
#include <object\Obj.h>
#include <EFFECT.h>

struct MushroomAttack
{
	void operator ()(Obj& obj, std::vector<sharedObj>& objList);
private:
	EFFECT _id;													// À°¹Ş¯Ä‚É‚æ‚Á‚Äo‚·´Ìª¸Ä‚ªˆá‚¤
	double _effectRad;											// ´Ìª¸Ä‚ÌŠp“x
};

