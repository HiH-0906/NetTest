#include "HoldenUpdate.h"
#include "../Obj.h"

void HoldenUpdate::operator()(Obj& obj, std::vector<sharedObj>& objList)
{
	obj._pos = (*obj._holdPlayer.lock()).pos();
	obj._rad = (*obj._holdPlayer.lock()).rad();

	obj.dir((*obj._holdPlayer.lock()).dir());
}
