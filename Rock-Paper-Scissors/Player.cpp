#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<string.h>
#include "Player.h"
#include"KeyManager.h"
#include"Debug_Manager.h"
#include"Jangeki_Homing.h"
#include"Jangeki_Player.h"
#include"GameData.h"
#include"SoundSystem.h"
#include"SortSave.h"

//じゃん撃発射間隔　（1秒）
#define PLAYER_JAN_INTERVAL 30


//コンストラクタ　　　　　　　　　　　　　  ｘ　ｙ　幅　　　高さ
Player::Player(float x, float y) : CharaBase(x, y, 57.0f, 100.0f)  //基底クラスのコンストラクタを呼ぶ
, player_Image(0), playerGetMove(0), playerCount(0), playerChange_Image(0), pCount(0), player_state(PLAYER_STATE::ALIVE), playerCount2(0), Prev_recoveryScore(0)
, obj_effect(nullptr), obj_effectchange(nullptr)
{
	speed = 7.0f;
	hp = 100;

	//向きを設定（右）
	dir = static_cast<int>(DIRECTION::RIGHT);//LEFT
	 
	//画像読み込み
	
	//顔
	head_Image[0] = LoadGraph("images/ワンパンマン目なし右.png");
	head_Image[1] = LoadGraph("images/ワンパンマン目なし左.png");
	head_Image[2] = LoadGraph("images/ワンパンマン目なし右弱.png");
	head_Image[3] = LoadGraph("images/ワンパンマン目なし左弱.png");
	//head_Image[0] = LoadGraph("images/ワンパンマン顔のみ右.png");
	//head_Image[1] = LoadGraph("images/ワンパンマン顔のみ左.png");

	//目
	eye_ImageR[0] = LoadGraph("images/ワンパンマン目のみ右.png");
	eye_ImageL[0] = LoadGraph("images/ワンパンマン目のみ左.png");
	eye_ImageR[1] = LoadGraph("images/ワンパンマン目つむし右.png");
	eye_ImageL[1] = LoadGraph("images/ワンパンマン目つむし左png");

	//体
	LoadDivGraph("images/ワンパンマン画像顔無しグー.png", 10, 5, 2, 100, 100, image[0]);
	LoadDivGraph("images/ワンパンマン画像顔無しチョキ.png", 10, 5, 2, 100, 100, image[1]);
	LoadDivGraph("images/ワンパンマン画像顔無しパー.png", 10, 5, 2, 100, 100, image[2]);

	image[0][4] = LoadGraph("images/ワンパンマンジャンプ画像腕無し右グー.png");
	image[0][9] = LoadGraph("images/ワンパンマンジャンプ画像腕無し左グー.png");

	image[1][4] = LoadGraph("images/ワンパンマンジャンプ画像腕無し右チョキ.png");
	image[1][9] = LoadGraph("images/ワンパンマンジャンプ画像腕無し左チョキ.png");

	image[2][4] = LoadGraph("images/ワンパンマンジャンプ画像腕無し右パー.png");
	image[2][9] = LoadGraph("images/ワンパンマンジャンプ画像腕無し左パー.png");

	//腕
	armL_Image[0] = LoadGraph("images/腕のみぐーh左.png");
	armR_Image[0] = LoadGraph("images/腕のみぐーh右.png");

	armL_Image[1] = LoadGraph("images/腕のみちょき左.png");
	armR_Image[1] = LoadGraph("images/腕のみちょき右.png");

	armL_Image[2] = LoadGraph("images/腕のみぱー左.png");
	armR_Image[2] = LoadGraph("images/腕のみぱー右.png");

	//死亡時
	image_death = LoadGraph("images/ワンパンマン顔のみ左弱.png");

	image_setsumei = LoadGraph("images/Setumei.png");
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, image_JanType);  //じゃん撃画像
	image_setsumei = LoadGraph("images/Janken/Setumei50ptg.png");
	image_set_circle = LoadGraph("images/Janken/Setumei_Select50.png");
	image_set_LTRT = LoadGraph("images/Janken/Setumei_LTRT_235_105.png");
	image_set_GPT = LoadGraph("images/Janken/Setumei_GTP.png");

	hpImage = LoadGraph("images/HitPoint.png");

	Init_Jangeki();       //じゃん撃を用意

	//デフォルトは グー
	select_JanType = Jan_Type::ROCK;

	//フォントを作成
	ui_font = CreateFontToHandle("メイリオ", 20, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);

	//フォントを作成
	name_font = CreateFontToHandle("メイリオ", 20, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);

	LoadDivGraph("images/stage09/teleport2.png", 15, 15, 1, 120, 150, img_Playeranim); //img_Playeranim
}

//コンストラクタ（コピーコンストラクタ）
Player::Player(const Player& player) : CharaBase(player.x, player.y, player.w, player.h)  //基底クラスのコンストラクタを呼ぶ
, player_Image(0), playerGetMove(0), playerCount(0), playerChange_Image(0), pCount(0), player_state(PLAYER_STATE::ALIVE), playerCount2(0)
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
	LoadDivGraph("images/ワンパンマンALL画像腕無し.png", 10, 5, 2, 100, 100, image[0]);
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, image_JanType);  //じゃん撃画像
	image_setsumei = LoadGraph("images/Janken/Setumei50ptg.png");
	image_set_circle = LoadGraph("images/Janken/Setumei_Select50.png");
	image_set_LTRT = LoadGraph("images/Janken/Setumei_LTRT_235_105.png");
	image_set_GPT = LoadGraph("images/Janken/Setumei_GTP.png");

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
	//プレイヤーのHPが0以下の時または時間切れ、"死んだ"状態に
	if (this->hp <= 0 || GameData::Get_Each_Time() <= 0) player_state = PLAYER_STATE::DEATH;

	//前回の座標ｘを保存
	old_x = x;

	//スコア1000毎にHP回復
	int _score = GameData::Get_MaxScore();
	if (_score % 300 == 0 && _score != Prev_recoveryScore)
	{
		Prev_recoveryScore = _score;
		Recover_HP(20);

		if (obj_effect == nullptr) obj_effect = new Effect_Player(x, y);
	}

	//エフェクト
	if (obj_effect != nullptr)
	{
		obj_effect->SetPlayerLocation(x, y);
		obj_effect->Update();

		//再生終了
		if (obj_effect->IsEffectFinished() == true)
		{
			delete obj_effect;
			obj_effect = nullptr;
		}
	}
	//エフェクト
	if (obj_effectchange != nullptr)
	{
		obj_effectchange->SetPlayerLocation(x, y);
		obj_effectchange->Update();

		//再生終了
		if (obj_effectchange->IsEffectFinished() == true)
		{
			delete obj_effectchange;
			obj_effectchange = nullptr;
		}
	}

	//死亡時以外
	if (player_state == PLAYER_STATE::ALIVE)
	{
		//左
		if (KeyManager::OnPadPressed(PAD_INPUT_LEFT))
		{
			x -= speed;

			if (KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 
				&& KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0 /*|| x < old_x*/) //右スティックが押されてない時
			{
				dir = static_cast<int>(DIRECTION::LEFT);   //向きを設定（左）
			}
		}
		playerChange_Image = 2; //switch文の割り当て番号

		//右
		if (KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
		{
			x += speed;
			if (KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 
				&& KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0 /*|| x > old_x*/) //右スティックが押されてない時
			{
				dir = static_cast<int>(DIRECTION::RIGHT);   //向きを設定（右）
			}
		}
		/*else
		{
			x--;
		}*/
		playerChange_Image = 1; //switch文の割り当て番号

		//画像の選択変更
		PlayerSwitch();

		//if (land_flg == true && KeyManager::OnPadClicked_LT())
		if (land_flg == true && KeyManager::OnPadClicked(PAD_INPUT_5))
		{
			g_add = -21.5f;    //重力加速度をマイナス値に
			land_flg = false;  //地面についていない

			//SE
			SoundSystem::PlaySE(SE::PLAYER_JUMP);
		}
	}
	else if(player_state == PLAYER_STATE::DEATH)
	{
		static bool isJumped;
		jan_angle = 0.0;

		if (land_flg == false && isJumped == false) 
		{
			land_flg = true;
		}

		if (land_flg == true)
		{
			isJumped = true;
			g_add = -24.5f;    //重力加速度をマイナス値に
			land_flg = false;  //地面についていない
		}
		w = 0;
		h = 0;

		if (y > 780.f)
		{
			player_state = PLAYER_STATE::DEATH_END;
		}
	}

	//じゃん撃
	Update_Jangeki();

	/********************   ジャンプ関係   ********************/

	y_add = (y - old_y) + g_add;  //今回の落下距離を設定

	//落下速度の制限
	if (player_state != PLAYER_STATE::DEATH)
	{
		if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);
	}


	old_y = y;                    //1フレーム前のｙ座標
	y += y_add;                   //落下距離をｙ座標に加算する
	g_add = _GRAVITY;              //重力加速度を初期化する

	if (y > old_y) land_flg = false;

	/**********************************************************/



//～～～～～～～～～～～～～～～～～～～～～～～～　照準　～～～～～～～～～～～～～～～～～～～～～～～～～～～

	static double old_angle;

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
			if (KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
			{
				//角度をなしにする
				jan_angle = 0;
			}
			if (jan_angle > (M_PI / 2) || jan_angle < (M_PI / -2))
			{
				dir = static_cast<int>(DIRECTION::LEFT);
			}
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false && 
			    KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			//角度をなしにする
			jan_angle = 0;
		}

		if (jan_angle > (M_PI / 2) || jan_angle < (M_PI / -2))
		{
			dir = static_cast<int>(DIRECTION::LEFT);
		}

		//左向きの時
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true)
		{
			if (/*jan_angle < 0*/KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
			{
				//角度をなしにする
				jan_angle = M_PI;
			}
			if (jan_angle < (M_PI / 2) && jan_angle > (M_PI / -2))
			{
				dir = static_cast<int>(DIRECTION::RIGHT);
			}
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false && 
			    KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			//角度をなしにする
			jan_angle = M_PI;
		}

		if (jan_angle < (M_PI / 2) && jan_angle > (M_PI / -2))
		{
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

	//角度を保持する
	if (old_angle != jan_angle)
	{
       old_angle = jan_angle;
	}
	

//～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～～
}

/* 頭の描画・動き)*/
void Player::HeadDrawMove() const
{
	///*********************
	//*                    *
	//*   頭の描画のみ     *
	//*                    *
	//*********************/

	//DrawRotaGraph(x + 3, y - 22, 1.0f, M_PI - jan_angle, head_Image[0], TRUE);

	/*HPが半分以上の時*/
	if (this->hp > 50)
	{
		/*右向き*/
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 0)
		{
			//DrawRotaGraph(x + 3, y - 22, 1.0f, M_PI, head_Image[0], TRUE);

			/*躍動感*/
			static int st = 0;
			switch (st)
			{
			case 0:
				if (playerCount % 200 != 0) //頭フレームの処理
				{
					DrawRotaGraph(x + 3, y - 22, 1.0f, M_PI, head_Image[0], TRUE);
				}
				else
				{
					st = 1;
				}
				break;
			case 1:
				if (playerCount % 50 != 0) //頭フレームの処理
				{
					DrawRotaGraph(x + 3, y - 18, 1.0f, M_PI, head_Image[0], TRUE);
				}
				else
				{
					st = 0;
				}
				break;
			}
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 1)
		{
			DrawRotaGraph(x + 3, y - 19, 1.0f, M_PI, head_Image[0], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)
		{
			DrawRotaGraph(x - 7, y - 19, 1.0f, M_PI, head_Image[0], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 3)
		{
			DrawRotaGraph(x + 5, y - 17, 1.0f, M_PI, head_Image[0], TRUE);
		}
		/*else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false) //ジャンプの時
		{
			DrawRotaGraph(x + 3, y - 22, 1.0f, M_PI, head_Image[0], TRUE);
		}*/

		/*左向き*/
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 5)
		{
			//DrawRotaGraph(x - 3, y - 22, 1.0f, 0, head_Image[1], TRUE);

			/*躍動感*/
			static int st = 0;
			switch (st)
			{
			case 0:
				if (playerCount % 200 != 0) //頭フレームの処理
				{
					DrawRotaGraph(x - 3, y - 22, 1.0f, 0, head_Image[1], TRUE);
				}
				else
				{
					st = 1;
				}
				break;
			case 1:
				if (playerCount % 50 != 0) //頭フレームの処理
				{
					DrawRotaGraph(x - 3, y - 18, 1.0f, 0, head_Image[1], TRUE);
				}
				else
				{
					st = 0;
				}
				break;
			}
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 6)
		{
			DrawRotaGraph(x - 3, y - 19, 1.0f, 0, head_Image[1], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)
		{
			DrawRotaGraph(x + 7, y - 19, 1.0f, 0, head_Image[1], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 8)
		{
			DrawRotaGraph(x - 5, y - 17, 1.0f, 0, head_Image[1], TRUE);
		}
		/*else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false) //ジャンプの時
		{
			DrawRotaGraph(x - 3, y - 22, 1.0f, 0, head_Image[1], TRUE);
		}*/
	}
	/*HPが半分以下の時*/
	else if (this->hp <= 50)
	{
		/*右向き*/
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 0)
		{
			/*躍動感*/
			static int st = 0;
			switch (st)
			{
			case 0:
				if (playerCount % 200 != 0) //頭フレームの処理
				{
					DrawRotaGraph(x + 3, y - 22, 1.0f, M_PI, head_Image[2], TRUE);
				}
				else
				{
					st = 1;
				}
				break;
			case 1:
				if (playerCount % 50 != 0) //頭フレームの処理
				{
					DrawRotaGraph(x + 3, y - 18, 1.0f, M_PI, head_Image[2], TRUE);
				}
				else
				{
					st = 0;
				}
				break;
			}
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 1)
		{
			DrawRotaGraph(x + 3, y - 19, 1.0f, M_PI, head_Image[2], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)
		{
			DrawRotaGraph(x - 7, y - 19, 1.0f, M_PI, head_Image[2], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 3)
		{
			DrawRotaGraph(x + 5, y - 17, 1.0f, M_PI, head_Image[2], TRUE);
		}

		/*左向き*/
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 5)
		{
			/*躍動感*/
			static int st = 0;
			switch (st)
			{
			case 0:
				if (playerCount % 200 != 0) //頭フレームの処理
				{
					DrawRotaGraph(x - 3, y - 22, 1.0f, 0, head_Image[3], TRUE);
				}
				else
				{
					st = 1;
				}
				break;
			case 1:
				if (playerCount % 50 != 0) //頭フレームの処理
				{
					DrawRotaGraph(x - 3, y - 18, 1.0f, 0, head_Image[3], TRUE);
				}
				else
				{
					st = 0;
				}
				break;
			}
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 6)
		{
			DrawRotaGraph(x - 3, y - 19, 1.0f, 0, head_Image[3], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)
		{
			DrawRotaGraph(x + 7, y - 19, 1.0f, 0, head_Image[3], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 8)
		{
			DrawRotaGraph(x - 5, y - 17, 1.0f, 0, head_Image[3], TRUE);
		}
	}

	///*********************
	//*                    *
	//*   頭の描画・動き   *
	//*                    *
	//*********************/

	/*右向き*/
	/*if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 0)
	{
		DrawRotaGraph(x + 3, y - 22, 1.0f, M_PI - jan_angle, head_Image[0], TRUE);
	}
	 if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 1)
	{
		DrawRotaGraph(x + 3, y - 19, 1.0f, M_PI - jan_angle, head_Image[0], TRUE);
	}
	 if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)
	{
		DrawRotaGraph(x - 7, y - 19, 1.0f, M_PI - jan_angle, head_Image[0], TRUE);
	}
	 if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 3)
	{
		DrawRotaGraph(x + 5, y - 17, 1.0f, M_PI - jan_angle, head_Image[0], TRUE);
	}*/
	/*if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false) //ジャンプの時
	{
		DrawRotaGraph(x + 3, y - 22, 1.0f, M_PI, head_Image[0], TRUE);
	}*/

	/*左向き*/
	/*if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 5)
	{
		DrawRotaGraph(x - 3, y - 22, 1.0f, M_PI - jan_angle, head_Image[1], TRUE);
	}
	 if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 6)
	{
		DrawRotaGraph(x - 3, y - 19, 1.0f, M_PI - jan_angle, head_Image[1], TRUE);
	}
	 if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)
	{
		DrawRotaGraph(x + 7, y - 19, 1.0f, M_PI - jan_angle, head_Image[1], TRUE);
	}
	 if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 8)
	{
		DrawRotaGraph(x - 5, y - 17, 1.0f, M_PI - jan_angle, head_Image[1], TRUE);
	}*/
	/*if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false) //ジャンプの時
	{
		DrawRotaGraph(x - 3, y - 22, 1.0f, 0, head_Image[1], TRUE);
	}*/
}

/*目の描画・動き*/
void Player::EyeDrawMove() const
{
	///*********************
	//*                    *
	//*   目の描画のみ     *
	//*                    *
	//*********************/

	/*右向き*/
	if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 0)
	{
		/*瞬き感*/
		static int st = 0;
		static int stk = 0;
		switch (st)
		{
		case 0:
			if (playerCount % 200 != 0) //頭フレームの処理
			{
				switch (stk)
				{
				case 0:
					if (playerCount % 120 != 0) //目フレームの処理
					{
						DrawRotaGraph(x + 6, y - 28, 1.0f, M_PI, eye_ImageR[0], TRUE);
					}
					else
					{
						stk = 1;
					}
					break;
				case 1:
					if (playerCount % 10 != 0) //目フレームの処理
					{
						DrawRotaGraph(x + 6, y - 28, 1.0f, M_PI, eye_ImageR[1], TRUE);
					}
					else
					{
						stk = 0;
					}
					break;
				}
			}
			else
			{
				st = 1;
			}
			break;
		case 1:
			if (playerCount % 50 != 0) //頭フレームの処理
			{
				switch (stk)
				{
				case 0:
					if (playerCount % 120 != 0) //目フレームの処理
					{
						DrawRotaGraph(x + 6, y - 24, 1.0f, M_PI, eye_ImageR[0], TRUE);
					}
					else
					{
						stk = 1;
					}
					break;
				case 1:
					if (playerCount % 10 != 0) //目フレームの処理
					{
						DrawRotaGraph(x + 6, y - 24, 1.0f, M_PI, eye_ImageR[1], TRUE);
					}
					else
					{
						stk = 0;
					}
					break;
				}
			}
			else
			{
				st = 0;
			}
			break;
		}
	}
	else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 1)
	{
		DrawRotaGraph(x + 6, y - 25, 1.0f, M_PI, eye_ImageR[0], TRUE);
		/*瞬き感*/
		//static int st = 0;
		//switch (st)
		//{
		//case 0:
		//	if (playerCount % 100 != 0) //10フレーム毎の処理
		//	{
		//		DrawRotaGraph(x + 6, y - 25, 1.0f, M_PI, eye_ImageR[0], TRUE);
		//	}
		//	else
		//	{
		//		st = 1;
		//	}
		//	break;
		//case 1:
		//	if (playerCount % 10 != 0) //10フレーム毎の処理
		//	{
		//		DrawRotaGraph(x + 6, y - 25, 1.0f, M_PI, eye_ImageR[1], TRUE);
		//	}
		//	else
		//	{
		//		st = 0;
		//	}
		//	break;
		//}
	}
	else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)
	{
		DrawRotaGraph(x - 3, y - 25, 1.0f, M_PI, eye_ImageR[0], TRUE);
	}
	else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 3)
	{
		DrawRotaGraph(x + 9, y - 23, 1.0f, M_PI, eye_ImageR[0], TRUE);
	}

	/*左向き*/
	if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 5)
	{
		/*瞬き感*/
		static int st = 0;
		static int stk = 0;
		switch (st)
		{
		case 0:
			if (playerCount % 200 != 0) //頭フレームの処理
			{
				switch (stk)
				{
				case 0:
					if (playerCount % 120 != 0) //目フレームの処理
					{
						DrawRotaGraph(x - 6, y - 28, 1.0f, 0, eye_ImageL[0], TRUE);
					}
					else
					{
						stk = 1;
					}
					break;
				case 1:
					if (playerCount % 10 != 0) //目フレームの処理
					{
						DrawRotaGraph(x - 6, y - 28, 1.0f, 0, eye_ImageL[1], TRUE);
					}
					else
					{
						stk = 0;
					}
					break;
				}
			}
			else
			{
				st = 1;
			}
			break;
		case 1:
			if (playerCount % 50 != 0) //頭フレームの処理
			{
				switch (stk)
				{
				case 0:
					if (playerCount % 120 != 0) //目フレームの処理
					{
						DrawRotaGraph(x - 6, y - 24, 1.0f, 0, eye_ImageL[0], TRUE);
					}
					else
					{
						stk = 1;
					}
					break;
				case 1:
					if (playerCount % 10 != 0) //目フレームの処理
					{
						DrawRotaGraph(x - 6, y - 24, 1.0f, 0, eye_ImageL[1], TRUE);
					}
					else
					{
						stk = 0;
					}
					break;
				}
			}
			else
			{
				st = 0;
			}
			break;
		}
	}
	else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 6)
	{
		DrawRotaGraph(x - 6, y - 25, 1.0f, 0, eye_ImageL[0], TRUE);
	}
	else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)
	{
		DrawRotaGraph(x + 3, y - 25, 1.0f, 0, eye_ImageL[0], TRUE);
	}
	else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 8)
	{
		DrawRotaGraph(x - 9, y - 23, 1.0f, 0, eye_ImageL[0], TRUE);
	}

	///*********************
	//*                    *
	//*       瞬きこみ     *
	//*                    *
	//*********************/

	/*static int st = 0;
	static int stk = 0;
	static int stky = 0;*/

	/*右向き*/
	//if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true)
	//{
	//	//static int st = 0;
	//	//static int stk = 0;
	//	if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 0)
	//	{
	//		/*瞬き感*/
	//		switch (st)
	//		{
	//		case 0:
	//			if (playerCount % 200 != 0) //頭フレームの処理
	//			{
	//				switch (stk)
	//				{
	//				case 0:
	//					if (playerCount % 120 != 0) //目フレームの処理
	//					{
	//						DrawRotaGraph(x + 6, y - 28, 1.0f, M_PI, eye_ImageR[0], TRUE);
	//					}
	//					else
	//					{
	//						stk = 1;
	//					}
	//					break;
	//				case 1:
	//					if (playerCount % 10 != 0) //目フレームの処理
	//					{
	//						DrawRotaGraph(x + 6, y - 28, 1.0f, M_PI, eye_ImageR[1], TRUE);
	//					}
	//					else
	//					{
	//						stk = 0;
	//					}
	//					break;
	//				}
	//			}
	//			else
	//			{
	//				st = 1;
	//			}
	//			break;
	//		case 1:
	//			if (playerCount % 50 != 0) //頭フレームの処理
	//			{
	//				switch (stk)
	//				{
	//				case 0:
	//					if (playerCount % 120 != 0) //目フレームの処理
	//					{
	//						DrawRotaGraph(x + 6, y - 24, 1.0f, M_PI, eye_ImageR[0], TRUE);
	//					}
	//					else
	//					{
	//						stk = 1;
	//					}
	//					break;
	//				case 1:
	//					if (playerCount % 10 != 0) //目フレームの処理
	//					{
	//						DrawRotaGraph(x + 6, y - 24, 1.0f, M_PI, eye_ImageR[1], TRUE);
	//					}
	//					else
	//					{
	//						stk = 0;
	//					}
	//					break;
	//				}
	//			}
	//			else
	//			{
	//				st = 0;
	//			}
	//			break;
	//		}
	//	}
	//	switch (stky)
	//	{
	//	case 0:
	//		if (playerCount2 % 120 != 0) //目フレームの処理
	//		{
	//			if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 1)
	//			{
	//				DrawRotaGraph(x + 6, y - 25, 1.0f, M_PI, eye_ImageR[0], TRUE);
	//			}
	//			if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)
	//			{
	//				DrawRotaGraph(x - 3, y - 25, 1.0f, M_PI, eye_ImageR[0], TRUE);
	//			}
	//			if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 3)
	//			{
	//				DrawRotaGraph(x + 9, y - 23, 1.0f, M_PI, eye_ImageR[0], TRUE);
	//			}
	//		}
	//		else
	//		{
	//			stky = 1;
	//		}
	//		break;
	//	case 1:
	//		if (playerCount2 % 10 != 0) //目フレームの処理
	//		{
	//			if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 1)
	//			{
	//				DrawRotaGraph(x + 6, y - 25, 1.0f, M_PI, eye_ImageR[1], TRUE);
	//			}
	//			if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)
	//			{
	//				DrawRotaGraph(x - 3, y - 25, 1.0f, M_PI, eye_ImageR[1], TRUE);
	//			}
	//			if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 3)
	//			{
	//				DrawRotaGraph(x + 9, y - 23, 1.0f, M_PI, eye_ImageR[1], TRUE);
	//			}
	//		}
	//		else
	//		{
	//			stky = 0;
	//		}
	//		break;
	//	}
	//}
	///*左向き*/
	//if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true)
	//{
	//	//static int st = 0;
	//	//static int stk = 0;
	//	if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 5)
	//	{
	//		/*瞬き感*/
	//		static int st = 0;
	//		static int stk = 0;
	//		switch (st)
	//		{
	//		case 0:
	//			if (playerCount % 200 != 0) //頭フレームの処理
	//			{
	//				switch (stk)
	//				{
	//				case 0:
	//					if (playerCount % 120 != 0) //目フレームの処理
	//					{
	//						DrawRotaGraph(x - 6, y - 28, 1.0f, 0, eye_ImageL[0], TRUE);
	//					}
	//					else
	//					{
	//						stk = 1;
	//					}
	//					break;
	//				case 1:
	//					if (playerCount % 10 != 0) //目フレームの処理
	//					{
	//						DrawRotaGraph(x - 6, y - 28, 1.0f, 0, eye_ImageL[1], TRUE);
	//					}
	//					else
	//					{
	//						stk = 0;
	//					}
	//					break;
	//				}
	//			}
	//			else
	//			{
	//				st = 1;
	//			}
	//			break;
	//		case 1:
	//			if (playerCount % 50 != 0) //頭フレームの処理
	//			{
	//				switch (stk)
	//				{
	//				case 0:
	//					if (playerCount % 120 != 0) //目フレームの処理
	//					{
	//						DrawRotaGraph(x - 6, y - 24, 1.0f, 0, eye_ImageL[0], TRUE);
	//					}
	//					else
	//					{
	//						stk = 1;
	//					}
	//					break;
	//				case 1:
	//					if (playerCount % 10 != 0) //目フレームの処理
	//					{
	//						DrawRotaGraph(x - 6, y - 24, 1.0f, 0, eye_ImageL[1], TRUE);
	//					}
	//					else
	//					{
	//						stk = 0;
	//					}
	//					break;
	//				}
	//			}
	//			else
	//			{
	//				st = 0;
	//			}
	//			break;
	//		}
	//	}
	//	switch (stky)
	//	{
	//	case 0:
	//		if (playerCount2 % 120 != 0) //目フレームの処理
	//		{
	//			if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 6)
	//			{
	//				DrawRotaGraph(x - 6, y - 25, 1.0f, 0, eye_ImageL[0], TRUE);
	//			}
	//			if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)
	//			{
	//				DrawRotaGraph(x + 3, y - 25, 1.0f, 0, eye_ImageL[0], TRUE);
	//			}
	//			if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 8)
	//			{
	//				DrawRotaGraph(x - 9, y - 23, 1.0f, 0, eye_ImageL[0], TRUE);
	//			}
	//		}
	//		else
	//		{
	//			stky = 1;
	//		}
	//		break;
	//	case 1:
	//		if (playerCount2 % 10 != 0) //目フレームの処理
	//		{
	//			if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 6)
	//			{
	//				DrawRotaGraph(x - 6, y - 25, 1.0f, 0, eye_ImageL[1], TRUE);
	//			}
	//			if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)
	//			{
	//				DrawRotaGraph(x + 3, y - 25, 1.0f, 0, eye_ImageL[1], TRUE);
	//			}
	//			if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 8)
	//			{
	//				DrawRotaGraph(x - 9, y - 23, 1.0f, 0, eye_ImageL[1], TRUE);
	//			}
	//		}
	//		else
	//		{
	//			stky = 0;
	//		}
	//		break;
	//	}
	//}
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

/*体の描画・動き*/
void Player::BodyDrawMove() const
{
	//中心から描画
	switch (select_JanType)
	{
	case Jan_Type::ROCK:
		DrawRotaGraphF(x, y, 1, 0, image[0][player_Image], TRUE);
		break;
	case Jan_Type::SCISSORS:
		DrawRotaGraphF(x, y, 1, 0, image[1][player_Image], TRUE);
		break;
	case Jan_Type::PAPER:
		DrawRotaGraphF(x, y, 1, 0, image[2][player_Image], TRUE);
		break;
	case Jan_Type::NONE:
		break;
	default:
		break;
	}
}

//プレイヤーのUI描画
void Player::PlayerDrawUI(int hp) const
{
	float draw_x = x - 50;  //描画ｘ
	float draw_y = y - 100; //描画ｙ

	int bar_color = 0x00ff00;
	if (hp <= 30) 
	{
		bar_color = 0xff0000;

		static int flash_count;       //点滅回数
		if (flash_count < 4)
		{
			static int frame_count;
			if (++frame_count < 10)
			{
				//枠
				DrawBoxAA(draw_x - 3, draw_y - 3, draw_x + 103, draw_y + 13, 0xffffff, TRUE);
				DrawBoxAA(draw_x, draw_y, (draw_x + 100), draw_y + 10, 0x000000, TRUE);
				//HP
				DrawBoxAA(draw_x, draw_y, (draw_x + hp), draw_y + 10, bar_color, TRUE);
			}
			else if (frame_count > 20)
			{
				frame_count = 0;
				flash_count++;
			}
		}
		else
		{
			//枠
			DrawBoxAA(draw_x - 3, draw_y - 3, draw_x + 103, draw_y + 13, 0xffffff, TRUE);
			DrawBoxAA(draw_x, draw_y, (draw_x + 100), draw_y + 10, 0x000000, TRUE);
			//HP
			DrawBoxAA(draw_x, draw_y, (draw_x + hp), draw_y + 10, bar_color, TRUE);
		}
	}
	else
	{
		//枠
		DrawBoxAA(draw_x - 3, draw_y - 3, draw_x + 103, draw_y + 13, 0xffffff, TRUE);
		DrawBoxAA(draw_x, draw_y, (draw_x + 100), draw_y + 10, 0x000000, TRUE);
		//HP
		DrawBoxAA(draw_x, draw_y, (draw_x + hp), draw_y + 10, bar_color, TRUE);
	}
}

//描画
void Player::Draw() const
{
	//じゃん撃描画
	Draw_Jangeki();

	//死亡時以外
	if (player_state == PLAYER_STATE::ALIVE)
	{
		//エフェクト
		if (obj_effectchange != nullptr)
		{
			obj_effectchange->Draw_Back();
		}
		else {};
		//エフェクト
		if (obj_effect != nullptr)
		{
			obj_effect->Draw_Back();
		}
		else {};

		//照準線        右スティックに入力がある時
		if (KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 &&
			KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			/*腕の描画だけ*/
			ArmDrawMove();
		}
		else
		{
			int vx = static_cast<int>(550 * cos(jan_angle));
			int vy = static_cast<int>(550 * sin(jan_angle));

			/*真っ直ぐな線の照準先*/
			//DrawLineAA(x, y, x + vx, y - vy, 0xffff00, 3); 

			/*腕の描画・動き*/
			ArmDrawMove();
		}
		//中心から描画
		BodyDrawMove();

		/*顔*/
		HeadDrawMove();

		//目
		EyeDrawMove();

		//エフェクト
		if (obj_effectchange != nullptr)
		{
			obj_effectchange->Draw_Front();
		}
		else {};
		//エフェクト
		if (obj_effect != nullptr)
		{
			obj_effect->Draw_Front();
		}
	}
	else
	{
		//死亡画像
		DrawRotaGraphF(x, y, 1, 0, image_death, TRUE);
	}

	PlayerDrawUI(GetHP());

	//テスト 選択じゃん撃
	DrawStringToHandle(30, 150, "RB : 発射", 0xffffff, ui_font);
	DrawStringToHandle(30, 180, "LB : ジャンプ", 0xffffff, ui_font);

	//名前表示
	for (int i = 0; i < 10; i++)
	{
		DrawFormatStringToHandle(x - 80, y - 80, 0x00ff00, name_font, "%10s", sortSave.getRankingData(i).name);
	}

	//テスト 110
	int circle_x = 0;
	switch (select_JanType)
	{
	case Jan_Type::ROCK:
		circle_x = 2;
		break;
	case Jan_Type::SCISSORS:
		circle_x = 1;
		break;
	case Jan_Type::PAPER:
		circle_x = 0;
		break;
	default:
		circle_x = 0;
		break;
	}

	DrawGraph(40, 40,  image_setsumei, TRUE);
	DrawGraph(50 + (circle_x * 60), 50, image_set_circle, TRUE);
	DrawGraph(13, 10, image_set_LTRT, TRUE);
	DrawGraph(55, 100, image_set_GPT, TRUE);

	//選択の演出 XYB
	if (KeyManager::OnPadPressed(PAD_INPUT_3))      //X
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 100);
		DrawCircle(75, 120, 15, 0xffffff, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (KeyManager::OnPadPressed(PAD_INPUT_4))  //Y
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 120);
		DrawCircle(135, 120, 15, 0xffffff, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (KeyManager::OnPadPressed(PAD_INPUT_B))  //B
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 120);
		DrawCircle(195, 120, 15, 0xffffff, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else {}

	// LT RT
	if (KeyManager::GetValue_LT() > 30)
	{
		//SetDrawBlendMode(DX_BLENDMODE_ADD, 30);
		DrawTriangleAA(33.f, 17.f, 33.f, 39.f, 23.f, 28.f, 0xffa500, TRUE);
		DrawBoxAA(33.f, 24.f, 60.f, 32.f, 0xffa500, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (KeyManager::GetValue_RT() > 30)
	{
		//SetDrawBlendMode(DX_BLENDMODE_ADD, 30);
		DrawTriangleAA(234.f, 17.f, 234.f, 39.f, 244.f, 28.f, 0xffa500, TRUE);
		DrawBoxAA(207.f, 24.f, 234.f, 32.f, 0xffa500, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	///*テレポート時のアニメーション*/
	//if (animflg == true)
	//{
	//	if(DrawGraph(x - 50, y - 50, img_Playeranim[animtimer / 2 % 15], TRUE));
	//}
}

/*画像の変更取得*/
void  Player::PlayerSwitch()
{
	/*プレイヤーの画像変更*/
	switch (playerChange_Image)
	{

	/***********
	* 左右移動 *
	************/

	case 1: //右移動
	   /*                右向き            接地                   右・押されてる                      */
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_RIGHT) /*|| x > old_x*/)
		{
			playerGetMove = 1;      //画像を取得
			playerCount++;          //フレームカウントを増やす
			PlayerChangeMoveimg();  //画像変更へ
			pCount = 0;             //動いてないとき用
			playerChange_Image = 0; //動いてないとき用
			break;
		}
		/*               左向き            接地                   右・押されてる                     */
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_RIGHT) /*|| x > old_x*/)
		{
			playerGetMove = 6;      //画像を取得
			playerCount++;          //フレームカウントを増やす
			PlayerChangeMoveimg();  //画像変更へ
			pCount = 5;             //動いてないとき用
			playerChange_Image = 0; //動いてないとき用
			break;
		}

		/*自動画像変更*/
		//if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && x > old_x)
		//{
		//	playerGetMove = 1;      //画像を取得
		//	playerCount++;          //フレームカウントを増やす
		//	PlayerChangeMoveimg();  //画像変更へ
		//	pCount = 0;             //動いてないとき用
		//	playerChange_Image = 0; //動いてないとき用
		//	break;
		//}
		//else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && x > old_x)
		//{
		//	playerGetMove = 6;      //画像を取得
		//	playerCount++;          //フレームカウントを増やす
		//	PlayerChangeMoveimg();  //画像変更へ
		//	pCount = 5;             //動いてないとき用
		//	playerChange_Image = 0; //動いてないとき用
		//	break;
		//}

		/*ジャンプの時*/
		/*         右向き         非接地     */
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false)
		{
			player_Image = 4;     //画像を取得
			break;
		}

	case 2: //左移動の時
	   /*               左向き            接地                   左・押されてる                     */
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_LEFT) /*|| x < old_x*/)
		{
			playerGetMove = 6;      //画像を取得
			playerCount++;          //フレームカウントを増やす
			PlayerChangeMoveimg();  //画像変更へ
			pCount = 5;             //動いてないとき用
			playerChange_Image = 0; //動いてないとき用
			break;
		}
		/*               右向き            接地                   左・押されてる                     */
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_LEFT) /*|| x < old_x*/)
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
		if (dir == static_cast<int>(DIRECTION::RIGHT) /*&& jan_angle < (M_PI / 2)*/ && KeyManager::OnPadPressed(PAD_INPUT_RIGHT)/* || x > old_x*/)
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
		else if (dir == static_cast<int>(DIRECTION::LEFT) && KeyManager::OnPadPressed(PAD_INPUT_RIGHT)/* || x > old_x*/)
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
		if (dir == static_cast<int>(DIRECTION::LEFT) /*&& jan_angle > (M_PI / 2)*/ && KeyManager::OnPadPressed(PAD_INPUT_LEFT)/* || x < old_x*/)
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
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && KeyManager::OnPadPressed(PAD_INPUT_LEFT)/* || x > old_x*/)
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

			//LT,RTで発射するじゃん撃属性を選択（セット）する
	static int select_num;

	if (KeyManager::OnPadClicked_RT()) select_num++, animflg = true; //アニメーション開始;
	if (select_num > 2) select_num = 0;

	if (KeyManager::OnPadClicked_LT()) select_num--, animflg = true; //アニメーション開始;
	if (select_num < 0) select_num = 2;

	//前回の属性
	Jan_Type old_type = select_JanType;

	// B,Y,X　ボタンで発射するじゃん撃属性を選択（セット）する
	if (KeyManager::OnPadClicked(PAD_INPUT_B))         //Bボタン
	{
		//  グーを選択 
		select_JanType = Jan_Type::ROCK;
		select_num = 2;
		animflg = true; //アニメーション開始
	}
	else if (KeyManager::OnPadClicked(PAD_INPUT_4))    //Yボタン
	{
		//  チョキを選択 
		select_JanType = Jan_Type::SCISSORS;
		select_num = 1;
		animflg = true; //アニメーション開始
	}
	else if (KeyManager::OnPadClicked(PAD_INPUT_3))    //Xボタン
	{
		//  パーを選択 
		select_JanType = Jan_Type::PAPER;
		select_num = 0;
		animflg = true; //アニメーション開始
	}
	else
	{

	}
	switch (select_num)
	{
	case 0:
		select_JanType = Jan_Type::PAPER;

		break;

	case 1:
		select_JanType = Jan_Type::SCISSORS;

		break;

	case 2:
		select_JanType = Jan_Type::ROCK;

		break;

	default:
		break;
	}

	/*アニメーションの処理*/
	if (animflg == true)
	{
		animtimer++;

		if (animtimer / 3 % 15 == 14)
		{

			if (anim_count == 0)
			{
				animtimer = 0;
				anim_count = 1;
			}
			else
			{
				animtimer = 0;
				animflg = false;
				anim_count = 0;
			}

		}
	}

	if (old_type != select_JanType)
	{
		//エフェクト生成
		if (obj_effectchange != nullptr)
		{
			delete obj_effectchange;
			obj_effectchange = nullptr;
		}
		if (obj_effectchange == nullptr)obj_effectchange = new Effect_ChangePlayer(select_JanType, x, y);
	}

	//select_JanType = static_cast<Jan_Type>(select_num);

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
	obj_jangeki[jan_count]->SetPlayerHoming();
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

//プレイヤーが死亡しているか
bool Player::IsDeathPlayer() const
{
	if (player_state == PLAYER_STATE::DEATH_END)
	{
		return true;
	}
	return false;
}

