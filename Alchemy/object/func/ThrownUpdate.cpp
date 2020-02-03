#include "ThrownUpdate.h"
#include <scene/SceneMng.h>
#include <EffekseerForDXLib.h>
#include <EffectMng.h>
#include <Camera.h>
#include "../Pot.h"
#include "../Enemy.h"

void ThrownUpdate::operator()(Obj& obj, std::vector<sharedObj>& objList)
{
	// 画面外判定
	auto tmpPos = obj._pos + obj._vel.x * Vector2Dbl{ cos(obj._rad), sin(obj._rad) };
	tmpPos.y -= obj._height;

	// x軸で反転
	if (tmpPos.x <= 0 || tmpPos.x >= lpSceneMng.WorldSize.x)
	{
		obj._rad = atan2(sin(obj._rad), -cos(obj._rad));
	}
	
	// y軸で反転
	if (tmpPos.y <= 0 || tmpPos.y >= lpSceneMng.WorldSize.y)
	{
		obj._rad = atan2(-sin(obj._rad), cos(obj._rad));
	}

	obj._pos += obj._vel.x * Vector2Dbl{cos(obj._rad), sin(obj._rad)};
	obj._height += obj._vel.y;

	// 煙エフェクトつけてみた
	/*lpSceneMng.AddEffectQue({ EFFECT_ID(EFFECT::DASH),
								 obj._pos.x - lpCamera.OfSet().x,
								obj._pos.y - lpCamera.OfSet().y - obj._height,
								100,LAYER::CHAR });*/

	// 投げられ終了判定
	if (obj._height <= 0)
	{
		// 壺に向かっているときは壺に入るか判定する
		if (!obj._tageObj.expired())
		{
			if ((*obj._tageObj.lock()).unitID() == UNIT_ID::POT)
			{
				lpSceneMng.AddActQue({ ACT_QUE::INTO_POT, obj });
				return;
			}
		}
		// 着地ｴﾌｪｸﾄを再生したい
		if (IsEffekseer2DEffectPlaying(obj._effectID) == -1)
		{
			if (obj._effectFlg)
			{
				// ステータスを戻す
				StopEffekseer2DEffect(obj._effectID);
				obj._effectFlg = false;
				obj._height = 0;
				obj.state(STATE::NORMAL);
				obj._tageObj.reset();
				return;
			}
		}
		else
		{
			obj._effectFlg = true;
		}
		Vector2Dbl ofSet = { 0.0,static_cast<double>(obj._size.y / 2) };
		// ｴﾌｪｸﾄをｷｭｰに投げる
		lpEffectMng.AddEffectQue({ obj,obj._pos + ofSet,0,EFFECT::LANDING,obj._zOrder + 1 });
		obj._vel = { 0,0 };
		obj._height = 0;
		return;
	}

	obj._vel.y -= obj._gravity;
}
