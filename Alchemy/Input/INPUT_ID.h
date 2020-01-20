#pragma once

enum class INPUT_ID:int
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	BTN_START,
	BTN_BACK,
	BTN_LS,
	BTN_RS,
	BTN_LB,
	BTN_RB,
	BTN_A = 12,
	BTN_B,
	BTN_X,
	BTN_Y,
	MAX
};

INPUT_ID begin(INPUT_ID);
INPUT_ID end(INPUT_ID);

INPUT_ID operator++(INPUT_ID& id);
INPUT_ID operator*(INPUT_ID id);