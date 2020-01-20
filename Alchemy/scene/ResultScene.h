#pragma once
#include "BaseScene.h"
#include <object/Obj.h>
#include <Input/InputState.h>

class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();

	UniqueBase Update(UniqueBase own)override;

private:

	void Init(void);
	std::shared_ptr<InputState> _input;		// “ü—ÍŠÇ—ƒNƒ‰ƒX
};

