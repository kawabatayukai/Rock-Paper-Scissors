#include "Enemy_Cannon.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include "Jangeki_Coming.h"
//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_Cannon::Enemy_Cannon(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 7.0f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //じゃん撃を用意

	Enemy_image = LoadGraph("images/stage08/Stage8_image.png");
}

//デストラクタ2
Enemy_Cannon::~Enemy_Cannon()
{

}


//更新
void Enemy_Cannon::Update()
{
	//じゃん撃更新・生成
	Update_Jangeki();

	if (x + (w / 2) == (1280 -20))
	{
		dir = -1;
	}
	else if (x - (w / 2) == (20))
	{
		dir = 1;
	}

	/*x += dir * speed;*/
}
//描画
	void Enemy_Cannon::Draw () const
	{
	//中心から描画
	DrawRotaGraphF(x, y, 4.f, 0, Enemy_image, TRUE);

	//じゃん撃描画
	Draw_Jangeki();

	//テスト
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);

}

//じゃん撃生成・更新
void Enemy_Cannon::Update_Jangeki()
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
		float radius = 45.5f;   //半径
		float speed = -13.0f;     //スピード

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		//生成
		if (frame_count % 90 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);
	}
}
