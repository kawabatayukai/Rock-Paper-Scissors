#include"Effect_ChangePlayer.h"
#include"DxLib.h"

//コンストラクタ
Effect_ChangePlayer::Effect_ChangePlayer(Jan_Type type, const float& x, const float& y)
	:index_effect(0), max_index(10), effect_x(x), effect_y(y), frame_count(0)
{
	image_effect = new int[max_index];
	
	switch (type)
	{
	case Jan_Type::ROCK:
		LoadDivGraph("images/Effect/change_p_red.png", 10, 5, 2, 192, 192, image_effect);
		break;
	case Jan_Type::SCISSORS:
		LoadDivGraph("images/Effect/pipo-btleffect160.png", 10, 5, 2, 192, 192, image_effect);
		break;
	case Jan_Type::PAPER:
		LoadDivGraph("images/Effect/change_p_blue.png", 10, 5, 2, 192, 192, image_effect);
		break;

	default:
		break;
	}

	//se
	se_change = LoadSoundMem("Sound/Player/change.wav");
	//SetVolumeSoundMem(255, se_change);
}

//デストラクタ
Effect_ChangePlayer::~Effect_ChangePlayer()
{
	delete[] image_effect;
	DeleteSoundMem(se_change);
}

//更新
void Effect_ChangePlayer::Update()
{
	if (++frame_count % 3 == 0)
	{
		if (index_effect < max_index) index_effect++;
	}

	if (CheckSoundMem(se_change) == 0) PlaySoundMem(se_change, DX_PLAYTYPE_BACK);
}

//描画
void Effect_ChangePlayer::Draw() const
{
	
	DrawRotaGraphF(effect_x, effect_y - 10, 0.8, GetRand(360), image_effect[index_effect], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//描画背面
void Effect_ChangePlayer::Draw_Back() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 250);
	DrawRotaGraphF(effect_x, effect_y - 10, 0.8, GetRand(360), image_effect[index_effect], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//描画前面
void Effect_ChangePlayer::Draw_Front() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DrawRotaGraphF(effect_x, effect_y - 10, 0.8, GetRand(360), image_effect[index_effect], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//プレイヤーの座標
void Effect_ChangePlayer::SetPlayerLocation(const float& x, const float& y)
{
	effect_x = x;
	effect_y = y;
}

//削除 エフェクトが終了していればtrue
bool Effect_ChangePlayer::IsEffectFinished()
{
	if (index_effect >= max_index) return true;
	return false;
}
