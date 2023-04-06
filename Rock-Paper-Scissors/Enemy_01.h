#pragma once
#include"EnemyBase.h"

//1ステージ　敵キャラ
class Enemy_01 : public EnemyBase
{
public:
	//コンストラクタ 座標・属性を設定
	Enemy_01(float x, float y, Jan_Type type);

	~Enemy_01();                     //デストラクタ

	void Update() override;          //更新
	void Draw() const override;      //描画

	void Update_Jangeki() override;  //じゃん撃生成・更新


	//ジャンプ（ジャンプ力）
	void Jump_Enemy(float g_add = -21.5f);

/*---------------------------- パターン行動 --------------------------------------*/

	//行動制御
	void Move_Controller();

	//左右移動
	void Action01_LR(float& target_x, float& target_y);

	//ジャンプで足場を渡る
	void Action02_Jump(float& target_x, float& target_y);

	//足場上を往復する
	void Action03_Floor_LR(float& target_x, float& target_y);

	//足場を左から降りる
	void Action04_GetOff_Floor_LEFT(float& target_x, float& target_y);

	//プレイヤー目掛けてじゃん撃を発射する
	void Fire_JanTakeAim(const float& player_x, const float& player_y);

/*--------------------------------------------------------------------------------*/

private:
	/********************   ジャンプ関係   ********************/

	float old_x = 0;          //前回の位置X
	float old_y = 0;          //前回の位置Y
	float y_add = 0;          //落下距離
	float g_add = 1.0f;       //重力加速度

	/**********************************************************/

	int jan_count;           //じゃん撃配列の空要素先頭番号が入る（やむなし）

	//行動
	enum class ACT_TYPE
	{
		NOT_ACT,             //行動なし
		 
		LEFT_TO_RIGHT,       //左右移動
		CROSS_FLOOR,         //足場を渡る
		LEFT_TO_RIGHT_FLOOR, //足場上で左右に往復
	};
	ACT_TYPE Now_Action;

	int current_action;        //現在のアクション
};


