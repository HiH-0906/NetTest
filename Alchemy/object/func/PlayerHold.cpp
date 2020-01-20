#include <scene/SceneMng.h>
#include "PlayerHold.h"
#include <Input/InputState.h>
void PlayerHold::operator()(Obj& player, std::vector<sharedObj>& objList)
{
	// 壺に入れられる距離なら壺をターゲットに設定
	// 距離350、角度45度
	if (LengthSquare((*player._potObj.lock()).pos(), player._pos) < (350.0*350.0)
		&& abs(atan2((*player._potObj.lock()).pos().y - player._pos.y, (*player._potObj.lock()).pos().x - player._pos.x) - player._rad) < PI / 4.0)
	{
		player._rad = atan2((*player._potObj.lock()).pos().y - player._pos.y, (*player._potObj.lock()).pos().x - player._pos.x);
		player._tageObj = player._potObj;
	}

	// 投げる
	if ((*player._input).btnState(INPUT_ID::BTN_A).first && !(*player._input).btnState(INPUT_ID::BTN_A).second)
	{
		lpSceneMng.AddActQue({ ACT_QUE::THOROW,player });
	}
}
