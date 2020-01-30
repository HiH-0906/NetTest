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

void Camera::exMoveFlag(bool exMove)
{
	_exMoveFlag = exMove;
}

bool Camera::exMoveFlag(void)
{
	return _exMoveFlag;
}



void Camera::UpDate(void)
{
	if (_exMoveFlag)
	{
		/*if (_moveCnt <= CAMERA_MOVE_CNT)
		{
			_pos += _unitVel * (_b + _a * static_cast<double>((_moveCnt - CAMERA_MOVE_CNT / 2) * (_moveCnt - CAMERA_MOVE_CNT / 2)));
			_moveCnt++;
		}*/

		if (_moveCnt > 0)
		{
			_pos += _unitVel * (_length * _moveCnt / _cntSum);
			_moveCnt--;
		}
	}
	else
	{
		_pos = (*_plObj.lock()).pos();
		// Õﬁ¿∂ﬁ∑ÇµÇΩÇ≠Ç»Ç¢ä¥ñûç⁄
		if (lpSceneMng.WorldSize.x < _pos.x + _size.x)
		{
			_pos.x = lpSceneMng.WorldSize.x - _size.x;
		}
		if (0 > _pos.x - _size.x)
		{
			_pos.x = _size.x;
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

void Camera::SetMoveData(Vector2Dbl aimPos)
{
	_length = sqrt(LengthSquare(aimPos, _pos));

	_a = -6.0 * _length / static_cast<double>(CAMERA_MOVE_CNT * CAMERA_MOVE_CNT * CAMERA_MOVE_CNT);
	_b = -static_cast<double>(CAMERA_MOVE_CNT / 2 * CAMERA_MOVE_CNT / 2) * _a;
	
	_cntSum = 0;

	for (int i = 1; i < CAMERA_MOVE_CNT; i++)
	{
		_cntSum += i;
	}
	/*_b = length / 20.0;
	_a = -_b / static_cast<double>(CAMERA_MOVE_CNT /2  * CAMERA_MOVE_CNT / 2);*/
	_unitVel = (aimPos - _pos) / _length;
	_moveCnt = CAMERA_MOVE_CNT;
}
