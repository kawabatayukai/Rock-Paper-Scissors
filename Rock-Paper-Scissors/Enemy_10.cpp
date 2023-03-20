#include "Enemy_10.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Homing.h"

//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_10::Enemy_10(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 7.0f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //じゃん撃を用意

}

//デストラクタ
Enemy_10::~Enemy_10()
{

}

int switchMove = 0; //作業用変数

/*敵の動き*/
void  Enemy_10::Move()
{
	/*左右の足場にジャンプ移動の処理*/
	switch (switchMove)
	{
	case 0:
		if (x > 120) //左へ移動
		{
			x--;

			if (land_flg == true && x < 990 && x > 200) //ジャンプ
			{
				g_add = -25.0f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
				land_flg = false;  //地面についていない
			}

			if (land_flg == false) //ジャンプ中の加速
			{
				if (v < 15) //加速上限
				{
					v += a;
				}
				x -= v;
			}
		}
		else
		{
			switchMove = 1; //次の処理へ
		}
		break;

	case 1:
		if (x < 1100) //右へ移動
		{
			x++;

			if (land_flg == true && x > 200 && x < 1000) //ジャンプ
			{
				g_add = -25.0f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
				land_flg = false;  //地面についていない
			}

			if (land_flg == false) //ジャンプ中の加速
			{
				if (v < 15) //加速上限
				{
					v += a;
				}
				x += v;
			}
		}
		else
		{
			switchMove = 0; //次の処理へ
		}
		break;
	}

	/*敵直接の属性変化*/
	//e_type = Jan_Type::PAPER;

	/********************   ジャンプ関係   ********************/

	//if (land_flg == true && GetRand(30) == 3)    //GetRand(30) == 3　のところがジャンプの条件
	//{
		//g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
		//land_flg = false;  //地面についていない
	//}

	y_add = (y - old_y) + g_add;  //今回の落下距離を設定

	//落下速度の制限
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1フレーム前のｙ座標
	y += y_add;                   //落下距離をｙ座標に加算する
	g_add = _GRAVITY;              //重力加速度を初期化する

	/**********************************************************/
}

//更新
void Enemy_10::Update()
{
	//じゃん撃更新・生成
	Update_Jangeki();

	Move();

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
	//	g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
	//	land_flg = false;  //地面についていない
	//}
	//
	//y_add = (y - old_y) + g_add;  //今回の落下距離を設定
	//
	////落下速度の制限
	//if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);
	//
	//old_y = y;                    //1フレーム前のｙ座標
	//y += y_add;                   //落下距離をｙ座標に加算する
	//g_add = _GRAVITY;              //重力加速度を初期化する

	/**********************************************************/

}

//描画
void Enemy_10::Draw() const
{
	//中心から描画
	DrawRotaGraphF(x, y, 1, 0, image, TRUE);

	//じゃん撃描画
	Draw_Jangeki();

	//テスト
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);
	DrawFormatString(500, 200, 0xffffffff, "%f", x);

}

//じゃん撃生成・更新
void Enemy_10::Update_Jangeki()
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
		float speed = /* - */3.0f;     //スピード

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		/*********************** ↓↓ 生成( 通常弾 ) ↓↓ ***********************/

		//            生成速度
		//if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type); //通常弾

		/************************************************************************/

		/*********************** ↓↓ 生成( 追跡弾 ) ↓↓ ***********************/

		//            生成速度
		if (frame_count % 50 == 0) obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type); //追跡弾 

		/************************************************************************/
	}
}