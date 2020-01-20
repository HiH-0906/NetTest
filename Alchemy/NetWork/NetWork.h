#pragma once
#include <DxLib.h>
#include <vector>
#include <map>
#include <memory>
#include <_debug/_DebugConOut.h>
#include <scene/SceneMng.h>
#include <object/PlNum.h>
#include "../Input/InputState.h"
#include "NetWorkUnit.h"

enum class NETMODE
{
	OFFLINE,			// ��ײ�
	HOST,				// νď��
	GUEST,				// �ײ��ď��
	MAX
};


#define lpNetWork NetWork::GetInstans()
#define MATCH_TIME 30


class NetWork
{
public:
	static NetWork &GetInstans(void)
	{
		return *sInstans;
	}

	bool NetMode(NETMODE mode);
	const NETMODE NetMode(void);
	bool Active(void);									// �ڑ��m�����Ă��邩
	void Connect(void);									// �ڑ������ɍs��
	void UpDate(void);									// �ڑ�������͂�����񂵂Ă�΂����͂�
	void ReSetRecMes(void);								// ��Mү���ލ폜
	MES GetMes(PlNum num,MES_TYPE type);				// �w�肳�ꂽPlNum,type��ү���ގ擾
	PlNum GetPlNum(void);								// ���݂̎�����PlNum�擾
	void MakeKeyMes(KeyMap butan, StickState& stick);	// Key�������ү���މ�
	void MakeMatchMes(Vector2Dbl& pos);					// �ʒu���ү���މ�
private:
	struct NetWorkDeleter
	{
		void operator()(NetWork* netWork)const
		{
			delete netWork;
		}
	};
	static std::unique_ptr<NetWork, NetWorkDeleter> sInstans;
	NetWork();
	virtual ~NetWork();
	int _matchTime;										// �����̂��߂̶���
	MES _tmpMes;										// �󂯎��MES�ꎞ�ۑ��p
	NETMODE _netMode;									// ȯ�ܰ���Ӱ�� host��Guest��
	std::unique_ptr<NetWorkUnit> _netWorkUnit;			// �ư��߲��
};

