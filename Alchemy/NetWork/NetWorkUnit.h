#pragma once
#include <DxLib.h>
#include <vector>
#include <map>
#include <object/PlNum.h>
#include <stdio.h>

enum class MES_TYPE
{
	NON,										// 無し
	GAMEMODE,									// ｹﾞｰﾑ開始
	CONNECT,									// 接続
	MATCH,										// 同期
	KEY,										// ｷｰ情報
	MAX
};

// Connect情報用
struct CONNECT_INF
{
	unsigned char type : 4;
	unsigned char plNum : 2;
};

// Key情報用
struct KEY_INF
{
	unsigned char type : 4;
	unsigned char num;							// ｷｰ情報通し番号
	unsigned char plNum : 2;					// Player識別番号 4人なので2bit
	unsigned char lf : 1;						// stick入力があるかどうか
	unsigned char a : 1;
	unsigned char b : 1;
	unsigned char y : 1;
	short ls;
	// 合計32bit 4byte
};

// Match情報用
struct MATCH_INF
{
	unsigned char type : 4;
	unsigned short x : 13;
	unsigned short y : 12;
	// 合計32bit 6byte
};

// MESのﾀｲﾌﾟ確認用
struct TYPE_INF
{
	unsigned char type : 4;
	// 合計4bit
};

union MES
{
	// 8byteのはず
	unsigned int data;									// 送信用
	CONNECT_INF connect;								// 接続確認用
	TYPE_INF check;										// MES_TYPE確認用
	KEY_INF key;										// Key情報確認用
	MATCH_INF match;									// 同期情報確認用
};

#define MES_SIZE (sizeof(MES))

class NetWorkUnit
{
public:
	NetWorkUnit();
	virtual ~NetWorkUnit();
	virtual IPDATA ip(PlNum num) = 0;					// ipｱﾄﾞﾚｽ獲得
	virtual PlNum GetPlNum(void) = 0;					// PlNum獲得
	virtual int netWorkHandle(PlNum num) = 0;			// netWorkHandle獲得
	virtual void Connect(void) = 0;						// ﾎｽﾄ/ｹﾞｽﾄとの接続
	virtual void RunMesList(void);						// ﾘｽﾄのﾃﾞｰﾀ送信
	virtual void StartGame(void);						// ｹﾞｰﾑｽﾀｰﾄﾒｯｾｰｼﾞ作成関数
	virtual void Update(void) = 0;
	virtual bool GetData(void) = 0;						// Bufからのﾃﾞｰﾀ取得
	bool DataSend(int handle, MES mes);					// ﾃﾞｰﾀ送信
	bool AddSendMesList(MES mes);						// 送信用ﾃﾞｰﾀ追加
	bool AddRecMesList(MES mes);						// 受信ﾒｯｾｰｼﾞﾘｽﾄ
	void ReSetRecMes(void);								// 受信ﾒｯｾｰｼﾞ削除
	MES GetMes(PlNum num,MES_TYPE type);				// 指定されたPlNum,typeのﾒｯｾｰｼﾞ取得
	MES GetMes(MES_TYPE type);
	bool SetNetWorkHandle(int handle);					// _netWorkHandleの設定
	const bool LinkFlag(void)const;						// 接続できているか確認
protected:
	MES _mes;											// 受け取りﾒｯｾｰｼﾞ一時保存用
	std::vector<MES> _sendMesList;						// 送信ﾒｯｾｰｼﾞﾘｽﾄ
	std::vector<MES> _recMesList;						// 受信ﾒｯｾｰｼﾞﾘｽﾄ
	PlNum _plNum;										// 何番目のﾌﾟﾚｲﾔｰか
	std::map<PlNum,int> _netWorkHandle;					// NetWorkHandle保存用変数
	bool _linkFlag;										// 接続できたかﾌﾗｸﾞ
	std::map<PlNum, IPDATA> _ip;						// ipｱﾄﾞﾚｽ
	int _port;											// ﾎﾟｰﾄ番号
	bool CheckData(PlNum plNum);						// 引数のPlNumのbufにﾃﾞｰﾀがあるかﾁｪｯｸ　あった場合は取り出す
};

