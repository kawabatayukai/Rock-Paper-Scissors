#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<string.h>
#include "Player.h"
#include"KeyManager.h"
#include"Debug_Manager.h"
#include"Jangeki_Homing.h"
#include"Jangeki_Player.h"

//じゃん撃発射間隔　（1秒）
#define PLAYER_JAN_INTERVAL 30


//コンストラクタ　　　　　　　　　　　　　  ｘ　ｙ　幅　　　高さ
Player::Player(float x, float y) : CharaBase(x, y, 57.0f, 100.0f)  //基底クラスのコンストラクタを呼ぶ
, player_Image(0), playerGetMove(0), playerCount(0), playerChange_Image(0), pCount(0)
{
	speed = 7.0f;
	hp = 100;

	//向きを設定（右）
	dir = static_cast<int>(DIRECTION::RIGHT);//LEFT
	 
	//画像読み込み
	//image = LoadGraph("images/sd_body-1.png");
	LoadDivGraph("images/ワンパンマンALL画像腕無し3.png", 10, 5, 2, 100, 100, image);
	//LoadDivGraph("images/ワンパンマン画像顔無し.png", 10, 5, 2, 100, 100, image);

	//LoadDivGraph("images/ワンパンマンALL画像腕無し3.png", 2, 1, 2, 126, 125, image_Jamp);

	LoadDivGraph("images/ワンパンマンジャンプ画像腕無し.png", 3, 3, 1, 100, 100, image_JanType);  //じゃん撃画像

	image[4] = LoadGraph("images/ワンパンマンジャンプ画像腕無し右.png");
	image[9] = LoadGraph("images/ワンパンマンジャンプ画像腕無し左.png");

	image_setsumei = LoadGraph("images/Setumei.png");

	head_Image[0] = LoadGraph("images/ワンパンマン顔のみ.png");
	head_Image[1] = LoadGraph("images/ワンパンマン顔のみ左.png");

	armL_Image[0] = LoadGraph("images/腕のみぐーh左.png");
	armR_Image[0] = LoadGraph("images/腕のみぐーh右.png");

	armL_Image[1] = LoadGraph("images/腕のみちょき左.png");
	armR_Image[1] = LoadGraph("images/腕のみちょき右.png");

	armL_Image[2] = LoadGraph("images/腕のみぱー左.png");
	armR_Image[2] = LoadGraph("images/腕のみぱー右.png");

	hpImage = LoadGraph("images/HitPoint.png");

	Init_Jangeki();       //じゃん撃を用意

	//デフォルトは グー
	select_JanType = Jan_Type::ROCK;

	//フォントを作成
	ui_font = CreateFontToHandle("メイリオ", 20, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);
}

//コンストラクタ（コピーコンストラクタ）
Player::Player(const Player& player) : CharaBase(player.x, player.y, player.w, player.h)  //基底クラスのコンストラクタを呼ぶ
, player_Image(0), playerGetMove(0), playerCount(0), playerChange_Image(0), pCount(0)
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


	//this->image = player.image;             //プレイヤー画像
	this->select_JanType = player.select_JanType;    //選択した"手"
	this->jan_angle = player.jan_angle;              //じゃん撃角度
	LoadDivGraph("images/ワンパンマンALL画像腕無し.png", 10, 5, 2, 100, 100, image);
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, image_JanType);  //じゃん撃画像
	image_setsumei = LoadGraph("images/Setumei.png");

	armL_Image[0] = LoadGraph("images/腕のみぐーh左.png");
	armR_Image[0] = LoadGraph("images/腕のみぐーh右.png");

	armL_Image[1] = LoadGraph("images/腕のみちょき左.png");
	armR_Image[1] = LoadGraph("images/腕のみちょき右.png");

	armL_Image[2] = LoadGraph("images/腕のみぱー左.png");
	armR_Image[2] = LoadGraph("images/腕のみぱー右.png");

	hpImage = LoadGraph("images/HitPoint.png");

	//フォントを作成
	ui_font = CreateFontToHandle("メイリオ", 20, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);
}

//デストラクタ
Player::~Player()
{
	//フォントデータを削除
	DeleteFontToHandle(ui_font);
}

//更新
void Player::Update()
{
	//前回の座標ｘを保存
	old_x = x;

	//左
	if (KeyManager::OnPadPressed(PAD_INPUT_LEFT))
	{
		x -= speed;
		if (KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0) //右スティックが押されてない時
		{
			dir = static_cast<int>(DIRECTION::LEFT);   //向きを設定（左）
		}
	}
	playerChange_Image = 2; //switch文の割り当て番号

	//右
	if (KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
	{
		x += speed;
		if (KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0) //右スティックが押されてない時
		{
			dir = static_cast<int>(DIRECTION::RIGHT);   //向きを設定（右）
		}
	}
	playerChange_Image = 1; //switch文の割り当て番号

	//画像の選択変更
	PlayerSwitch();

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
		//右向きの時
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true)
		{
			if (/*jan_angle < 0*/KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0) jan_angle = 0;
			if (jan_angle > (M_PI / 2) || jan_angle < (M_PI / -2))
			{
				//jan_angle = (M_PI / 2);
				dir = static_cast<int>(DIRECTION::LEFT);
			}
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false && 
			    KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			jan_angle = 0;
		}

		if (jan_angle > (M_PI / 2) || jan_angle < (M_PI / -2))
		{
			//jan_angle = (M_PI / 2);
			dir = static_cast<int>(DIRECTION::LEFT);
		}

		//左向きの時
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true)
		{
			if (/*jan_angle < 0*/KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0) jan_angle = M_PI;
			if (jan_angle < (M_PI / 2) && jan_angle > (M_PI / -2))
			{
				//jan_angle = (M_PI / 2);
				dir = static_cast<int>(DIRECTION::RIGHT);
			}
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false && 
			    KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			jan_angle = M_PI;
		}

		if (jan_angle < (M_PI / 2) && jan_angle > (M_PI / -2))
		{
			//jan_angle = (M_PI / 2);
			dir = static_cast<int>(DIRECTION::RIGHT);
		}

		//上向きの時
		if (dir == static_cast<int>(DIRECTION::LEFT) && KeyManager::OnPadPressed(PAD_INPUT_UP) &&
			KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			jan_angle = jan_angle / 2;
		}
		if (dir == static_cast<int>(DIRECTION::LEFT) && KeyManager::OnPadPressed(PAD_INPUT_DOWN) &&
			KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			jan_angle = jan_angle / -2;
		}

		//下向きの時
		if (dir == static_cast<int>(DIRECTION::RIGHT) && KeyManager::OnPadPressed(PAD_INPUT_UP) &&
			KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			jan_angle = M_PI / 2;
		}
		if (dir == static_cast<int>(DIRECTION::RIGHT) && KeyManager::OnPadPressed(PAD_INPUT_DOWN) &&
			KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			jan_angle = M_PI / -2;
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

/* 頭の描画・動き(時間があったら)*/
void Player::HeadDrawMove() const
{
	///*********************
	//*                    *
	//*   頭の描画・動き   *
	//*                    *
	//*********************/

	//DrawRotaGraph(x + 3, y - 22, 1.0f, M_PI - jan_angle, head_Image[0], TRUE);
}

/*腕の描画・動き*/
void Player::ArmDrawMove() const
{
	/*********************
	*                    *
	*   腕の描画・動き   *
	*                    *
	*********************/

	int x = static_cast<int>(this->x);
	int y = static_cast<int>(this->y);

	switch (select_JanType)
	{
	case Jan_Type::ROCK: //グーの時

		// 左向き && 接地 && プレイヤー画像が中間の画像じゃない時  
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image != 2 && player_Image != 7) //左腕の動き
		{
			DrawRotaGraph(x - 20, y + 3, 1.0f, M_PI - jan_angle, armL_Image[0], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)//プレイヤー画像が中間の時
		{
			DrawRotaGraph(x - 1, y + 3, 1.0f, M_PI - jan_angle, armL_Image[0], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false) //ジャンプの時
		{
			DrawRotaGraph(x - 14, y - 5, 1.0f, M_PI - jan_angle, armL_Image[0], TRUE);
		}

		// 右向き && 接地 && プレイヤー画像が中間の画像じゃない時 
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image != 2 && player_Image != 7) //右腕の動き
		{
			DrawRotaGraph(x + 20, y + 3, 1.0f, M_PI - jan_angle, armR_Image[0], TRUE);
			//DrawRotaGraph(x + 8, y - 5, 1.0f, M_PI - jan_angle, armR_Image[0], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)//プレイヤー画像が中間の時
		{
			DrawRotaGraph(x + 1, y + 3, 1.0f, M_PI - jan_angle, armR_Image[0], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false) //ジャンプの時
		{
			DrawRotaGraph(x + 14, y - 5, 1.0f, M_PI - jan_angle, armR_Image[0], TRUE);
		}
		break;

	case Jan_Type::SCISSORS: //チョキの時

		// 左向き && 接地 && プレイヤー画像が中間の画像じゃない時  
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image != 2 && player_Image != 7) //左腕の動き
		{
			DrawRotaGraph(x - 20, y + 3, 1.0f, M_PI - jan_angle, armL_Image[1], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)//プレイヤー画像が中間の時
		{
			DrawRotaGraph(x - 1, y + 3, 1.0f, M_PI - jan_angle, armL_Image[1], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false) //ジャンプの時
		{
			DrawRotaGraph(x - 14, y - 5, 1.0f, M_PI - jan_angle, armL_Image[1], TRUE);
		}

		// 右向き && 接地 && プレイヤー画像が中間の画像じゃない時  
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image != 2 && player_Image != 7) //右腕の動き
		{
			DrawRotaGraph(x + 20, y + 3, 1.0f, M_PI - jan_angle, armR_Image[1], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)//プレイヤー画像が中間の時
		{
			DrawRotaGraph(x + 1, y + 3, 1.0f, M_PI - jan_angle, armR_Image[1], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false) //ジャンプの時
		{
			DrawRotaGraph(x + 14, y - 5, 1.0f, M_PI - jan_angle, armR_Image[1], TRUE);
		}
		break;

	case Jan_Type::PAPER: //パーの時

		// 左向き && 接地 && プレイヤー画像が中間の画像じゃない時  
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image != 2 && player_Image != 7) //左腕の動き
		{
			DrawRotaGraph(x - 20, y + 3, 1.0f, M_PI - jan_angle, armL_Image[2], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)//プレイヤー画像が中間の時
		{
			DrawRotaGraph(x - 1, y + 3, 1.0f, M_PI - jan_angle, armL_Image[2], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false) //ジャンプの時
		{
			DrawRotaGraph(x - 14, y - 5, 1.0f, M_PI - jan_angle, armL_Image[2], TRUE);
		}

		// 右向き && 接地 && プレイヤー画像が中間の画像じゃない時 
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image != 2 && player_Image != 7) //右腕の動き
		{
			DrawRotaGraph(x + 20, y + 3, 1.0f, M_PI - jan_angle, armR_Image[2], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)//プレイヤー画像が中間の時
		{
			DrawRotaGraph(x + 1, y + 3, 1.0f, M_PI - jan_angle, armR_Image[2], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false) //ジャンプの時
		{
			DrawRotaGraph(x + 14, y - 5, 1.0f, M_PI - jan_angle, armR_Image[2], TRUE);
		}
		break;
	default:
		break;
	}
}

//プレイヤーのUI描画
void Player::PlayerDrawUI(int hp) const
{
	/*switch (type)
	{
	case Jan_Type::ROCK:
		DrawRotaGraph(810, 60, 0.5, 0, typeImage[0], TRUE);
		break;
	case Jan_Type::SCISSORS:

		DrawRotaGraph(810, 60, 0.5, 0, typeImage[1], TRUE);
		break;
	case Jan_Type::PAPER:
		DrawRotaGraph(950, 60, 0.5, 0, typeImage[2], TRUE);
		break;
	default:
		break;
	}*/

	//DrawRotaGraph(200, 50, 0.5, 0, hpImage, TRUE);			//体力ゲージ枠
	//DrawBox(115, 33, 120 + static_cast<int>(hp * 2.54), 67, 0x00ff00, TRUE);	//体力ゲージ
	//DrawFormatString(200, 40, 0x0000ff, "残り:%d", hp);	//残り体力(数値)

	float draw_x = x - 50;  //描画ｘ
	float draw_y = y - 100; //描画ｙ

	int bar_color = 0x00ff00;

	//枠
	DrawBoxAA(draw_x - 3, draw_y - 3, draw_x + 103, draw_y + 13, 0xffffff, TRUE);
	DrawBoxAA(draw_x, draw_y, (draw_x + 100), draw_y + 10, 0x000000, TRUE);
	//HP
	DrawBoxAA(draw_x, draw_y, (draw_x + hp), draw_y + 10, bar_color, TRUE);
}

//描画
void Player::Draw() const
{
	//中心から描画
	//DrawRotaGraphF(x, y, 1, 0, image, TRUE,
		//dir == static_cast<int>(DIRECTION::RIGHT) ? TRUE : FALSE);  //向きによって反転

	//じゃん撃描画
	Draw_Jangeki();

	//照準線        右スティックに入力がある時
	if (  KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 &&
		  KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0 )
	{
		/*腕の描画だけ*/
		ArmDrawMove();
	}
	else
	{
		int vx = static_cast<int>(550 * cos(jan_angle));
		int vy = static_cast<int>(550 * sin(jan_angle));

		DrawLineAA(x, y, x + vx, y - vy, 0xffff00, 3);

		/*腕の描画・動き*/
		ArmDrawMove();
	}

#ifdef DEBUG_OFF_PLAYER

	//テスト HP表示
	//if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	//DrawFormatString((int)(x), (int)(y - 100), 0xffffff, "%s", dir == 0 ? "L" : "R");

	PlayerDrawUI(GetHP());

	//テスト 選択じゃん撃
	DrawStringToHandle(30, 105, "SELECT : ", 0xffffff, ui_font);
	DrawRotaGraph(165, 115, 0.5, 0, image_JanType[static_cast<int>(select_JanType)], TRUE);
	DrawStringToHandle(30, 150, "RB : 発射", 0xffffff, ui_font);
	DrawStringToHandle(30, 180, "LB : ジャンプ", 0xffffff, ui_font);

	//テスト
	//DrawGraph(20, 80, image_setsumei, TRUE);
	DrawRotaGraph(300, 130, 0.5, 0, image_setsumei, TRUE);

#endif // DEBUG_OFF_PLAYER

	//中心から描画
	DrawRotaGraphF(x, y, 1, 0, image[player_Image], TRUE);
	//DrawRotaGraphF(x, y, 1, 0, image[9], TRUE);
}

/*画像の変更取得*/
void  Player::PlayerSwitch()
{
	/*プレイヤーの画像変更*/
	switch (playerChange_Image)
	{
		/*左右移動*/
	case 1: //右移動
	   /*                右向き            接地                   右・押されてる                      */
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
		{
			playerGetMove = 1;      //画像を取得
			playerCount++;          //フレームカウントを増やす
			PlayerChangeMoveimg();  //画像変更へ
			pCount = 0;             //動いてないとき用
			playerChange_Image = 0; //動いてないとき用
			break;
		}
		/*               左向き            接地                   右・押されてる                     */
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
		{
			playerGetMove = 6;      //画像を取得
			playerCount++;          //フレームカウントを増やす
			PlayerChangeMoveimg();  //画像変更へ
			pCount = 5;             //動いてないとき用
			playerChange_Image = 0; //動いてないとき用
			break;
		}

		/*ジャンプの時*/
		/*         右向き         非接地     */
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false)
		{
			player_Image = 4;     //画像を取得
			break;
		}

	case 2: //左移動の時
	   /*               左向き            接地                   左・押されてる                     */
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_LEFT))
		{
			playerGetMove = 6;      //画像を取得
			playerCount++;          //フレームカウントを増やす
			PlayerChangeMoveimg();  //画像変更へ
			pCount = 5;             //動いてないとき用
			playerChange_Image = 0; //動いてないとき用
			break;
		}
		/*               右向き            接地                   左・押されてる                     */
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_LEFT))
		{
			playerGetMove = 1;      //画像を取得
			playerCount++;          //フレームカウントを増やす
			PlayerChangeMoveimg();  //画像変更へ
			pCount = 0;             //動いてないとき用
			playerChange_Image = 0; //動いてないとき用
			break;
		}

		/*ジャンプの時*/
		/*           左向き         非接地     */
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false)
		{
			player_Image = 9;     //画像を取得
			break;
		}


	case 0: //止まっている

		/*                              右向き            接地                                           押されてない   */
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_RIGHT) == FALSE)
		{
			pCount = 0;  //動いてないとき用
		}

		/*                           左向き            接地                                           押されてない  */
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_LEFT) == FALSE)
		{
			pCount = 5;  //動いてないとき用
		}
		playerGetMove = pCount; //最後に動いた時の画像
		playerCount++;          //フレームのカウント

		PlayerChangeMoveimg();  //画像変更へ
		break;

	default:
		break;
	}
}

/*画像の動作変更*/
void  Player::PlayerChangeMoveimg()
{
	static int std = 0; //画像の基準

	/*画像の保持*/
	switch (playerGetMove)
	{
		/*右移動*/
	case 1: //1の画像
		if (player_Image != 2 && player_Image != 3)
		{
			player_Image = 1;
			std = 1; //セット処理
		}
		break;
	case 2: //2の画像
		if (player_Image != 1 && player_Image != 3)
		{
			player_Image = 2;
			std = 2; //セット処理
		}
		break;
	case 3: //3の画像
		if (player_Image != 1 && player_Image != 2)
		{
			player_Image = 3;
			std = 3; //セット処理
		}
		break;

		/*左移動*/
	case 6: //6の画像
		if (player_Image != 7 && player_Image != 8)
		{
			player_Image = 6;
			std = 6; //セット処理
		}
		break;
	case 7: //7の画像
		if (player_Image != 6 && player_Image != 8)
		{
			player_Image = 7;
			std = 7; //セット処理
		}
		break;
	case 8: //8の画像
		if (player_Image != 6 && player_Image != 7)
		{
			player_Image = 8;
			std = 8; //セット処理
		}
		break;

		/*ジャンプ*/
	case 4: //4の画像
		player_Image = 4;
		std = 0; //セット処理
		break;
	case 9: //9の画像
		player_Image = 9;
		std = 0; //セット処理
		break;

		/*止まっている*/
	case 0: //0の画像
		player_Image = 0;
		std = 0; //セット処理
		break;
	case 5: //5の画像
		player_Image = 5;
		std = 0; //セット処理
		break;
	default:
		break;
	}

	/*走っているように画像変更*/
	if (playerCount % 10 == 0) //10フレーム毎の処理
	{
		/*右移動*/
		/*右向き && 照準が反対を向いてない && 右・押されている*/
		if (dir == static_cast<int>(DIRECTION::RIGHT) /*&& jan_angle < (M_PI / 2)*/ && KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
		{
			if (std == 1 && 2 > player_Image) // 画像 1
			{
				player_Image = 2;
				std = 2;
			}
			else if (std == 2 && 3 > player_Image) // 画像 2
			{
				player_Image = 3;
				std = 3;
			}
			else if (std == 3 && 2 < player_Image) //画像 3
			{
				player_Image = 2;
				std = 4;
			}
			else if (std == 4 && 1 < player_Image) // 画像 2
			{
				player_Image = 1;
				std = 1;
			}
			playerCount = 0;
		}
		/*左向き && 右・押されている*/
		else if (dir == static_cast<int>(DIRECTION::LEFT) && KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
		{
			if (std == 6 && 7 > player_Image) // 画像 6
			{
				player_Image = 7;
				std = 7;
			}
			else if (std == 7 && 8 > player_Image) // 画像 7
			{
				player_Image = 8;
				std = 8;
			}
			else if (std == 8 && 7 < player_Image) // 画像 8
			{
				player_Image = 7;
				std = 9;
			}
			else if (std == 9 && 6 < player_Image) // 画像 7
			{
				player_Image = 6;
				std = 6;
			}
			playerCount = 0;
		}

		/*左移動*/
		/*左向き && 照準が反対を向いてない && 左・押されている*/
		if (dir == static_cast<int>(DIRECTION::LEFT) /*&& jan_angle > (M_PI / 2)*/ && KeyManager::OnPadPressed(PAD_INPUT_LEFT))
		{
			if (std == 6 && 7 > player_Image) // 画像 6
			{
				player_Image = 7;
				std = 7;
			}
			else if (std == 7 && 8 > player_Image) // 画像 7
			{
				player_Image = 8;
				std = 8;
			}
			else if (std == 8 && 7 < player_Image) // 画像 8
			{
				player_Image = 7;
				std = 9;
			}
			else if (std == 9 && 6 < player_Image) // 画像 7
			{
				player_Image = 6;
				std = 6;
			}
			playerCount = 0;
		}
		/*右向き && 左・押されている*/
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && KeyManager::OnPadPressed(PAD_INPUT_LEFT))
		{
			if (std == 1 && 2 > player_Image) // 画像 1
			{
				player_Image = 2;
				std = 2;
			}
			else if (std == 2 && 3 > player_Image) // 画像 2
			{
				player_Image = 3;
				std = 3;
			}
			else if (std == 3 && 2 < player_Image) //画像 3
			{
				player_Image = 2;
				std = 4;
			}
			else if (std == 4 && 1 < player_Image) // 画像 2
			{
				player_Image = 1;
				std = 1;
			}
			playerCount = 0;
		}
	}
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
		obj_jangeki[jan_count]->SetTargetLocation(enemy_x, enemy_y);  //じゃん撃に敵の座標をセット

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
				obj_jangeki[jan_count] = new Jangeki_Player(x, y, radius, speed, jan_angle, select_JanType);
			}
			else
			{
				//じゃん撃生成        (角度指定なし)                                        
				obj_jangeki[jan_count] = new Jangeki_Player(x, y, radius, speed, select_JanType);
			}

			//間隔設定
			jan_interval = PLAYER_JAN_INTERVAL;
		}
	}

	//間隔
	jan_interval--;
	if (jan_interval < 0) jan_interval = 0;
}

//ホーミングを特殊生成
void Player::Create_Homing(int jan_count, float x, float y, float r, float speed, Jan_Type type)
{
	//不正な場合は処理しない
	if (jan_count > JANGEKI_MAX || jan_count < 0)  return;

	//一旦削除
	delete obj_jangeki[jan_count];
	
	//ホーミングを生成
	obj_jangeki[jan_count] = new Jangeki_Homing(x, y, r, speed, type);
}

//敵の座標を取得
void Player::SetEnemyLocation(const float x, const float y)
{
	this->enemy_x = x;
	this->enemy_y = y;
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

//HP回復（引数 : 回復量）
void Player::Recover_HP(const unsigned int recovery)
{
	//HP最大量（ここは要改善）
	int max_hp = 100;

	this->hp += recovery;
	if (hp > max_hp) hp = max_hp;
}