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
	// file���J��
	if (!file.is_open())
	{
		// �J����ĂȂ������ꍇ�I��
		AST();
		return false;
	}
	// file�̓ǂݍ���
	while (!file.eof())
	{
		// 1�s�ǂݍ���
		std::string buf;
		file >> buf;

		std::vector<int> strList;				// 1�s����ؽ�
		std::istringstream strbuf(buf);			// �������ذ�
		std::string token;						// 1�ٕ��̕�����

		while (std::getline(strbuf, token, ','))
		{
			strList.emplace_back(std::stoi(token));
		}
		_mapData.emplace_back(strList);
	}
	file.close();
	return true;
}
