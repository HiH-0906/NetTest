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

	bool _throwPot;					// �����Ă�Ƃ��ɚ���^�[�Q�b�g�ɂ��邩�ǂ���
	int _holdWeightMax;				// ���Ă�d�����
	double _throwRange;				// �����̋���
	int _playerHPImg[2];				// �v���C���[�p��HP�摜
	int _heartImg;
	PlNum _plNum;
	std::vector<sharedObj> _holdList;			// ���ݎ����Ă���I�u�W�F�N�g

};

