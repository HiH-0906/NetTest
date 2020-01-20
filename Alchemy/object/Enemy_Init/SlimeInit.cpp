#include <DxLib.h>
#include "SlimeInit.h"
#include <ImageMng.h>
#include <Input/Enemy_AI/Slime.h>
#include "../Obj.h"
#include "../func/TestEnemyUpdate.h"
#include "../func/HoldenUpdate.h"
#include "../func/ThrownUpdate.h"

bool SlimeInit::operator()(Obj & obj)
{
	// ----------アニメーション登録開始
	AnimVector data;

	ImageKey key = { IMG::ENEMY_SLIME,STATE::NORMAL };

	for (auto dir = DIR::LEFT; dir != DIR::MAX; dir = static_cast<DIR>(static_cast<int>(dir) + 1))
	{
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4], 10);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 1], 20);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 2], 30);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 3], 40);
		obj.SetAnim({ STATE::NORMAL,dir }, data);
	}

	for (auto dir = DIR::LEFT; dir != DIR::MAX; dir = static_cast<DIR>(static_cast<int>(dir) + 1))
	{
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4], 10);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 1], 20);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 2], 30);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 3], 40);
		obj.SetAnim({ STATE::HOLDEN,dir }, data);
	}

	for (auto dir = DIR::LEFT; dir != DIR::MAX; dir = static_cast<DIR>(static_cast<int>(dir) + 1))
	{
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4], 10);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 1], 20);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 2], 30);
		data.emplace_back(IMAGE_ID(key)[static_cast<int>(dir) * 4 + 3], 40);
		obj.SetAnim({ STATE::THROWN,dir }, data);
	}

	//_input = std::make_unique<PadState>(DX_INPUT_PAD1);
	obj._input = std::make_unique<Slime>(obj);

	obj._searchRange = 150.0;
	obj._attackRange = 40.0;

	obj._speed = 2.0;
	obj._size = { 48,48 };
	obj._funcState = { { STATE::NORMAL,TestEnemyUpdate() },{ STATE::HOLDEN,HoldenUpdate() },{ STATE::THROWN,ThrownUpdate() } };

	return true;
}
