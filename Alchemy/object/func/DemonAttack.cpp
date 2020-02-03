#include "DemonAttack.h"
#include <DxLib.h>
#include <math.h>
#include <algorithm>
#include <EffekseerForDXLib.h>
#include <Vector2.h>
#include <scene\SceneMng.h>
#include <EffectMng.h>
#include <EFFECT.h>
#include <_DebugConOut.h>

void DemonAttack::operator()(Obj & obj, std::vector<sharedObj>& objList)
{
	// リンク切れ
	if (obj.tageObj().expired())
	{
		TRACE("attackの対象が消えました")
		StopEffekseer2DEffect(obj._effectID);
		obj._effectFlg = false;
		obj._coolCnt = obj._coolCntMax;
		_move = MOVE_TYPE::CHARGE;
		obj.state(STATE::NORMAL);
		return;
	}

	switch (_move)
	{
	case MOVE_TYPE::CHARGE:
		Charge(obj);
		break;
	case MOVE_TYPE::BLAST:
		Blast(obj, objList);
		break;
	default:
		AST();
		break;
	}

}

void DemonAttack::Charge(Obj & obj)
{
	// 再生ﾁｪｯｸ
	if (IsEffekseer2DEffectPlaying(obj._effectID) == -1)
	{
		if (!obj._effectFlg)
		{
			_chargeCnt++;
		}
		else
		{
			// 2回警告出したら次の攻撃に移動
			if (_chargeCnt >= 2)
			{
				StopEffekseer2DEffect(obj._effectID);
				obj._effectFlg = false;
				obj._coolCnt = obj._coolCntMax;
				_chargeCnt = 0;
				_move = MOVE_TYPE::BLAST;
				return;
			}
			obj._effectFlg = false;
			return;
		}
	}
	else
	{
		obj._effectFlg = true;
	}

	// ｴﾌｪｸﾄをｷｭｰに投げる
	lpEffectMng.AddEffectQue({ obj,obj._pos,0,EFFECT::DEMON_WAR,obj._zOrder + 1 });
}

void DemonAttack::Warning(Obj & obj)
{

}

void DemonAttack::Blast(Obj & obj, std::vector<sharedObj>& objList)
{
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
					if ((*list)._state != STATE::HOLDEN )
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

			// 終了
			if (obj._coolCnt <= 0)
			{
				StopEffekseer2DEffect(obj._effectID);
				obj._effectFlg = false;
				obj._coolCnt = obj._coolCntMax;
				_move = MOVE_TYPE::CHARGE;
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
	lpEffectMng.AddEffectQue({ obj,obj._pos,0,EFFECT::FIRE,obj._zOrder + 1 });
}
