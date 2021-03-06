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
	auto target = obj.tageObj().lock();								// ターゲットの情報格納

	// ｶｳﾝﾄで発射
	if (_endCnt >= 75)
	{
		StopEffekseer2DEffect(obj._effectID);
		_endCnt = 0;
		_shotPos = obj._pos;										// 弾の初期座標
		_move = MOVE_TYPE::SHOT;
		return;
	}

	if (IsEffekseer2DEffectPlaying(obj._effectID) == 0)
	{
		_endCnt++;
	}

	// ｴﾌｪｸﾄをｷｭｰに投げる
	lpEffectMng.AddEffectQue({ obj, obj._pos,0, EFFECT::GHOST_CHARGE, obj._zOrder + 1});
}

void GhostAttack::Shot(Obj & obj)
{
	auto target = obj.tageObj().lock();								// ﾀｰｹﾞｯﾄの情報格納

	if (IsEffekseer2DEffectPlaying(obj._effectID) == -1)
	{
		_shotPos = obj._pos;										// 弾の初期座標
	}
	else
	{
		// 当たったら爆発してほしい
		if (IsHitObj(_shotPos, (*target)._pos, (*target)._size))
		{
			StopEffekseer2DEffect(obj._effectID);
			_endCnt = 0;
			_move = MOVE_TYPE::BLAST;
			return;
		}

		_shotPos += ((*target)._pos - obj._pos) / 30.0;				// 移動
		_endCnt++;
	}

	// 攻撃中断
	if (_endCnt >= 60)
	{
		StopEffekseer2DEffect(obj._effectID);
		_move = MOVE_TYPE::CHARGE;
		_endCnt = 0;
		obj.state(STATE::NORMAL);
		return;
	}

	// ｴﾌｪｸﾄをｷｭｰに投げる
	lpEffectMng.AddEffectQue({ obj, _shotPos, 0, EFFECT::GHOST_SHOT, (*target)._zOrder + 1 });
}

void GhostAttack::Blast(Obj & obj)
{
	auto target = obj.tageObj().lock();								// ﾀｰｹﾞｯﾄの情報格納

	// 再生ﾁｪｯｸ
	if (IsEffekseer2DEffectPlaying(obj._effectID) == -1)
	{
		if (!obj._effectFlg)
		{
			(*target).DoDamage(obj._power);				// ﾀﾞﾒｰｼﾞをあたえる
		}
		else
		{
			obj._coolCnt--;								// ｸｰﾙﾀｲﾑ

			// ステータスを戻す
			if (obj._coolCnt <= 0)
			{
				StopEffekseer2DEffect(obj._effectID);
				obj._effectFlg = false;
				_move = MOVE_TYPE::CHARGE;
				obj._coolCnt = obj._coolCntMax;
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
	lpEffectMng.AddEffectQue({ obj, (*target)._pos, 0, EFFECT::GHOST_BLAST, (*target)._zOrder + 1 });
}

bool GhostAttack::IsHitObj(Vector2Dbl shot, Vector2Dbl targetPos, Vector2Int targetSize)
{
	Vector2Dbl lenght = { targetPos.x - shot.x, targetPos.y - shot.y };

	if (sqrt(lenght.x * lenght.x + lenght.y * lenght.y) < sqrt(targetSize.x) &&
		sqrt(lenght.x * lenght.x + lenght.y * lenght.y) < sqrt(targetSize.y))
	{
		return true;
	}

	return false;
}
