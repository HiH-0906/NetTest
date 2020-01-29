#include <scene/SceneMng.h>
#include "PlayerHold.h"
#include <Input/InputState.h>
#include <_DebugConOut.h>
#include "../Player.h"
void PlayerHold::operator()(Obj& player, std::vector<sharedObj>& objList)
{
	if (((Player&)player).throwPot())
	{
		// ��ɓ�����鋗���Ȃ����^�[�Q�b�g�ɐݒ�
		// ����350�A�p�x45�x
		auto potRad = atan2((*player._potObj.lock()).pos().y - player._pos.y, (*player._potObj.lock()).pos().x - player._pos.x);
		auto relRad = player._rad - potRad;

		if (abs(relRad) > PI)
		{
			relRad = player._rad + potRad;
		}

		//TRACE("rad : %f, player : %f\n", potRad, player._rad);

		if (LengthSquare((*player._potObj.lock()).pos(), player._pos) < (350.0*350.0)
			&& abs(relRad) < PI / 4.0)
		{
			player._rad = atan2((*player._potObj.lock()).pos().y - player._pos.y, (*player._potObj.lock()).pos().x - player._pos.x);
			player._tageObj = player._potObj;
		}
	}	

	// ��ɓ����邩�؂�ւ�
	if ((*player._input).btnState(INPUT_ID::BTN_LB).first && (*player._input).btnState(INPUT_ID::BTN_LB).second)
	{
		((Player&)player).throwPot(true);
	}
	else
	{
		((Player&)player).throwPot(false);
	}

	// ������
	if ((((*player._input).btnState(INPUT_ID::BTN_B).first && !(*player._input).btnState(INPUT_ID::BTN_B).second) || ((*player._input).btnState(INPUT_ID::BTN_A).first && !(*player._input).btnState(INPUT_ID::BTN_A).second)))
	{
		lpSceneMng.AddActQue({ ACT_QUE::THOROW,player });
	}

	
}
