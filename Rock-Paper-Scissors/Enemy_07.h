#pragma once
#include"EnemyBase.h"
#include"Player.h"

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
	
/*---------------------------- パターンでない行動 --------------------------------------*/

	void Move_Controller();         //行動制御

	//プレイヤーがリング上 
	void Move_ON_RING(float& target_x, float& target_y);                            

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

	Pattern_07 moveinfo[20];   //行動パターン
	short current = 0;         //現在のパターン配列添字

	//自身から見たプレイヤーの状態
	enum class PLAYER_STATE
	{
		ON_RING,         //リング上
		DO_NOT,          //判断しない
	};
	PLAYER_STATE Player_State;

	//行動の種類
	enum class ACT_TYPE
	{
		NO_ACT,           //行動なし
		
		LEFT_TO_RIGHT,    //左から右（最終的に右）
		RIGHT_TO_LEFT,    //右から左（最終的に左）
	};
	ACT_TYPE Now_Action;  //実行中の行動

//------------------------ テスト ------------------------


};


