#pragma once
#include <memory>
#include "Obj.h"
#include "PlNum.h"
#include <Message.h>

class NetWork;
struct FuncThrow;
struct FuncHold;
struct FuncPut;
struct PlayerHold;

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
	friend NetWork;
	friend FuncHold;
	friend FuncThrow;
	friend FuncPut;
	friend PlayerHold;
	void Init(void);
	void DrawHP(void)override;

	bool _throwPot;					// 持ってるときに壺をターゲットにするかどうか
	int _holdWeightMax;				// 持てる重さ上限
	double _throwRange;				// 投げの距離
	int _playerHPImg[3];		// プレイヤー用のHP画像
	int _heartImg;
	static int _playerIcon[4][2];	//
	PlNum _plNum;
	std::vector<sharedObj> _holdList;			// 現在持っているオブジェクト

};

