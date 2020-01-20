#pragma once
#include <vector>
#include <tuple>
#include <functional>
#include <scene/SceneMng.h>
#include "Obj.h"

#define COMBO_TIME	60						// ��ɓ���Ă���o�Ă���܂ł̎��� ��肠����1�b

// �����X�^�[�̘B���Ɏg���f�[�^�Q
// UNIT_ID : Player�̎��ʂɎg��
// int     : �����X�^�[��TYPE��int�ɕϊ��������́APlayer�̏ꍇ��PLNUM�H
// ���ヂ���X�^�[�̃��A�x�Ȃǂ�ǉ��\��Ȃ̂�tuple
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

	int _comboCnt;							// ��ɕ��������Ă���̃J�E���g,��������x�Ƀ��Z�b�g
	std::vector<MixData> _mixList;			// ��ɓ����Ă����
	std::vector<int> _throwList;			// �₩�炾�����̂�serialNum
	void InitFunc(void);					// AlchemyQue�̏�����
	std::map<UNIT_ID,PotFunc> AlchemyQue;	// ��B�����܂Ƃ߁H
};

