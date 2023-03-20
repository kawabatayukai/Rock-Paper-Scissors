#pragma once
#include"EnemyBase.h"


//2ステージ　敵キャラ
class Enemy_02 : public EnemyBase
{
public:
	//コンストラクタ 座標・属性を設定
	Enemy_02(float x, float y, Jan_Type type);

	~Enemy_02();                     //デストラクタ

	void Update() override;          //更新
	void Draw() const override;      //描画

	void Update_Jangeki() override;  //じゃん撃生成・更新

	int Get_OldY();                   //old_yの取得関数
	int Get_Y();                      //yの取得

	void Jan_360degrees(int count, float rad, float speed, Jan_Type type);
private:
	/********************   ジャンプ関係   ********************/

	float old_x = 0;          //前回の位置X
	float old_y = 0;          //前回の位置Y

	float y_add = 0;          //落下距離
	float x_add = 1;
	float x_sdd = 1;
	float x_zdd = 1;

	float g_add = 1.0f;       //重力加速度
	float g_sdd = 1.0f;
	float g_zdd = 1.0f;


	bool jump_flg = false;        //ジャンプ用フラグ　　ジャンプさせる:true   ジャンプしない:false
	bool Stop_flg = false;        //ジャンプ用フラグ　　ジャンプさせる:true   ジャンプしない:false
	int  jump_cnt =0;            //ジャンプカウント
	bool direction_flg = false;   //左右反転フラグ      左向き:true   
	/**********************************************************/
	int waitTime = 5;			//待ち時間用変数
	int frame_count = 0;       //じゃん撃発射用
	short current = 0; //現在のパターン配列添字
	
};


