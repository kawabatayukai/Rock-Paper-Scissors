#include "Enemy_02.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"

//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_02::Enemy_02(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 7.0f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/stage02/junp4.png");

	Init_Jangeki();       //じゃん撃を用意

}

//デストラクタ
Enemy_02::~Enemy_02()
{

}


//更新
void Enemy_02::Update()
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

	if (jump_cnt < 1)
	{
		if (GetRand(1) == 1)  //乱数でjump_flgをtrueにする
		{
			jump_flg = true;
		}

		if (land_flg == true && jump_flg == true)    //jump_flgがジャンプの条件
		{
			//g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
			land_flg = false;  //地面についていない
			jump_flg = false;  //ジャンプ用フラグのリセット
			jump_cnt++;
		}
	}
	//左に行く
	if (jump_cnt >= 1 && direction_flg == false)
	{

		x = x - 5;
		if (x < 100)
		{
			image = LoadGraph("images/stage02/junp2.png");
			jump_cnt = 0;
			direction_flg = true;
		}
		
		if (land_flg == true && GetRand(1) == 1)    //GetRand(30) == 3　のところがジャンプの条件
		{
			g_add = -25.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
			land_flg = false;  //地面についていない
			
		}
		
	}
	//右に行く
	else if (jump_cnt >= 1 && direction_flg == true)
	{
		x = x + 5;
		if (x > 1180)
		{
			image = LoadGraph("images/stage02/junp4.png");
			jump_cnt = 0;
			direction_flg = false;
		}
		if (land_flg == true && GetRand(1) == 1)    //GetRand(30) == 3　のところがジャンプの条件
		{
			g_add = -25.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
			land_flg = false;  //地面についていない

		}
		
	}

	
 
	y_add = (y - old_y) + g_add;  //今回の落下距離を設定
	
	//落下速度の制限
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);
   

	old_y = y;                    //1フレーム前のｙ座標
	y += y_add;                   //落下距離をｙ座標に加算する
	g_add = _GRAVITY;              //重力加速度を初期化する


	if (hp <= 0)hp = 0;
	/************************************************************/
}

//描画
void Enemy_02::Draw() const
{
	//中心から描画
	DrawRotaGraphF(x, y, 1, 0, image, TRUE);

	//じゃん撃描画
	Draw_Jangeki();

	//テスト
	/*if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);*/

}

//じゃん撃生成・更新
void Enemy_02::Update_Jangeki()
{
	int jan_count;

	//じゃん撃配列をひとつずつ
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//配列の jan_count 番目がnullptr（空要素）ならそれ以上処理しない
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();

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
		float speed = -3.0f;     //スピード

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		//生成
		if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type);
	}
}
//old_yの取得関数
int Enemy_02::Get_OldY()
{
	return old_y;
}

//yの取得関数
int Enemy_02::Get_Y()
{
	return y;
}