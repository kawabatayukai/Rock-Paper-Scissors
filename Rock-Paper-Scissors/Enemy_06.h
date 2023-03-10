#pragma once
#include"EnemyBase.h"

//6ステージ　敵キャラ
class Enemy_06 : public EnemyBase
{
public:
	//コンストラクタ 座標・属性を設定
	Enemy_06(float x, float y, Jan_Type type);

	~Enemy_06();                     //デストラクタ

	void Update() override;          //更新
	void Draw() const override;      //描画

	void Update_Jangeki() override;  //じゃん撃生成・更新

	int Get_OldY();                   //old_yの取得関数
	int Get_Y();                      //yの取得

private:
	/********************   ジャンプ関係   ********************/

	float old_x = 0;          //前回の位置X
	float old_y = 0;          //前回の位置Y
	float y_add = 0;          //落下距離
	float g_add = 1.0f;       //重力加速度

	int  attack_pattern = 0;      //攻撃パターン変数
	bool jump_flg = false;        //ジャンプ用フラグ　　ジャンプさせる:true   ジャンプしない:false
	int  jump_cnt = 0;            //ジャンプカウント
	bool direction_flg = false;   //左右反転フラグ      左向き:true           右向き:false

	/**********************************************************/

	int frame_count = 0;       //じゃん撃発射用
};


