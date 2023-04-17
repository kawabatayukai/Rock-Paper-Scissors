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

	void AttackPattern_1();          //行動ループ1
	void AttackPattern_2();          //行動ループ2
	void AttackPattern_3();          //行動ループ3
	void SpeedUp();                  //特殊行動1   speed = 8.0f
	void Teleportation();            //特殊行動2   プレイヤーの後方側に移動し、接近してくる

	void AttackPattern_00();         //旧行動ループ2(保存用)

	void decision_Direction();       //向きを乱数で決める関数
	void jump_Direction();           //ジャンプするかを乱数で決める関数
	void jump();                     //ジャンプ
	void low_jump();                 //低いジャンプ

	float Get_OldY();                   //old_yの取得関数
	float Get_Y();                      //yの取得

private:
	/********************   ジャンプ関係   ********************/

	float old_x = 0;              //前回の位置X
	float old_y = 0;              //前回の位置Y
	float y_add = 0;              //落下距離
	float g_add = 1.0f;           //重力加速度

	/********************  行動パターン関係  ******************/

	int  attack_pattern = 0;      //攻撃パターン変数
	bool jump_flg = false;        //ジャンプ用フラグ　　       ジャンプさせる:true   ジャンプしない:false
	int  jump_cnt = 0;            //ジャンプカウント
	bool teleport_Flg = true;     //瞬間移動フラグ              瞬間移動する:true     瞬間移動しない:false
	bool P1_side = false;         //パターン2時の位置フラグ     左側:true             右側:false
	int  floor = 5;
	int  ChangeCnt = 0;           //敵の属性変化までのカウント用変数

	/**********************************************************/

	int frame_count = 0;          //じゃん撃発射用
	int images[3];                //敵画像
	Jan_Type old_type;            //前回の敵ジャンケン属性
};


