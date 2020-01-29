#include <DxLib.h>
#include "Item.h"
#include "../_debug/_DebugConOut.h"
#include "../common/ImageMng.h"
#include "func/ItemNormal.h"
#include "func/HoldenUpdate.h"
#include "func/ThrownUpdate.h"

Item::Item(ENEMY_TYPE type, Vector2Dbl pos)
{
	_pos = pos;
	_type = type;
	Init();
}

Item::~Item()
{
}

void Item::Update(std::vector<sharedObj>& objList)
{
	if (DestroyProc())
	{
		return;
	}
	try
	{
		_funcState[state()](*this, objList);
		_floatCnt++;
	}
	catch (...)
	{
		AST();
	}
}

int Item::getType(void)
{
	return static_cast<int>(_type);
}

int Item::floatCnt(void)
{
	return _floatCnt;
}

void Item::Init(void)
{
	// ----------アニメーション登録開始
	_unitID = UNIT_ID::ITEM;

	AnimVector data;
	ImageKey key;

	switch (_type)
	{
	case ENEMY_TYPE::SLIME:
		key = { IMG::ITEM_SLIME,STATE::NORMAL };
		break;
	case ENEMY_TYPE::BAD:
		key = { IMG::ITEM_BAT,STATE::NORMAL };
		break;
	case ENEMY_TYPE::GHOST:
		key = { IMG::ITEM_GHOST,STATE::NORMAL };
		break;
	case ENEMY_TYPE::MUSH:
		key = { IMG::ITEM_MUSH,STATE::NORMAL };
		break;
	case ENEMY_TYPE::DAEMON:
		key = { IMG::ITEM_DEMON,STATE::NORMAL };
		break;
	case ENEMY_TYPE::MAX:
		AST();
		break;
	default:
		AST();
		break;
	}

	// -- 通常
	for (auto dir = DIR::LEFT; dir != DIR::MAX; dir = static_cast<DIR>(static_cast<int>(dir) + 1))
	{
		data.emplace_back(IMAGE_ID(key)[0], 10);
		SetAnim({ STATE::NORMAL,dir }, data);
	}

	for (auto dir = DIR::LEFT; dir != DIR::MAX; dir = static_cast<DIR>(static_cast<int>(dir) + 1))
	{
		data.emplace_back(IMAGE_ID(key)[0], 10);
		SetAnim({ STATE::HOLDEN,dir }, data);
	}

	for (auto dir = DIR::LEFT; dir != DIR::MAX; dir = static_cast<DIR>(static_cast<int>(dir) + 1))
	{
		data.emplace_back(IMAGE_ID(key)[0], 10);
		SetAnim({ STATE::THROWN,dir }, data);
	}
	// 初期アニメーション
	state(STATE::NORMAL);
	dir(DIR::DOWN);
	_floatCnt = 0;
	_size = { 48,48 };
	_glowID = MakeScreen(_size.x * 2, _size.y * 2, true);
	_funcState = { {STATE::NORMAL,ItemNormal()},{ STATE::HOLDEN,HoldenUpdate() },{ STATE::THROWN,ThrownUpdate() } };
}
