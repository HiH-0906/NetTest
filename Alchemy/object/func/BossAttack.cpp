#include "BossAttack.h"
#include <DxLib.h>
#include <algorithm>
#include <EffekseerForDXLib.h>
#include <scene\SceneMng.h>
#include <EffectMng.h>
#include <EFFECT.h>

void BossAttack::operator()(Obj & obj, std::vector<sharedObj>& objList)
{
	// リンク切れ
	if (obj.tageObj().expired())
	{
		StopEffekseer2DEffect(obj._effectID);
		obj._effectFlg = false;
		obj._coolCnt = obj._coolCntMax;
		obj.state(STATE::NORMAL);
		return;
	}

	auto target = obj.tageObj().lock();					// ターゲットの情報格納

	// 再生ﾁｪｯｸ
	if (IsEffekseer2DEffectPlaying(obj._effectID) == -1)
	{
		if (!obj._effectFlg)
		{
			// 自分からの距離が近い順にobjListをソート
			std::sort(objList.begin(), objList.end(),
				[&](sharedObj objA, sharedObj objB) {
				return LengthSquare(obj._pos, (*objA)._pos) < LengthSquare(obj._pos, (*objB)._pos);
			});

			for (auto list : objList)
			{
				// 範囲内の敵全てにﾀﾞﾒｰｼﾞを与えたい
				if ((*list).teamTag() == TEAM_TAG::ALLY_TEAM)
				{
					if ((*list)._state != STATE::HOLDEN)
					{
						if ((obj._attackRange * obj._attackRange) > LengthSquare(obj._pos, (*list)._pos))
						{
							(*list).DoDamage(obj._power);		// ﾀﾞﾒｰｼﾞ
						}
						else
						{
							break;
						}
					}
				}
			}
		}
		else
		{
			obj._coolCnt--;								// ｸｰﾙﾀｲﾑ

			// ステータスを戻す
			if (obj._coolCnt <= 0)
			{
				StopEffekseer2DEffect(obj._effectID);
				obj._coolCnt = obj._coolCntMax;
				obj._effectFlg = false;
				obj.state(STATE::NORMAL);
				return;
			}
			return;										// 攻撃が終わってるから処理はここまで
		}
	}
	else
	{
		obj._effectFlg = true;
	}

	// ｴﾌｪｸﾄをｷｭｰに投げる
	lpEffectMng.AddEffectQue({ obj,obj._pos,0,EFFECT::DARK,obj._zOrder -1 });
}
