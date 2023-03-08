#pragma once
#include "CharaBase.h"

//プレイヤークラス　CharaBaseを継承
class Player : public CharaBase
{
public:
	//コンストラクタ
	Player(float x, float y);
	Player(const Player& player);

	~Player();                       //デストラクタ

	void Update() override;          //更新
	void Draw() const override;      //描画

	void Update_Jangeki() override;  //じゃん撃生成・更新

	int Get_OldX();                   //old_xの取得関数
	int Get_X();                      //xの取得
	int Get_OldY();                   //old_yの取得関数
	int Get_Y();                      //yの取得

private:
	/********************   ジャンプ関係   ********************/

	float old_x = 0;          //前回の位置X
	float old_y = 0;          //前回の位置Y
	float y_add = 0;          //落下距離
	float g_add = 1.0f;       //重力加速度

	/**********************************************************/

	int image = 0;  //画像用

	Jan_Type select_JanType;  //選択した"手"

	double jan_angle = 0;     //じゃん撃の角度
	int jan_interval = 0;     //じゃん撃発射間隔

	int image_JanType[3];     //選択じゃん撃画像
	int image_setsumei;       //操作説明用　モロ

	//向き（左右のみ）
	enum class DIRECTION
	{
		LEFT,
		RIGHT,
	};
};

