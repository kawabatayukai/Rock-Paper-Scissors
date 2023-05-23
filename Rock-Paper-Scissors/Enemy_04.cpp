#include "Enemy_04.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Coming.h"
#include "Jangeki_whole.h"
#include"SoundSystem.h"
#include <typeinfo>
#define _USE_MATH_DEFINES
#include<math.h>

//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_04::Enemy_04(float x, float y, Jan_Type type) : EnemyBase(x, y, 150.0f, 150.0f, type)
{
	speed = 1.0f;
	dir = 1;
	hp = 100;

	enemy_x = 640;
	enemy_y = 360;

	enemy_image[0] = LoadGraph("images/Stage04/stage_Boss04.png");
	enemy_image[1] = LoadGraph("images/Stage04/stage_Boss04(上).png");
	enemy_image[2] = LoadGraph("images/Stage04/stage_Boss04(右上).png");
	enemy_image[3] = LoadGraph("images/Stage04/stage_Boss04(右).png");
	enemy_image[4] = LoadGraph("images/Stage04/stage_Boss04(右下).png");
	enemy_image[5] = LoadGraph("images/Stage04/stage_Boss04(下).png");
	enemy_image[6] = LoadGraph("images/Stage04/stage_Boss04(左下).png");
	enemy_image[7] = LoadGraph("images/Stage04/stage_Boss04(左).png");
	enemy_image[8] = LoadGraph("images/Stage04/stage_Boss04(左上).png");
	enemy_image[9] = LoadGraph("images/Stage04/stage_Boss04(特殊行動).png");

	Init_Jangeki();       //じゃん撃を用意
}

//デストラクタ
Enemy_04::~Enemy_04()
{

}


//更新
void Enemy_04::Update()
{
	//じゃん撃更新・生成
	Update_Jangeki();

	//プレイヤーとの角度
	angle = atan2f((player_x - x), (player_y - y));

	//動きパターン(通常時)
	moveinfo[0] = { 1, player_x, player_y, 0, 0 };

	//動きパターン(特殊行動時)
	moveinfo[1] = { 1,  enemy_x,  enemy_y, 0, 2 };
	moveinfo[2] = { 0,      0.f,      0.f, 0, 1 };

	switch (moveinfo[current].moveflg)
	{
	case 0:
		waitTime++;
		if (moveinfo[current].waitFlameTime <= waitTime)
		{
			if (specialFlg == true)
			{
				enemy_x = GetRand(1080) + 100;
				enemy_y = GetRand(340) + 100;
			}
			waitTime = 0;
			current = moveinfo[current].next_index;
		}
		break;

	case 1:
		Move_Pattern();
		break;

	default:
		break;
	}

	//体力ゲージがマイナスにならないように
	if (hp <= 0) hp = 0;

	//特殊行動時や残りHPによってスピードが変わる
	if (specialFlg == true)
	{
		speed = 20.0f;
		specialTime++;
	}
	else if (hp <= 50)
	{
		speed = 2.6f;
	}
	else
	{
		speed = 1.8f;
	}

	//少しずつHP回復
	if (hp < 100 && frame_count % 20 == 0) hp++;

	//特殊行動時間(4秒間)
	if (specialTime >= 240)
	{
		specialTime = 0;
		specialFlg = false;
		current = 0;
		SoundSystem::StopSE(SE::ENEMY_SPECIAL);
	}
}

//描画
void Enemy_04::Draw() const
{	
	//中心から描画
	DrawRotaGraphF(x, y, 1.5, 0, enemy_image[0], TRUE);

	/************* ↓↓ 黒目をプレイヤーの角度へ向ける ↓↓ *************/

	//上向きの画像
	if (angle > 2.625 && angle <= 3.15 || angle <= -2.625 && angle > -3)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[1], TRUE);
	}

	//右上向きの画像
	if (angle <= 2.625 && angle > 1.875)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[2], TRUE);
	}

	//右向きの画像
	if (angle <= 1.875 && angle > 1.125)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[3], TRUE);
	}

	//右下向きの画像
	if (angle <= 1.125 && angle > 0.375)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[4], TRUE);
	}

	//下向きの画像
	if (angle <= 0.375 && angle > -0.375)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[5], TRUE);
	}

	//左下向きの画像
	if (angle <= -0.375 && angle > -1.125)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[6], TRUE);
	}

	//左向きの画像
	if (angle <= -1.125 && angle > -1.875)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[7], TRUE);
	}

	//左上向きの画像
	if (angle <= -1.875 && angle > -2.625)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[8], TRUE);
	}

	if (specialFlg == true)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[9], TRUE);
	}

	//じゃん撃描画
	Draw_Jangeki();

	//残りHP50以下の時に表示
	if (hp <= 50) DrawFormatString((int)(x - 60), (int)(y - 155), GetColor(30, 30, 255), "スピードUP↑", hp);
}

//じゃん撃生成・更新
void Enemy_04::Update_Jangeki()
{
	int jan_count;

	//じゃん撃配列をひとつずつ
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//配列の jan_count 番目がnullptr（空要素）ならそれ以上処理しない
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();

		//プレイヤーの座標をセットする
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
		float radius = 45.0f;   //半径
		float speed  =  6.0f;   //スピード

		//HP50以下でジャン撃スピード変更
		if (hp <= 50) speed = 10.0f;
		
		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		//特殊行動状態かどうか
		if (specialFlg == false)
		{
			//プレイヤーの角度へ発射するジャン撃生成
			if (frame_count % 60 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);

			//if (frame_count % 121 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius * 0.7, speed * 0, type, player_x, player_y);

		}
		else if (specialFlg == true)
		{
			if (frame_count % 60 == 0)
			{
				Jan_360degrees(jan_count, radius * 0.8, speed * 0.8, type);
				SoundSystem::PlaySE(SE::ENEMY_SPECIAL_ATTACK);
			}
		}
	}
}

void Enemy_04::Move_Pattern() {

	//移動する量
	float move_x = x;
	float move_y = y;

	//目指しているx座標とy座標が一致したとき
	if (x == moveinfo[current].location_x && y == moveinfo[current].location_y) {
		current = moveinfo[current].next_index; //次のパターン
	}

	//x座標が目指している座標と不一致
	if (x != moveinfo[current].location_x) {

		//目指しているx座標の右方が大きい
		if (x < moveinfo[current].location_x) {
			move_x += speed; //右移動にプラスする

			//目指していた座標を超えたとき
			if (x <= moveinfo[current].location_x && moveinfo[current].location_x <= move_x)
			{

				move_x = moveinfo[current].location_x; //目指していた座標で固定

			}

		}
		else
		{
			move_x -= speed; //左移動にマイナスする

			//目指していた座標を超えたとき
			if (move_x <= moveinfo[current].location_x && moveinfo[current].location_x <= x)
			{

				move_x = moveinfo[current].location_x; //目指していた座標で固定

			}


		}


	}

	//y座標が目指している座標と不一致
	if (y != moveinfo[current].location_y) {

		//目指しているy座標の右方が大きい
		if (y < moveinfo[current].location_y) {
			move_y += speed; //下移動にプラスする

			//目指していた座標を超えたとき
			if (y <= moveinfo[current].location_y && moveinfo[current].location_y <= move_y)
			{

				move_y = moveinfo[current].location_y; //目指していた座標で固定

			}

		}
		else
		{
			move_y -= speed; //上移動にマイナスする

			//目指していた座標を超えたとき
			if (move_y <= moveinfo[current].location_y && moveinfo[current].location_y <= y)
			{

				move_y = moveinfo[current].location_y; //目指していた座標で固定

			}


		}


	}

	//移動を反映する
	x = move_x;
	y = move_y;

}

void Enemy_04::Change_JanType()
{
	//現在の属性と異なる2属性のうちランダム
	switch (this->e_type)
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

void Enemy_04::Special_Action()
{
	specialFlg = true;
	current = 1;
	SoundSystem::PlaySE(SE::ENEMY_SPECIAL);
}

//360度発射
void Enemy_04::Jan_360degrees(int count, float rad, float speed, Jan_Type type)
{
	//20度ずつ18個生成
	for (int i = count; i < (count + 18); i++)
	{
		double angle = static_cast<double>((20.0 * i) * (M_PI / 180));

		obj_jangeki[i] = new Jangeki_Base(x, y, rad, speed, angle, type);
	}
}