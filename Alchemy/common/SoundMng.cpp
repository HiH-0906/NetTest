#include <DxLib.h>
#include "SoundMng.h"

std::unique_ptr<SoundMng, SoundMng::SoundMngDeleter> SoundMng::_sInstance(new SoundMng());

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

const std::vector<int>& SoundMng::GetID(const SOUND & key, const std::string & fileName, const int num)
{
	if (_soundMap.find(key) == _soundMap.end())
	{
		_soundMap[key].resize(1);
		_soundMap[key][0] = LoadSoundMem(fileName.c_str());
	}
	else
	{
		_soundMap[key].resize(num);
		_soundMap[key].emplace_back(LoadSoundMem(fileName.c_str()));
	}
	return _soundMap[key];
}

SoundMng::SoundMng()
{
}

SoundMng::~SoundMng()
{
}
