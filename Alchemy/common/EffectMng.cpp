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

void EffectMng::Clear(void)
{
	_effectList.clear();
}

void EffectMng::Draw(void)
{

	// ¥Ã™∏ƒópΩ∏ÿ∞›Ç…êÿÇËë÷Ç¶
	for (auto data : _effectList)
	{
		Obj& obj = std::get<(int)EFFECT_QUE::OBJ>(data);
		Vector2Dbl pos;
		double rad;
		EFFECT playID;
		int zOrder;
		std::tie(std::ignore, pos, rad, playID, zOrder) = data;

		SetDrawScreen(obj._effectScreen);
		ClsDrawScreen();

		if (obj._effectFlg)
		{
			if (IsEffekseer2DEffectPlaying(obj._effectID) == -1)
			{
				obj._effectFlg = false;
				obj._effectID = PlayEffekseer2DEffect(EFFECT_ID(playID));
			}
		}

		// ¥Ã™∏ƒÇÃç¿ïWéwíË
		SetPosPlayingEffekseer2DEffect(obj._effectID,
			static_cast<float>(_screenSize.x / 2),
			static_cast<float>(_screenSize.y / 2),
			0);

		// ¥Ã™∏ƒÇÃäpìxéwíË
		SetRotationPlayingEffekseer2DEffect(obj._effectID, 0, 0, static_cast<float>(rad));

		// ¥Ã™∏ƒÇÃï`âÊ
		DrawEffekseer2D_Begin();
		DrawEffekseer2D_Draw(obj._effectID);
		DrawEffekseer2D_End();

		lpSceneMng.AddDrawQue({ obj._effectScreen,
						pos.x - lpCamera.OfSet().x ,
						pos.y - lpCamera.OfSet().y,
						0,
						1.0,
						0.0,
						zOrder,
						LAYER::CHAR,
						DX_BLENDMODE_NOBLEND,
						255 });
	}
}

EffectMng::EffectMng():	_screenSize{ 500.0,500.0 }
{
}


EffectMng::~EffectMng()
{
	// √ﬁÿ∞ƒ
	_effectMap.clear();
}
