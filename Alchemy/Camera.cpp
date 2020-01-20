#include "Camera.h"
#include "scene/SceneMng.h"
#include "NetWork/NetWork.h"
#include "object/Player.h"

std::unique_ptr<Camera, Camera::CameraDeleter> Camera::sInstance(new Camera());

Camera::Camera()
{
}


Camera::~Camera()
{
}

Vector2Dbl Camera::OfSet(void)
{
	// Ç∏ÇÁÇ∑ï™ï‘Ç∑
	return _pos - _size;
}

Vector2Dbl Camera::pos(void)
{
	return _pos;
}

Vector2Dbl Camera::size(void)
{
	return _size;
}



void Camera::UpDate(void)
{
	_pos = (*_plObj.lock()).pos();
	// Õﬁ¿∂ﬁ∑ÇµÇΩÇ≠Ç»Ç¢ä¥ñûç⁄
	if (lpSceneMng.WorldSize.x < _pos.x + _size.x)
	{
		_pos.x = lpSceneMng.WorldSize.x - _size.x;
	}
	if (0 > _pos.x - _size.x)
	{
		_pos.x =  _size.x;
	}
	if (lpSceneMng.WorldSize.y < _pos.y + _size.y)
	{
		_pos.y = lpSceneMng.WorldSize.y - _size.y;
	}
	if (0 > _pos.y - _size.y)
	{
		_pos.y = _size.y;
	}
}

void Camera::SearchObj(std::vector<sharedObj> List)
{
	for (auto obj : List)
	{
		if ((*obj).unitID() == UNIT_ID::PLAYER)
		{
			if (((Player&)(*obj)).plNum() == PlNum::PL_01/*lpNetWork.GetPlNum()*/)
			{
				_size = lpSceneMng.ScreenSize / 2.0;
				_plObj = obj;
				return;
			}
		}
	}
}
