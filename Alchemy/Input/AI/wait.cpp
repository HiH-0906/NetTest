#include "wait.h"

bool wait::operator()(Obj & master, std::vector<sharedObj> objList, InputState & input)
{
	StickState state;
	state.isInput = false;
	state.angle = 0;
	state.dir = DIR::DOWN;
	input.LStickState(state);
	master.tageObj().reset();
	return true;
}
