#include "Leave.h"

bool Leave::operator()(Obj & master, std::vector<sharedObj>& objList, InputState & input)
{
	if (!master.tageObj().expired())
	{
		if (((master.attackRange() * 0.8) * (master.attackRange() * 0.8)) > LengthSquare(master.pos(), (*master.tageObj().lock()).pos()))
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
