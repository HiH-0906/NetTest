#pragma once

#include <memory>
#include <vector>


#define lpMap Map::GetInstans()
#define CHIP_SIZE_X 16
#define CHIP_SIZE_Y 16
#define MAP_CHIP_X 160
#define MAP_CHIP_Y 90

class Map
{
public:
	void Draw(void);
	static Map& GetInstans(void)
	{
		return *sInstans;
	}
	int _mapScreen;									// ϯ�ߑS�̐}
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
	std::vector<std::vector<int>> _mapData;			// ϯ���ް�
	std::vector<std::vector<int>> _mapData2;			// ϯ���ް�
	bool LoadMap(void);								// csv����̓ǂݍ���
};

