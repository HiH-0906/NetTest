#include <DxLib.h>
#include "SoundMng.h"

const std::vector<int>& SoundMng::GetID(const SOUND & key)
{
	return GetID(key, "");
}

const std::vector<int>& SoundMng::GetID(const SOUND & key, const std::string & fileName)
{
	if (_soundMap.find(key) == _soundMap.end())
	{
		_soundMap[key].resize(1);
		_soundMap[key][0] = LoadSoundMem(fileName.c_str());
	}
	return _soundMap[key];
}

SoundMng::SoundMng()
{
}

SoundMng::~SoundMng()
{
}
