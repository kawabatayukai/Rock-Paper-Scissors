#include "Enemy_06.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"

//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_06::Enemy_06(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 7.0f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //じゃん撃を用意

}

//デストラクタ
Enemy_06::~Enemy_06()
{

}


//更新
void Enemy_06::Update()
{
	//じゃん撃更新・生成
	Update_Jangeki();

	if (hp <= 0)hp = 0;

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

	if (attack_pattern == 0)      //攻撃パターン1
	{
		if (jump_cnt < 3)         //4回ジャンプするまでの間以下の処理を繰り返す
		{
			if (GetRand(3) == 3)  //乱数でjump_flgをtrueにする
			{
				jump_flg = true;
			}

			if (land_flg == true && jump_flg == true)    //jump_flgがジャンプの条件
			{
				g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
				land_flg = false;  //地面についていない
				jump_flg = false;  //ジャンプ用フラグのリセット
				jump_cnt++;        //ジャンプ回数のカウント
			}
		}

		//4回以上ジャンプした際の処理
		if (jump_cnt >= 3 && direction_flg == false)        //左を向いている時の処理
		{

			x = x - 4;      //1フレームの間に左へ進む距離
			if (x < 100)    //目標座標に到着したかのチェック
			{
				jump_cnt = 0;          //ジャンプ回数のリセット
				direction_flg = true;  //向いている向きの反転
			}
		}
		else if (jump_cnt >= 3 && direction_flg == true)    //右を向いている時の処理
		{
			x = x + 4;      //1フレームの間に右へ進む距離
			if (x > 1180)   //目標座標に到着したかのチェック
			{
				jump_cnt = 0;           //ジャンプ回数のリセット
				direction_flg = false;  //向いている向きの反転
			}
		}

		if (hp <= 150)
		{
			/*attack_pattern = 1;*/
		}
	}
	
	if (attack_pattern == 1)
	{
		if (GetRand(30) == 3)  //乱数でjump_flgをtrueにする
		{
			jump_flg = true;
		}

		if (jump_flg == true && land_flg == true)    //jump_flgがジャンプの条件
		{
			g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
			land_flg = false;  //地面についていない
			jump_flg = false;  //ジャンプ用フラグのリセット
		}
				
		//4回以上ジャンプした際の処理
		if (direction_flg == false)        //左を向いている時の処理
		{
			x = x - 20;      //1フレームの間に左へ進む距離
			if (x < 100)    //目標座標に到着したかのチェック
			{
				direction_flg = true;  //向いている向きの反転
			}
		}
		else if (direction_flg == true)    //右を向いている時の処理
		{
			x = x + 20;      //1フレームの間に右へ進む距離
			if (x > 1180)   //目標座標に到着したかのチェック
			{
				direction_flg = false;  //向いている向きの反転
			}
		}


		/*if (hp <= 100)
		{
			attack_pattern = 2;
		}*/
	}

	y_add = (y - old_y) + g_add;  //今回の落下距離を設定

	//落下速度の制限
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1フレーム前のｙ座標
	y += y_add;                   //落下距離をｙ座標に加算する
	g_add = _GRAVITY;              //重力加速度を初期化する

	/**********************************************************/

}

//描画
void Enemy_06::Draw() const
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
void Enemy_06::Update_Jangeki()
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
		float speed = -8.0f;     //スピード

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		//生成
		if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type);
	}
}

//old_yの取得関数
int Enemy_06::Get_OldY()
{
	return old_y;
}

//yの取得関数
int Enemy_06::Get_Y()
{
	return y;
}