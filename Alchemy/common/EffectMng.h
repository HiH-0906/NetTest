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
	OBJ,		// �������Đ����Ă���̪�Ă�ۑ�������
	POS,
	RAD,		// �p�x
	ZORDER		// �`��D��x
};

using EffectQueT = std::tuple <sharedObj, Vector2Dbl, double, int>;						// <�����̏��A���W�A�p�x�A�`��D��x>

class EffectMng
{
public:
	static EffectMng& GetInstance(void)
	{
		return *sInstance;
	}

	const int& GetID(EFFECT id);													// �擾
	const int& GetID(EFFECT id, const std::string& key, float magnification);		// �o�^
	bool AddEffectQue(EffectQueT eQue);												// �̪�ķ���̒ǉ�
	void DrawFront(void);																// �`��
	void DrawBack(void);
	void Init(void);
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
	int _effectScreen;									// �̪�ėp��ذ�
	std::vector<EffectQueT> _effectList;				// �̪�ķ���̊Ǘ��z��
	EffectMng();
	~EffectMng();
};

