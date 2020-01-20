#pragma once
#include <memory>
#include <vector>
#include <map>
#include <EFFECT.h>

#define lpEffectMng EffectMng::GetInstance()
#define EFFECT_ID(KEY) EffectMng::GetInstance().GetID(KEY)

class EffectMng
{
public:
	static EffectMng& GetInstance(void)
	{
		return *sInstance;
	}

	const int& GetID(EFFECT id);													// �擾
	const int& GetID(EFFECT id, const std::string& key, float magnification);		// �o�^
	void AddHundle(int& id);														// �ǉ�
	const std::vector<int>& hundle(void) const;
private:
	// ������ذ��
	struct EffectMngDeleter
	{
		void operator ()(EffectMng* EffectMng)
		{
			delete EffectMng;
		}
	};

	static std::unique_ptr<EffectMng, EffectMngDeleter> sInstance;

	std::map<EFFECT,int> _effectMap;					// �o�^�p
	int _hundle;
	int _oldhundle;
	std::vector<int>_hundleList;						// �Đ��׸ޕۑ��p
	EffectMng();
	~EffectMng();
};

