#pragma once
#include <memory>
#include "Obj.h"
#include "PlNum.h"

struct FuncThrow;
struct FuncHold;
struct FuncPut;

class Player :
	public Obj
{
public:
	Player();
	Player(PlNum plNum, Vector2Dbl pos, int padNum,sharedObj potObj);
	Player(PlNum plNum, Vector2Dbl pos, sharedObj potObj);
	void Update(std::vector<sharedObj>& objList) override;
	PlNum plNum(void);
	int holdWeightMax(void);
	int GetHoldListSize(void);
	bool throwPot(void);
	void throwPot(bool throwMode);

	~Player();
private:
	friend FuncHold;
	friend FuncThrow;
	friend FuncPut;
	void Init(void);
	void DrawHP(void)override;

	bool _throwPot;					// 持ってるときに壺をターゲットにするかどうか
	int _holdWeightMax;				// 持てる重さ上限
	double _throwRange;				// 投げの距離
	int _playerHPImg[2];				// プレイヤー用のHP画像
	int _heartImg;
	PlNum _plNum;
	std::vector<sharedObj> _holdList;			// 現在持っているオブジェクト

};

