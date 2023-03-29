#include "Enemy_07.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Homing.h"
#include"Jangeki_Vertical.h"
#include<typeinfo>

#define _USE_MATH_DEFINES
#include<math.h>

//定数　
namespace _CONSTANTS_07
{
	const float RING_LEFT  = 250.0f;    //リング左端
	const float RING_RIGHT = 1030.0f;   //リング右端
	const float RING_HEIGHT = 590.0f;   //リングの高さ

	const float RING_CENTER = 640.0f;   //リングの中心

	const float CORNER_LEFT  = 235.0f;  //左コーナートップ (中心ｘ座標)
	const float CORNER_RIGHT = 1045.0f; //右コーナートップ (中心ｘ座標)
	const float CORNER_Y = 440.0f;      //コーナーの高さ（共通）

	// "足場"は画面左から順に 1,2,3,....と番号をつける
	const float FLOOR_NO_01 = 95.0f;    //足場１ (中心ｘ座標)
	const float FLOOR_NO_02 = 490.0f;   //足場２ (中心ｘ座標)
	const float FLOOR_NO_03 = 790.0f;   //足場３ (中心ｘ座標)
	const float FLOOR_NO_04 = 1185.0f;  //足場４ (中心ｘ座標)

	const float FLOOR_NO_01_04_Y = 230.0f;  // 足場１，４のｙ座標
	const float FLOOR_NO_02_03_Y = 110.0f;  // 足場２，３のｙ座標

	const float OUT_RING_LEFT = 120.0f;     //場外左
	const float OUT_RING_RIGHT = 1160.0f;   //場外右

	//テスト表示用
	char state_str [][20] = { "ON_RING","ON_FLOOR","ON_FLOOR_LURK","OUT_RING","DO_NOT" };   
	char action_str[][20] = { "NO_ACT","LEFT_TO_RIGHT","RIGHT_TO_LEFT"
		                     ,"CLIMB_CORNER_LEFT", "CLIMB_CORNER_RIGHT"
		                     ,"CROSS_FLOOR_LEFT","CROSS_FLOOR_RIGHT"
	                         ,"DIVE_OUT_LEFT","DIVE_OUT_RIGHT"};
}

//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_07::Enemy_07(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type), init_speed(4.0f), jan_count(0), draw_angle(0.0)
, Player_State(PLAYER_STATE::DO_NOT), Now_Action(ACT_TYPE::NO_ACT), Pre_Action(ACT_TYPE::NO_ACT)
{
	speed = 4.0f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //じゃん撃を用意

}

//デストラクタ
Enemy_07::~Enemy_07()
{
	
}


//更新
void Enemy_07::Update()
{
	//Move_Pattern();
	Move_Controller();

	//じゃん撃更新・生成
	Update_Jangeki();


	/********************   ジャンプ関係   ********************/

	//if (land_flg == true)    //GetRand(30) == 3　のところがジャンプの条件
	//{
	//	g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
	//	land_flg = false;  //地面についていない
	//}

	y_add = (y - old_y) + g_add;  //今回の落下距離を設定

	//落下速度の制限
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1フレーム前のｙ座標
	y += y_add;                   //落下距離をｙ座標に加算する
	g_add = _GRAVITY;             //重力加速度を初期化する

	/**********************************************************/
}

//描画
void Enemy_07::Draw() const
{
	//中心から描画
	DrawRotaGraphF(x, y, 1, draw_angle, image, TRUE);

	//じゃん撃描画
	Draw_Jangeki();

	//テスト
	//if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	//else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);

	LPCTSTR string = _CONSTANTS_07::state_str[static_cast<int>(Player_State)];
	LPCTSTR string_act = _CONSTANTS_07::action_str[static_cast<int>(Now_Action)];
	LPCTSTR string_pre = _CONSTANTS_07::action_str[static_cast<int>(Pre_Action)];

	DrawString(23, 580, string, 0x00ff00);
	DrawString(23, 610, string_act, 0x00ff00);
	DrawString(23, 640, string_pre, 0x00ff00);
}

//じゃん撃生成・更新
void Enemy_07::Update_Jangeki()
{
	//int jan_count;

	//じゃん撃配列をひとつずつ
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//配列の jan_count 番目がnullptr（空要素）ならそれ以上処理しない
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();

		//ホーミングじゃん撃であればプレイヤーの座標をセットする
		obj_jangeki[jan_count]->SetTargetLocation(player_x, player_y);

		//画面外で削除する
		if (obj_jangeki[jan_count]->CheckScreenOut() == true)
		{
			DeleteJangeki(jan_count);
			jan_count--;
		}
	}

	/*********************** ↓↓ 発射・生成 ↓↓ ***********************/
	//配列の空要素                                                     　じゃん撃発射 ON
	if (jan_count < JANGEKI_MAX && obj_jangeki[jan_count] == nullptr)
	{
		float radius = 25.5f;   //半径
		float speed = 6.0f;     //スピード

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		////生成
		//if (0)
		//{
		//	switch (GetRand(2))
		//	{
		//	case 0:
		//		Jan_360degrees(jan_count, radius, speed, type);
		//		break;

		//	case 1:
		//		obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type);
		//		break;

		//	case 2:
		//		Jan_Vertical(jan_count, radius, speed, type);
		//		break;

		//	default:
		//		break;

		//	obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, this->speed, type);
		//	}

		//}

	}

}

//ジャンプ（ジャンプ力）
void Enemy_07::Jump_Enemy(float g_add)
{
	//マイナス値でなければ処理しない
	if (g_add > 0) return;

	//接地していれば
	if (land_flg == true)
	{
		this->g_add = g_add;    //重力加速度をマイナス値に　
		land_flg = false;       //地面についていない
	}
}

//ランダムに属性変化
void Enemy_07::Change_JanType()
{
	//現在の属性と異なる2属性のうちランダム
	switch (this -> e_type)
	{
	case Jan_Type::ROCK:

		e_type = GetRand(1) == 1 ? Jan_Type::PAPER : Jan_Type::SCISSORS;
		break;

	case Jan_Type::SCISSORS:

		e_type = GetRand(1) == 1 ? Jan_Type::PAPER : Jan_Type::ROCK;
		break;

	case Jan_Type::PAPER:

		e_type = GetRand(1) == 1 ? Jan_Type::ROCK : Jan_Type::SCISSORS;
		break;

	default:
		break;
	}

	return;
}

/*--------------------------------------------------------------------------------------*/

//行動制御
void Enemy_07::Move_Controller()
{
	//目標座標
	float target_x = 0;
	float target_y = 0;

	//移動量
	float move_x = x;
	float move_y = y;

	//プレイヤーの状態によって行動を決める
	switch (Player_State)
	{
	case PLAYER_STATE::ON_RING:       //リング上

		Move_ON_RING(target_x, target_y);
		break;

	case PLAYER_STATE::ON_FLOOR:      //足場上

		Move_ON_FLOOR(target_x, target_y);
		break;

	case PLAYER_STATE::ON_FLOOR_LURK: //足場上で3秒以上

		Move_ON_FLOOR_LURK(target_x, target_y);
		break;

	case PLAYER_STATE::OUT_RING:      //場外

		Move_OUT_RING(target_x, target_y);
		break;

	default:

		target_x = 1280 / 2;
		break;
	}

	//x座標が目標と不一致
	if (x != target_x)
	{
		//目標の方が大きい（目標は右方向）
		if (x < target_x)
		{
			move_x += speed;      //右移動（正の値）

			//目標を超えた場合
			if (x <= target_x && target_x <= move_x)
			{
				move_x = target_x;     //目標座標で固定
			}
		}
		else
		{
			move_x -= speed; //左移動（負の値）

			//目標を超えた場合
			if (move_x <= target_x && target_x <= x)
			{
				move_x = target_x;     //目標座標で固定
			}
		}
	}

	//移動を反映
	x = move_x;
	y = move_y;
}

//プレイヤーがリング上 
void Enemy_07::Move_ON_RING(float& target_x, float& target_y)
{
	//右（左）から　左（右）　と目標座標が切り替わる

	//目標座標(1番目)と一致しているか
	static bool match = false;

	//生成するじゃん撃の半径
	float radius = 25.5f;

	//ランダムな属性を生成
	Jan_Type type = static_cast<Jan_Type>(GetRand(2));

	//行動中でない
	if (Now_Action == ACT_TYPE::NO_ACT)
	{
		//プレイヤーが半分より左側
		if (player_x < (1280 / 2))
		{
			Now_Action = ACT_TYPE::RIGHT_TO_LEFT;  //右→左
		}
		else
		{
			Now_Action = ACT_TYPE::LEFT_TO_RIGHT;  //左→右
		}

		match = false;
	}

	//右→左
	if (Now_Action == ACT_TYPE::RIGHT_TO_LEFT)
	{
		/*******************************　１  **++***************************/
		{
			//リング右を目指す
			if (match == false) target_x = _CONSTANTS_07::RING_RIGHT - (w / 2);

			//リング右に到達
			if (x == _CONSTANTS_07::RING_RIGHT - (w / 2))
			{
				match = true;  //1番目終了
				speed = 9.0f;  //スピードアップ

				//じゃん撃を生成する（配列の空要素であることを確実に）                                       
				if ( jan_count + 2 < JANGEKI_MAX && obj_jangeki[jan_count + 2] == nullptr )
				{
					//スピードが自身と同じ かつ マイナス方向に飛ぶじゃん撃
					obj_jangeki[jan_count] = new Jangeki_Base(x, y - 40, radius, -speed, type);
					obj_jangeki[jan_count + 1] = new Jangeki_Base(x - 40, y + 30, radius, -speed, type);
					obj_jangeki[jan_count + 2] = new Jangeki_Base(x + 40, y + 30, radius, -speed, type);
				}
			}
		}
		/*******************************************************************/


		//リング右に到達したのち、リング左を目指す

		/*******************************　２  **++***************************/
		{
			//リング左を目指す
			//if (match == true) target_x = _CONSTANTS_07::RING_LEFT + 200;
			if (match == true) target_x = _CONSTANTS_07::RING_CENTER - 100;

			//リング左に到達                             
			//if (x == _CONSTANTS_07::RING_LEFT + 200)
			if (x == _CONSTANTS_07::RING_CENTER - 100)
			{
				Pre_Action = Now_Action;        //今回のActionを保存

				Now_Action = ACT_TYPE::NO_ACT;  //Actionの完了
				speed = init_speed;             //スピードを戻す
			}
		}
		/*******************************************************************/
	}

	//左→右
	if (Now_Action == ACT_TYPE::LEFT_TO_RIGHT)
	{
		/*******************************　１  **++***************************/
		{
			//リング左を目指す
			if (match == false) target_x = _CONSTANTS_07::RING_LEFT + (w / 2);

			//リング左に到達
			if (x == _CONSTANTS_07::RING_LEFT + (w / 2))
			{
				match = true;  //1番目終了
				speed = 9.0f;  //スピードアップ

				//じゃん撃を生成する（配列の空要素であることを確実に）                                       
				if (jan_count + 2 < JANGEKI_MAX && obj_jangeki[jan_count + 2] == nullptr)
				{
					//スピードが自身と同じ かつ プラス方向に飛ぶじゃん撃
					obj_jangeki[jan_count] = new Jangeki_Base(x, y - 40, radius, speed, type);
					obj_jangeki[jan_count + 1] = new Jangeki_Base(x - 40, y + 30, radius, speed, type);
					obj_jangeki[jan_count + 2] = new Jangeki_Base(x + 40, y + 30, radius, speed, type);
				}
			}
		}
		/*******************************************************************/


		//リング左に到達したのち、リング右を目指す

		/*******************************　２  **++***************************/
		{
			//リング右を目指す
			//if (match == true) target_x = _CONSTANTS_07::RING_RIGHT - 200;
			if (match == true) target_x = _CONSTANTS_07::RING_CENTER + 100;

			//リング右に到達                            
			//if (x == _CONSTANTS_07::RING_RIGHT - 200)
			if (x == _CONSTANTS_07::RING_CENTER + 100)
			{
				Pre_Action = Now_Action;        //今回のActionを保存

				Now_Action = ACT_TYPE::NO_ACT;  //Actionの完了
				speed = init_speed;             //スピードを戻す
			}
		}
		/*******************************************************************/
	}
}

//プレイヤーが足場（空中）上
void Enemy_07::Move_ON_FLOOR(float& target_x, float& target_y)
{
	//プレイヤーが足場上にいる時間をカウント
	static unsigned int time_count;

	//生成するじゃん撃の半径
	float radius = 25.5f;

	//ランダムな属性を生成
	Jan_Type type = static_cast<Jan_Type>(GetRand(2));

	//行動中でない
	if (Now_Action == ACT_TYPE::NO_ACT)
	{
		// 左右ランダム
		if (GetRand(1) == 0)
		{
			Now_Action = ACT_TYPE::CLIMB_CORNER_LEFT;    //コーナーに上る（左）
		}
		else
		{
			Now_Action = ACT_TYPE::CLIMB_CORNER_RIGHT;   //コーナーに上る（右）
		}

		//カウンターをリセット
		time_count = 0;
	}


	//コーナーに上る（左）
	if (Now_Action == ACT_TYPE::CLIMB_CORNER_LEFT)
	{
		//(１) ジャンプ地点に到達・ジャンプ    (２) コーナー上を目指す

		/*******************************　１  **++***************************/
		{
			//（左）ジャンプ地点を目指す
			if (time_count == 0) target_x = _CONSTANTS_07::RING_LEFT + 100;

			//ジャンプ地点に到達
			if (x == _CONSTANTS_07::RING_LEFT + 100 && y == (_CONSTANTS_07::RING_HEIGHT - (h / 2)))
			{
				time_count = 1;

				//ジャンプ
				Jump_Enemy();
			}
		}
		/*******************************************************************/

		/*******************************　２  **++***************************/
		{
			// ジャンプした後
			if ( time_count > 0 )
			{
				//コーナー上を目指す         左
				target_x = _CONSTANTS_07::CORNER_LEFT;

				//１秒おきにじゃん撃生成
				if (time_count % 100 == 0)
				{
					obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, 3.0f, type);
				}

				//３秒後
				if (time_count++ > 180)
				{
					Pre_Action = Now_Action;        //今回のActionを保存

					Now_Action = ACT_TYPE::NO_ACT;  //Actionの完了
				}
			}
		}
		/*******************************************************************/
	}

	//コーナーに上る（右）
	if (Now_Action == ACT_TYPE::CLIMB_CORNER_RIGHT)
	{
		//(１) ジャンプ地点に到達・ジャンプ    (２) コーナー上を目指す

		/*******************************　１  **++***************************/
		{
			//（右）ジャンプ地点を目指す
			if (time_count == 0) target_x = _CONSTANTS_07::RING_RIGHT - 100;

			//ジャンプ地点に到達
			if (x == _CONSTANTS_07::RING_RIGHT - 100 && y == (_CONSTANTS_07::RING_HEIGHT - (h / 2)))
			{
				time_count = 1;

				//ジャンプ
				Jump_Enemy();
			}
		}
		/*******************************************************************/

		/*******************************　２  **++***************************/
		{
			// ジャンプした後
			if (time_count > 0)
			{
				//コーナー上を目指す         右
				target_x = _CONSTANTS_07::CORNER_RIGHT;

				//１秒おきにじゃん撃生成
				if (time_count % 100 == 0)
				{
					obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, 3.0f, type);
				}

				//３秒後
				if (time_count++ > 180)
				{
					Pre_Action = Now_Action;        //今回のActionを保存

					Now_Action = ACT_TYPE::NO_ACT;  //Actionの完了
				}
			}
		}
		/*******************************************************************/
	}
}

//プレイヤーが足場で3秒以上
void Enemy_07::Move_ON_FLOOR_LURK(float& target_x, float& target_y)
{
	// 到達した回数
	static unsigned short count_ari;

	//ジャンプ力（テスト）
	float jump_add = -21.5f;

	//(既にコーナーに上っている前提)

	//行動中でない
	if (Now_Action == ACT_TYPE::NO_ACT)
	{
		// 前回のActionが左コーナー上
		if (Pre_Action == ACT_TYPE::CLIMB_CORNER_LEFT)   Now_Action = ACT_TYPE::CROSS_FLOOR_LEFT;

		// 前回のActionが右コーナー上 
		if (Pre_Action == ACT_TYPE::CLIMB_CORNER_RIGHT)  Now_Action = ACT_TYPE::CROSS_FLOOR_RIGHT;

		//カウントの初期化
		count_ari = 0;

		//ジャンプ
		Jump_Enemy(jump_add);
	}

	
	//生成するじゃん撃の半径
	float radius = 25.5f;
	//ランダムな属性を生成
	Jan_Type type = static_cast<Jan_Type>(GetRand(2));


	// 足場を渡る（左から右）
	if (Now_Action == ACT_TYPE::CROSS_FLOOR_LEFT)
	{
        /*******************************　１  **++***************************/
		if (count_ari == 0)
		{
			// 足場 1 を目指す
			target_x = _CONSTANTS_07::FLOOR_NO_01;

			// 足場 1 に到達
			if (x == _CONSTANTS_07::FLOOR_NO_01)
			{
				count_ari = 1;

				//じゃん撃を発射する
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, this->speed, type);

				speed = 7.5f;
				Jump_Enemy(jump_add);   //ジャンプ
			}
		}

		/*******************************************************************/

		/*******************************　２  **++***************************/
		if (count_ari == 1)
		{
			// 足場 2 を目指す
			target_x = _CONSTANTS_07::FLOOR_NO_02;

			// 足場 2 に到達
			if (x == _CONSTANTS_07::FLOOR_NO_02)
			{
				count_ari = 2;

				//じゃん撃を発射する
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, this->speed, type);
				Jump_Enemy(-18.f);   //ジャンプ
			}
		}

		/*******************************************************************/

		/*******************************　３  **++***************************/
		if (count_ari == 2)
		{
			// 足場 3 を目指す
			target_x = _CONSTANTS_07::FLOOR_NO_03;

			// 足場 3 に到達
			if (x == _CONSTANTS_07::FLOOR_NO_03)
			{
				count_ari = 3;

				//じゃん撃を発射する
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, this->speed, type);
				Jump_Enemy(jump_add);   //ジャンプ
			}
		}

		/*******************************************************************/

		/*******************************　４  **++***************************/
		if (count_ari == 3)
		{
			// 足場 4 を目指す
			target_x = _CONSTANTS_07::FLOOR_NO_04;

			// 足場 4 に到達
			if (x == _CONSTANTS_07::FLOOR_NO_04 && y == (_CONSTANTS_07::FLOOR_NO_01_04_Y - (h / 2)))
			{
				count_ari = 4;

				//じゃん撃を発射する
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, this->speed, type);
				Jump_Enemy(jump_add);   //ジャンプ
			}
		}

		/*******************************************************************/

		/*******************************　５  **++***************************/
		if (count_ari == 4)
		{
			// 右コーナー上 を目指す
			target_x = _CONSTANTS_07::CORNER_RIGHT;

			// 右コーナー上 に到達
			if (x == _CONSTANTS_07::CORNER_RIGHT && y == (_CONSTANTS_07::CORNER_Y - (h / 2)))
			{
				Pre_Action = Now_Action;        //今回のActionを保存
				Now_Action = ACT_TYPE::NO_ACT;  //Actionの完了

				speed = init_speed;             //スピードを初期に戻す
			}
		}

		/*******************************************************************/
	}


	// 足場を渡る（右から左）
	if (Now_Action == ACT_TYPE::CROSS_FLOOR_RIGHT)
	{
		/*******************************　１  **++***************************/
		if (count_ari == 0)
		{
			// 足場 4 を目指す
			target_x = _CONSTANTS_07::FLOOR_NO_04;

			// 足場 4 に到達
			if (x == _CONSTANTS_07::FLOOR_NO_04)
			{
				count_ari = 1;

				//じゃん撃を発射する
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, -(this->speed), type);

				speed = 7.5f;
				Jump_Enemy(jump_add);   //ジャンプ
			}
		}

		/*******************************************************************/

		/*******************************　２  **++***************************/
		if (count_ari == 1)
		{
			// 足場 3 を目指す
			target_x = _CONSTANTS_07::FLOOR_NO_03;

			// 足場 3 に到達
			if (x == _CONSTANTS_07::FLOOR_NO_03)
			{
				count_ari = 2;

				//じゃん撃を発射する
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, -(this->speed), type);
				Jump_Enemy(-18.f);   //ジャンプ
			}
		}

		/*******************************************************************/

		/*******************************　３  **++***************************/
		if (count_ari == 2)
		{
			// 足場 2 を目指す
			target_x = _CONSTANTS_07::FLOOR_NO_02;

			// 足場 2 に到達
			if (x == _CONSTANTS_07::FLOOR_NO_02)
			{
				count_ari = 3;

				//じゃん撃を発射する
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, -(this->speed), type);
				Jump_Enemy(jump_add);   //ジャンプ
			}
		}

		/*******************************************************************/

		/*******************************　４  **++***************************/
		if (count_ari == 3)
		{
			// 足場 1 を目指す
			target_x = _CONSTANTS_07::FLOOR_NO_01;

			// 足場 1 に到達
			if (x == _CONSTANTS_07::FLOOR_NO_01 && y == (_CONSTANTS_07::FLOOR_NO_01_04_Y - (h / 2)))
			{
				count_ari = 4;

				//じゃん撃を発射する
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, -(this->speed), type);
				Jump_Enemy(jump_add);   //ジャンプ
			}
		}

		/*******************************************************************/

		/*******************************　５  **++***************************/
		if (count_ari == 4)
		{
			// 左コーナー上 を目指す
			target_x = _CONSTANTS_07::CORNER_LEFT;

			// 左コーナー上 に到達
			if (x == _CONSTANTS_07::CORNER_LEFT && y == (_CONSTANTS_07::CORNER_Y - (h / 2)))
			{
				Pre_Action = Now_Action;        //今回のActionを保存
				Now_Action = ACT_TYPE::NO_ACT;  //Actionの完了

				speed = init_speed;
			}
		}

		/*******************************************************************/
	}
}

//プレイヤーが場外
void Enemy_07::Move_OUT_RING(float& target_x, float& target_y)
{
	//場外へダイブ（トペ・コンヒーロ的な）

	// 到達した回数
	static unsigned short count_ari;

	//行動中でない
	if (Now_Action == ACT_TYPE::NO_ACT)
	{
		//プレイヤーが半分より左側
		if (player_x < _CONSTANTS_07::RING_CENTER)
		{
			Now_Action = ACT_TYPE::DIVE_OUT_LEFT;   //リング左
		}
		else
		{
			Now_Action = ACT_TYPE::DIVE_OUT_RIGHT;  //リング右
		}

		count_ari = 0;  //カウンターをリセット
		speed = 11.0f;  //スピードアップ
	}

	//リング左へダイブ
	if (Now_Action == ACT_TYPE::DIVE_OUT_LEFT)
	{
		// （1）助走      (2) ジャンプ地点に到達・ジャンプ   
		//  (3)ダイブ     (4) リング内に戻る

        /*******************************　１  **++***************************/
		{
			//リング右を目指す
			if (count_ari == 0) target_x = _CONSTANTS_07::RING_RIGHT - (w / 2);

			//リング右に到達
			if (x == _CONSTANTS_07::RING_RIGHT - (w / 2))
			{
				count_ari = 1;   // 2 へ
				speed = 11.0f;   //スピードアップ
			}
		}
		/*******************************************************************/

		/*******************************　２  **++***************************/
		{
			if (count_ari == 1)
			{
				//（左）ジャンプ地点を目指す
				target_x = _CONSTANTS_07::RING_LEFT + 400;

				//ジャンプ地点に到着
				if (x == _CONSTANTS_07::RING_LEFT + 400 && y == (_CONSTANTS_07::RING_HEIGHT - (h / 2)))
				{
					count_ari = 2;       // 3 へ
					Jump_Enemy(-23.0f);  //ジャンプ

					Jan_360degrees();    //じゃん撃発射
				}
			}
		}
		/*******************************************************************/

		/*******************************　３  **++***************************/
		{
			if (count_ari == 2)
			{
				//ジャンプ中

				//リング外を目指す         左
				target_x = _CONSTANTS_07::OUT_RING_LEFT - 35;
				
				//画像を回転させる
				draw_angle -= 0.1;

				//着地
				if (x == _CONSTANTS_07::OUT_RING_LEFT - 35 && land_flg == true)
				{
					count_ari = 3;       // 4 へ
					speed = init_speed;  //スピードを初期に戻す
					draw_angle = 0.0;    //初期の角度に戻す
				}
			}
		}
		/*******************************************************************/

		/*******************************　４  **++***************************/
		{
			//20フレーム待機    count_ariでフレームを計測する
			if (count_ari >= 3 && count_ari < 23)
			{
				count_ari++;

				//20フレーム経過後
				if (count_ari == 23)
				{
					Jump_Enemy(-18.0f);
					count_ari = 99;
				}
			}

			if (count_ari == 99)
			{
				//リング内を目指す         
				target_x = _CONSTANTS_07::RING_LEFT + (w / 2);

				//リング内に到達
				if (x == _CONSTANTS_07::RING_LEFT + (w / 2))
				{
					Pre_Action = Now_Action;        //今回のActionを保存
					Now_Action = ACT_TYPE::NO_ACT;  //Actionの完了
					speed = init_speed;             //スピードを初期に戻す
				}
			}
		}
		/*******************************************************************/
	}


	//リング右へダイブ
	if (Now_Action == ACT_TYPE::DIVE_OUT_RIGHT)
	{
		// （1）助走      (2) ジャンプ地点に到達・ジャンプ   
		//  (3)ダイブ     (4) リング内に戻る

		/*******************************　１  **++***************************/
		{
			//リング左を目指す
			if (count_ari == 0) target_x = _CONSTANTS_07::RING_LEFT + (w / 2);

			//リング左に到達
			if (x == _CONSTANTS_07::RING_LEFT + (w / 2))
			{
				count_ari = 1;   // 2 へ
				speed = 11.0f;   //スピードアップ
			}
		}
		/*******************************************************************/

		/*******************************　２  **++***************************/
		{
			if (count_ari == 1)
			{
				//（右）ジャンプ地点を目指す
				target_x = _CONSTANTS_07::RING_RIGHT - 400;

				//ジャンプ地点に到着
				if (x == _CONSTANTS_07::RING_RIGHT - 400 && y == (_CONSTANTS_07::RING_HEIGHT - (h / 2)))
				{
					count_ari = 2;       // 3 へ
					Jump_Enemy(-23.0f);  //ジャンプ

					Jan_360degrees();    //じゃん撃発射
				}
			}
		}
		/*******************************************************************/

		/*******************************　３  **++***************************/
		{
			if (count_ari == 2)
			{
				//ジャンプ中

				//リング外を目指す         右
				target_x = _CONSTANTS_07::OUT_RING_RIGHT + 35;

				//画像を回転させる
				draw_angle += 0.1;

				//着地
				if (x == _CONSTANTS_07::OUT_RING_RIGHT + 35 && land_flg == true)
				{
					count_ari = 3;       // 4 へ
					speed = init_speed;  //スピードを初期に戻す
					draw_angle = 0.0;    //初期の角度に戻す
				}
			}
		}
		/*******************************************************************/

		/*******************************　４  **++***************************/
		{
			//20フレーム待機    count_ariでフレームを計測する
			if (count_ari >= 3 && count_ari < 23)
			{
				count_ari++;

				//20フレーム経過後
				if (count_ari == 23)
				{
					Jump_Enemy(-18.0f);
					count_ari = 99;
				}
			}

			if (count_ari == 99)
			{
				//リング内を目指す         
				target_x = _CONSTANTS_07::RING_RIGHT - (w / 2);

				//リング内に到達
				if (x == _CONSTANTS_07::RING_RIGHT - (w / 2))
				{
					Pre_Action = Now_Action;        //今回のActionを保存
					Now_Action = ACT_TYPE::NO_ACT;  //Actionの完了
					speed = init_speed;             //スピードを初期に戻す
				}
			}
		}
		/*******************************************************************/
	}
}

//プレイヤーの状況を取得
void Enemy_07::CheckPlayerState(const Player* player)
{
	//実行中のAction（行動）を終えてから変更する
	if (Now_Action == ACT_TYPE::NO_ACT)
	{
		//当たり判定を活用          
		if (player->CheckHitBox_Box(220, 260, 840, 330) == true)        //リング上の範囲
		{
			Player_State = PLAYER_STATE::ON_RING;   //リング上
		}
		else if (player->CheckHitBox_Box(20, -180, 1240, 380) == true)  //空中の足場全体の範囲
		{
			//前回も足場上の行動をしていた
			if ( Pre_Action == ACT_TYPE::CLIMB_CORNER_LEFT || Pre_Action == ACT_TYPE::CLIMB_CORNER_RIGHT )
			{
				Player_State = PLAYER_STATE::ON_FLOOR_LURK;  //足場上で潜んでいる
			}
			else 
				Player_State = PLAYER_STATE::ON_FLOOR;       //足場上
		}
		else if (player->CheckHitBox_Box(20, 620, 200, 80) == true || player->CheckHitBox_Box(1060, 620, 200, 80) == true)
		{
			Player_State = PLAYER_STATE::OUT_RING;  //場外（リング外）
		}
		else
		{
			Player_State = PLAYER_STATE::DO_NOT;    //判断しない
		}
	}
}


//行動を初期化（接触じゃんけん終了後　用）
void Enemy_07::Init_MoveAndAction()
{
	Player_State = PLAYER_STATE::DO_NOT;
	Now_Action = ACT_TYPE::NO_ACT;
	Pre_Action = ACT_TYPE::NO_ACT;
}

//（ダイブ中に）当たり判定をとらない  true : ダイブ中。当たり判定をとらない 
bool Enemy_07::Is_Diving_Collision()
{
	// Actionはダイブ かつ リングより高い位置にいる  →　　ジャンプ中（足場に引っかからないように）  
	if (Now_Action == ACT_TYPE::DIVE_OUT_LEFT && y < (_CONSTANTS_07::RING_HEIGHT - (h / 2)) ||
		Now_Action == ACT_TYPE::DIVE_OUT_RIGHT && y < (_CONSTANTS_07::RING_HEIGHT - (h / 2)))
	{
		return true;
	}
	return false;
}

//（ダイブ中に）接触じゃんけんをしない  true : ダイブ中。接触じゃんけんをしない
bool Enemy_07::Is_Diving_TouchJanken()
{
	if (Now_Action == ACT_TYPE::DIVE_OUT_LEFT || Now_Action == ACT_TYPE::DIVE_OUT_RIGHT)
	{
		return true;
	}
	return false;
}

/*--------------------------------------------------------------------------------------*/

//360度発射
void Enemy_07::Jan_360degrees()
{
	//生成するじゃん撃の半径
	float radius = 25.5f;

	//ランダムな属性を生成
	Jan_Type type = static_cast<Jan_Type>(GetRand(2));

	//45度ずつ8個生成
	for (int i = jan_count; i < (jan_count + 8); i++)
	{
		double angle = static_cast<double>((45.0 * i) * (M_PI / 180));

		obj_jangeki[i] = new Jangeki_Base(x, y, radius, speed, angle, type);
	}
}

//縦にたくさん発射（特殊）
void Enemy_07::Jan_Vertical(int count, float rad, float speed, Jan_Type type)
{
	//4個生成
	obj_jangeki[count]     = new Jangeki_Vertical(x, y, rad, -speed, (y + 50), type);
	obj_jangeki[count + 1] = new Jangeki_Vertical(x, y, rad, -speed, (y + 75), type);
	obj_jangeki[count + 2] = new Jangeki_Vertical(x, y, rad, -speed, (y - 50), type);
	obj_jangeki[count + 3] = new Jangeki_Vertical(x, y, rad, -speed, (y - 75), type);
}



