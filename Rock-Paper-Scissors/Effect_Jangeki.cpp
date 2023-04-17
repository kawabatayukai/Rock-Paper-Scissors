#include"DxLib.h"
#include"Effect_Jangeki.h"

//コンストラクタ
Effect_Jangeki::Effect_Jangeki(float play_x, float play_y) : play_x(play_x), play_y(play_y), frame_count(0), index_image(0)
{
	//画像読み込み
	LoadDivGraph("images/Effect/test_jan.png", 10, 10, 1, 180, 180, image_effect);
}

//デストラクタ
Effect_Jangeki::~Effect_Jangeki()
{

}

//更新
void Effect_Jangeki::Update()
{
	if (++frame_count % 3 == 0)
	{
		index_image++;
		frame_count = 0;
	}
}

//描画
void Effect_Jangeki::Draw() const
{
	//描画可能
	if (index_image < 10)
	{
		DrawRotaGraphF(play_x, play_y, 1, 0, image_effect[index_image], TRUE);
	}
}

