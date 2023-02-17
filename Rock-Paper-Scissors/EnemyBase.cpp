#include "EnemyBase.h"

//コンストラクタ                                         
EnemyBase::EnemyBase(float x, float y, float w, float h, Jan_Type type)
	: e_type(type), CharaBase(x, y, w, h)   //基底クラスのコンストラクタ呼び出し
{
}

//デストラクタ
EnemyBase::~EnemyBase()
{
	delete[] obj_jangeki;
}

//HPをセット
void EnemyBase::SetHP(int damage)
{
	if (this->hp > 0)
	{
		hp -= damage;
	}
}
