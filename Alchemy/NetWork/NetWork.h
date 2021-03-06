#pragma once
#include <DxLib.h>
#include <vector>
#include <map>
#include <memory>
#include <_debug/_DebugConOut.h>
#include <scene/SceneMng.h>
#include <object/Player.h>
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
#define SYNC_TIME 30


class NetWork
{
public:
	static NetWork &GetInstans(void)
	{
		return *sInstans;
	}

	bool NetMode(NETMODE mode);
	const NETMODE NetMode(void);
	bool Active(void);											// 接続確立しているか
	void Connect(void);											// 接続させに行く
	void UpDate(void);											// 接続した後はこれを回してればいいはず
	void ReSetRecMes(void);										// 受信ﾒｯｾｰｼﾞ削除
	void SyncObj(Player& obj);										// 同期ﾒｯｾｰｼﾞ獲得時位置矯正
	MES GetMes(MES_TYPE type);									// 指定されたtypeのﾒｯｾｰｼﾞ取得
	MES GetMes(PlNum num,MES_TYPE type);						// 指定されたPlNum,typeのﾒｯｾｰｼﾞ取得
	void GetKey(std::vector<MES>& buf,PlNum num );				// _recMesListからのｷｰ情報の取り出し
	PlNum GetPlNum(void);										// 現在の自分のPlNum取得
	void MakeKeyMes(KeyMap butan, StickState& stick);			// Key押下情報ﾒｯｾｰｼﾞ化
	void MakeAgainMes(PlNum plNum ,unsigned int num);			// 再送依頼ﾒｯｾｰｼﾞ作成
	void MakeSyncMes(Vector2Dbl pos);							// 同期用ﾒｯｾｰｼﾞ作成
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
	unsigned char _keyNum;										// ｷｰ情報確認用通し番号
	int _syncTime;										// 同期のためのｶｳﾝﾄ
	MES _tmpMes;										// 受け取りMES一時保存用
	NETMODE _netMode;									// ﾈｯﾄﾜｰｸのﾓｰﾄﾞ hostかGuestか
	std::unique_ptr<NetWorkUnit> _netWorkUnit;			// ﾕﾆｰｸﾎﾟｲﾝﾀ
};

