#include "HeadPot.h"

bool HeadPot::operator()(Obj & master, std::vector<sharedObj>& objList, InputState & input)
{
	if (!master._potObj.expired())
	{
		StickState state;
		state.isInput = true;
		state.angle = static_cast<short>DEG(atan2((*master._potObj.lock()).pos().y - master.pos().y, (*master._potObj.lock()).pos().x - master.pos().x));
		state.dir = convToDir(state.angle);
		input.LStickState(state);
		return true;
	}
	return false;
}
