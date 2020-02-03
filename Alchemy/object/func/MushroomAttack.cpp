#include "MushroomAttack.h"
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <scene\SceneMng.h>
#include <EffectMng.h>
#include <EFFECT.h>

void MushroomAttack::operator()(Obj & obj, std::vector<sharedObj>& objList)
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

	auto target = obj.tageObj().lock();							// ターゲットの情報格納
	Vector2Dbl _ofSet;											// ｵﾌｾｯﾄ
	Vector2Dbl _effectPos;										// 攻撃か回復で渡す座標が違う


	// 再生ﾁｪｯｸ
	if (IsEffekseer2DEffectPlaying(obj._effectID) == -1)
	{
		if (!obj._effectFlg)
		{

			// ﾀｰｹﾞｯﾄが敵か味方かで変わる
			if ((*target).teamTag() == TEAM_TAG::ENEMY_TEAM)
			{
				(*target).DoDamage(-obj._power);				// 回復
				_id = EFFECT::HEAL;
				_effectRad = 0;
			}
			else if ((*target).teamTag() == TEAM_TAG::ALLY_TEAM)
			{
				(*target).DoDamage(obj._power);					// ﾀﾞﾒｰｼﾞをあたえる
				_id = EFFECT::SMOKE;
				_effectRad = atan2((*target).pos().y - obj._pos.y, (*target).pos().x - obj._pos.x);
			}
		}
		else
		{
			obj._coolCnt--;										// ｸｰﾙﾀｲﾑ

			// ステータスを戻す
			if (obj._coolCnt <= 0)
			{
				StopEffekseer2DEffect(obj._effectID);
				obj._coolCnt = obj._coolCntMax;
				obj._effectFlg = false;
				obj.state(STATE::NORMAL);
				return;
			}
			return;												// 攻撃が終わってるから処理はここまで
		}
	}
	else
	{
		obj._effectFlg = true;
	}

	// ｷｭｰに必要な変数の設定
	if (_id == EFFECT::HEAL)
	{
		_effectPos = (*target)._pos;
		_ofSet = { 0,(*target)._size.y / 2.0 };						// 足元からｴﾌｪｸﾄ出てほしい

	}
	else if (_id == EFFECT::SMOKE)
	{
		_effectPos = obj._pos;
		_ofSet = { 0,0 };
	}


	// ｴﾌｪｸﾄをｷｭｰに投げる
	lpEffectMng.AddEffectQue({ obj,_effectPos + _ofSet,_effectRad,_id,(*target)._zOrder + 1});
}
