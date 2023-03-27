#include "Enemy_04.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Coming.h"
#include <typeinfo>

//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_04::Enemy_04(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 1.5f;
	dir = 1;
	hp = 100;

	//ランダムな座標取得
	enemy_x = GetRand(1160) + 100;
	enemy_y = GetRand(600) + 100;

	image = LoadGraph("images/Stage4/ステージ4_ボス.png");

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

	//動きパターン
	moveinfo[0] = { 1,enemy_x,enemy_y, 0, 1 };
	moveinfo[1] = { 0,    0.f,    0.f, 0, 0 };

	switch (moveinfo[current].moveflg)
	{
	case 0:
		waitTime++;
		if (moveinfo[current].waitFlameTime <= waitTime)
		{
			waitTime = 0;
			enemy_x = GetRand(1160) + 100;
			enemy_y = GetRand(600) + 100;
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
	
	//HP50％以下でスピードUP
	if (hp <= 50) speed = 3.0f;
	else speed = 1.5f;
	
	//少しずつHP回復
	//if (hp < 100 && frame_count % 15 == 0) hp++;
}

//描画
void Enemy_04::Draw() const
{	
	//中心から描画
	DrawRotaGraphF(x, y, 3, 0, image, TRUE);

	//じゃん撃描画
	Draw_Jangeki();
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
		float radius = 50.0f;   //半径
		float speed  =  2.0f;   //スピード
		
		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		//プレイヤーの角度へ発射するジャン撃生成
		if (frame_count % 50 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);

		////HPが50%以下で新たなジャン撃生成
		//if (hp <= 50)
		//{
		//	//プレイヤーのx座標によって発射する方向を変える(左右)
		//	if (player_x <= 640)
		//	{
		//		if (frame_count % 40 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius * 0.5, speed * -2, type);
		//	}
		//	else if (player_x > 640)
		//	{
		//		if (frame_count % 40 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius * 0.5, speed *  2, type);
		//	}
		//	
		//}
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