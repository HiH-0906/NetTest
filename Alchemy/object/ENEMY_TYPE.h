#pragma once

enum class ENEMY_TYPE
{
	SLIME,		// �ײ�
	BAD,		// ����
	DAEMON,		// �ް��
	GHOST,		// ���΂�
	MUSH,		// ���̂�
	MAX
};


ENEMY_TYPE begin(ENEMY_TYPE);
ENEMY_TYPE end(ENEMY_TYPE);

ENEMY_TYPE operator++(ENEMY_TYPE type);
ENEMY_TYPE operator*(ENEMY_TYPE type);