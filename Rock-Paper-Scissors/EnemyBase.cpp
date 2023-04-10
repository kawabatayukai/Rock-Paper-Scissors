#include "EnemyBase.h"

//�R���X�g���N�^                                         
EnemyBase::EnemyBase(float x, float y, float w, float h, Jan_Type type)
	: e_type(type), CharaBase(x, y, w, h)   //���N���X�̃R���X�g���N�^�Ăяo��
{
}

//�f�X�g���N�^
EnemyBase::~EnemyBase()
{
	delete[] obj_jangeki;
}

//�����ύX
void EnemyBase::SetType(Jan_Type type)
{
	this->e_type = type;
}

//HP���Z�b�g
void EnemyBase::SetHP(int damage)
{
	if (this->hp > 0)
	{
		hp -= damage;
	}
}

//HP�񕜁i���� : �񕜗ʁj
void EnemyBase::Recover_HP(const unsigned int recovery)
{
	//HP�ő�ʁi�����͗v���P�j
	int max_hp = 100;

	this->hp += recovery;
	if (hp > max_hp) hp = max_hp;
}

/*                   ����Ȋ����Ŏg���܂�                                  */
/*   obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY()); */

//�ǐՑΏۂ̍��W���Z�b�g�@ ��{�v���C���[
void EnemyBase::SetPlayerLocation(const float player_x, const float player_y)
{
	this->player_x = player_x;
	this->player_y = player_y;
}
