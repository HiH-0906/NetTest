#include <algorithm>
#include <time.h>
#include <DxLib.h>
#include <_DebugConOut.h>
#include <ImageMng.h>
#include <EffectMng.h>
#include "GameScene.h"
#include <object/Player.h>
#include <object/Enemy.h>
#include <object/Pot.h>
#include <object/Follower.h>
#include <object/Item.h>
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

	srand((unsigned int)time(NULL));

	_objList.emplace_back(new Pot());

	potObj = _objList[0];
	(*potObj).LoadStaticImg();

	_objList.emplace_back(new Player(PlNum::PL_01, {1080.0,800.0 },potObj));
	//_objList.emplace_back(new Player(PlNum::PL_02, {1080.0,800.0 }, DX_INPUT_PAD2,potObj));
	//_objList.emplace_back(new Player(PlNum::PL_03, { 1080.0,800.0 }, DX_INPUT_PAD3, potObj));

	lpSceneMng.AddInstanceQue({ UNIT_ID::FOLLOWER,1,{960.0,440.0},0 });
	lpSceneMng.AddInstanceQue({ UNIT_ID::FOLLOWER,1,{960.0,900.0},0 });
	lpSceneMng.AddInstanceQue({ UNIT_ID::FOLLOWER,1,{1700.0,440.0},0 });
	lpSceneMng.AddInstanceQue({ UNIT_ID::FOLLOWER,1,{1700.0,900.0},0 });
	/*_objList.emplace_back(new Enemy({ ENEMY_TYPE::BAD, { 500.0, 500.0 },{0,0},0.0 }, potObj));
	_objList.emplace_back(new Enemy({ ENEMY_TYPE::BAD,{ 600.0, 500.0 },{ 0,0},0.0 }, potObj));*/

	//RunPlayerQue(lpSceneMng.playerList(), potObj);

	enemyListInit();
	lpCamera.SearchObj(_objList);
	lpEffectMng.Init();
	lpMap.Init();
	lpSceneMng.FrameCntReset();
}


GameScene::~GameScene()
{
}

UniqueBase GameScene::Update(UniqueBase own)
{
	// ｶﾒﾗ位置更新
	lpCamera.UpDate();
	// とりあえずの背景
	lpSceneMng.AddDrawQue({ lpMap.mapScreen(),lpSceneMng.WorldCenter.x - lpCamera.OfSet().x ,lpSceneMng.WorldCenter.y - lpCamera.OfSet().y,0.0,1.0,255,LAYER::BG , DX_BLENDMODE_NOBLEND, 255 });

	if (!lpCamera.exMoveFlag())
	{
		searchEnlist();

		// 各々のオブジェクトでソートができるように、引数で渡す用のListをコピーで作成
		auto copyList = _objList;

		for (auto obj : _objList)
		{
			(*obj).Update(copyList);
		}
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
	lpImageMng.GetID({ IMG::PLAYER_1 ,STATE::NORMAL}, "image/Player01_walk.png", { 120,128 }, { 4,4 });
	lpImageMng.GetID({ IMG::PLAYER_1 ,STATE::HOLD }, "image/Player01_hold.png", { 120,128 }, { 4,4 });
	lpImageMng.GetID({ IMG::PLAYER_1 ,STATE::DEATH }, "image/Player01_death.png");

	lpImageMng.GetID({ IMG::PLAYER_2 ,STATE::NORMAL }, "image/Player02_walk.png", { 120,128 }, { 4,4 });
	lpImageMng.GetID({ IMG::PLAYER_2 ,STATE::HOLD }, "image/Player02_hold.png", { 120,128 }, { 4,4 });
	lpImageMng.GetID({ IMG::PLAYER_2 ,STATE::DEATH }, "image/Player02_death.png");


	lpImageMng.GetID({ IMG::PLAYER_3 ,STATE::NORMAL }, "image/Player03_walk.png", { 120,128 }, { 4,4 });
	lpImageMng.GetID({ IMG::PLAYER_3 ,STATE::HOLD }, "image/Player03_hold.png", { 120,128 }, { 4,4 });
	lpImageMng.GetID({ IMG::PLAYER_3 ,STATE::DEATH }, "image/Player03_death.png");


	lpImageMng.GetID({ IMG::PLAYER_4 ,STATE::NORMAL }, "image/Player04_walk.png", { 120,128 }, { 4,4 });
	lpImageMng.GetID({ IMG::PLAYER_4 ,STATE::HOLD }, "image/Player04_hold.png", { 120,128 }, { 4,4 });
	lpImageMng.GetID({ IMG::PLAYER_4 ,STATE::DEATH }, "image/Player04_death.png");


	// pot
	lpImageMng.GetID({ IMG::POT,STATE::HOLD }, "image/pot_ani.png", { 140,140 }, { 5,1 });

	// 敵
	lpImageMng.GetID({ IMG::ENEMY_SLIME ,STATE::NORMAL }, "image/slime.png", { 120,128 }, { 4,4 });
	lpImageMng.GetID({ IMG::ENEMY_BAT ,STATE::NORMAL }, "image/bad.png", { 120,128 }, { 4,4 });
	lpImageMng.GetID({ IMG::ENEMY_DAEMON ,STATE::NORMAL }, "image/daemon.png", { 120, 128 }, { 4,4 });
	lpImageMng.GetID({ IMG::ENEMY_GHOST ,STATE::NORMAL }, "image/ghost.png", { 120, 128 }, { 4,4 });
	lpImageMng.GetID({ IMG::ENEMY_MUSH ,STATE::NORMAL }, "image/mashroom.png", { 120, 128 }, { 4,4 });

	// 敵素材
	lpImageMng.GetID({ IMG::ITEM_BAT ,STATE::NORMAL }, "image/bat_item.png");
	lpImageMng.GetID({ IMG::ITEM_SLIME ,STATE::NORMAL }, "image/slime_item.png");
	lpImageMng.GetID({ IMG::ITEM_DEMON ,STATE::NORMAL }, "image/demon_item.png");
	lpImageMng.GetID({ IMG::ITEM_GHOST ,STATE::NORMAL }, "image/ghost_item.png");
	lpImageMng.GetID({ IMG::ITEM_MUSH ,STATE::NORMAL }, "image/mush_item.png");

	// 味方
	lpImageMng.GetID({ IMG::FOL_OCTOPUS ,STATE::NORMAL }, "image/Octpus.png", { 120, 128 }, { 4,4 });
	lpImageMng.GetID({ IMG::FOL_BEE ,STATE::NORMAL }, "image/bee_unit.png", { 120, 128 }, { 4,4 });
	lpImageMng.GetID({ IMG::FOL_DAEMON ,STATE::NORMAL }, "image/daemon_unit.png", { 120, 128 }, { 4,4 });
	lpImageMng.GetID({ IMG::FOL_GHOST ,STATE::NORMAL }, "image/ghost_unit.png", { 120, 128 }, { 4,4 });
	lpImageMng.GetID({ IMG::FOL_MUSH ,STATE::NORMAL }, "image/mashroom_unit.png", { 120, 128 }, { 4,4 });

	lpImageMng.GetID({ IMG::BG ,STATE::NORMAL }, "image/tf_jungle_tileset.png", { 16,16 }, { 18,20 });
	lpImageMng.GetID({ IMG::POT ,STATE::NORMAL }, "image/pot.png");
	lpImageMng.GetID({ IMG::BLAST ,STATE::DEATH }, "image/blast.png", { 192,192 }, { 5,2 });


}

void GameScene::enemyListInit(void)
{
	FILE* filePt;
	fopen_s(&filePt, "data/enemyList.csv", "rb");

	if (filePt == nullptr)
	{
		AST();
		return;
	}

	int frame = 0;
	int type = 0;
	Vector2Dbl pos;

	while (fscanf_s(filePt, "%d, %d, %lf, %lf", &frame, &type, &pos.x, &pos.y) != EOF)
	{
		_enemyList.emplace_back(frame, type, pos.x, pos.y);
	}

	fclose(filePt);
}

void GameScene::searchEnlist(void)
{
	// 出現ﾌﾚｰﾑになったらｴﾈﾐｰのｲﾝｽﾀﾝｽｷｭｰを投げる
	int frame, type;
	Vector2Dbl pos;
	for (auto data : _enemyList)
	{
		std::tie(frame, type, pos.x, pos.y) = data;
		if (frame <= lpSceneMng.frameCnt())
		{
			lpSceneMng.AddInstanceQue({ UNIT_ID::ENEMY, type,{ pos.x, pos.y }, 0 });
		}
		else
		{
			break;
		}
	}
	_enemyList.erase(
		std::remove_if(_enemyList.begin(),
			_enemyList.end(),
			[](enemyData &data) {return std::get<0>(data) <= lpSceneMng.frameCnt(); }),
		_enemyList.end()
	);
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
		case UNIT_ID::ITEM:
			_objList.emplace_back(new Item({ static_cast<ENEMY_TYPE>(type),pos }));
			break;
		default:
			AST();
			break;
		}
	}

}
