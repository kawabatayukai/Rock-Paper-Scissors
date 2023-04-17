#include "Enemy_09.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Scene_Stage09.h"
#include"Jangeki_Homing.h"
#include"Jangeki_whole.h"
#define _USE_MATH_DEFINES
#include <math.h>



//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_09::Enemy_09(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{

	speed = 7.0f;
	dir = 1;
	hp = 100;

	
	Rimage = LoadGraph("images/stage09/Stage9_1.png");	//反射ON
	image = LoadGraph("images/stage09/Stage9.png");		//反射OFF

	LoadDivGraph("images/stage09/teleport2.png", 15, 15, 1, 120, 150, img_teleport);
	LoadDivGraph("images/stage09/teleport22.png", 15, 15, 1, 120, 150, img_teleport2);


	//じゃん撃を用意
	Init_Jangeki();       
	reflection = new Jangeki_Reflection(x, y, w, h, Jan_Type::ROCK);
	reflection->Init_reflectionJangeki();
	
}

//デストラクタ
Enemy_09::~Enemy_09()
{

}


//更新
void Enemy_09::Update()
{
	//じゃん撃更新・生成
	Update_Jangeki();
	reflection->Update_reflection();

	if(Spflg==false)MoveEnmey_09();
	else  SpecialMoveEnmey();
	

}

//描画
void Enemy_09::Draw() const
{

	//中心から描画
	if (animflg == false)
	{
		if (rflg == false)DrawRotaGraphF(x, y, 1, 0, Rimage, TRUE);
		if (rflg == true)DrawRotaGraphF(GetX(), GetY(), 1, 0, image, TRUE);
	}

	if (animflg == true)
	{
		if (anim_count == 0) DrawGraph(before_x - 65, before_y - 50, img_teleport[animtimer / 3 % 15], TRUE);
		else DrawGraph(x - 50, y - 50, img_teleport2[animtimer / 2 % 15], TRUE);
	}
		

	//じゃん撃描画
	Draw_Jangeki();
	reflection->Draw_reflectionJangeki();
	
	//テスト
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);

}

//じゃん撃生成・更新
void Enemy_09::Update_Jangeki()
{	

	//じゃん撃配列をひとつずつ
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//配列の jan_count 番目がnullptr（空要素）ならそれ以上処理しない
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();
		
		//ホーミングじゃん撃であればプレイヤーの座標をセットする
		obj_jangeki[jan_count]->SetTargetLocation(player_x, player_y);
		reflection->SetTargetLocation(player_x, player_y);

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
		float speed = 3.5f;     //スピード

		//if (GetHP() <= 51)speed=4.5f;

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));
		/*if(GetHP()!=1)
		{
			if (frame_count % 100 == 0) obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type);
		}*/

		//アニメーション再生中でなければ生成
		//if (animflg == false)
		//{
			if (frame_count % janFrame == 0)
			{
				if (Spflg == false)
				{
					obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type);
					count++;
				}
				else
				{
					Jan_360degrees();
					count = 0;		 //リセット
				}
				if (count == 5)		//五回目で特殊弾発射
				{
					Jan_40degrees();
					count = 0;		 //リセット
				}

			}

			//反射じゃん撃生成
			if (reflection->GetFlg() == true)reflection->obj_reflection[reflection->jan_count_reflection] = new Jangeki_Homing(x, y, radius, speed, type, true);
			reflection->falseFlg();
		//}
	}
}

void Enemy_09::Jan_360degrees()
{
	if (Spflg == true)
	{
		//生成するじゃん撃の半径
		float radius = 40.f;
		int count = 0;

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		for (int i = jan_count; i < (jan_count + 14); i++)
		{
			double angle = static_cast<double>((30.0 * i) * (M_PI / 70));

			obj_jangeki[i] = new Jangeki_Base(x, y, radius, speed, angle, type);
			count++;

			if (GetRand(3) == count)
				Spflg = false;
		}
	}
}

void Enemy_09::Jan_40degrees()
{
	if (Spflg == false)
	{
		//生成するじゃん撃の半径
		float radius = 35.5f;
		if (GetHP() <= 51)radius = 45.f;
	
		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		for (int i = jan_count; i < (jan_count + 8); i++)
		{
			double angle = static_cast<double>((270.0 * i) * (M_PI / 120));

			obj_jangeki[i] = new Jangeki_Base(x, y, radius, speed, angle, type);
		
		}
	}
}

void Enemy_09::MoveEnmey_09()
{
	interval++;
	if (GetHP() <= 51)teleport = 200;

	if (GetHP() == 1)teleport = 500;

		if (interval % teleport == 0) {

		animflg = true;

		before_x = x;
		before_y = y;

		switch (GetRand(12))
		{
			//左側
		case 0:
			x = 160;
			y = 480;
			break;
		case 1:
			x = 160;
			y = 700;
			break;
		case 2:
			x = 360;
			y = 305;
			break;
		case 3:
			x = 360;
			y = 700;
			break;
		case 4:
			x = 160;
			y = 130;
			break;
			//右側
		case 5:
			x = 1110;
			y = 480;
			break;
		case 6:
			x = 1110;
			y = 700;
			break;
		case 7:
			x = 910;
			y = 305;
			break;
		case 8:
			x = 910;
			y = 700;
			break;
		case 9:
			x = 1110;
			y = 130;
			break;
			//真ん中
		case 10:
			x = 620;
			y = 400;
			break;
		case 11:
			x = 620;
			y = 80;
			break;
		case 12:
			x = 620;
			y = 700;
			break;
		}
	}

		if (animflg == true)
		{
			animtimer++;

			if (animtimer / 3 % 15 == 14) {
				
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
}

void Enemy_09::SpecialMoveEnmey()
{
	interval++;
	int Rand = 0;
	int i = 0;


	if (Spflg == true) {
		if (interval % 30 == 0) {
			animflg = true;

			before_x = x;
			before_y = y;

			switch (GetRand(12))
			{
				//左側
			case 0:
				x = 160;
				y = 480;
				break;
			case 1:
				x = 160;
				y = 700;
				break;
			case 2:
				x = 360;
				y = 305;
				break;
			case 3:
				x = 360;
				y = 700;
				break;
			case 4:
				x = 160;
				y = 130;
				break;
				//右側
			case 5:
				x = 1110;
				y = 480;
				break;
			case 6:
				x = 1110;
				y = 700;
				break;
			case 7:
				x = 910;
				y = 305;
				break;
			case 8:
				x = 910;
				y = 700;
				break;
			case 9:
				x = 1110;
				y = 130;
				break;
				//真ん中
			case 10:
				x = 620;
				y = 420;
				break;
			case 11:
				x = 620;
				y = 110;
				break;
			case 12:
				x = 620;
				y = 700;
				break;
			}
		}
		if (animflg == true)
		{
			animtimer++;

			if (animtimer / 1 % 15 == 14)
			{
				animtimer = 0;
				animflg = false;
			}
		}
	}
}

void Enemy_09::frameUP()
{
	if (janFrame >= 55)
	{
		janFrame = janFrame - 5;
	}
}

void Enemy_09::frameDown()
{
	if (janFrame < 75)
	{
		janFrame = janFrame + 5;
	}

}

void Enemy_09::HP() 
{
	if (hp <= 0)
	{
		hp = 1;
	}
}

bool Enemy_09::Getflg()
{
	return rflg;
}
void Enemy_09::Tflg()
{
	rflg = true;
}
void Enemy_09::Fflg()
{
	rflg = false;
}
