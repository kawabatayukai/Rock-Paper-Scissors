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

//属性変更
void EnemyBase::SetType(Jan_Type type)
{
	this->e_type = type;
}

//HPをセット
void EnemyBase::SetHP(int damage)
{
	if (this->hp > 0)
	{
		hp -= damage;
	}
}


/*                   こんな感じで使えます                                  */
/*   obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY()); */

//追跡対象の座標をセット　 基本プレイヤー
void EnemyBase::SetPlayerLocation(const float player_x, const float player_y)
{
	this->player_x = player_x;
	this->player_y = player_y;
}
