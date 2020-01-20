#pragma once
#include <vector2.h>
#include "object/Obj.h"

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
	void UpDate(void);
	void SearchObj(std::vector<sharedObj> List);
private:
	Vector2Dbl _pos;
	Vector2Dbl _size;
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

