#include <algorithm>
#include "EffectMng.h"
#include <EffekseerForDXLib.h>
#include <EFFECT.h>
#include "../scene/SceneMng.h"
#include"../Camera.h"
#include <_DebugConOut.h>

std::unique_ptr<EffectMng, EffectMng::EffectMngDeleter> EffectMng::sInstance(new EffectMng());

const int& EffectMng::GetID(EFFECT id)
{
	return GetID(id, "", 5.0f);
}

const int& EffectMng::GetID(EFFECT id, const std::string& key, float magnification)
{
	// ìoò^Ç≥ÇÍÇƒÇ¢ÇÈÇ©¡™Ø∏
	if (_effectMap.find(id) == _effectMap.end())
	{
		_effectMap[id] = LoadEffekseerEffect(key.c_str(), magnification);
	}
	return _effectMap[id];
}

bool EffectMng::AddEffectQue(EffectQueT eQue)
{
	_effectList.emplace_back(eQue);
	return true;
}

void EffectMng::Init(void)
{
	_effectScreen = MakeScreen(static_cast<int>(lpSceneMng.WorldSize.x), static_cast<int>(lpSceneMng.WorldSize.y), true);

	GetID(EFFECT::HEAL, "effect/heal.efk", 25.0F);
	GetID(EFFECT::AT_SLIME, "effect/slime.efk", 30.0F);
	GetID(EFFECT::AT_BITE, "effect/bite.efk", 15.0F);
	GetID(EFFECT::GHOST_CHARGE, "effect/charge.efk", 15.0F);
	GetID(EFFECT::GHOST_SHOT, "effect/shot.efk", 15.0F);
	GetID(EFFECT::GHOST_BLAST, "effect/blast.efk", 25.0F);
	GetID(EFFECT::INK, "effect/ink.efk", 20.0F);
	GetID(EFFECT::FIRE, "effect/fire.efk", 20.0F);
	GetID(EFFECT::DEMON_CHARGE, "effect/demon_charge.efk", 30.0F);
	GetID(EFFECT::DEMON_WAR, "effect/warning.efk", 40.0F);
	GetID(EFFECT::AT_BEE, "effect/spear.efk", 10.0F);
	GetID(EFFECT::SMOKE, "effect/smoke.efk", 20.0F);
}

void EffectMng::DrawFront(void)
{
	//sharedObj obj;
	//Vector2Dbl pos;
	//double rad;
	//int zOrder;

	// ¥Ã™∏ƒópΩ∏ÿ∞›Ç…êÿÇËë÷Ç¶
	SetDrawScreen(_effectScreen);

	for (auto data : _effectList)
	{
		ClsDrawScreen();

		// ¥Ã™∏ƒÇÃï`âÊ
		DrawEffekseer2D();

		SetDrawScreen(DX_SCREEN_BACK);
	}

	lpSceneMng.AddDrawQue({ _effectScreen,
							lpSceneMng.WorldCenter.x - lpCamera.OfSet().x ,
							lpSceneMng.WorldCenter.y - lpCamera.OfSet().y,
							0,
							1.0,
							0,
							LAYER::CHAR,
							DX_BLENDMODE_NOBLEND,
							255 });
}

void EffectMng::DrawBack(void)
{
	// ¥Ã™∏ƒópΩ∏ÿ∞›Ç…êÿÇËë÷Ç¶
	SetDrawScreen(_effectScreen);
	ClsDrawScreen();

	// ¥Ã™∏ƒÇÃï`âÊ
	DrawEffekseer2D();

	SetDrawScreen(DX_SCREEN_BACK);

	lpSceneMng.AddDrawQue({ _effectScreen,
							lpSceneMng.WorldCenter.x - lpCamera.OfSet().x ,
							lpSceneMng.WorldCenter.y - lpCamera.OfSet().y,
							0,
							1.0,
							0,
							LAYER::CHAR,
							DX_BLENDMODE_NOBLEND,
							255 });
}


EffectMng::EffectMng()
{
}


EffectMng::~EffectMng()
{
	// √ﬁÿ∞ƒ
	_effectMap.clear();
}
