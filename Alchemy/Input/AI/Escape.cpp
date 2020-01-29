#include "Escape.h"

bool Escape::operator()(Obj & master, std::vector<sharedObj>& objList, InputState & input)
{
	if (!master.tageObj().expired())
	{
		if (master.hp() < master.hpMax() * 0.2)
		{
			StickState state;
			state.isInput = true;
			state.angle = static_cast<short>DEG(atan2((*master.tageObj().lock()).pos().y - master.pos().y, (*master.tageObj().lock()).pos().x - master.pos().x) + 180.0);
			state.dir = convToDir(state.angle);
			input.LStickState(state);
			return true;
		}
	}
	return false;
}
