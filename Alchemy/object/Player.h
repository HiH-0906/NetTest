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
	int _holdWeightMax;				// ���Ă�d�����
	double _throwRange;				// �����̋���
	PlNum _plNum;
	std::vector<sharedObj> _holdList;			// ���ݎ����Ă���I�u�W�F�N�g

};

