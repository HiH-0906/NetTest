#pragma once
#include <vector>
#include <object\Obj.h>

struct BeeAttack
{
	void operator ()(Obj& obj, std::vector<sharedObj>& objList);
private:
	float _effectRad;		// �̪�ėp�̊p�x
};
