#pragma once
#include <vector2.h>
#include "object/Obj.h"

#define CAMERA_MOVE_CNT 60

#define lpCamera Camera::GetInstance()

class Camera
{
public:
	static Camera& GetInstance(void)
	{
		return *sInstance;
	}
	Vector2Dbl OfSet(void);
	Vector2Dbl pos(void);
	Vector2Dbl size(void);
	void exMoveFlag(bool);
	bool exMoveFlag(void);
	void UpDate(void);
	void SearchObj(std::vector<sharedObj> List);
	void SetMoveData(Vector2Dbl aimPos);		// カメラの特殊移動の時に使うデータをセットする
private:
	Vector2Dbl _pos;
	Vector2Dbl _size;
	Vector2Dbl _unitVel;	// 特殊移動するときの速度の単位ベクトル
	double _a;				// 速さの変化関数v = a * (x - CAMERA_MOVE_CNT / 2) + b　のa
	double _b;				// 速さの変化関数v = a * (x - CAMERA_MOVE_CNT / 2) + b　のb
	bool _exMoveFlag;		// 特殊移動のﾌﾗｸﾞ
	int _moveCnt;
	std::weak_ptr<Obj> _plObj;
	struct CameraDeleter
	{
		void operator()(Camera *camera)
		{
			delete camera;
		}
	};
	static std::unique_ptr<Camera, CameraDeleter> sInstance;
	Camera();
	~Camera();
};

