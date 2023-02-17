#include"DxLib.h"
#include"Floor.h"

//コンストラクタ
Floor::Floor(int x, int y, int w, int h) : x(x), y(y), w(w), h(h)
{
}

//描画
void Floor::Draw() const
{
	//白
	DrawBox(x, y, (x + w), (y + h), 0xffffff, TRUE);
}