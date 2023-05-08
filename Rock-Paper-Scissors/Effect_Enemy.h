#pragma once
#include"Jangeki_Base.h"

//属性変化
class Effect_Enemy
{
public:
	Effect_Enemy(const float& x, const float& y, Jan_Type enemyType = Jan_Type::ROCK);
	~Effect_Enemy();

	void Update();
	void Draw() const;

	//Enemyの座標
	void SetEnemyLocation(const float& x = 0.f, const float& y = 0.f);

	//削除 エフェクトが終了していればtrue
	bool IsEffectFinished();

private:
	float effect_x;
	float effect_y;

	int* image_effect;   //画像
	int index_effect;    //配列操作
	const int max_index; //画像最大数
	int frame_count;     //フレームカウンター
};
