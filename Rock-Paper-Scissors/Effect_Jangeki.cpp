#include"DxLib.h"
#include"Effect_Jangeki.h"

//コンストラクタ
Effect_Jangeki::Effect_Jangeki(float play_x, float play_y, int result_num)
	: play_x(play_x), play_y(play_y), frame_count(0), index_image(0), play_end(false), image_max(0)
{
	//種類によって読み込む画像が違う
	switch (result_num)
	{
	case 0:

		image_max = 10;
		image_effect = new int[image_max];
		LoadDivGraph("images/Effect/test_jan.png", 10, 10, 1, 180, 180, image_effect);
		break;

	case 1:

		image_max = 15;
		image_effect = new int[image_max];
		LoadDivGraph("images/Effect/test_jan2.png", 15, 15, 1, 156, 156, image_effect);
		break;

	case 2:

		image_max = 12;
		image_effect = new int[image_max];
		LoadDivGraph("images/Effect/test_jan3.png", 12, 12, 1, 240, 240, image_effect);
	}
}

//デストラクタ
Effect_Jangeki::~Effect_Jangeki()
{

}

//更新
void Effect_Jangeki::Update()
{
	if (++frame_count % 2 == 0)
	{
		index_image++;
		frame_count = 0;

		if (index_image > image_max - 1) play_end = true;
	}
}

//描画
void Effect_Jangeki::Draw() const
{
	//描画可能
	if (index_image < image_max)
	{
		DrawRotaGraphF(play_x, play_y, 1, 0, image_effect[index_image], TRUE);
	}
}

//再生終了 true
bool Effect_Jangeki::Check_PlayEnd()
{
	return play_end;
}

