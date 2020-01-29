#pragma once
#include <vector>
#include <tuple>
#include <functional>
#include <scene/SceneMng.h>
#include "Obj.h"
#include "FOLLOWER_TYPE.h"

#define COMBO_TIME_MAX 120					// 壺に入れてから出てくるまでの時間 取りあえず1秒
#define COMBO_NUM_MAX 4						// 最大コンボ回数

// モンスターの錬金に使うデータ群
// UNIT_ID : Playerの識別に使う
// int     : モンスターのTYPEをintに変換したもの、Playerの場合はPLNUM？
// 今後モンスターのレア度などを追加予定なのでtuple
using MixData = std::tuple<UNIT_ID, int>;

using PotFunc = std::function<void(std::vector<MixData>&)>;

struct PotHold;
struct FuncThrow;
struct FuncIntoPot;

// 配合データ用の構造体
struct MixCombination
{
	int confType;			// 組み合わせによって確定で出てくる
	char  mixProb[10];				// 確率格納場所
};

class Pot :
	public Obj
{
public:
	Pot();
	~Pot();
	void Update(std::vector<sharedObj>& objList)override;
	void AddMixList(MixData data);			// 壺に入ったものを判別して排出するものを変える

private:
	friend PotHold;
	friend FuncThrow;
	void Init(void);
	void CombiListInit(void);

	int _comboCnt;							// 壺に物が入ってからのカウント,物が入る度にリセット
	int _comboNum;							// コンボ回数
	int _gaugeID;							// コンボゲージの描画スクリーン
	int _gaugeImg[2];							// コンボゲージの画像ID
	std::vector<MixData> _mixList;			// 壺に入ってるもの
	std::vector<MixCombination> _combiList;	// 配合の組み合わせのリスト
	std::vector<int> _throwList;			// 壺からだすもののserialNum
	void InitFunc(void);					// AlchemyQueの初期化
	std::map<UNIT_ID,PotFunc> AlchemyQue;	// 壺錬金回りまとめ？
};

