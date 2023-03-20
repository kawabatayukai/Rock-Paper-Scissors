#include "Enemy_07.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Homing.h"
#include<typeinfo>

#define _USE_MATH_DEFINES
#include<math.h>

//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_07::Enemy_07(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
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
	Move_Pattern();

	//じゃん撃更新・生成
	Update_Jangeki();


	/********************   ジャンプ関係   ********************/

	if (land_flg == true && GetRand(30) == 3)    //GetRand(30) == 3　のところがジャンプの条件
	{
		g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
		land_flg = false;  //地面についていない
	}

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
			if (GetRand(1) == 0)
			{
				Jan_360degrees(jan_count, radius, speed, type);
			}
			else
			{
				obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type);
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