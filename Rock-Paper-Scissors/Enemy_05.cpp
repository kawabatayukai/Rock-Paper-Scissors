#include "Enemy_05.h"
#include "DxLib.h"
#include "Player.h"
#include "Jangeki_Base.h"
#include "Jangeki_Changespeed.h"
#include "Jangeki_Zigzag.h" 
#include "Jangeki_Spin.h" 
#include "Jangeki_Homing.h"


//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_05::Enemy_05(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type), respawn(false)
{
	speed = 7.0f;
	dir = 1;
	hp = 100;
	Movepattern = 1;
	Movetimer = 0;
	runanimfragL = FALSE;
	runanimfragR = FALSE;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //じゃん撃を用意

	Enemy_imageL = LoadGraph("images/stage05/Stage5_Enemy_NoMove_L.png", TRUE);
	Enemy_imageR = LoadGraph("images/stage05/Stage5_Enemy_NoMove_R.png", TRUE);
	Enemy_barrier = LoadGraph("images/stage05/Stage5_EnemyBarrier.png", TRUE);

	LoadDivGraph("images/stage05/Stage5_enemyRun_L.png", 4, 4, 1, 100, 100, Enemy_run_L);
	LoadDivGraph("images/stage05/Stage5_enemyRun_R.png", 4, 4, 1, 100, 100, Enemy_run_R);
	reflection = new Jangeki_Reflection(x, y, h, w, Jan_Type::ROCK);
	reflection->Init_reflectionJangeki();
}

//デストラクタ
Enemy_05::~Enemy_05()
{

}


//更新
void Enemy_05::Update()
{
	//じゃん撃更新・生成
	Update_Jangeki();
	reflection->Update_reflection();

	/*if (x + (w / 2) == (1280 - 20))
	{
		dir = -1;
	}
	else if (x - (w / 2) == (20))
	{
		dir = 1;
	}*/

	/*x += dir * speed;*/

	///********************   ジャンプ関係   ********************/

	//if (land_flg == true && GetRand(30) == 3)    //GetRand(30) == 3　のところがジャンプの条件
	//{
	//	//g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
	//	g_add = -25.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
	//	land_flg = false;  //地面についていない
	//}



	if (mob[0]->GetHP() <= 0 && mob[1]->GetHP() <= 0 && mob[2]->GetHP() <= 0)
	{
		mob[0]->Init_Jangeki();
		mob[1]->Init_Jangeki();
		mob[2]->Init_Jangeki();

		Movetimer++;
		//敵の移動
		switch (Movepattern)
		{
		case 1:		//真ん中の台へ
			if (x >= 650 && Movetimer >= 30)
			{
				x -= 5;
				runanimfragL = TRUE;
			}
			else if (Movetimer > 30)
			{
				Movepattern = 2;
				dir = -1;
				runanimfragL = FALSE;
			}
			if (Movepattern == 2)
			{
				Movetimer = 0;
			}
			if (land_flg == true && Movetimer == 60)
			{
				g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
				land_flg = false;  //地面についていない
			}
			break;

		case 2:		//右下の台へ
			if (x <= 1000 && Movetimer >= 30)
			{
				x += 5;
				runanimfragR = TRUE;
			}
			else if (Movetimer > 30)
			{
				Movepattern = 3;
				dir = 1;
				runanimfragR = FALSE;
			}
			if (Movepattern == 3)
			{
				Movetimer = 0;
			}
			if (land_flg == true && Movetimer == 40)
			{
				g_add = -15.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
				land_flg = false;  //地面についていない
			}
			break;

		case 3:		//左上の台へ
			if (x >= 300 && Movetimer >= 30)
			{
				x -= 5;
				runanimfragL = TRUE;
			}
			else if (Movetimer > 30)
			{
				Movepattern = 4;
				dir = -1;
				runanimfragL = FALSE;
			}
			if (Movepattern == 4)
			{
				Movetimer = 0;
			}
			if (land_flg == true && Movetimer == 60 || Movetimer == 120)
			{
				g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
				land_flg = false;  //地面についていない
			}
			break;

		case 4:		//真ん中の台へ
			if (x <= 650 && Movetimer >= 30)
			{
				x += 5;
				runanimfragR = TRUE;
			}
			else if (Movetimer > 30)
			{
				Movepattern = 5;
				dir = 1;
				runanimfragR = FALSE;
			}
			if (Movepattern == 5)
			{
				Movetimer = 0;
			}
			if (land_flg == true && Movetimer == 60)
			{
				g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
				land_flg = false;  //地面についていない
			}
			break;

		case 5:		//右下の台へ
			if (x >= 300 && Movetimer >= 30)
			{
				x -= 5;
				runanimfragL = TRUE;
			}
			else if (Movetimer > 30)
			{
				Movepattern = 6;
				dir = -1;
				runanimfragL = FALSE;
			}
			if (Movepattern == 6)
			{
				Movetimer = 0;
			}
			if (land_flg == true && Movetimer == 40)
			{
				g_add = -15.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
				land_flg = false;  //地面についていない
			}
			break;

		case 6:		//右上の台へ
			if (x <= 1000 && Movetimer >= 30)
			{
				x += 5;
				runanimfragR = TRUE;
			}
			else if (Movetimer > 30)
			{
				Movepattern = 7;
				dir = 1;
				runanimfragR = FALSE;
			}
			if (Movepattern == 1)
			{
				Movetimer = 0;
			}
			if (land_flg == true && Movetimer == 60 || Movetimer == 120)
			{
				g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
				land_flg = false;  //地面についていない
			}
			break;

		case 7:
			//mob[1]->SetHP(-100);

			Movepattern = 1;
			respawn = true;
			Movetimer = 0;
			break;
		}
	}




	y_add = (y - old_y) + g_add;  //今回の落下距離を設定

	//落下速度の制限
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1フレーム前のｙ座標
	y += y_add;                   //落下距離をｙ座標に加算する
	g_add = _GRAVITY;              //重力加速度を初期化する

	/**********************************************************/

	animtimer++;
}

//描画
void Enemy_05::Draw() const
{
	DrawFormatString(600, 600, 0x00ff00, "%f", player_x);
	if (runanimfragL == FALSE && runanimfragR == FALSE)
	{
		//中心から描画
		if (dir == 1) DrawRotaGraphF(x, y, 1, 0, Enemy_imageL, TRUE);
		else if (dir == -1) DrawRotaGraphF(x, y, 1, 0, Enemy_imageR, TRUE);
	}


	//バリア描画
	if (mob[0]->GetHP() <= 0 && mob[1]->GetHP() <= 0 && mob[2]->GetHP() <= 0){}
	else DrawRotaGraphF(x, y, 1, 0, Enemy_barrier, TRUE);
	

	//左に走るアニメーション
	if (runanimfragL == TRUE) DrawGraph(x - 50, y - 50, Enemy_run_L[animtimer / 15 % 4], TRUE);

	//右に走るアニメーション
	if (runanimfragR == TRUE) DrawGraph(x - 50, y - 50, Enemy_run_R[animtimer / 15 % 4], TRUE);


	//じゃん撃描画
	Draw_Jangeki();
	reflection->Draw_reflectionJangeki();

	//テスト
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);


}

//じゃん撃生成・更新
void Enemy_05::Update_Jangeki()
{
	int jan_count;
	reflection->SetTargetLocation(player_x, player_y);

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
		float speed = 5.0f;     //スピード

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		//生成
		//if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Spin(x, y, radius, speed, type,player_x,player_y);

		//反射じゃん撃生成
		if (reflection->GetFlg() == true)reflection->obj_reflection[reflection->jan_count_reflection] = new Jangeki_Homing(x, y, radius, speed - 2, type, true);
		reflection->falseFlg();
	}
}

void Enemy_05::GetMobEnemy(MobEnemy_05** mobenemy)
{
	mob = mobenemy;
}

bool Enemy_05::respawn_mobenemy()
{
	return respawn;
}

void Enemy_05::SetRespawn(bool flag)
{
	respawn = flag;
}

void Enemy_05::Change_JanType()
{
	switch (GetRand(2))
	{
	case 0:
		SetType(Jan_Type::ROCK);
		break;
	case 1:
		SetType(Jan_Type::SCISSORS);
		break;
	case 2:
		SetType(Jan_Type::PAPER);
		break;
	default:
		break;
	}
}

void Enemy_05::MoveReset()
{
	Movepattern = 1;
	Movetimer = 0;
}