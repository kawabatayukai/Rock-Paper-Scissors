#include "MobEnemy_05.h"
#include "DxLib.h"
#include "Player.h"
#include "Jangeki_Spin.h"
//#include "Enemy_05.h"
#include "Jangeki_Base.h"
#include "Jangeki_Changespeed.h"
#include "Jangeki_Zigzag.h" 
#define _USE_MATH_DEFINES
#include <math.h>

MobEnemy_05::MobEnemy_05(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	hp = 100;

	Mobenemy_image = LoadGraph("images/stage05/Mobenemy_image.png", TRUE);

	Init_Jangeki();       //じゃん撃を用意


}

MobEnemy_05::~MobEnemy_05()
{

}

void MobEnemy_05::Update()
{
	//じゃん撃更新・生成
	Update_Jangeki();
}

void MobEnemy_05::Draw() const
{
	//中心から描画
	DrawRotaGraphF(x, y, 1, 0, Mobenemy_image, TRUE);

	//じゃん撃描画
	Draw_Jangeki();
	//テスト
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);
}

void MobEnemy_05::Update_Jangeki()
{

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
		float radius = 35.5f;   //半径
		float speed = 2.0f;     //スピード

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		//生成
		switch (GetRand(1))
		{
		case 0:
			if (frame_count % 240 == 0) obj_jangeki[jan_count] = new Jangeki_Zigzag(x, y, radius, speed, type, player_x, player_y);
			break;

		case 1:
			if (frame_count % 240 == 0) obj_jangeki[jan_count] = new Jangeki_Spin(x, y, radius, speed, type, player_x, player_y);
			break;
		}

		losetimer++;

		if (Jan_loseflg == true)
		{
			if (frame_count % 60 == 0) obj_jangeki[jan_count] = new Jangeki_Spin(x, y, radius, speed, type, player_x, player_y);
		}
		if (losetimer > 180)
		{
			Jan_loseflg = false;
		}
	}
}

void MobEnemy_05::Janken_lose()
{
	hp = 100;

	Jan_360degrees();

	//じゃん撃配列をひとつずつ
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//配列の jan_count 番目がnullptr（空要素）ならそれ以上処理しない
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();

		DeleteJangeki(jan_count);
		jan_count--;
	}
	Jan_loseflg = true;
	losetimer = 0;
}

void MobEnemy_05::Janken_win()
{
	hp = hp / 2;

	//じゃん撃配列をひとつずつ
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//配列の jan_count 番目がnullptr（空要素）ならそれ以上処理しない
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();

		DeleteJangeki(jan_count);
		jan_count--;
	}

}

void MobEnemy_05::Jan_360degrees()
{
	if (Spflg == true)
	{
		//生成するじゃん撃の半径
		float radius = 40.f;

		for (int i = jan_count; i < (jan_count + 14); i++)
		{
			//ランダムな属性を生成
			Jan_Type type = static_cast<Jan_Type>(GetRand(2));
			double angle = static_cast<double>((30.0 * i) * (M_PI / 70));

			obj_jangeki[i] = new Jangeki_Base(x, y, radius, speed, angle, type);

			if (GetRand(2) == SPcount)
			{
				Spflg = false;
				SPcount = 0;
			}
		}
	}
}
