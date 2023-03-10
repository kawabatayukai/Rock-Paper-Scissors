#pragma once
#include"EnemyBase.h"

//行動パターン07用
struct Pattern_07
{
	int moveflag;       //0:動かない　1:動く
	float location_x;   //目標座標ｘ
	float location_y;   //目標座標ｙ


	int next_index;     //次の配列(パターン)番号
};

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

	void Move_Pattern();             //行動パターンに沿った行動

private:
	/********************   ジャンプ関係   ********************/

	float old_x = 0;          //前回の位置X
	float old_y = 0;          //前回の位置Y
	float y_add = 0;          //落下距離
	float g_add = 1.0f;       //重力加速度

	/**********************************************************/

	int frame_count = 0;       //じゃん撃発射用

	Pattern_07 moveinfo[20];   //行動パターン
	short current = 0;         //現在のパターン配列添字
};


