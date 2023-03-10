#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<string.h>
#include "Player.h"
#include"KeyManager.h"

//じゃん撃発射間隔　（1秒）
#define PLAYER_JAN_INTERVAL 60


//コンストラクタ　　　　　　　　　　　　　  ｘ　ｙ　幅　　　高さ
Player::Player(float x, float y) : CharaBase(x, y, 57.0f, 100.0f)  //基底クラスのコンストラクタを呼ぶ
{
	speed = 7.0f;
	hp = 100;

	//向きを設定（左）
	dir = static_cast<int>(DIRECTION::LEFT);

	//画像読み込み
	image = LoadGraph("images/sd_body-1.png");
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, image_JanType);  //じゃん撃画像

	Init_Jangeki();       //じゃん撃を用意

	//デフォルトは グー
	select_JanType = Jan_Type::ROCK;
}

//コンストラクタ（コピーコンストラクタ）
Player::Player(const Player& player) : CharaBase(player.x, player.y, player.w, player.h)  //基底クラスのコンストラクタを呼ぶ
{
	//メンバ変数を引数のオブジェクトの内容で初期化する
	// 
	//
	//メンバにポインタ変数を含むため注意


/************ 基底クラス　CharaBase　の内容 ************/

	this->speed = player.speed;       //スピード
	this->hp = player.hp;          //HP
	this->dir = player.dir;         //向き
	this->land_flg = player.land_flg;    //接地フラグ

	Init_Jangeki();       //じゃん撃を用意（じゃん撃は引き継がない）

/************* ここまで　CharaBase　の内容 *************/


	this->image = player.image;             //プレイヤー画像
	this->select_JanType = player.select_JanType;    //選択した"手"
	this->jan_angle = player.jan_angle;              //じゃん撃角度


	//選択じゃん撃画像コピー（多分いらない）
	memcpy_s(image_JanType, sizeof(player.image_JanType), player.image_JanType, sizeof(player.image_JanType));
}

//デストラクタ
Player::~Player()
{

}

//更新
void Player::Update()
{
	//左
	if (KeyManager::OnPadPressed(PAD_INPUT_LEFT))
	{
		x -= speed;
		dir = static_cast<int>(DIRECTION::LEFT);   //向きを設定（左）
	}

	//右
	if (KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
	{
		x += speed;
		dir = static_cast<int>(DIRECTION::RIGHT);  //向きを設定（右）
	}

	//じゃん撃
	Update_Jangeki();

	/********************   ジャンプ関係   ********************/

	if (land_flg == true && KeyManager::OnPadClicked(PAD_INPUT_5))
	{
		g_add = -21.5f;    //重力加速度をマイナス値に
		land_flg = false;  //地面についていない
	}

	y_add = (y - old_y) + g_add;  //今回の落下距離を設定

	//落下速度の制限
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1フレーム前のｙ座標
	y += y_add;                   //落下距離をｙ座標に加算する
	g_add = _GRAVITY;              //重力加速度を初期化する

	/**********************************************************/



//～～～～～～～～～～～～～～～～～～～～～～～～　照準　～～～～～～～～～～～～～～～～～～～～～～～～～～～

	//右スティックのアナログ入力を取得
	double right_x = static_cast<double>(KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X));   //ｘ
	double right_y = static_cast<double>(KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y));   //ｙ

	//入力値を制限(わかりやすく)
	if (right_x > 30000) right_x = 30000;
	if (right_x < -30000) right_x = -30000;
	if (right_y > 30000) right_y = 30000;
	if (right_y < -30000) right_y = -30000;

	//逆正接で照準の角度を求める
	jan_angle = atan2(static_cast<double>(right_y - y), static_cast<double>(right_x - x));


	//角度を制限する
	{
		if (land_flg == true)
		{
			//右向きの時
			if (dir == static_cast<int>(DIRECTION::RIGHT))
			{
				if (jan_angle < 0) jan_angle = 0;
				//if (jan_angle > (M_PI / 2)) jan_angle = (M_PI / 2);
			}
		}
		if (jan_angle > (M_PI / 2)) //左向きに
		{
			dir = static_cast<int>(DIRECTION::LEFT);
		}

		if (land_flg == true)
		{
			 //左向きの時
			 if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true)
			 {
				 if (jan_angle < 0) jan_angle = M_PI;
				 //if (jan_angle < (M_PI / 2)) jan_angle = (M_PI / 2);
			 }
		}
		if (jan_angle < (M_PI / 2)) //右向きに
		{
			dir = static_cast<int>(DIRECTION::RIGHT);
		}
	}



	////プレイヤー座標
	//DrawFormatString(300, 200, 0xffffff, "Player_X : %f", x);
	//DrawFormatString(300, 230, 0xffffff, "Player_Y : %f", y);

	////右スティックアナログ入力値
	//DrawFormatString(500, 300, 0xffffff, "Right_X : %d", static_cast<int>(right_x));
	//DrawFormatString(500, 330, 0xffffff, "Right_Y : %d", static_cast<int>(right_y));

	//DrawFormatString(500, 430, 0xffffff, "逆正接座標_X : %lf", static_cast<double>(right_x - x));
	//DrawFormatString(500, 460, 0xffffff, "逆正接座標_Y : %lf", static_cast<double>(right_y - y));
	//DrawFormatString(500, 490, 0xffffff, "逆正接(弧度法) : %lf", jan_angle * 180 / M_PI);
	//DrawFormatString(500, 360, 0xffffff, "Angle : %lf", jan_angle);

//～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～
}

//描画
void Player::Draw() const
{
	//中心から描画
	DrawRotaGraphF(x, y, 1, 0, image, TRUE,
		dir == static_cast<int>(DIRECTION::RIGHT) ? TRUE : FALSE);  //向きによって反転

	//じゃん撃描画
	Draw_Jangeki();

	//照準線        右スティックに入力がある時
	if (  KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 &&
		  KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0 )
	{}
	else
	{
		int vx = static_cast<int>(550 * cos(jan_angle));
		int vy = static_cast<int>(550 * sin(jan_angle));

		DrawLineAA(x, y, x + vx, y - vy, 0xffff00, 5);
	}


	//テスト HP表示
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	DrawFormatString((int)(x), (int)(y - 100), 0xffffff, "%s", dir == 0 ? "L" : "R");

	//テスト 選択じゃん撃
	DrawString(30, 100, "SELECT : ", 0xffffff);
	DrawRotaGraph(160, 100, 0.5, 0, image_JanType[static_cast<int>(select_JanType)], TRUE);
	DrawString(30, 150, "RB : 発射", 0xffffff);
}

//じゃん撃生成・更新
void Player::Update_Jangeki()
{
	int jan_count;

	//じゃん撃配列をひとつずつ
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//配列の jan_count 番目がnullptr（空要素）ならそれ以上処理しない
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();

		//画面外で削除する
		if (obj_jangeki[jan_count]->CheckScreenOut() == true)
		{
			DeleteJangeki(jan_count);
			jan_count--;
		}
	}

	/*********************** ↓↓ 発射・生成 ↓↓ ***********************/

	// B,Y,X　ボタンで発射するじゃん撃属性を選択（セット）する
	if (KeyManager::OnPadClicked(PAD_INPUT_B))         //Bボタン
	{
		//  グーを選択 
		select_JanType = Jan_Type::ROCK;
	}
	else if (KeyManager::OnPadClicked(PAD_INPUT_4))    //Yボタン
	{
		//  チョキを選択 
		select_JanType = Jan_Type::SCISSORS;
	}
	else if (KeyManager::OnPadClicked(PAD_INPUT_3))    //Xボタン
	{
		//  パーを選択 
		select_JanType = Jan_Type::PAPER;
	}
	else {}


	//配列の空要素
	if (jan_count < JANGEKI_MAX && obj_jangeki[jan_count] == nullptr)
	{
		float radius = 35.5f;   //半径
		float speed = 8.0f;     //スピード

		//左向き マイナス方向　　右向き　プラス方向
		speed = speed * (dir == static_cast<int>(DIRECTION::LEFT) ? -1 : 1);

		//RBボタンで選択した属性のじゃん撃を発射
		if (KeyManager::OnPadClicked(PAD_INPUT_6) == true && jan_interval == 0)
		{
			//角度がある時（照準使用時）
			if (jan_angle != 0)
			{
				//じゃん撃生成        (角度指定付き)                                        
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, jan_angle, select_JanType);
			}
			else
			{
				//じゃん撃生成        (角度指定なし)                                        
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, select_JanType);
			}

			//間隔設定
			jan_interval = PLAYER_JAN_INTERVAL;
		}
	}

	//間隔
	jan_interval--;
	if (jan_interval < 0) jan_interval = 0;
}

//old_yの取得関数
int Player::Get_OldX()
{
	return static_cast<int>(old_x);
}

//yの取得関数
int Player::Get_X()
{
	return static_cast<int>(x);
}

//old_yの取得関数
int Player::Get_OldY()
{
	return static_cast<int>(old_y);
}

//yの取得関数
int Player::Get_Y()
{
	return static_cast<int>(y);
}