#pragma once
#include <DxLib.h>
#include <vector>
#include <map>
#include <object/PlNum.h>
#include <stdio.h>

enum class MES_TYPE
{
	NON,										// ����
	GAMEMODE,									// �ްъJ�n
	CONNECT,									// �ڑ�
	KEY,										// �����
	SYNC,										// �����pү����
	AGAIN,										// ү���ލđ��˗�
	MAX
};

// Connect���p
struct CONNECT_INF
{
	unsigned char type : 4;
	unsigned char plNum : 2;
};

// Key���p
struct KEY_INF
{
	unsigned char type : 4;
	unsigned char plNum : 2;					// Player���ʔԍ� 4�l�Ȃ̂�2bit
	unsigned char lf : 1;						// stick���͂����邩�ǂ���
	unsigned char a : 1;
	unsigned char b : 1;
	unsigned char y : 1;
	unsigned char lb : 1;
	unsigned char rb : 1;
	unsigned char lt : 1;
	unsigned char rt : 1;
	short ls;
	unsigned int num : 8;						// �����ʂ��ԍ�
};

// MES�����ߊm�F�p
struct TYPE_INF
{
	unsigned char type : 4;
};

// AGAIN���p
struct AGAIN_INF
{	unsigned char type : 4;

	unsigned char plNum : 2;
	unsigned int num : 8;
};

struct SYNC_INF
{
	unsigned char type : 4;
	unsigned char plnum : 2;
	unsigned int x : 13;
	unsigned int y : 12;
};

union MES
{
	// 8byte�̂͂�
	unsigned int data;											// ���M�p
	CONNECT_INF connect;										// �ڑ��m�F�p
	TYPE_INF check;												// MES_TYPE�m�F�p
	KEY_INF key;												// Key���m�F�p
	AGAIN_INF again;											// �đ��˗�
	SYNC_INF sync;												// �����pү����
};

#define MES_SIZE (sizeof(MES))


class NetWorkUnit
{
public:
	NetWorkUnit();
	virtual ~NetWorkUnit();
	virtual IPDATA ip(PlNum num) = 0;							// ip���ڽ�l��
	virtual PlNum GetPlNum(void) = 0;							// PlNum�l��

	virtual int netWorkHandle(PlNum num) = 0;					// netWorkHandle�l��
	virtual void Connect(void) = 0;								// ν�/�޽ĂƂ̐ڑ�
	virtual void RunMesList(void);								// ؽĂ��ް����M
	virtual void StartGame(void);								// �ްѽ���ү���ލ쐬�֐�
	virtual void Update(void) = 0;
	virtual bool GetData(void) = 0;								// Buf������ް��擾
	bool CheckSyncMes(PlNum num);								// ����ү���ޓ͂��Ă��邩
	bool DataSend(int handle, MES mes);							// �ް����M
	bool AddSendMesList(MES mes);								// ���M�p�ް��ǉ�
	bool AddRecMesList(MES mes);								// ��Mү����ؽ�
	void DeleteBackUpMes(void);									// ���ȏ��backupMes�폜
	void ReSetRecMes(void);										// ��Mү���ލ폜
	MES GetMes(PlNum num, MES_TYPE type);						// �w�肳�ꂽPlNum,type��ү���ގ擾
	MES GetMes(MES_TYPE type);									// �w�肳�ꂽtype��ү���ގ擾
	void GetKey(std::vector<MES>& buf, PlNum num);				// _recMesList����̷����̎��o��
	bool SetNetWorkHandle(int handle);							// _netWorkHandle�̐ݒ�
	const bool LinkFlag(void)const;								// �ڑ��ł��Ă��邩�m�F
protected:
	MES _mes;													// �󂯎��ү���ވꎞ�ۑ��p
	std::vector<MES> _sendMesList;								// ���Mү����ؽ�
	std::vector<MES> _recMesList;								// ��Mү����ؽ�
	PlNum _plNum;												// ���Ԗڂ���ڲ԰��
	std::map<PlNum,int> _netWorkHandle;							// NetWorkHandle�ۑ��p�ϐ�
	bool _linkFlag;												// �ڑ��ł������׸�
	std::map<PlNum, IPDATA> _ip;								// ip���ڽ
	int _port;													// �߰Ĕԍ�
	bool CheckData(PlNum plNum);								// ������PlNum��buf���ް������邩�����@�������ꍇ�͎��o��
};

