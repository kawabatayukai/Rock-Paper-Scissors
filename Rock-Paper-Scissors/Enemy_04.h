#pragma once
#include"EnemyBase.h"

//行動パターン04用
struct Pattern_04 {

	int moveflg; //0:動かない,1:動く
	float location_x; //目指している座標x
	float location_y; //目指している座標y
	float waitFlameTime; //待ち時間
	int next_index; //次配列のパターンの番号

};

//4ステージ　敵キャラ
class Enemy_04 : public EnemyBase
{
public:
	//コンストラクタ 座標・属性を設定
	Enemy_04(float x, float y, Jan_Type type);

	~Enemy_04();                     //デストラクタ

	void Update() override;          //更新
	void Draw() const override;      //描画

	void Update_Jangeki() override;  //じゃん撃生成・更新

	void Move_Pattern();

	void Change_JanType();           //ランダムに属性変化

	void Special_Action();			//特殊行動

	void Jan_360degrees(int count, float rad, float speed, Jan_Type type);

private:
	/********************   ジャンプ関係   ********************/

	//float old_x = 0;          //前回の位置X
	//float old_y = 0;          //前回の位置Y
	//float y_add = 0;          //落下距離
	//float g_add = 1.0f;       //重力加速度

	/**********************************************************/

	int waitTime = 0;				//待ち時間用変数
	int frame_count = 0;			//じゃん撃発射用
	Pattern_04 moveinfo[4];	    //行動パターン
	short current = 0;				//現在のパターン配列添字
	float enemy_x = 0;
	float enemy_y = 0;

	int enemy_image[10];			//画像用変数
	float angle;

	int specialTime = 0;
	bool specialFlg = false;
};


