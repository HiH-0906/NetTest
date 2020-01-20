#include <scene/SceneMng.h>
#include "PlayerNormal.h"
#include "../Player.h"
#include <Input/InputState.h>

void PlayerNormal::operator()(Obj& player, std::vector<sharedObj>& objList)
{
	// ���������ĂȂ��Ƃ�
		// ���㎝�Ă鐔��������\��������̂ŏ������ς�邩��

		// �^�[�Q�b�g����
	for (auto obj : objList)
	{
		if (LengthSquare((*obj).pos(), player._pos) > player._searchRange * player._searchRange)
		{
			// ��Ń\�[�g���Ă�̂ō��G�͈͂𒴂����G�������画��I���
			break;
		}

		if ((*obj).weight() > ((Player&)player).holdWeightMax() || (*obj).state() == STATE::HOLDEN || (*obj).state() == STATE::THROWN)
		{
			continue;
		}

		player._tageObj = obj;
		break;
	}

	// ����
	if (!(player._tageObj.expired()) && (*player._input).btnState(INPUT_ID::BTN_B).first && !(*player._input).btnState(INPUT_ID::BTN_B).second)
	{
		lpSceneMng.AddActQue({ ACT_QUE::HOLD,player });
	}
}

