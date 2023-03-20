#pragma once
#include"EnemyBase.h"
#include"Jangeki_Base.h"
#include"Jangeki_reflection.h"
#include"Player.h"
//9ステージ　敵キャラ
class Enemy_09 : public EnemyBase
{
public:
	//コンストラクタ 座標・属性を設定
	Enemy_09(float x, float y, Jan_Type type);

	~Enemy_09();                     //デストラクタ

	void Update() override;          //更新
	void Draw() const override;      //描画

	void Update_Jangeki() override;  //じゃん撃生成・更新

	void MoveEnmey_09();



	Jangeki_Reflection* reflection;

private:
	/********************   ジャンプ関係   ********************/

	float old_x = 0;          //前回の位置X
	float old_y = 0;          //前回の位置Y
	float y_add = 0;          //落下距離
	float g_add = 1.0f;       //重力加速度

	/**********************************************************/

	int teleport = 0;
	int frame_count = 0;       //じゃん撃発射用
	int interval = 0;
	int image;

	
	Player* type;

};


