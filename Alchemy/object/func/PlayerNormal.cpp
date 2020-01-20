#include <scene/SceneMng.h>
#include "PlayerNormal.h"
#include "../Player.h"
#include <Input/InputState.h>

void PlayerNormal::operator()(Obj& player, std::vector<sharedObj>& objList)
{
	// 何も持ってないとき
		// 今後持てる数が増える可能性があるので条件が変わるかも

		// ターゲット検索
	for (auto obj : objList)
	{
		if (LengthSquare((*obj).pos(), player._pos) > player._searchRange * player._searchRange)
		{
			// 上でソートしてるので索敵範囲を超えた敵がいたら判定終わり
			break;
		}

		if ((*obj).weight() > ((Player&)player).holdWeightMax() || (*obj).state() == STATE::HOLDEN || (*obj).state() == STATE::THROWN)
		{
			continue;
		}

		player._tageObj = obj;
		break;
	}

	// 持つ
	if (!(player._tageObj.expired()) && (*player._input).btnState(INPUT_ID::BTN_B).first && !(*player._input).btnState(INPUT_ID::BTN_B).second)
	{
		lpSceneMng.AddActQue({ ACT_QUE::HOLD,player });
	}
}

