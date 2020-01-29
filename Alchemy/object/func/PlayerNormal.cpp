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

		// holden,thrwon,death�̎��͎��ĂȂ�
		if ((*obj).weight() > ((Player&)player).holdWeightMax() || static_cast<int>((*obj).state()) >= static_cast<int>(STATE::THROWN))
		{
			continue;
		}

		player._tageObj = obj;
		break;
	}

	// ����
	if (!(player._tageObj.expired()) && (((*player._input).btnState(INPUT_ID::BTN_B).first && !(*player._input).btnState(INPUT_ID::BTN_B).second) || ((*player._input).btnState(INPUT_ID::BTN_A).first && !(*player._input).btnState(INPUT_ID::BTN_A).second)))
	{
		lpSceneMng.AddActQue({ ACT_QUE::HOLD,player });
	}
}

