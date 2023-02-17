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

//HP���Z�b�g
void EnemyBase::SetHP(int damage)
{
	if (this->hp > 0)
	{
		hp -= damage;
	}
}
