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
	auto target = obj.tageObj().lock();		// ターゲットの情報格納

	if (!obj._effectFlg)
	{
		// 再生します
		obj._effectID = PlayEffekseer2DEffect(EFFECT_ID(EFFECT::DEMON_CHARGE));
		_warning = PlayEffekseer2DEffect(EFFECT_ID(EFFECT::DEMON_WAR));
		// ﾁｪｯｸ
		if (IsEffekseer2DEffectPlaying(obj._effectID) == 0 && IsEffekseer2DEffectPlaying(_warning) == 0)
		{
			obj._effectFlg = true;
		}
		else
		{
			return;
		}
	}
	else
	{
		_chargeCnt++;
		if (_chargeCnt >= 120)				// ｴﾌｪｸﾄが終わってからだと少しラグがあるのでｶｳﾝﾄで管理した
		{
			StopEffekseer2DEffect(_warning);
			StopEffekseer2DEffect(obj._effectID);
			_move = MOVE_TYPE::BLAST;
			_chargeCnt = 0;
			obj._effectFlg = false;
		}
		else if (_chargeCnt % 60 == 0)		// もう一回
		{
			StopEffekseer2DEffect(_warning);
			_warning = PlayEffekseer2DEffect(EFFECT_ID(EFFECT::DEMON_WAR));
		}
	}

	// エフェクトの座標指定
	SetPosPlayingEffekseer2DEffect(obj._effectID,
		static_cast<float>(obj._pos.x),
		static_cast<float>(obj._pos.y),
		0);
	SetPosPlayingEffekseer2DEffect(_warning,
		static_cast<float>(obj._pos.x),
		static_cast<float>(obj._pos.y),
		0);
}

void DemonAttack::Blast(Obj & obj, std::vector<sharedObj>& objList)
{
	auto target = obj.tageObj().lock();					// ターゲットの情報格納

	if (!obj._effectFlg)
	{
		// 再生します
		obj._effectID = PlayEffekseer2DEffect(EFFECT_ID(EFFECT::FIRE));

		// ﾁｪｯｸ
		if (IsEffekseer2DEffectPlaying(obj._effectID) == 0)
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
					if ((obj._attackRange * obj._attackRange) > LengthSquare(obj._pos, (*list)._pos))
					{
						(*list).DoDamage(obj._power);		// enemyのpowerを引数にしてね
					}
					else
					{
						break;
					}
				}
			}
			obj._effectFlg = true;
		}
		else
		{
			return;
		}
	}
	else
	{
		// 再生が終わっていたらクールタイム
		if (IsEffekseer2DEffectPlaying(obj._effectID) == -1)
		{
			obj._coolCnt--;
		}
	}

	SetPosPlayingEffekseer2DEffect(obj._effectID,
		static_cast<float>(obj._pos.x),
		static_cast<float>(obj._pos.y),
		0);

	// 終了
	if (obj._coolCnt <= 0)
	{
		StopEffekseer2DEffect(obj._effectID);
		obj._effectFlg = false;
		obj._coolCnt = obj._coolCntMax;
		_move = MOVE_TYPE::CHARGE;
		obj.state(STATE::NORMAL);
	}
}
