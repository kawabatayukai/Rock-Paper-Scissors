#include"DxLib.h"
#include"Effect_Jangeki.h"

//コンストラクタ
Effect_Jangeki::Effect_Jangeki(float play_x, float play_y)
	: play_x(play_x), play_y(play_y)
	, frame_count(0), index_effect(0), index_max(0), image_effect(nullptr), finish_effect(false)
{
	//最大数セット
	index_max = 10;
	image_effect = new int[index_max];

	//分割読み込み
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
		//最後まで再生
		if (++index_effect > index_max) finish_effect = true;
	}
}

//描画
void Effect_Jangeki::Draw() const
{
	DrawRotaGraph(play_x, play_y, 1, 0, image_effect[index_effect], TRUE);
}

//再生終了 true
bool Effect_Jangeki::Check_PlayEnd()
{
	return finish_effect;
}

