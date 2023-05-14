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
	void Jan_360degrees();
	void Jan_40degrees();
	void SpecialMoveEnmey();

	void HP(); 

	void frameUP();
	void frameDown();

	bool Getflg();
	void Tflg();
	void Fflg();
	int Rand();

	bool Spflg = true;  //特殊行動フラグ
	bool animflg = false;	//アニメーションフラグ
	bool ranimflg = false; //反射アニメーション
	bool Ranimflg = false;	//再再生用


	Jangeki_Reflection* reflection;


private:
	/********************   ジャンプ関係   ********************/

	float old_x = 0;          //前回の位置X
	float old_y = 0;          //前回の位置Y
	float y_add = 0;          //落下距離
	float g_add = 1.0f;       //重力加速度

	/**********************************************************/

	int teleport = 300;
	int frame_count = 0;       //じゃん撃発射用
	int interval = 0;
	int Rimage;
	int image;
	int janFrame = 75;
	int count = 0;
	int SPcount = 0;
	
	bool rflg = false; //反射用
	
	int animtimer = 0;

	
	int jan_count;
	
	Player* type;
	//アニメーション用画像変数
	int img_teleport[15];	//再生
	int img_teleport2[15];	//逆再生
	float before_x = 0;
	float before_y = 0;
	int anim_count = 0;  //アニメーション回数

	int refanim[15];

};


