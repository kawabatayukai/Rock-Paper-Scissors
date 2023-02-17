#pragma once

//矩形
class Floor
{
public:

	//コンストラクタ  
	Floor(int x = 0, int y = 700, int w = 1280, int h = 20);

	void Draw() const;                //描画

	int GetX() const { return x; }    //ｘ座標取得
	int GetY() const { return y; }    //ｙ座標取得
	int GetW() const { return w; }    //幅　　取得
	int GetH() const { return h; }    //高さ　取得

private:
	//座標は左上基準(キャラクターは中心)
	int x;
	int y;
	int w;
	int h;
};