#include "PotThrow.h"
#include <scene\SceneMng.h>
void PotThrow::operator()(Obj& pot, std::vector<sharedObj>& objList)
{
	pot.state(STATE::NORMAL);
}
