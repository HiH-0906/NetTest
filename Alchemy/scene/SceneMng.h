#pragma once
#include <map>
#include <memory>
#include <tuple>
#include <vector>
#include <Vector2.h>
#include "BaseScene.h"
#include "LAYER.h"
#include<object/PlNum.h>

class SceneMng;

#define lpSceneMng SceneMng::GetInstance()

enum class DRAW_QUE
{
	IMAGE,
	X,
	Y,
	RAD,
	ZORDER,
	LAYER
};

enum class EFFECT_QUE
{
	EFFECT,
	X,
	Y,
	ZORDER,
	LAYER
};

enum class SOUND_QUE
{
	SOUND,
	LOOP,
	VOL,
};

enum class PLAYER_QUE
{
	PLNUM,
	POS,
	PADNUM
};


using DrawQueT = std::tuple<int, double, double, double, int, LAYER,int,int>;
using EffectQueT = std::tuple<int, double, double, int, LAYER>; 
using SoundQueT = std::tuple<int, bool, int>;
using PlayerQueT = std::tuple <PlNum, Vector2Dbl, int >;						// <��ڲ԰�ԍ��A���W�APAD�ԍ�>

class SceneMng
{
public:
	static SceneMng& GetInstance(void)
	{
		return *sInstance;
	}

	void Run(void);										// �ް�ٰ��

	bool AddDrawQue(DrawQueT dQue);						// �`�淭��̒ǉ�
	bool AddEffectQue(EffectQueT eQue);					// �̪�ķ���̒ǉ�
	bool AddActQue(ActQueT aQue);						// ����ݷ���̒ǉ�
	bool AddSoundQue(SoundQueT sQue);					// ����޷���̒ǉ�
	bool AddPlayerQue(PlayerQueT pQue);					// ��ڲ԰����̒ǉ�
	bool AddInstanceQue(InstanceQueT iQue);				// �ݽ�ݽ����̒ǉ�
	bool SetInstanceQue(InstanceQueT iQue);				// �ݽ�ݽ����̒ǉ�

	const size_t GetPlayerListSize(void)const;			// ��ڲ԰����̻��ގ擾
	std::vector<PlayerQueT>& playerList(void);			// ��ڲ԰����擾

	void FlameCntReset(void);
	const int flameCnt(void)const;
	int serialNumCnt(void);
	void AddSerialNum(void);							// �ʂ��ԍ����C���N�������g
	
	const Vector2Dbl ScreenSize;
	const Vector2Dbl WorldSize;							// ���E����
	const Vector2Dbl ScreenCenter;						// ��ʒ���
	const Vector2Dbl WorldCenter;
	

private:
	struct SceneMngDeleter
	{
		void operator()(SceneMng* sceneMng)const
		{
			delete sceneMng;
		}
	};

	SceneMng();
	~SceneMng();


	static std::unique_ptr<SceneMng, SceneMngDeleter> sInstance;

	void Draw(void);
	bool SysInit(void);

	int _layerGID;							// �`��p��ذ�
	int _flameCnt;							// �ڰѶ���
	int _serialNumCnt;						// �ʂ��ԍ��Ǘ��ϐ�

	std::map<LAYER, int> _screenID;

	std::vector<DrawQueT> _drawList;		// �`�淭��̊Ǘ��z��
	std::vector<EffectQueT> _effectList;	// �̪�ķ���̊Ǘ��z��
	std::vector<ActQueT> _actList;			// ����ݷ���̊Ǘ��z��
	std::vector<SoundQueT> _soundList;		// ����޷���̊Ǘ��z��
	std::vector<PlayerQueT> _playerList;	// ��ڲ԰����̊Ǘ��z��
	std::vector<InstanceQueT> _instanceList;// �ݽ�ݽ����̊Ǘ��z��

	UniqueBase _activeScene;
};

