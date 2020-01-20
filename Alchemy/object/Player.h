#pragma once
#include <memory>
#include "Obj.h"
#include "PlNum.h"

struct FuncThrow;
struct FuncHold;

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
	~Player();
private:
	friend FuncHold;
	friend FuncThrow;
	void Init(void);
	int _holdWeightMax;				// 持てる重さ上限
	double _throwRange;				// 投げの距離
	PlNum _plNum;
	std::vector<sharedObj> _holdList;			// 現在持っているオブジェクト

};

