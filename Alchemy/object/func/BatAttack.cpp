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
		obj._effectFlg = false;
		obj.state(STATE::NORMAL);
		return;
	}

	auto target = obj.tageObj().lock();		// �^�[�Q�b�g�̏��i�[
	
	if (!obj._effectFlg)
	{
		// �Đ����܂�
		obj._effectID = PlayEffekseer2DEffect(EFFECT_ID(EFFECT::AT_BITE));

		// ����
		if (IsEffekseer2DEffectPlaying(obj._effectID) == 0)
		{
			(*target).DoDamage(obj._power);		// enemy��power�������ɂ��Ă�
			obj._effectFlg = true;
		}
		else
		{
			return;
		}
	}
	else
	{
		// �Đ����I����Ă�����N�[���^�C��
		if (IsEffekseer2DEffectPlaying(obj._effectID) == -1)
		{
			obj._coolCnt--;					
		}
	}

	// �G�t�F�N�g�̍��W�w��
	SetPosPlayingEffekseer2DEffect(obj._effectID,
									static_cast<float>((*target).pos().x),
									static_cast<float>((*target).pos().y + 10),
									0);

	// �I��
	if (obj._coolCnt <= 0)
	{
		StopEffekseer2DEffect(obj._effectID);
		obj._effectFlg = false;
		obj._coolCnt = obj._coolCntMax;
		obj.state(STATE::NORMAL);
	}

}
