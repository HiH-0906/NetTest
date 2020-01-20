#pragma once
#include <map>
#include <memory>
#include <vector>
#include "Vector2.h"
#include <object\STATE.h>

// �摜�}�b�v�ɃA�N�Z�X����L�[
enum class IMG
{
	PLAYER,
	FOL_OCTOPUS,
	FOL_BEE,
	FOL_DAEMON,
	FOL_GHOST,
	FOL_MUSH,
	ENEMY_SLIME,
	ENEMY_BAD,
	ENEMY_DAEMON,
	ENEMY_GHOST,
	ENEMY_MUSH,
	POT,
	BG,
};

#define lpImageMng ImageMng::GetInstance()
#define IMAGE_ID(KEY) (ImageMng::GetInstance().GetID(KEY))

using ImageKey = std::pair<IMG, STATE>;

class ImageMng
{
public:
	static ImageMng& GetInstance(void)
	{
		return *sInstance;
	}

	const std::vector<int>& GetID(ImageKey key);
	const std::vector<int>& GetID(ImageKey key, const std::string& fileName);
	const std::vector<int>& GetID(ImageKey key, const std::string& fileName,const Vector2Int& divSize,const Vector2Int& divCnt);

private:
	struct ImageMngDeleter
	{
		void operator()(ImageMng *ImageMng)
		{
			delete ImageMng;
		}
	};

	static std::unique_ptr<ImageMng, ImageMngDeleter> sInstance;
	std::map < ImageKey, std::vector<int>> _imgMap;		// �摜�f�[�^���i�[����Ă���map
	ImageMng();
	~ImageMng();
};

