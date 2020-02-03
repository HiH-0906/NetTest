#include "Slime_Attack.h"
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <scene\SceneMng.h>
#include <EffectMng.h>
#include <EFFECT.h>

void Slime_Attack::operator()(Obj & obj, std::vector<sharedObj>& objList)
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
			(*target).DoDamage(obj._power);				// ﾀﾞﾒｰｼﾞをあたえる
		}
		else
		{
			obj._coolCnt--;								// ｸｰﾙﾀｲﾑ

			// ステータスを戻す
			if (obj._coolCnt <= 0)
			{
				StopEffekseer2DEffect(obj._effectID);
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

	_ofSet = { 0,(*target)._size.y / 2.0 };

	// ｴﾌｪｸﾄをｷｭｰに投げる
	lpEffectMng.AddEffectQue({ obj,(*target)._pos + _ofSet,0,EFFECT::AT_SLIME,(*target)._zOrder });
}
