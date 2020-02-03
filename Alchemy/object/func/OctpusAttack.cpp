#include "OctpusAttack.h"
#include "BatAttack.h"
#include <DxLib.h>
#include <math.h>
#include <EffekseerForDXLib.h>
#include <scene\SceneMng.h>
#include <EffectMng.h>
#include <EFFECT.h>

void OctpusAttack::operator()(Obj & obj, std::vector<sharedObj>& objList)
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
	int _effectzOrder;									// ｾﾞｯﾄｵｰﾀﾞｰ
	Vector2Dbl _ofSet = { 0,0 };						// 座標のｵﾌｾｯﾄ

	// 再生ﾁｪｯｸ
	if (IsEffekseer2DEffectPlaying(obj._effectID) == -1)
	{
		if (!obj._effectFlg)
		{
			(*target).DoDamage(obj._power);				// ﾀﾞﾒｰｼﾞをあたえる
			_effectRad = atan2((*target).pos().y - obj._pos.y, (*target).pos().x - obj._pos.x);
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


	// ｵﾌｾｯﾄとｵｰﾀﾞｰの調整
	switch (obj._dir)
	{
	case DIR::UP:
		_effectzOrder = obj._zOrder - 1;
		_ofSet.y -= obj._size.y / 2.0;
		break;
	case DIR::LEFT:
		_effectzOrder = obj._zOrder;
		_ofSet.x -= obj._size.x / 2.0;
		break;
	case DIR::RIGHT:
		_effectzOrder = obj._zOrder;
		_ofSet.x = obj._size.x / 2.0;
		break;
	case DIR::DOWN:
		_effectzOrder = obj._zOrder;
		break;
	default:
		break;
	}

	// ステータスを戻す
	if (obj._coolCnt <= 0)
	{
		StopEffekseer2DEffect(obj._effectID);
		obj._coolCnt = obj._coolCntMax;
		obj.state(STATE::NORMAL);
		return;
	}

	// ｴﾌｪｸﾄをｷｭｰに投げる
	lpEffectMng.AddEffectQue({ obj,obj._pos + _ofSet,_effectRad,EFFECT::INK,_effectzOrder });
}
