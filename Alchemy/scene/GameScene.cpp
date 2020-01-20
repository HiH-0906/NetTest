#include <algorithm>
#include <DxLib.h>
#include <_DebugConOut.h>
#include <ImageMng.h>
#include <EffectMng.h>
#include "GameScene.h"
#include <object/Player.h>
#include <object/Enemy.h>
#include <object/Pot.h>
#include <object/Follower.h>
#include "func/FuncHold.h"
#include "func/FuncThrow.h"
#include "func/FuncIntoPot.h"
#include "Map.h"
#include <EffekseerForDXLib.h>

GameScene::GameScene()
{
	TRACE("ｹﾞｰﾑｼｰﾝ\n");
	initFunc();
	initImg();
	initeffect();

	_objList.emplace_back(new Pot());

	potObj = _objList[0];

	_objList.emplace_back(new Player(PlNum::PL_01, {100.0,100.0}, DX_INPUT_PAD1,potObj));
	/*_objList.emplace_back(new Enemy({ ENEMY_TYPE::BAD, { 500.0, 500.0 },{0,0},0.0 }, potObj));
	_objList.emplace_back(new Enemy({ ENEMY_TYPE::BAD,{ 600.0, 500.0 },{ 0,0},0.0 }, potObj));*/

	//RunPlayerQue(lpSceneMng.playerList(), potObj);
	// 取りあえずの蝙蝠
	lpSceneMng.SetInstanceQue({ UNIT_ID::ENEMY,1,{700.0,500.0},0});
	lpSceneMng.SetInstanceQue({ UNIT_ID::ENEMY,1,{800.0,500.0},0 });
	lpSceneMng.SetInstanceQue({ UNIT_ID::ENEMY,1,{900.0,500.0},0 });
	lpSceneMng.SetInstanceQue({ UNIT_ID::ENEMY,1,{1000.0,500.0},0 });
	lpSceneMng.SetInstanceQue({ UNIT_ID::ENEMY,1,{1100.0,500.0},0 });

	lpCamera.SearchObj(_objList);

	lpMap.Draw();
	lpSceneMng.FlameCntReset();
}


GameScene::~GameScene()
{
}

UniqueBase GameScene::Update(UniqueBase own)
{
	// ｶﾒﾗ位置更新
	lpCamera.UpDate();
	// とりあえずの背景
	lpSceneMng.AddDrawQue({ lpMap._mapScreen,lpSceneMng.WorldCenter.x - lpCamera.OfSet().x ,lpSceneMng.WorldCenter.y - lpCamera.OfSet().y,0,255,LAYER::BG , DX_BLENDMODE_NOBLEND, 255 });
	// 各々のオブジェクトでソートができるように、引数で渡す用のListをコピーで作成
	auto copyList = _objList;

	for (auto obj : _objList)
	{
		(*obj).Update(copyList);
	}
	for (auto obj : _objList)
	{
		(*obj).Draw();
	}

	UpdateEffekseer2D();

	// 死んでいるオブジェクトの削除
	_objList.erase(
		std::remove_if(
			_objList.begin(),
			_objList.end(),
			[](sharedObj& obj) {return (*obj).dead(); }
		),
		_objList.end()
	);

	return std::move(own);
}

void GameScene::initFunc(void)
{
	funcQue = { {ACT_QUE::HOLD,FuncHold()} ,{ACT_QUE::THOROW,FuncThrow()} ,{ACT_QUE::INTO_POT,FuncIntoPot()} };
}

void GameScene::initImg(void)
{
	lpImageMng.GetID({ IMG::PLAYER ,STATE::NORMAL}, "image/Player02_walk.png", { 120,128 }, { 4,4 });
	lpImageMng.GetID({ IMG::PLAYER ,STATE::HOLD }, "image/Player02_hold.png", { 120,128 }, { 4,4 });

	// 敵
	lpImageMng.GetID({ IMG::ENEMY_SLIME ,STATE::NORMAL }, "image/slime.png", { 120,128 }, { 4,4 });
	lpImageMng.GetID({ IMG::ENEMY_BAD ,STATE::NORMAL }, "image/bad.png", { 120,128 }, { 4,4 });
	lpImageMng.GetID({ IMG::ENEMY_DAEMON ,STATE::NORMAL }, "image/daemon.png", { 120, 128 }, { 4,4 });
	lpImageMng.GetID({ IMG::ENEMY_GHOST ,STATE::NORMAL }, "image/ghost.png", { 120, 128 }, { 4,4 });
	lpImageMng.GetID({ IMG::ENEMY_MUSH ,STATE::NORMAL }, "image/mashroom.png", { 120, 128 }, { 4,4 });

	// 味方
	lpImageMng.GetID({ IMG::FOL_OCTOPUS ,STATE::NORMAL }, "image/Octpus.png", { 120, 128 }, { 4,4 });
	lpImageMng.GetID({ IMG::FOL_BEE ,STATE::NORMAL }, "image/bee_unit.png", { 120, 128 }, { 4,4 });
	lpImageMng.GetID({ IMG::FOL_DAEMON ,STATE::NORMAL }, "image/daemon_unit.png", { 120, 128 }, { 4,4 });
	lpImageMng.GetID({ IMG::FOL_GHOST ,STATE::NORMAL }, "image/ghost_unit.png", { 120, 128 }, { 4,4 });
	lpImageMng.GetID({ IMG::FOL_MUSH ,STATE::NORMAL }, "image/mashroom_unit.png", { 120, 128 }, { 4,4 });

	lpImageMng.GetID({ IMG::BG ,STATE::NORMAL }, "image/tf_jungle_tileset.png", { 16,16 }, { 18,20 });
	lpImageMng.GetID({ IMG::POT ,STATE::NORMAL }, "image/pot.png");
}

void GameScene::initeffect(void)
{
	//lpEffectMng.GetID(EFFECT::DASH, "effect/smoke.efk", 10.0F);
	lpEffectMng.GetID(EFFECT::ATTACK_BITE, "effect/bite.efk", 20.0F);
}

void GameScene::RunActQue(std::vector<ActQueT> actList)
{
	for (auto actData : actList)
	{
		try
		{
			funcQue[actData.first](actData, _objList);
		}
		catch (...)
		{
			AST();
		}
	}
}

void GameScene::PlayerInstance(std::vector<PlayerQueT> &playerList, sharedObj potObj)
{
	for (auto iList : playerList)
	{
		PlNum num;
		Vector2Dbl pos;
		int padNum;
		std::tie(num, pos, padNum) = iList;

		_objList.emplace_back(new Player(num, pos, padNum,potObj));
	}
}

void GameScene::RunInstanceQue(std::vector<InstanceQueT> instanceList)
{
	int type,num;
	UNIT_ID id;
	Vector2Dbl pos;

	for (unsigned int i = 0; i < instanceList.size(); i++)
	{
		std::tie(id, type, pos,num) = instanceList[i];

		switch (id)
		{
		case UNIT_ID::ENEMY:
			_objList.emplace_back(new Enemy({ static_cast<ENEMY_TYPE>(type),pos,num }, potObj));
			break;
		case UNIT_ID::FOLLOWER:
			_objList.emplace_back(new Follower({ static_cast<FOLLOWER_TYPE>(type),pos,num }, potObj));
			break;
		default:
			AST();
			break;
		}
	}

}
