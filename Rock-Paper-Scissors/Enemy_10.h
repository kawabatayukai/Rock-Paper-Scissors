#pragma once
#include"EnemyBase.h"

const static float V = 1.f;

/*敵：移動・動きの情報*/
struct MoveInformation10
{
	int pattern;               /*方法・パターン*/

	//T_Location TargetLocation; /*目的地*/
	//
	float x;                   /*目的地 X座標*/
	float y;                   /*目的地 Y座標*/

	int next;                  /*次の(配列)処理*/

	int waitTimeFlame;         /*(待ちなど)時間*/

	int attackPattern;         /*攻撃方法*/
};

//10ステージ　敵キャラ
class Enemy_10 : public EnemyBase
{
public:
	//コンストラクタ 座標・属性を設定
	Enemy_10(float x, float y, Jan_Type type);

	~Enemy_10();                     //デストラクタ

	void Update() override;          //更新
	void Draw() const override;      //描画

	void Update_Jangeki() override;  //じゃん撃生成・更新

	/*敵の動き*/
	void Move();

	/*敵の動き*/
	void Enemy10_Move();

	/*画像の変更取得*/
	void EnemySwitch();

	/*画像の動作変更*/
	void EnemyChangeMoveimg();

private:
	/********************   ジャンプ関係   ********************/

	float old_x = 0;          //前回の位置X
	float old_y = 0;          //前回の位置Y
	float y_add = 0;          //落下距離
	float g_add = 1.0f;       //重力加速度

	/**********************************************************/

	int frame_count = 0;       //じゃん撃発射用

	float v = V;
	float a = 0.6f;

	int image[10]; //画像

	int jangeki_Set; //じゃん撃セット用変数

	int jan_count;

	int enemy_Image; //画像の配列保持

	int enemyGetMove;   //移動保持

	int enemyCount; //画像のフレームカウント

	int enemyChange_Image; //画像変更

	int pCount; //最後の画像

	//向き（左右のみ）
	enum class DIRECTION
	{
		LEFT,
		RIGHT,
	};

	/*敵：移動, 目的地, NEXT, 待ち時間, 攻撃方法の配列*/
	MoveInformation10 MoveInfo[10] = {};
};


