#pragma once
#include"CharaBase.h"

//死亡したときに別オブジェクトを生成する
class Enemy_Death : public CharaBase
{
public:
	//引数 : 死亡時の座標、ステージ番号
	Enemy_Death(const float& x, const float& y, const int& stage_num = 0, const Jan_Type& type = Jan_Type::NONE);
	~Enemy_Death();

	void Update() override;
	void Draw() const override;

	bool IsDeathEnd();  //死亡演出完了

private:
	int image_death;

	float old_x = 0;          //前回の位置X
	float old_y = 0;          //前回の位置Y
	float y_add = 0;          //落下距離
	float g_add = 1.0f;       //重力加速度
};
