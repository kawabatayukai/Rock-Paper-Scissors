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

	void decision_Direction();       //向きを乱数で決める関数
	void jump_Direction();           //ジャンプするかを乱数で決める関数
	void jump();                     //ジャンプ
	void low_jump();                 //低いジャンプ
	void smoke();                    //煙エフェクト関数

	float Get_OldY();                   //old_yの取得関数
	float Get_Y();                      //yの取得
	int   Get_smokeflg();               //煙エフェクトのフラグの取得
	float GetSpeed();                   //スピード取得

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
	bool attack1_InitFlg = false; //攻撃パターン1の初期化フラグ
	bool attack2_Flg = true;      //攻撃パターン2開始前フラグ  初期化:true       初期化終了:false
	bool P1_side = false;         //パターン2時の位置フラグ      左側:true             右側:false
	int  floor = 5;
	int  ChangeCnt = 0;           //敵の属性変化までのカウント用変数

	int  SpeedUpTime = 0;         //SpeedUp中のカウント

	bool TeleportFlg = false;     //瞬間移動接触処理フラグ     瞬間移動接触:true    それ以外:false
	bool TeleportInit = true;     //瞬間移動接触処理初期化フラグ     初期化:true  初期化終了:false
	int  TeleportTime = 0;        //瞬間移動開始までのカウント

	bool smokeFlg = true;         //煙エフェクトのフラグ
	int  smokeImage[10];          //煙画像
	int  smokeCnt = 0;            //煙用カウント変数

	/**********************************************************/

	int frame_count = 0;          //じゃん撃発射用
	int images[12];                //敵画像
	float bef_x = 0;              //前回のx座標(画像表示用)
	float bef_y = 0;              //前回のy座標(画像表示用)
	Jan_Type old_type;            //前回の敵ジャンケン属性
};