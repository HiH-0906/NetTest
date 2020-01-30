#include "BatAttack.h"
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <scene\SceneMng.h>
#include <EffectMng.h>
#include <EFFECT.h>

void BatAttack::operator()(Obj & obj, std::vector<sharedObj>& objList)
{
	// �����N�؂�
	if (obj.tageObj().expired())
	{
		StopEffekseer2DEffect(obj._effectID);
		obj._effectFlg = true;
		obj._coolCnt = obj._coolCntMax;
		obj.state(STATE::NORMAL);
		return;
	}

	auto target = obj.tageObj().lock();			// �^�[�Q�b�g�̏��i�[

	if (!obj._effectFlg)
	{
		(*target).DoDamage(obj._power);			// enemy��power�������ɂ��Ă�
		obj._effectFlg = true;
	}

	// �̪�Ă𷭰�ɓ�����
	lpEffectMng.AddEffectQue({ obj,(*target)._pos,0,EFFECT::AT_BITE,(*target)._zOrder });
}
