#pragma once

#include <memory>
#include <vector>
#include <tuple>
#include "object/PlNum.h"
#include <scene\SceneMng.h>

#define lpMap Map::GetInstans()
#define CHIP_SIZE_X 16
#define CHIP_SIZE_Y 16
#define MAP_CHIP_X 160
#define MAP_CHIP_Y 90
#define MINI_MAP_POS_X (lpSceneMng.ScreenSize.x-(lpSceneMng.ScreenSize.x / 8)-CHIP_SIZE_X)
#define MINI_MAP_POS_Y (lpSceneMng.ScreenSize.y-(lpSceneMng.ScreenSize.y / 8)-CHIP_SIZE_Y)

enum class MAP_QUE
{
	X,												// X方向
	Y,												// Y方向
	RAD,											// 角度
	TYPE,											// ﾌﾟﾚｲﾔｰ判別用　壺はPl_NONとかでどうですかね
};

using MapQueT = std::tuple<int, int, double,int>;

class Map
{
public:
	void Draw(void);
	static Map& GetInstans(void)
	{
		return *sInstans;
	}
	void Init(void);								// 初期化
	const int mapScreen(void)const;
	void miniMapDrawFlag(void);
	void ChangeChip(Vector2Dbl pos,double rad,int num);
private:
	struct MapDeleter
	{
		void operator()(Map* map)const
		{
			delete map;
		}
	};
	static std::unique_ptr<Map, MapDeleter>sInstans;
	Map();
	~Map();
	std::vector<MapQueT> _chipData;					// ﾐﾆﾏｯﾌﾟ用chip
	int _mapScreen;									// ﾏｯﾌﾟ全体図
	int _miniMapScreen;								// ﾐﾆﾏｯﾌﾟ
	bool _miniMapDrawFlag;							// ﾐﾆﾏｯﾌﾟ描画するかどうか
	std::vector<std::vector<int>> _mapData;			// ﾏｯﾌﾟﾃﾞｰﾀ
	bool LoadMap(void);								// csvからの読み込み
};

