#include "Enemy_04.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include <typeinfo>

//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_04::Enemy_04(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 2.5f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/Stage4/ステージ4_ボス.png");

	Init_Jangeki();       //じゃん撃を用意

		//動きパターン
	moveinfo[0] = { 1,0.f,200.f,1 };
	moveinfo[1] = { 1,0.f,500.f,0 };
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

	//ステ04パターン用関数
	Move_Pattern();

	//if (hp <= 50)
	//{
	//	speed = 6.0f;
	//}

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
	//	g_add = -31.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
	//	land_flg = false;  //地面についていない
	//}

	//y_add = (y - old_y) + g_add;  //今回の落下距離を設定

	////落下速度の制限
	//if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	//old_y = y;                    //1フレーム前のｙ座標
	//y += y_add;                   //落下距離をｙ座標に加算する
	//g_add = _GRAVITY;              //重力加速度を初期化する

	/**********************************************************/

}

//描画
void Enemy_04::Draw() const
{	
	//中心から描画
	DrawRotaGraphF(x, y, 3, 0, image, TRUE);

	//じゃん撃描画
	Draw_Jangeki();



	//テスト
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);

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

void Enemy_04::Move_Pattern() {

	//移動する量
	float move_x = x;
	float move_y = y;

	//目指している座標とX座標が一致したとき
	if (y == moveinfo[current].location_y) {
		current = moveinfo[current].next_index; //次のパターン
	}

	//x座標が目指している座標と不一致
	if (y != moveinfo[current].location_y) {

		//目指しているx座標の右方が大きい
		if (y < moveinfo[current].location_y) {
			move_y += speed; //右移動にプラスする

			//目指していた座標を超えたとき
			if (y <= moveinfo[current].location_y && moveinfo[current].location_y <= move_y)
			{

				move_y = moveinfo[current].location_y; //目指していた座標で固定

			}

		}
		else
		{
			move_y -= speed; //左移動にマイナスする

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