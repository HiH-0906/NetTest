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
	OFFLINE,			// ｵﾌﾗｲﾝ
	HOST,				// ﾎｽﾄ状態
	GUEST,				// ｸﾗｲｱﾝﾄ状態
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
	bool Active(void);									// 接続確立しているか
	void Connect(void);									// 接続させに行く
	void UpDate(void);									// 接続した後はこれを回してればいいはず
	void ReSetRecMes(void);								// 受信ﾒｯｾｰｼﾞ削除
	MES GetMes(PlNum num,MES_TYPE type);				// 指定されたPlNum,typeのﾒｯｾｰｼﾞ取得
	PlNum GetPlNum(void);								// 現在の自分のPlNum取得
	void MakeKeyMes(KeyMap butan, StickState& stick);	// Key押下情報ﾒｯｾｰｼﾞ化
	void MakeMatchMes(Vector2Dbl& pos);					// 位置情報ﾒｯｾｰｼﾞ化
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
	int _matchTime;										// 同期のためのｶｳﾝﾄ
	MES _tmpMes;										// 受け取りMES一時保存用
	NETMODE _netMode;									// ﾈｯﾄﾜｰｸのﾓｰﾄﾞ hostかGuestか
	std::unique_ptr<NetWorkUnit> _netWorkUnit;			// ﾕﾆｰｸﾎﾟｲﾝﾀ
};

