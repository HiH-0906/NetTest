#include "GhostAttack.h"
#include <cmath>
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <_DebugConOut.h>
#include <scene\SceneMng.h>
#include <EffectMng.h>
#include <EFFECT.h>

void GhostAttack::operator()(Obj & obj, std::vector<sharedObj>& objList)
{
	// �����N�؂�
	if (obj.tageObj().expired())
	{
		TRACE("attack�̑Ώۂ������܂���")
		StopEffekseer2DEffect(obj._effectID);
		obj._effectFlg = false;
		_move = MOVE_TYPE::CHARGE;
		obj.state(STATE::NORMAL);
		return;
	}
	
	switch (_move)
	{
	case MOVE_TYPE::CHARGE:
		Charge(obj);
		break;
	case MOVE_TYPE::SHOT:
		Shot(obj);
		break;
	case MOVE_TYPE::BLAST:
		Blast(obj);
		break;
	default:
		AST();
		break;
	}

}

void GhostAttack::Charge(Obj & obj)
{
	auto target = obj.tageObj().lock();		// �^�[�Q�b�g�̏��i�[

	if (!obj._effectFlg)
	{
		// �Đ����܂�
		obj._effectID = PlayEffekseer2DEffect(EFFECT_ID(EFFECT::GHOST_CHARGE));

		// ����
		if (IsEffekseer2DEffectPlaying(obj._effectID) == 0)
		{
			obj._effectFlg = true;
		}
		else
		{
			return;
		}
	}
	else
	{
		// ���ĂŔ���
		if (_endCnt >= 60)
		{
			StopEffekseer2DEffect(obj._effectID);
			obj._effectFlg = false;
			_endCnt = 0;
			_move = MOVE_TYPE::SHOT;
		}
		_endCnt++;
	}

	// �G�t�F�N�g�̍��W�w��
	SetPosPlayingEffekseer2DEffect(obj._effectID,
		static_cast<float>(obj._pos.x),
		static_cast<float>(obj._pos.y),
		0);
}

void GhostAttack::Shot(Obj & obj)
{
	auto target = obj.tageObj().lock();								// ���ޯĂ̏��i�[

	if (!obj._effectFlg)
	{
		// �Đ����܂�
		obj._effectID = PlayEffekseer2DEffect(EFFECT_ID(EFFECT::GHOST_SHOT));

		// �Đ�����Ă�����
		if (IsEffekseer2DEffectPlaying(obj._effectID) == 0)
		{
			_shotPos = obj._pos;									// �e�̏������W
			obj._effectFlg = true;
		}
	}
	else
	{
		// ���������甚�����Ăق���
		if (IsHitObj(_shotPos, (*target)._pos, (*target)._size))
		{
			StopEffekseer2DEffect(obj._effectID);
			_move = MOVE_TYPE::BLAST;
			obj._effectFlg = false;
		}

		// �U�����f
		if (_endCnt >= MAX_CNT)
		{
			StopEffekseer2DEffect(obj._effectID);
			_move = MOVE_TYPE::CHARGE;
			obj._effectFlg = false;
			_endCnt = 0;
			obj.state(STATE::NORMAL);
		}
		_shotPos += ((*target)._pos - obj._pos) / 30.0;		// �ړ�

		_endCnt++;
	}

	// �G�t�F�N�g�̍��W�w��
	SetPosPlayingEffekseer2DEffect(obj._effectID,
		static_cast<float>(_shotPos.x),
		static_cast<float>(_shotPos.y),
		0);
}

void GhostAttack::Blast(Obj & obj)
{
	auto target = obj.tageObj().lock();						// ���ޯĂ̏��i�[

	if (!obj._effectFlg)
	{
		// �Đ����܂�
		obj._effectID = PlayEffekseer2DEffect(EFFECT_ID(EFFECT::GHOST_BLAST));

		// �Đ�����Ă�����
		if (IsEffekseer2DEffectPlaying(obj._effectID) == 0)
		{
			(*target).DoDamage(obj._power);					// ��Ұ��
			obj._effectFlg = true;
		}
	}
	else
	{
		// �Đ����I�������ðĕύX
		if (IsEffekseer2DEffectPlaying(obj._effectID) == -1)
		{
			StopEffekseer2DEffect(obj._effectID);
			obj._effectFlg = false;
			_move = MOVE_TYPE::CHARGE;
			obj.state(STATE::NORMAL);
		}
	}

	// �G�t�F�N�g�̍��W�w��
	SetPosPlayingEffekseer2DEffect(obj._effectID,
		static_cast<float>((*target)._pos.x),
		static_cast<float>((*target)._pos.y),
		0);
}

bool GhostAttack::IsHitObj(Vector2Dbl shot, Vector2Dbl targetPos, Vector2Int targetSize)
{
	Vector2Dbl lenght = { targetPos.x - shot.x, targetPos.y - shot.y };

	if (sqrt(lenght.x * lenght.x + lenght.y * lenght.y) < sqrt(targetSize.x - 1.0) &&
		sqrt(lenght.x * lenght.x + lenght.y * lenght.y) < sqrt(targetSize.y - 1.0))
	{
		return true;
	}

	return false;
}
