#pragma once
#include <vector>
#include <tuple>
#include <functional>
#include <scene/SceneMng.h>
#include "Obj.h"

#define COMBO_TIME	60						// 壺に入れてから出てくるまでの時間 取りあえず1秒

// モンスターの錬金に使うデータ群
// UNIT_ID : Playerの識別に使う
// int     : モンスターのTYPEをintに変換したもの、Playerの場合はPLNUM？
// 今後モンスターのレア度などを追加予定なのでtuple
using MixData = std::tuple<UNIT_ID, int>;

using PotFunc = std::function<void(std::vector<MixData>&)>;

struct PotHold;
struct FuncThrow;
struct FuncIntoPot;

class Pot :
	public Obj
{
public:
	Pot();
	~Pot();
	void Update(std::vector<sharedObj>& objList)override;
	void AddMixList(MixData data);
	void SetComboCnt(void);

private:
	friend PotHold;
	friend FuncThrow;
	friend FuncIntoPot;
	void Init(void);

	int _comboCnt;							// 壺に物が入ってからのカウント,物が入る度にリセット
	std::vector<MixData> _mixList;			// 壺に入ってるもの
	std::vector<int> _throwList;			// 壺からだすもののserialNum
	void InitFunc(void);					// AlchemyQueの初期化
	std::map<UNIT_ID,PotFunc> AlchemyQue;	// 壺錬金回りまとめ？
};

