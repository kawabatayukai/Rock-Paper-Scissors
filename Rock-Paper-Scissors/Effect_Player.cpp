#include"Effect_Player.h"
#include"DxLib.h"

//�R���X�g���N�^
Effect_Player::Effect_Player(const float& x, const float& y)
	:index_effect(0), max_index(15), effect_x(x), effect_y(y), frame_count(0)
{
	image_effect = new int[max_index];
	LoadDivGraph("images/Effect/recovery2.png", 15, 5, 3, 120, 120, image_effect);
	se_rec = LoadSoundMem("Sound/Player/recovery.wav");
	//SetVolumeSoundMem(255, se_rec);
}

//�f�X�g���N�^
Effect_Player::~Effect_Player()
{
	delete image_effect;
	DeleteSoundMem(se_rec);
}

//�X�V
void Effect_Player::Update()
{
	if (++frame_count % 3 == 0)
	{
		if (index_effect < max_index) index_effect++;
	}
	if(CheckSoundMem(se_rec)==0)PlaySoundMem(se_rec, DX_PLAYTYPE_BACK);
}

//�`��
void Effect_Player::Draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawRotaGraphF(effect_x, effect_y + 20, 2, 0, image_effect[index_effect], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�`��w��
void Effect_Player::Draw_Back() const
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 150);
	DrawRotaGraphF(effect_x, effect_y -10 , 1.3, 0, image_effect[index_effect], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�`��O��
void Effect_Player::Draw_Front() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawRotaGraphF(effect_x, effect_y - 10, 1.3, 0, image_effect[index_effect], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�v���C���[�̍��W
void Effect_Player::SetPlayerLocation(const float& x, const float& y)
{
	effect_x = x;
	effect_y = y;
}

//�폜 �G�t�F�N�g���I�����Ă����true
bool Effect_Player::IsEffectFinished()
{
	if (index_effect >= max_index) return true;
	return false;
}
