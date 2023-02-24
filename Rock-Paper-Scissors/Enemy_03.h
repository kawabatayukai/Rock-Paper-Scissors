#pragma once
#include"EnemyBase.h"

//3ステージ　敵キャラ
class Enemy_03 : public EnemyBase
{
public:
	//コンストラクタ 座標・属性を設定
	Enemy_03(float x, float y, Jan_Type type);

	~Enemy_03();                     //デストラクタ

	void Update() override;          //更新
	void Draw() const override;      //描画

	void Update_Jangeki() override;  //じゃん撃生成・更新

private:
	/********************   ジャンプ関係   ********************/

	float old_x = 0; 
	//前回の位置X
	//float old_y = 0;          //前回の位置Y
	//float y_add = 0;          //落下距離
	float g_add = 1.0f;       //重力加速度
	float enemy_x = 0;

	/**********************************************************/

	int frame_count = 0;       //じゃん撃発射用
	
};


