#include "AimTarget.h"
#include <DIR.h>

bool AimTarget::operator()(Obj & master, std::vector<sharedObj>& objList, InputState & input)
{
	if (!master.tageObj().expired())
	{
		if ((master.searchRange() * master.searchRange()) > LengthSquare(master.pos(), (*master.tageObj().lock()).pos()))
		{
			StickState state;
			state.isInput = true;
			state.angle = static_cast<short>DEG(atan2((*master.tageObj().lock()).pos().y - master.pos().y, (*master.tageObj().lock()).pos().x - master.pos().x));
			state.dir = convToDir(state.angle);
			input.LStickState(state);
			return true;
		}
		else
		{
			master.tageObj().reset();
			return false;
		}
	}
	return false;
}
