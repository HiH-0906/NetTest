#include <DxLib.h>
#include "AttackTarget.h"

bool AttackTarget::operator()(Obj & master, std::vector<sharedObj>& objList, InputState & input)
{
	if (!master.tageObj().expired())
	{
		if ((master.attackRange() * master.attackRange()) > LengthSquare(master.pos(), (*master.tageObj().lock()).pos()))
		{
			StickState state;
			state.isInput = false;
			state.angle = 0;
			state.dir = DIR::DOWN;
			input.LStickState(state);

			input.btnState(INPUT_ID::BTN_B, true);

			return true;
		}
	}
	return false;
}
