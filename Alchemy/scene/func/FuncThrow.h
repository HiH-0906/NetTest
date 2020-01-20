#pragma once
#include "../GameScene.h"

#define THROW_CNT_MAX 30.0			// “Š‚°‚Ä‚©‚ç’…’n‚Ü‚Å‚ÌŠÔ
#define THROW_INITIAL_SPEED 15.0	// “Š‚°‚Ì‰‘¬A_vel‚ğİ’è‚·‚é‚Ì‘å‚«‚³

// Player‚ª•¨‚ğ“Š‚°‚é‚Æ‚«‚Ìˆ—
struct FuncThrow
{
	bool operator()(ActQueT&, std::vector<sharedObj>&);
};

