#pragma once
#include "object/Obj.h"

#define BOSS_CNT_MAX 120.0

class Boss :
	public Obj
{
public:
	Boss();
	Boss(sharedObj potObj);
	~Boss();
	void Update(std::vector<sharedObj>& objList) override;

private:
	void Init();
	bool AddBossMove();					// �ݽ�ݽ����ďo������Ƃ��̓���
	void DrawHP(void)override;			// Hp�`��p

	int _bossHPImg[3];					// �޽��HP�摜�p
	Vector2Dbl _endPos;					// �I�_�i�[
	int _addCnt;						// �o������
	double _addVec;						// �o�����̽�߰��
	bool _addFlag;						// �o�����p�׸�
};

