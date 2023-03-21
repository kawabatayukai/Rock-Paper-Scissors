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
namespace _ENEMY_07
{
	const float RING_LEFT  = 250.0f;    //リング左端
	const float RING_RIGHT = 1030.0f;   //リング右端


	char state_string[][10] = { "ON_RING","DO_NOT" };   //テスト用
	char action_str[][15] = { "NO_ACT","LEFT_TO_RIGHT","RIGHT_TO_LEFT" };
}

//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_07::Enemy_07(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
, Player_State(PLAYER_STATE::DO_NOT), Now_Action(ACT_TYPE::NO_ACT)
{
	speed = 3.0f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //じゃん撃を用意

	//パターン（csvに）
	moveinfo[0] = { 1,620.f,0.f,1 };
	moveinfo[1] = { 1,1030.f,0.f,0 };
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
	DrawRotaGraphF(x, y, 1, 0, image, TRUE);

	//じゃん撃描画
	Draw_Jangeki();

	//テスト
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);

	LPCTSTR string = _ENEMY_07::state_string[static_cast<int>(Player_State)];
	LPCTSTR string_act = _ENEMY_07::action_str[static_cast<int>(Now_Action)];

	DrawString(200, 300, string, 0xff0000);
	DrawString(200, 330, string_act, 0xff0000);
}

//じゃん撃生成・更新
void Enemy_07::Update_Jangeki()
{
	int jan_count;

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
	frame_count++;

	//配列の空要素
	if (jan_count < JANGEKI_MAX && obj_jangeki[jan_count] == nullptr)
	{
		float radius = 25.5f;   //半径
		float speed = 6.0f;     //スピード

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		//生成
		if (frame_count % 120 == 0)
		{
			switch (GetRand(2))
			{
			case 0:
				Jan_360degrees(jan_count, radius, speed, type);
				break;

			case 1:
				obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type);
				break;

			case 2:
				Jan_Vertical(jan_count, radius, speed, type);
				break;

			default:
				break;
			}

		}
	}

}

//行動パターンに沿った行動
void Enemy_07::Move_Pattern()
{
	//移動量
	float move_x = x;
	float move_y = y;

	//目標座標と完全一致（x座標だけ）
	if (x == moveinfo[current].location_x)
	{
		current = moveinfo[current].next_index;   //次のパターンへ
	}

	//x座標が目標と不一致
	if (x != moveinfo[current].location_x)
	{
		//目標の方が大きい（目標は右方向）
		if (x < moveinfo[current].location_x)
		{
			move_x += speed;      //右移動（正の値）

			//目標を超えた場合
			if (x <= moveinfo[current].location_x && moveinfo[current].location_x <= move_x)
			{
				move_x = moveinfo[current].location_x;     //目標座標で固定
			}
		}
		else
		{
			move_x -= speed; //左移動（負の値）

			//目標を超えた場合
			if (move_x <= moveinfo[current].location_x && moveinfo[current].location_x <= x)
			{
				move_x =  moveinfo[current].location_x;     //目標座標で固定
			}
		}
	}

	//移動を反映
	x = move_x;
	y = move_y;
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

	switch (Player_State)
	{
	case PLAYER_STATE::ON_RING:    //リング上

		Move_ON_RING(target_x, target_y);
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

	//行動中でない
	if (Now_Action == ACT_TYPE::NO_ACT)
	{
		//プレイヤーが半分より左側
		if (player_x < (1280 / 2))
		{
			Now_Action = ACT_TYPE::RIGHT_TO_LEFT;  //右→左
			match = false;
		}
		else
		{
			Now_Action = ACT_TYPE::LEFT_TO_RIGHT;  //左→右
			match = false;
		}
	}

	//右→左
	if (Now_Action == ACT_TYPE::RIGHT_TO_LEFT)
	{
		/*******************************　１  **++***************************/
		{
			//リング右を目指す
			if (match == false) target_x = _ENEMY_07::RING_RIGHT - (w / 2);

			//リング右に到達
			if (x == _ENEMY_07::RING_RIGHT - (w / 2))
			{
				match = true;  //1番目終了
				speed = 9.0f;  //スピードアップ
			}
		}
		/*******************************************************************/


		//リング右に到達したのち、リング左を目指す

		/*******************************　２  **++***************************/
		{
			//リング左を目指す
			if (match == true) target_x = _ENEMY_07::RING_LEFT + (w / 2);

			//リング左に到達                             
			if (x == _ENEMY_07::RING_LEFT + (w / 2))
			{
				Now_Action = ACT_TYPE::NO_ACT;  //Actionの完了
				speed = 3.0f;                   //スピードを戻す
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
			if (match == false) target_x = _ENEMY_07::RING_LEFT + (w / 2);

			//リング右に到達
			if (x == _ENEMY_07::RING_LEFT + (w / 2))
			{
				match = true;  //1番目終了
				speed = 9.0f;  //スピードアップ
			}
		}
		/*******************************************************************/


		//リング左に到達したのち、リング右を目指す

		/*******************************　２  **++***************************/
		{
			//リング右を目指す
			if (match == true) target_x = _ENEMY_07::RING_RIGHT - (w / 2);

			//リング右に到達                            
			if (x == _ENEMY_07::RING_RIGHT - (w / 2))
			{
				Now_Action = ACT_TYPE::NO_ACT;  //Actionの完了
				speed = 3.0f;                   //スピードを戻す
			}
		}
		/*******************************************************************/
	}
}


//プレイヤーの状況を取得
void Enemy_07::CheckPlayerState(const Player* player)
{
	//当たり判定を活用          リング上の範囲
	if (player->CheckHitBox_Box(220, 260, 840, 330) == true)
	{
		Player_State = PLAYER_STATE::ON_RING;   //リング上
	}
	else
	{
		Player_State = PLAYER_STATE::DO_NOT;    //リング上ではない
	}
}


/*--------------------------------------------------------------------------------------*/

//360度発射（必殺）
void Enemy_07::Jan_360degrees(int count, float rad, float speed, Jan_Type type)
{
	//45度ずつ8個生成
	for (int i = count; i < (count + 18); i++)
	{
		double angle = static_cast<double>((20.0 * i) * (M_PI / 180));

		obj_jangeki[i] = new Jangeki_Base(x, y, rad, speed, angle, type);
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



