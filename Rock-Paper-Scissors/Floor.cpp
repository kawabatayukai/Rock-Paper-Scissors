#include"DxLib.h"
#include"Floor.h"

//コンストラクタ
Floor::Floor(int x, int y, int w, int h) : x(x), y(y), w(w), h(h)
{
	
}

//コンストラクタ  （色を指定）
Floor::Floor(int x , int y, int w, int h, int color)
	: x(x), y(y), w(w), h(h), color(color)
{

}

////コンストラクタ  （画像の使用）
Floor::Floor(const char* image_handle,int x, int y, int w, int h)
	: x(x), y(y), w(w), h(h)
{
	//コンストラクタで画像へのパスをもらう
	if (image_handle != nullptr) image = LoadGraph(image_handle);
}

//描画
void Floor::Draw() const
{
	//画像がある時
	if (image != 0)
	{
		DrawGraph(x, y, image, TRUE);  //画像で描画
	}
	else
	{
		//白
		DrawBox(x, y, (x + w), (y + h), color, TRUE);
	}

}