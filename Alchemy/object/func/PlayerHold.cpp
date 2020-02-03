#include <scene/SceneMng.h>
#include "PlayerHold.h"
#include <Input/InputState.h>
#include <_DebugConOut.h>
#include "../Player.h"
void PlayerHold::operator()(Obj& player, std::vector<sharedObj>& objList)
{
	if (_exChange)
	{
		ExchangeMove((Player&)player);
		return;
	}

	if (((*player._input).btnState(INPUT_ID::BTN_A).first && !(*player._input).btnState(INPUT_ID::BTN_A).second))
	{
		lpSceneMng.AddActQue({ ACT_QUE::PUT,player });
		return;
	}

	if (((Player&)player).throwPot())
	{
		// 壺に入れられる距離なら壺をターゲットに設定
		// 距離350、角度45度
		auto potRad = atan2((*player._potObj.lock()).pos().y - player._pos.y, (*player._potObj.lock()).pos().x - player._pos.x);
		auto relRad = player._rad - potRad;

		if (abs(relRad) > PI)
		{
			relRad = player._rad + potRad;
		}

		//TRACE("rad : %f, player : %f\n", potRad, player._rad);

		if (LengthSquare((*player._potObj.lock()).pos(), player._pos) < (350.0*350.0)
			/*&& abs(relRad) < PI / 4.0*/)
		{
			player._rad = atan2((*player._potObj.lock()).pos().y - player._pos.y, (*player._potObj.lock()).pos().x - player._pos.x);
			player._tageObj = player._potObj;
		}
	}
	else if (((Player&)player).GetHoldListSize() < ((Player&)player).holdWeightMax())
	{
		// ターゲット検索
		for (auto obj : objList)
		{
			if (LengthSquare((*obj).pos(), player._pos) > player._searchRange * player._searchRange)
			{
				// 上でソートしてるので索敵範囲を超えた敵がいたら判定終わり
				break;
			}

			// holden,thrwon,deathの時は持てない
			if ((*obj).weight() > ((Player&)player).holdWeightMax() || static_cast<int>((*obj).state()) >= static_cast<int>(STATE::THROWN))
			{
				continue;
			}

			player._tageObj = obj;
			break;
		}

		// 持つ
		if (!(player._tageObj.expired()) && (((*player._input).btnState(INPUT_ID::BTN_B).first && !(*player._input).btnState(INPUT_ID::BTN_B).second)))
		{
			lpSceneMng.AddActQue({ ACT_QUE::HOLD,player });
			lpSceneMng.AddSoundQue({ lpSoundMng.GetID(SOUND::HOLD)[0], 255 , player.pos().x, player.pos().y });
		}
	}

	// 壺に投げるか切り替え
	if ((*player._input).btnState(INPUT_ID::LEFT_TRIGGER).first)
	{
		((Player&)player).throwPot(true);
	}
	else
	{
		((Player&)player).throwPot(false);
	}

	// 投げる
	if ((((*player._input).btnState(INPUT_ID::BTN_Y).first && !(*player._input).btnState(INPUT_ID::BTN_Y).second)))
	{
		lpSceneMng.AddActQue({ ACT_QUE::THOROW,player });
		lpSceneMng.AddSoundQue({ lpSoundMng.GetID(SOUND::THROW)[0], 160, player.pos().x, player.pos().y});
		return;
	}

	// 持ってる物を入れ替える
	if (((Player&)player)._holdList.size() <= 1)
	{
		return;
	}

	if ((((*player._input).btnState(INPUT_ID::BTN_RB).first && !(*player._input).btnState(INPUT_ID::BTN_RB).second)))
	{
		auto frontObj = ((Player&)player)._holdList.front();
		((Player&)player)._holdList.erase(((Player&)player)._holdList.begin());
		((Player&)player)._holdList.emplace_back(frontObj);

		double height = static_cast<double>(((Player&)player)._size.y / 2);
		_heightList.resize(((Player&)player)._holdList.size());
		for (int i = 0; i < ((Player&)player)._holdList.size(); i++)
		{
			_heightList[i].first = (*((Player&)player)._holdList[i])._height;
			_heightList[i].second = height;
			height += static_cast<double>((*((Player&)player)._holdList[i])._size.x);
		}
		_moveCnt = 0;
		_exChange = true;
		return;
	}

	if ((((*player._input).btnState(INPUT_ID::BTN_LB).first && !(*player._input).btnState(INPUT_ID::BTN_LB).second)))
	{
		auto backObj = ((Player&)player)._holdList.back();
		((Player&)player)._holdList.erase(((Player&)player)._holdList.end() - 1);
		((Player&)player)._holdList.emplace(((Player&)player)._holdList.begin(),backObj);
		
		double height = static_cast<double>(((Player&)player)._size.y / 2);

		_heightList.resize(((Player&)player)._holdList.size());

		for (int i = 0; i < ((Player&)player)._holdList.size(); i++)
		{
			_heightList[i].first = (*((Player&)player)._holdList[i])._height;
			_heightList[i].second = height;
			height += static_cast<double>((*((Player&)player)._holdList[i])._size.x);
		}
		_moveCnt = 0;
		_exChange = true;

		return;
	}
}

void PlayerHold::ExchangeMove(Player & player)
{
	double length;
	_moveCnt++;
	for (int i = 0; i < player._holdList.size();i++)
	{
		length = _heightList[i].first - _heightList[i].second;
		(*(player._holdList[i]))._height -= length * static_cast<double>(_moveCnt)/ 55.0;
	}

	if (_moveCnt >= 10)
	{
		for (int i = 0; i < player._holdList.size(); i++)
		{
			(*player._holdList[i])._height = _heightList[i].second;
		}
		_exChange = false;
	}
}


