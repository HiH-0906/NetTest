#pragma once
#include <vector>
#include "Text.h"

class Message
{
public:
	Message();
	~Message();
	void AddMesList(Text& mes);			// リストにテキストを追加する
	int mesScreen(void);
	void DrawUpdate(void);

private:
	int _mesScreen;					// メッセージを描画するスクリーン
	int _boardImg;
	int _mesMoveCnt;
	std::vector<Text> _mesList;		// 送られてきたメッセージを格納する
};

