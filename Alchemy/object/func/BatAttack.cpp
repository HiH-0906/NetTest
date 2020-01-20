#include "BatAttack.h"
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <scene\SceneMng.h>
#include <EffectMng.h>
#include <Camera.h>
#include <EFFECT.h>

void BatAttack::operator()(Obj & obj, std::vector<sharedObj>& objList)
{
	// ÉäÉìÉNêÿÇÍ
	if (obj.tageObj().expired())
	{
		StopEffekseer2DEffect(obj._effectID);
		//(*target)._hp -= 2;
		obj._effectFlg = false;
		obj.state(STATE::NORMAL);
		return;
	}

	auto target = obj.tageObj().lock();
	
	if (!obj._effectFlg)
	{
		obj._effectID = PlayEffekseer2DEffect(EFFECT_ID(EFFECT::ATTACK_BITE));

		if (IsEffekseer2DEffectPlaying(obj._effectID) == 0)
		{

			lpSceneMng.AddEffectQue({ obj._effectID ,
							(*target).pos().x - lpCamera.OfSet().x,
							(*target).pos().y - lpCamera.OfSet().y,
							100,LAYER::CHAR });

			obj._effectFlg = true;
		}
	}
	else
	{
		if (IsEffekseer2DEffectPlaying(obj._effectID) == -1)
		{
			StopEffekseer2DEffect(obj._effectID);
			(*target)._hp -= 2;
			obj._effectFlg = false;
			obj.state(STATE::NORMAL);
		}
	}
}
