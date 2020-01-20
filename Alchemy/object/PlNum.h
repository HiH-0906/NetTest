#pragma once

enum class PlNum
{
	PL_01,
	PL_02,
	PL_03,
	PL_04,
	PL_MAX,
	PL_NON						// ｹﾞｽﾄ側未接続時設定用
};

PlNum begin(PlNum);
PlNum end(PlNum);
PlNum operator*(PlNum num);
PlNum operator++(PlNum& num);
