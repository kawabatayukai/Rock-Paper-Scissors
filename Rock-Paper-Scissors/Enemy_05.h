#pragma once
#include"EnemyBase.h"
#include"MobEnemy_05.h"
#include"Jangeki_reflection.h"

//5ステージ　敵キャラ
class Enemy_05 : public EnemyBase
{
public:
	//コンストラクタ 座標・属性を設定
	Enemy_05(float x, float y, Jan_Type type);

	~Enemy_05();                     //デストラクタ

	void Update() override;          //更新
	void Draw() const override;      //描画

	void Update_Jangeki() override;  //じゃん撃生成・更新

	void GetMobEnemy(MobEnemy_05** mobenemy);

	bool respawn_mobenemy();
	void SetRespawn(bool flag);

	void Change_JanType();

	Jangeki_Reflection* reflection;

private:
	/********************   ジャンプ関係   ********************/

	float old_x = 0;          //前回の位置X
	float old_y = 0;          //前回の位置Y
	float y_add = 0;          //落下距離
	float g_add = 1.0f;       //重力加速度

	/**********************************************************/

	int frame_count = 0;       //じゃん撃発射用

	int Enemy_image;		   //敵画像用
	int Enemy_jamp_image;	   //敵ジャンプ時画像用
	int Movepattern;			//動きのパターン
	int Movetimer;				//動き用のタイマー

	bool respawn;

	MobEnemy_05** mob;
};


