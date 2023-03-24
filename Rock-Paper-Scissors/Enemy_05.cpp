#include "Enemy_05.h"
#include "DxLib.h"
#include "Player.h"
#include "Jangeki_Base.h"
#include "Jangeki_Changespeed.h"
#include "Jangeki_Zigzag.h" 
#include "Jangeki_Spin.h" 


//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_05::Enemy_05(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 7.0f;
	dir = 1;
	hp = 100;
	Movepattern = 1;
	Movetimer = 0;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //じゃん撃を用意

	Enemy_image = LoadGraph("images/stage05/Stage5_Enemy_NoMove_Left.png", TRUE);
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

	//if (x + (w / 2) == (1280 - 20))
	//{
	//	dir = -1;
	//}
	//else if (x - (w / 2) == (20))
	//{
	//	dir = 1;
	//}

	//x += dir * speed;

	/********************   ジャンプ関係   ********************/

	//if (land_flg == true && GetRand(30) == 3)    //GetRand(30) == 3　のところがジャンプの条件
	//{
	//	//g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
	//	g_add = -25.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
	//	land_flg = false;  //地面についていない
	//}

	Movetimer++;

	//敵の移動
	//switch (Movepattern)
	//{
	//case 1:		//真ん中の台へ
	//	if (x >= 650 && Movetimer >= 30)
	//	{
	//		x -= 5;
	//	}
	//	else if (Movetimer > 30)
	//	{
	//		Movepattern = 2;
	//	}
	//	if (Movepattern == 2)
	//	{
	//		Movetimer = 0;
	//	}
	//	if (land_flg == true && Movetimer == 60)
	//	{
	//		g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
	//		land_flg = false;  //地面についていない
	//	}
	//	break;

	//case 2:		//右下の台へ
	//	if (x <= 1000 && Movetimer >= 30)
	//	{
	//		x += 5;
	//	}
	//	else if (Movetimer > 30)
	//	{
	//		Movepattern = 3;
	//	}
	//	if (Movepattern == 3)
	//	{
	//		Movetimer = 0;
	//	}
	//	if (land_flg == true && Movetimer == 40)
	//	{
	//		g_add = -15.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
	//		land_flg = false;  //地面についていない
	//	}
	//	break;

	//case 3:		//左上の台へ
	//	if (x >= 300 && Movetimer >= 30)
	//	{
	//		x -= 5;

	//	}
	//	else if (Movetimer > 30)
	//	{
	//		Movepattern = 4;
	//	}
	//	if (Movepattern == 4)
	//	{
	//		Movetimer = 0;
	//	}
	//	if (land_flg == true && Movetimer == 60 || Movetimer == 120)
	//	{
	//		g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
	//		land_flg = false;  //地面についていない
	//	}
	//	break;

	//case 4:		//真ん中の台へ
	//	if (x <= 650 && Movetimer >= 30)
	//	{
	//		x += 5;
	//	}
	//	else if (Movetimer > 30)
	//	{
	//		Movepattern = 5;
	//	}
	//	if (Movepattern == 5)
	//	{
	//		Movetimer = 0;
	//	}
	//	if (land_flg == true && Movetimer == 60)
	//	{
	//		g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
	//		land_flg = false;  //地面についていない
	//	}
	//	break;

	//case 5:		//右下の台へ
	//	if (x >= 300 && Movetimer >= 30)
	//	{
	//		x -= 5;
	//	}
	//	else if (Movetimer > 30)
	//	{
	//		Movepattern = 6;
	//	}
	//	if (Movepattern == 6)
	//	{
	//		Movetimer = 0;
	//	}
	//	if (land_flg == true && Movetimer == 40)
	//	{
	//		g_add = -15.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
	//		land_flg = false;  //地面についていない
	//	}
	//	break;

	//case 6:		//右上の台へ
	//	if (x <= 1000 && Movetimer >= 30)
	//	{
	//		x += 5;
	//	}
	//	else if (Movetimer > 30)
	//	{
	//		Movepattern = 1;
	//	}
	//	if (Movepattern == 1)
	//	{
	//		Movetimer = 0;
	//	}
	//	if (land_flg == true && Movetimer == 60|| Movetimer == 120)
	//	{
	//		g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
	//		land_flg = false;  //地面についていない
	//	}
	//	break;
	//}

	y_add = (y - old_y) + g_add;  //今回の落下距離を設定

	//落下速度の制限
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1フレーム前のｙ座標
	y += y_add;                   //落下距離をｙ座標に加算する
	g_add = _GRAVITY;              //重力加速度を初期化する

	/**********************************************************/

}

//描画
void Enemy_05::Draw() const
{
	//中心から描画
	DrawRotaGraphF(x, y, 1, 0, Enemy_image, TRUE);

	//じゃん撃描画
	Draw_Jangeki();

	//テスト
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);

}

//じゃん撃生成・更新
void Enemy_05::Update_Jangeki()
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
		float radius = 35.5f;   //半径
		float speed = 5.0f;     //スピード

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		//生成
		//if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Spin(x, y, radius, speed, type,player_x,player_y);

	}
}