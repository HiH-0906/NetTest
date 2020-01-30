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
	RATE,
	HEIGHT,
	ZORDER,
	LAYER,
	MODE,
	PARAMETER
};

enum class SOUND_QUE
{
	SOUND,
	VOL,
	X,
	Y
};

enum class PLAYER_QUE
{
	PLNUM,
	POS,
	PADNUM
};

using DrawQueT = std::tuple<int, double, double, double, double,double, int, LAYER, int, int>;
using SoundQueT = std::tuple<int, int, double, double>;							// <ﾊﾝﾄﾞﾙ, 音量, 発生座標X, 発生座標Y>
using PlayerQueT = std::tuple <PlNum, Vector2Dbl, int >;						// <ﾌﾟﾚｲﾔｰ番号、座標、PAD番号>

class SceneMng
{
public:
	static SceneMng& GetInstance(void)
	{
		return *sInstance;
	}

	void Run(void);										// ｹﾞｰﾑﾙｰﾌﾟ

	bool AddDrawQue(DrawQueT dQue);						// 描画ｷｭｰの追加
	bool AddActQue(ActQueT aQue);						// ｱｸｼｮﾝｷｭｰの追加
	bool AddSoundQue(SoundQueT sQue);					// ｻｳﾝﾄﾞｷｭｰの追加
	bool AddPlayerQue(PlayerQueT pQue);					// ﾌﾟﾚｲﾔｰｷｭｰの追加
	bool AddInstanceQue(InstanceQueT iQue);				// ｲﾝｽﾀﾝｽｷｭｰの追加
	bool SetInstanceQue(InstanceQueT iQue);				// ｲﾝｽﾀﾝｽｷｭｰの追加

	const size_t GetPlayerListSize(void)const;			// ﾌﾟﾚｲﾔｰｷｭｰのｻｲｽﾞ取得
	std::vector<PlayerQueT>& playerList(void);			// ﾌﾟﾚｲﾔｰｷｭｰ取得

	void FrameCntReset(void);
	const int frameCnt(void)const;
	int serialNumCnt(void);
	void AddSerialNum(void);							// 通し番号をインクリメント
	
	const Vector2Dbl ScreenSize;
	const Vector2Dbl WorldSize;							// 世界中央
	const Vector2Dbl ScreenCenter;						// 画面中央
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
	void SoundPlay(void);
	bool SysInit(void);

	int _layerGID;							// 描画用ｽｸﾘｰﾝ
	int _frameCnt;							// ﾌﾚｰﾑｶｳﾝﾄ
	int _serialNumCnt;						// 通し番号管理変数

	std::map<LAYER, int> _screenID;

	std::vector<DrawQueT> _drawList;		// 描画ｷｭｰの管理配列
	std::vector<ActQueT> _actList;			// ｱｸｼｮﾝｷｭｰの管理配列
	std::vector<SoundQueT> _soundList;		// ｻｳﾝﾄﾞｷｭｰの管理配列
	std::vector<PlayerQueT> _playerList;	// ﾌﾟﾚｲﾔｰｷｭｰの管理配列
	std::vector<InstanceQueT> _instanceList;// ｲﾝｽﾀﾝｽｷｭｰの管理配列

	UniqueBase _activeScene;
};

