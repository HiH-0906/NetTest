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
	MATCH,										// ����
	KEY,										// �����
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
	unsigned char lf : 1;
	unsigned char a : 1;
	unsigned char b : 1;
	unsigned char y : 1;
	short ls;
	// ���v32bit 4byte
};

// Match���p
struct MATCH_INF
{
	unsigned char type : 4;
	unsigned short x : 13;
	unsigned short y : 12;
	// ���v32bit 6byte
};

// MES�����ߊm�F�p
struct TYPE_INF
{
	unsigned char type : 4;
	// ���v4bit
};

union MES
{
	// 8byte�̂͂�
	unsigned int data;											// ���M�p
	CONNECT_INF connect;								// �ڑ��m�F�p
	TYPE_INF check;										// MES_TYPE�m�F�p
	KEY_INF key;										// Key���m�F�p
	MATCH_INF match;									// �������m�F�p
};

#define MES_SIZE (sizeof(MES))

class NetWorkUnit
{
public:
	NetWorkUnit();
	virtual ~NetWorkUnit();
	virtual IPDATA ip(PlNum num) = 0;					// ip���ڽ�l��
	virtual PlNum GetPlNum(void) = 0;					// PlNum�l��
	virtual int netWorkHandle(PlNum num) = 0;			// netWorkHandle�l��
	virtual void Connect(void) = 0;						// ν�/�޽ĂƂ̐ڑ�
	virtual void RunMesList(void);						// ؽĂ��ް����M
	virtual void StartGame(void);							// �ްѽ���ү���ލ쐬�֐�
	virtual void Update(void) = 0;
	virtual bool GetData(void);							// Buf������ް��擾
	bool DataSend(int handle, int mes);					// �ް����M
	bool AddSendMesList(MES mes);						// ���M�p�ް��ǉ�
	bool AddRecMesList(MES mes);						// ��Mү����ؽ�
	void ReSetRecMes(void);								// ��Mү���ލ폜
	MES GetMes(PlNum num,MES_TYPE type);				// �w�肳�ꂽPlNum,type��ү���ގ擾
	bool SetnetWorkHandle(int handle);
	bool LinkFlag(bool flag);
	const bool LinkFlag(void)const;
protected:
	MES _mes;											// �󂯎��ү���ވꎞ�ۑ��p
	std::vector<int> _sendMesList;						// ���Mү����ؽ�
	std::vector<MES> _recMesList;						// ��Mү����ؽ�
	PlNum _plNum;										// ���Ԗڂ���ڲ԰��
	std::map<PlNum,int> _netWorkHandle;					// NetWorkHandle�ۑ��p�ϐ�
	bool _startFlag;									// �ްъJ�n�׸�
	bool _linkFlag;										// �ڑ��ł������׸�
	std::map<PlNum, IPDATA> _ip;						// ip���ڽ
	int _port;											// �߰Ĕԍ�
	bool CheckData(PlNum plNum);						// buf���ް������邩�����@�������ꍇ�͎��o��
};

