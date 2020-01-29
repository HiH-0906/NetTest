#include "BeeAttack.h"
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <scene\SceneMng.h>
#include <EffectMng.h>
#include <EFFECT.h>


void BeeAttack::operator()(Obj & obj, std::vector<sharedObj>& objList)
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
		obj._effectID = PlayEffekseer2DEffect(EFFECT_ID(EFFECT::AT_BEE));

		// ����
		if (IsEffekseer2DEffectPlaying(obj._effectID) == 0)
		{
			(*target).DoDamage(obj._power);		// enemy��power�������ɂ��Ă�
			_effectRad = atan2f((*target).pos().y - obj._pos.y, (*target).pos().x - obj._pos.x);
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

	SetRotationPlayingEffekseer2DEffect(obj._effectID, 0, 0, -_effectRad);

	// �I��
	if (obj._coolCnt <= 0)
	{
		StopEffekseer2DEffect(obj._effectID);
		obj._effectFlg = false;
		obj._coolCnt = obj._coolCntMax;
		obj.state(STATE::NORMAL);
	}

}