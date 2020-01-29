#include "AttackTarget.h"

bool AttackTarget::operator()(Obj & master, std::vector<sharedObj>& objList, InputState & input)
{
	if (!master.tageObj().expired())
	{
		if (static_cast<int>((*master.tageObj().lock()).state()) >= static_cast<int>(STATE::HOLDEN))
		{
			master.tageObj().reset();
			return false;
		}

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
