#include "EffectMng.h"
#include <EffekseerForDXLib.h>
#include <EFFECT.h>
#include <_DebugConOut.h>

std::unique_ptr<EffectMng, EffectMng::EffectMngDeleter> EffectMng::sInstance(new EffectMng());

const int& EffectMng::GetID(EFFECT id)
{
	return GetID(id, "", 5.0f);
}

const int& EffectMng::GetID(EFFECT id, const std::string& key, float magnification)
{
	// “o˜^‚³‚ê‚Ä‚¢‚é‚©Áª¯¸
	if (_effectMap.find(id) == _effectMap.end())
	{
		_effectMap[id] = LoadEffekseerEffect(key.c_str(), magnification);
	}
	return _effectMap[id];
}

const std::vector<int> & EffectMng::hundle(void) const
{
	return _hundleList;
}

void EffectMng::AddHundle(int& id)
{
	_hundleList.emplace_back(id);
}

EffectMng::EffectMng()
{

}


EffectMng::~EffectMng()
{
	// ÃÞØ°Ä
	_effectMap.clear();
}
