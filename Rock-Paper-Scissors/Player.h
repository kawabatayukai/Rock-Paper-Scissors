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

	//ホーミングを特殊生成
	void Create_Homing(int jan_count, float x, float y,float r, float speed, Jan_Type type);

	//敵の座標を取得
	void SetEnemyLocation( const float x, const float y);

	int Get_OldX();                   //old_xの取得関数
	int Get_X();                      //xの取得
	int Get_OldY();                   //old_yの取得関数
	int Get_Y();                      //yの取得

	/*画像の変更取得*/
	void PlayerSwitch();

	/*画像の動作変更*/
	void PlayerChangeMoveimg();

	/*腕の描画・動き*/
	void ArmDrawMove() const;

	/*頭の描画・動き*/
	void HeadDrawMove() const;

	//プレイヤーのUI描画
	void PlayerDrawUI(int hp) const;

	//HP回復（引数 : 回復量）
	void Recover_HP(const unsigned int recovery);

	//向き取得 0:左　1:右
	int GetDirection() const { return dir; }

private:
	/********************   ジャンプ関係   ********************/

	float old_x = 0;          //前回の位置X
	float old_y = 0;          //前回の位置Y
	float y_add = 0;          //落下距離
	float g_add = 1.0f;       //重力加速度

	/**********************************************************/

	int image[10]; //画像
	int image_Jamp[2];

	int head_Image[1];

	int armL_Image[3];
	int armR_Image[3];

	int player_Image; //画像の配列保持

	int playerGetMove;   //移動保持

	int playerCount; //画像のフレームカウント

	int playerChange_Image; //画像変更

	int pCount; //最後の画像

	Jan_Type select_JanType;  //選択した"手"

	double jan_angle = 0;     //じゃん撃の角度
	int jan_interval = 0;     //じゃん撃発射間隔

	float enemy_x = 0;        //敵の座標ｘ
	float enemy_y = 0;        //敵の座標ｙ

	int image_JanType[3];     //選択じゃん撃画像
	int image_setsumei;       //操作説明用　モロ
	int hpImage;

	//向き（左右のみ）
	enum class DIRECTION
	{
		LEFT,
		RIGHT,
	};

	int ui_font;  //ui用フォントハンドル
};