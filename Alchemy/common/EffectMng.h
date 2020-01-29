#pragma once
#include <memory>
#include <vector>
#include <map>
#include <Vector2.h>
#include <object/Obj.h>
#include <EFFECT.h>
#include "../scene/SceneMng.h"
#include "../scene/LAYER.h"

#define lpEffectMng EffectMng::GetInstance()
#define EFFECT_ID(KEY) EffectMng::GetInstance().GetID(KEY)

enum class EFFECT_QUE
{
	OBJ,		// ©•ª‚ªÄ¶‚µ‚Ä‚¢‚é´Ìª¸Ä‚ğ•Û‘¶‚µ‚½‚¢
	POS,
	RAD,		// Šp“x
	ZORDER		// •`‰æ—Dæ“x
};

using EffectQueT = std::tuple <sharedObj, Vector2Dbl, double, int>;						// <©•ª‚Ìî•ñAÀ•WAŠp“xA•`‰æ—Dæ“x>

class EffectMng
{
public:
	static EffectMng& GetInstance(void)
	{
		return *sInstance;
	}

	const int& GetID(EFFECT id);													// æ“¾
	const int& GetID(EFFECT id, const std::string& key, float magnification);		// “o˜^
	bool AddEffectQue(EffectQueT eQue);												// ´Ìª¸Ä·­°‚Ì’Ç‰Á
	void DrawFront(void);																// •`‰æ
	void DrawBack(void);
	void Init(void);
private:
	// ¶½ÀÑÃŞØ°À°
	struct EffectMngDeleter
	{
		void operator ()(EffectMng* EffectMng)
		{
			delete EffectMng;
		}
	};

	static std::unique_ptr<EffectMng, EffectMngDeleter> sInstance;

	std::map<EFFECT,int> _effectMap;					// “o˜^—p
	int _effectScreen;									// ´Ìª¸Ä—p½¸Ø°İ
	std::vector<EffectQueT> _effectList;				// ´Ìª¸Ä·­°‚ÌŠÇ—”z—ñ
	EffectMng();
	~EffectMng();
};

