#include "FuncThrow.h"
#include <object/Player.h>
#include <object/Pot.h>
#include <_DebugConOut.h>

bool FuncThrow::operator()(ActQueT& actQue, std::vector<sharedObj>& objList)
{
	if (actQue.second.unitID() == UNIT_ID::PLAYER)
	{
		Player& player = ((Player&)actQue.second);
		auto thrownObj = player._holdList.front();
		// プレイヤーが投げるとき
		if (!(player._tageObj.expired()))
		{
			// 壺をターゲットにしているときは壺に向かって投げる
			if ((*player._tageObj.lock()).unitID() == UNIT_ID::POT)
			{
				(*thrownObj)._rad = player._rad;
				player._tageObj.reset();

				for (auto obj : objList)
				{
					if ((*obj).unitID() == UNIT_ID::POT)
					{
						(*thrownObj).SetTageObj(obj);

						// 水平方向の速さを設定
						(*thrownObj)._vel.x = sqrt(LengthSquare((*obj)._pos, (*thrownObj)._pos)) / THROW_CNT_MAX;
						break;
					}
				}
			}
		}
		else
		{
			(*thrownObj)._vel.x = player._throwRange / THROW_CNT_MAX;		// 距離300を30フレームで
		}

		(*thrownObj).state(STATE::THROWN);

		// 投げるときに方向を補正する
		//(*((Player&)actQue.second)._holdList.front())._rad = convToRad((*((Player&)actQue.second)._holdList.front())._dir);

		auto vel = (*thrownObj)._vel;
		vel.y = sqrt(THROW_INITIAL_SPEED*THROW_INITIAL_SPEED - vel.x * vel.x);
		(*thrownObj)._vel.y = vel.y;
		(*thrownObj)._gravity = 2 * ((*thrownObj)._height + vel.y * THROW_CNT_MAX) / (THROW_CNT_MAX * THROW_CNT_MAX);

		(*thrownObj)._holdPlayer.reset();
		player._holdList.erase(player._holdList.begin());
		player.state(STATE::THROW);
		return true;
	}
	else if (actQue.second.unitID() == UNIT_ID::POT)
	{
		// 壺から出るとき
		Pot& pot = ((Pot&)actQue.second);
		sharedObj thrownObj;

		double throwRad = 2.0 * PI / static_cast<double>(((Pot&)pot)._throwList.size());		// 吐き出すときの角度
		double cnt = 1.0;

		for (auto selNum : pot._throwList)
		{
			for (auto obj : objList)
			{
				if ((*obj)._serialNum == selNum)
				{
					thrownObj = obj;

					(*thrownObj)._rad = throwRad * cnt;
					(*thrownObj).dir(convToDir(throwRad * cnt));
					(*thrownObj)._vel.x = 200.0 / THROW_CNT_MAX;
					(*thrownObj)._vel.y = sqrt(THROW_INITIAL_SPEED*THROW_INITIAL_SPEED - (*thrownObj)._vel.x * (*thrownObj)._vel.x);
					(*thrownObj)._gravity = 2 * ((*thrownObj)._height + (*thrownObj)._vel.y * THROW_CNT_MAX) / (THROW_CNT_MAX * THROW_CNT_MAX);
					(*thrownObj).state(STATE::THROWN);
					cnt += 1.0;
					break;
				}
			}
		}
		
		pot._throwList.clear();
		pot.state(STATE::THROW);

		return true;
	}
	else
	{
		AST();
		return false;
	}
}
