#pragma once

enum class EFFECT
{
	AT_BITE,			// ���݂�
	HEAL,				// ��
	AT_SLIME,			// �ײ�
	GHOST_CHARGE,		// �����
	GHOST_SHOT,			// �e�\���p
	GHOST_BLAST,		// ����
	DEMON_CHARGE,
	DEMON_WAR,			// �x��
	DEMON_BLAST,
	INK,				// �n�U��
	FIRE,				// ���U��
	AT_BEE,				// �I�̂�������
	SMOKE,				// �ɺ�̉��U��
	MAX
};

EFFECT begin(EFFECT);
EFFECT end(EFFECT);

EFFECT operator ++(EFFECT& effect);
EFFECT operator *(EFFECT effect);