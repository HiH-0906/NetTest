#pragma once
#include <vector>
#include <object\Obj.h>
#include <EFFECT.h>

struct MushroomAttack
{
	void operator ()(Obj& obj, std::vector<sharedObj>& objList);
private:
	EFFECT _id;													// ﾀｰｹﾞｯﾄによって出すｴﾌｪｸﾄが違う
	double _effectRad;											// ｴﾌｪｸﾄの角度
};

