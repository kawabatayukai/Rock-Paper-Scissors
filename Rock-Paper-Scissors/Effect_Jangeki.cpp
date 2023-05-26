#include"DxLib.h"
#include"Effect_Jangeki.h"

//コンストラクタ
Effect_Jangeki::Effect_Jangeki(float play_x, float play_y, Jan_Type type, _CHAR_TYPE character)
	: play_x(play_x), play_y(play_y), character(character), image_sub(0), image_effect{}
	, frame_count(0), index_effect(0), index_max(0),  finish_effect(false)
	, rotation(0.0)
{
	if (character != _CHAR_TYPE::NOT_CHARA)
	{
		//最大数セット
		index_max = 10;
		int image_size = 120;

		//エフェクト
		switch (type)
		{
		case Jan_Type::ROCK:

			LoadDivGraph("images/Effect/janeffectRed.png", 10, 10, 1, image_size, image_size, image_effect);
			if (character == _CHAR_TYPE::PLAYER)
				image_sub = LoadGraph("images/Effect/lightning_gu_120.png");
			else if (character == _CHAR_TYPE::ENEMY)
				image_sub = LoadGraph("images/Effect/smoke_120_red.png");

			break;

		case Jan_Type::SCISSORS:

			LoadDivGraph("images/Effect/janeffectYellow.png", 10, 10, 1, image_size, image_size, image_effect);
			if (character == _CHAR_TYPE::PLAYER)
				image_sub = LoadGraph("images/Effect/lightning_tyoki_120.png");
			else if (character == _CHAR_TYPE::ENEMY)
				image_sub = LoadGraph("images/Effect/smoke_120_yellow.png");
			break;

		case Jan_Type::PAPER:

			LoadDivGraph("images/Effect/janeffectBlue.png", 10, 10, 1, image_size, image_size, image_effect);
			if (character == _CHAR_TYPE::PLAYER)
				image_sub = LoadGraph("images/Effect/lightning_pa_120.png");
			else if (character == _CHAR_TYPE::ENEMY)
				image_sub = LoadGraph("images/Effect/smoke_120_blue.png");
			break;

		case Jan_Type::NONE:
			//LoadDivGraph("images/Effect/janeffectYellow.png", 10, 10, 1, image_size, image_size, image_effect);
			break;

		default:
			break;
		}
	}
	else
	{ 
		//最大数セット
		index_max = 10;
		int image_size = 192;

		switch (type)
		{
		case Jan_Type::ROCK:
			LoadDivGraph("images/Effect/again_red.png", 10, 5, 2, 192, 192, image_effect);
			break;
		case Jan_Type::SCISSORS:
			LoadDivGraph("images/Effect/again_yellow.png", 10, 5, 2, 192, 192, image_effect);
			break;
		case Jan_Type::PAPER:
			LoadDivGraph("images/Effect/again_blue.png", 10, 5, 2, 192, 192, image_effect);
			break;
		case Jan_Type::NONE:
			LoadDivGraph("images/Effect/pipo-btleffect159.png", 10, 5, 2, 192, 192, image_effect);
			break;
		default:
			break;
		}
	}
}

//デストラクタ
Effect_Jangeki::~Effect_Jangeki()
{
}

//更新
void Effect_Jangeki::Update()
{
	int pct = 2;

	if (character == _CHAR_TYPE::NOT_CHARA) pct = 2;
	else pct = 3;

	if (++frame_count % pct == 0)
	{
		//最後まで再生
		if (++index_effect > index_max) 
		{
			finish_effect = true;
			rotation = 0.0;
		}
	}

	rotation += 0.05;
}

//描画
void Effect_Jangeki::Draw() const
{
	if (character != _CHAR_TYPE::NOT_CHARA)
	{
		//エフェクト
		SetDrawBlendMode(DX_BLENDMODE_ADD, GetRand(55) + 200);
		DrawRotaGraphF(play_x, play_y, 1, GetRand(360), image_sub, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
		DrawRotaGraphF(play_x, play_y, 1.0, 0, image_effect[index_effect], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
		DrawRotaGraphF(play_x, play_y, 0.6, rotation, image_effect[index_effect], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//エフェクト
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
		DrawRotaGraphF(play_x, play_y, 0.7, rotation, image_effect[index_effect], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
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

