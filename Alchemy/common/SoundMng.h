#pragma once
#include <memory>
#include <map>
#include <vector>

enum class SOUND
{
	BGM,
	SE,
};

#define lpSoundMng 

class SoundMng
{
public:
	// �ݽ�׸�
	static SoundMng & GetInstance(void)
	{
		return *_sInstance;
	}

	const std::vector<int>& GetID(const SOUND& key);
	const std::vector<int>& GetID(const SOUND& key, const std::string& fileName);

private:
	struct SoundMngDeleter
	{
		void operator()(SoundMng* soundMng) const
		{
			delete soundMng;
		}
	};
	SoundMng();
	~SoundMng();

	static std::unique_ptr<SoundMng, SoundMngDeleter> _sInstance;

	// ����ޏ����Ǘ����Ă���ϯ��
	std::map<SOUND, std::vector<int>> _soundMap;
};

