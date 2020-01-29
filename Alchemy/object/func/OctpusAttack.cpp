#include "OctpusAttack.h"
#include "BatAttack.h"
#include <DxLib.h>
#include <math.h>
#include <EffekseerForDXLib.h>
#include <scene\SceneMng.h>
#include <EffectMng.h>
#include <EFFECT.h>

void OctpusAttack::operator()(Obj & obj, std::vector<sharedObj>& objList)
{
	// �����N�؂�
	if (obj.tageObj().expired())
	{
		StopEffekseer2DEffect(obj._effectID);
		//(*target)._hp -= 2;
		obj._effectFlg = false;
		obj.state(STATE::NORMAL);
		return;
	}

	auto target = obj.tageObj().lock();		// �^�[�Q�b�g�̏��i�[

	if (!obj._effectFlg)
	{
		// �Đ����܂�
		obj._effectID = PlayEffekseer2DEffect(EFFECT_ID(EFFECT::INK));

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
		static_cast<float>(obj._pos.x),
		static_cast<float>(obj._pos.y),
		0);

	SetRotationPlayingEffekseer2DEffect(obj._effectID, 0, 0, _effectRad);

	// �I��
	if (obj._coolCnt <= 0)
	{
		StopEffekseer2DEffect(obj._effectID);
		obj._effectFlg = false;
		obj._coolCnt = obj._coolCntMax;
		obj.state(STATE::NORMAL);
	}

}
