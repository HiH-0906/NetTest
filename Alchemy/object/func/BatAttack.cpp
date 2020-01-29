#include "BatAttack.h"
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <scene\SceneMng.h>
#include <EffectMng.h>
#include <EFFECT.h>

void BatAttack::operator()(Obj & obj, std::vector<sharedObj>& objList)
{
	// リンク切れ
	if (obj.tageObj().expired())
	{
		StopEffekseer2DEffect(obj._effectID);
		obj._effectFlg = false;
		obj.state(STATE::NORMAL);
		return;
	}

	auto target = obj.tageObj().lock();		// ターゲットの情報格納
	
	if (!obj._effectFlg)
	{
		// 再生します
		obj._effectID = PlayEffekseer2DEffect(EFFECT_ID(EFFECT::AT_BITE));

		// ﾁｪｯｸ
		if (IsEffekseer2DEffectPlaying(obj._effectID) == 0)
		{
			(*target).DoDamage(obj._power);		// enemyのpowerを引数にしてね
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

	// エフェクトの座標指定
	SetPosPlayingEffekseer2DEffect(obj._effectID,
									static_cast<float>((*target).pos().x),
									static_cast<float>((*target).pos().y + 10),
									0);

	// 終了
	if (obj._coolCnt <= 0)
	{
		StopEffekseer2DEffect(obj._effectID);
		obj._effectFlg = false;
		obj._coolCnt = obj._coolCntMax;
		obj.state(STATE::NORMAL);
	}

}
