#pragma once
#include"EnemyBase.h"
#include"Player.h"

//7ステージ　敵キャラ
class Enemy_07 : public EnemyBase
{
public:
	//コンストラクタ 座標・属性を設定
	Enemy_07(float x, float y, Jan_Type type);

	~Enemy_07();                     //デストラクタ

	void Update() override;          //更新
	void Draw() const override;      //描画

	void Update_Jangeki() override;  //じゃん撃生成・更新

/*---------------------------- パターンでない行動 --------------------------------------*/

	void Move_Controller();          //行動制御

	//void SelectAction_From_State();  //プレイヤーの状態から行動を決める


	//プレイヤーがリング上 
	void Move_ON_RING(float& target_x, float& target_y);                            

	//プレイヤーが足場（空中）上
	void Move_ON_FLOOR(float& target_x, float& target_y);

	//プレイヤーが足場で3秒以上
	void Move_ON_FLOOR_LURK(float& target_x, float& target_y);

	//プレイヤーの状況を取得
	void CheckPlayerState(const Player* player);

/*--------------------------------------------------------------------------------------*/

	void Jan_360degrees(int count, float rad, float speed, Jan_Type type);  //360度発射（必殺）
	void Jan_Vertical(int count, float rad, float speed, Jan_Type type);    //縦にたくさん発射（特殊）

private:
	/********************   ジャンプ関係   ********************/

	float old_x = 0;          //前回の位置X
	float old_y = 0;          //前回の位置Y
	float y_add = 0;          //落下距離
	float g_add = 1.0f;       //重力加速度

	/**********************************************************/

	int frame_count = 0;       //じゃん撃発射用


	//自身から見たプレイヤーの状態
	enum class PLAYER_STATE
	{
		ON_RING,         //リング上
		ON_FLOOR,        //足場上
		ON_FLOOR_LURK,   //足場上で潜んでいる

		DO_NOT,          //判断しない
	};
	PLAYER_STATE Player_State;

	//行動の種類
	enum class ACT_TYPE
	{
		NO_ACT,             //行動なし
		
		LEFT_TO_RIGHT,      //左から右（最終的に右）
		RIGHT_TO_LEFT,      //右から左（最終的に左）
		CLIMB_CORNER_LEFT,  //コーナーに上る（左）
		CLIMB_CORNER_RIGHT, //コーナーに上る（右）
		CROSS_FLOOR_LEFT,   //足場を渡る（左から右）
		CROSS_FLOOR_RIGHT,  //足場を渡る（右から左）
	};
	ACT_TYPE Now_Action;    //実行中のAction（行動）
	ACT_TYPE Pre_Action;    //１つ前のAction（行動）

//------------------------ テスト ------------------------


};


