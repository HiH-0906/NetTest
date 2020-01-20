#pragma once

#define PI 3.1415926
#define DEG(rad) (static_cast<int>(rad * 180.0 / PI))
#define RAD(deg) (static_cast<double>(deg) * PI / 180.0)

enum class DIR
{
	LEFT,
	UP,
	RIGHT,
	DOWN,
	MAX
};

DIR begin(DIR);
DIR end(DIR);

DIR operator++(DIR& dir);
DIR operator*(DIR dir);

DIR convToDir(double rad);		// ラジアンを対応したDIRの値に変換
DIR convToDir(int angle);		// 度数を対応したDIRの値に変換

double convToRad(DIR dir);		// DIRをラジアンに変更
int convToAngle(DIR dir);

