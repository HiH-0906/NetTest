#include "GhostAttack.h"
#include <cmath>
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <_DebugConOut.h>
#include <scene\SceneMng.h>
#include <EffectMng.h>
#include <EFFECT.h>

void GhostAttack::operator()(Obj & obj, std::vector<sharedObj>& objList)
{
	// リンク切れ
	if (obj.tageObj().expired())
	{
		TRACE("attackの対象が消えました")
		StopEffekseer2DEffect(obj._effectID);
		obj._effectFlg = false;
		_move = MOVE_TYPE::CHARGE;
		obj.state(STATE::NORMAL);
		return;
	}
	
	switch (_move)
	{
	case MOVE_TYPE::CHARGE:
		Charge(obj);
		break;
	case MOVE_TYPE::SHOT:
		Shot(obj);
		break;
	case MOVE_TYPE::BLAST:
		Blast(obj);
		break;
	default:
		AST();
		break;
	}

}

void GhostAttack::Charge(Obj & obj)
{
	auto target = obj.tageObj().lock();		// ターゲットの情報格納

	if (!obj._effectFlg)
	{
		// 再生します
		obj._effectID = PlayEffekseer2DEffect(EFFECT_ID(EFFECT::GHOST_CHARGE));

		// ﾁｪｯｸ
		if (IsEffekseer2DEffectPlaying(obj._effectID) == 0)
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
		// ｶｳﾝﾄで発射
		if (_endCnt >= 60)
		{
			StopEffekseer2DEffect(obj._effectID);
			obj._effectFlg = false;
			_endCnt = 0;
			_move = MOVE_TYPE::SHOT;
		}
		_endCnt++;
	}

	// エフェクトの座標指定
	SetPosPlayingEffekseer2DEffect(obj._effectID,
		static_cast<float>(obj._pos.x),
		static_cast<float>(obj._pos.y),
		0);
}

void GhostAttack::Shot(Obj & obj)
{
	auto target = obj.tageObj().lock();								// ﾀｰｹﾞｯﾄの情報格納

	if (!obj._effectFlg)
	{
		// 再生します
		obj._effectID = PlayEffekseer2DEffect(EFFECT_ID(EFFECT::GHOST_SHOT));

		// 再生されていたら
		if (IsEffekseer2DEffectPlaying(obj._effectID) == 0)
		{
			_shotPos = obj._pos;									// 弾の初期座標
			obj._effectFlg = true;
		}
	}
	else
	{
		// 当たったら爆発してほしい
		if (IsHitObj(_shotPos, (*target)._pos, (*target)._size))
		{
			StopEffekseer2DEffect(obj._effectID);
			_move = MOVE_TYPE::BLAST;
			obj._effectFlg = false;
		}

		// 攻撃中断
		if (_endCnt >= MAX_CNT)
		{
			StopEffekseer2DEffect(obj._effectID);
			_move = MOVE_TYPE::CHARGE;
			obj._effectFlg = false;
			_endCnt = 0;
			obj.state(STATE::NORMAL);
		}
		_shotPos += ((*target)._pos - obj._pos) / 30.0;		// 移動

		_endCnt++;
	}

	// エフェクトの座標指定
	SetPosPlayingEffekseer2DEffect(obj._effectID,
		static_cast<float>(_shotPos.x),
		static_cast<float>(_shotPos.y),
		0);
}

void GhostAttack::Blast(Obj & obj)
{
	auto target = obj.tageObj().lock();						// ﾀｰｹﾞｯﾄの情報格納

	if (!obj._effectFlg)
	{
		// 再生します
		obj._effectID = PlayEffekseer2DEffect(EFFECT_ID(EFFECT::GHOST_BLAST));

		// 再生されていたら
		if (IsEffekseer2DEffectPlaying(obj._effectID) == 0)
		{
			(*target).DoDamage(obj._power);					// ﾀﾞﾒｰｼﾞ
			obj._effectFlg = true;
		}
	}
	else
	{
		// 再生が終わったらｽﾃｰﾄ変更
		if (IsEffekseer2DEffectPlaying(obj._effectID) == -1)
		{
			StopEffekseer2DEffect(obj._effectID);
			obj._effectFlg = false;
			_move = MOVE_TYPE::CHARGE;
			obj.state(STATE::NORMAL);
		}
	}

	// エフェクトの座標指定
	SetPosPlayingEffekseer2DEffect(obj._effectID,
		static_cast<float>((*target)._pos.x),
		static_cast<float>((*target)._pos.y),
		0);
}

bool GhostAttack::IsHitObj(Vector2Dbl shot, Vector2Dbl targetPos, Vector2Int targetSize)
{
	Vector2Dbl lenght = { targetPos.x - shot.x, targetPos.y - shot.y };

	if (sqrt(lenght.x * lenght.x + lenght.y * lenght.y) < sqrt(targetSize.x - 1.0) &&
		sqrt(lenght.x * lenght.x + lenght.y * lenght.y) < sqrt(targetSize.y - 1.0))
	{
		return true;
	}

	return false;
}
