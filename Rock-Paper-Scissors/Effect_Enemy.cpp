#include"Effect_Enemy.h"
#include"DxLib.h"

//�R���X�g���N�^
Effect_Enemy::Effect_Enemy(const float& x, const float& y, Jan_Type enemyType)
	:index_effect(0), max_index(15), effect_x(x), effect_y(y), frame_count(0)
{
	image_effect = new int[max_index];
	
	switch (enemyType)
	{
	case Jan_Type::ROCK:
		LoadDivGraph("images/Effect/change_red.png", 15, 5, 3, 120, 120, image_effect);
		break;
	case Jan_Type::SCISSORS:
		LoadDivGraph("images/Effect/change_yellow.png", 15, 5, 3, 120, 120, image_effect);
		break;
	case Jan_Type::PAPER:
		LoadDivGraph("images/Effect/change_blue.png", 15, 5, 3, 120, 120, image_effect);
		break;
	case Jan_Type::NONE:
		break;
	default:
		break;
	}
}

//�f�X�g���N�^
Effect_Enemy::~Effect_Enemy()
{
	delete[] image_effect;
}

//�X�V
void Effect_Enemy::Update()
{
	if (++frame_count % 3 == 0)
	{
		if (index_effect < max_index) index_effect++;
	}
}

//�`��
void Effect_Enemy::Draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (frame_count * 2));
	DrawRotaGraphF(effect_x, effect_y - 10, 1.5, 0, image_effect[index_effect], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


//�v���C���[�̍��W
void Effect_Enemy::SetEnemyLocation(const float& x, const float& y)
{
	effect_x = x;
	effect_y = y;
}

//�폜 �G�t�F�N�g���I�����Ă����true
bool Effect_Enemy::IsEffectFinished()
{
	if (index_effect >= max_index) return true;
	return false;
}
