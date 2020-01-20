#include "Map.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <DxLib.h>
#include  <_DebugConOut.h>
#include <scene\SceneMng.h>
#include <ImageMng.h>

std::unique_ptr<Map, Map::MapDeleter>Map::sInstans(new Map);

Map::Map()
{
	LoadMap();
}


Map::~Map()
{
}

void Map::Draw(void)
{
	_mapScreen = MakeScreen(static_cast<int>(lpSceneMng.WorldSize.x), static_cast<int>(lpSceneMng.WorldSize.y), true);
	ImageKey key = { IMG::BG,STATE::NORMAL };
	for (int y = 0; y < MAP_CHIP_Y; y++)
	{
		for (int x = 0; x < MAP_CHIP_X; x++)
		{
			SetDrawScreen(_mapScreen);
			DrawGraph(CHIP_SIZE_X*x, CHIP_SIZE_Y*y, lpImageMng.GetID(key)[_mapData[y][x]-1], true);
			SetDrawScreen(DX_SCREEN_BACK);
		}
	}
}

bool Map::LoadMap(void)
{
	std::fstream file("data/mapLayer01.csv");
	// fileを開く
	if (!file.is_open())
	{
		// 開けれてなかった場合終了
		AST();
		return false;
	}
	// fileの読み込み
	while (!file.eof())
	{
		// 1行読み込む
		std::string buf;
		file >> buf;

		std::vector<int> strList;				// 1行分のﾘｽﾄ
		std::istringstream strbuf(buf);			// 文字列ｽﾄﾘｰﾑ
		std::string token;						// 1ｾﾙ分の文字列

		while (std::getline(strbuf, token, ','))
		{
			strList.emplace_back(std::stoi(token));
		}
		_mapData.emplace_back(strList);
	}
	file.close();
	return true;
}
