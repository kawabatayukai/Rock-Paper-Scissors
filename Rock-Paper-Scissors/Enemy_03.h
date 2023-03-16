#pragma once
#include"EnemyBase.h"

//行動パターン03用
struct Pattern_03 {

	int moveflg; //0:動く,1:動かない
	float location_x; //目指している座標x
	float location_y; //目指している座標y
	int next_index; //次配列のパターンの番号
	int enemywaitTime;//エネミーの待ち時間

};

//3ステージ　敵キャラ
class Enemy_03 : public EnemyBase
{
public:
	//コンストラクタ 座標・属性を設定
	Enemy_03(float x, float y, Jan_Type type);

	~Enemy_03();                     //デストラクタ

	void Update() override;          //更新
	void Draw() const override;    //描画

	void Update_Jangeki() override;  //じゃん撃生成・更新

	void Move_Pattern();

	int GetWaitTime()const;

	void ChangeDir(float x);


private:
	/********************   ジャンプ関係   ********************/

	//float old_x = 0; 

	//前回の位置X
	float old_x = 0;    //前回の位置X
	float old_y = 0;	//前回の位置Y
	float y_add = 0;     //落下距離  
	float g_add = 1.0f;//重力加速度

	/**********************************************************/
	int frame_count = 0;       //じゃん撃発射用

	int waitcount = 0;//待ち時間カウント

	Pattern_03 moveinfo[20]; //行動パターン20種
	short current = 0; //現在のパターン配列添字

	int enemyimage[2];      //敵画像配列
};


