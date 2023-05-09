#include"DxLib.h"
#include"Effect_Jangeki.h"

//コンストラクタ
Effect_Jangeki::Effect_Jangeki(float play_x, float play_y, Jan_Type type, _CHAR_TYPE character)
	: play_x(play_x), play_y(play_y), character(character)
	, frame_count(0), index_effect(0), index_max(0), image_effect(nullptr), finish_effect(false)
{
	//最大数セット
	index_max = 10;
	image_effect = new int[index_max];

	int image_size = 120;

	//エフェクト
	switch (type)
	{
	case Jan_Type::ROCK:

		LoadDivGraph("images/Effect/janeffectRed.png", 10, 10, 1, image_size, image_size, image_effect);
		if (character == _CHAR_TYPE::PLAYER) 
			image_sub = LoadGraph("images/Effect/lightning_gu_120.png");
		else
			image_sub = LoadGraph("images/Effect/smoke_120_red.png");

		break;

	case Jan_Type::SCISSORS:

		LoadDivGraph("images/Effect/janeffectYellow.png", 10, 10, 1, image_size, image_size, image_effect);
		if (character == _CHAR_TYPE::PLAYER)
			image_sub = LoadGraph("images/Effect/lightning_tyoki_120.png");
		else
			image_sub = LoadGraph("images/Effect/smoke_120_yellow.png");
		break;

	case Jan_Type::PAPER:

		LoadDivGraph("images/Effect/janeffectBlue.png", 10, 10, 1, image_size, image_size, image_effect);
		if (character == _CHAR_TYPE::PLAYER)
			image_sub = LoadGraph("images/Effect/lightning_pa_120.png");
		else
			image_sub = LoadGraph("images/Effect/smoke_120_blue.png");
		break;

	case Jan_Type::NONE:
		LoadDivGraph("images/Effect/janeffectYellow.png", 10, 10, 1, image_size, image_size, image_effect);
		break;

	default:
		break;
	}
	

	//分割読み込み
	
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
	//エフェクト
	SetDrawBlendMode(DX_BLENDMODE_ADD, GetRand(55) + 200);
	DrawRotaGraph(play_x, play_y, 1, GetRand(360), image_sub, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
	DrawRotaGraph(play_x, play_y, 1.0, 0, image_effect[index_effect], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	
}

//再生終了 true
bool Effect_Jangeki::Check_PlayEnd()
{
	return finish_effect;
}

//Characterの座標
void Effect_Jangeki::SetCharacterLocation(const float& x, const float& y)
{
	play_x = x;
	play_y = y;
}

