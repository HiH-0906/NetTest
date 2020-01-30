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
	OBJ,			// ©•ª‚ªÄ¶‚µ‚Ä‚¢‚é´Ìª¸Ä‚ğ•Û‘¶‚µ‚½‚¢
	POS,
	RAD,			// Šp“x
	PLAY_ID,
	ZORDER			// •`‰æ—Dæ“x
};

using EffectQueT = std::tuple <Obj&, Vector2Dbl, double, EFFECT, int>;			// <´Ìª¸ÄIDAÀ•WAŠp“xAÄ¶‚µ‚½‚¢´Ìª¸ÄA•`‰æ—Dæ“x>

class EffectMng
{
public:
	static EffectMng& GetInstance(void)
	{
		return *sInstance;
	}

	const int& GetID(EFFECT id);												// æ“¾
	const int& GetID(EFFECT id, const std::string& key, float magnification);	// “o˜^
	bool AddEffectQue(EffectQueT eQue);											// ´Ìª¸Ä·­°‚Ì’Ç‰Á
	void Draw(void);															// •`‰æ
	void Init(void);
	void Clear(void);

	const Vector2Dbl _screenSize;												// ´Ìª¸Ä‚Ì½¸Ø°İ»²½Ş
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

	std::map<EFFECT,int> _effectMap;						// “o˜^—p
	std::vector<EffectQueT> _effectList;					// ´Ìª¸Ä·­°‚ÌŠÇ—”z—ñ
	EffectMng();
	~EffectMng();
};

