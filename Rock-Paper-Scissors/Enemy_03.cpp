#include "Enemy_03.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Coming.h"
#include <typeinfo>


//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_03::Enemy_03(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{

	speed = 1.5f;//1.5f //前回1.85f
	dir = 1;//エネミーの向き
	hp = 100;

	enemyimage[0] = LoadGraph("images/stage03/stage03attack.png");
	enemyimage[1] = LoadGraph("images/stage03/stage03gard.png");
	enemyimage[2] = LoadGraph("images/stage03/stage03jump.png");

	Init_Jangeki();       //じゃん撃を用意

	//動きパターン 繰り返し　//0で動き,1で止まる
	moveinfo[0] = { 0, 950.f, 0.f , 1,  0 ,1 };//初期位置のXが950で停止

	moveinfo[1] = { 1,  0 ,   0.f , 2, 200 ,1 };//初期位置のXが950で停止
	//ここから動く
	moveinfo[2] = { 0, 650.f, 0.f , 3,  0 ,1 };//Xが650まで動く

	moveinfo[3] = { 1,  0 ,   0.f , 4, 200 ,1 };//Xが650で停止

	moveinfo[4] = { 0, 350.f, 0.f , 5, 0 ,1 };//Xが350まで動く

	moveinfo[5] = { 1,  0 ,   0.f , 6, 200 ,1 };//Xが350で停止

	//足場に乗る
	moveinfo[6] = { 0, 350.f, 0.f , 7, 0 ,0 };//Xが350の足場に飛ぶ

	moveinfo[7] = { 1,  0 ,   0.f , 8, 200 ,1 };//Xが350で停止

	moveinfo[8] = { 0,  50.f , 0.f , 9, 0 ,0 };//Xが70足場に飛ぶ

	//moveinfo[9] = { 1,  0 ,   0.f , 10, 200 ,1 };//Xが70で停止

	moveinfo[9] = { 0, 280.f, 0.f , 10,  0 ,0 };//Xが280の足場に飛ぶ

	moveinfo[10] = { 1,  0 ,   0.f , 11, 200,1 };//Xが280で停止

	moveinfo[11] = { 0, 465.f, 0.f , 12,  0 ,0 };//Xが465の足場に飛ぶ

	//moveinfo[12] = { 1,  0 ,   0.f , 14, 200,1 };//Xが465で停止

	moveinfo[12] = { 0, 585.f,0.f , 13,  0 ,0 };//Xが585の足場に飛ぶ

	moveinfo[13] = { 1,  0 ,   0.f , 14, 200,1 };//Xが585で停止

	moveinfo[14] = { 0, 780.f, 0.f , 15,  0 ,0 };//Xが780の足場に飛ぶ

	//moveinfo[17] = { 1,  0 ,   0.f , 18, 200,1 };//Xが780で停止

	moveinfo[15] = { 0, 970.f, 0.f , 16,  0 ,0 };//Xが970の足場に飛ぶ

	moveinfo[16] = { 1,  0 ,   0.f , 17, 200,1 };//Xが970の足場で停止

	moveinfo[17] = { 0, 1150.f, 0.f , 18,  0 ,0 };//Xが1160の足場に飛ぶ

	//moveinfo[21] = { 1,  0 ,   0.f , 22, 200,1 };//Xが1160で停止

	moveinfo[18] = { 0,  1150.f , 0.f , 19, 0, 1 };//Xが1160の足場に飛ぶ

	//moveinfo[19] = { 1,  0 ,   0.f , 20, 200,1 };//Xが1160で停止

	moveinfo[19] = { 0,  970.f , 0.f , 20, 0, 1 };//Xが930まで移動

	moveinfo[20] = { 1,  0 , 0.f , 21, 200,1 };//Xが930で停止


	//前回の逆パターンへ
	moveinfo[21] = { 0, 1150.f , 0.f , 22, 0, 0 };//Xが1050の足場に飛ぶ

	//moveinfo[27] = { 1,  0 , 0.f , 28, 200,1 };//Xが1020で停止

	moveinfo[22] = { 0,  1150.f , 0.f , 23, 0, 0 };//Xが1160の足場に飛ぶ

	moveinfo[23] = { 1,  0 , 0.f , 24, 200, 1 };//Xが1160で停止

	moveinfo[24] = { 0,  970.f , 0.f , 25, 0, 0 };//Xが970の足場に飛ぶ

	//moveinfo[25] = { 1,  0 , 0.f , 26, 200,1 };//Xが970で停止

	moveinfo[25] = { 0,  780.f , 0.f , 26, 0, 0 };//Xが780の足場に飛ぶ

	moveinfo[26] = { 1,  0 , 0.f , 27, 200,1 };//Xが780で停止

	moveinfo[27] = { 0,  585.f , 0.f , 28, 0, 0 };//Xが585の足場に飛ぶ

	//moveinfo[28] = { 1,  0 ,   0.f , 29, 200,1 };//Xが585で停止

	moveinfo[28] = { 0, 465.f, 0.f , 29,  0 ,0 };//Xが465の足場に飛ぶ

	moveinfo[29] = { 1,  0 ,   0.f , 30, 200,1 };//Xが465で停止

	moveinfo[30] = { 0, 280.f, 0.f , 31,  0 ,0 };//Xが280の足場に飛ぶ


	//moveinfo[31] = { 1,  0 ,   0.f , 32, 200,1 };//Xが280で停止

	moveinfo[31] = { 0, 50.f,  0.f , 32,  0 ,0 };//Xが70まで動く

	moveinfo[32] = { 1,  0 ,   0.f , 33, 200,1 };//Xが70で停止
	//ここから動く2
	moveinfo[33] = { 0, 350.f, 0.f , 34,  0 ,1 };//初期位置のXが350で停止

	moveinfo[34] = { 1,  0 ,   0.f , 35, 200 ,1 };//初期位置のXが350で停止

	moveinfo[35] = { 0, 650.f, 0.f , 36,  0 ,1 };//Xが650まで動く

	moveinfo[36] = { 1,  0 ,   0.f , 37, 200 ,1 };//Xが650で停止

	moveinfo[37] = { 0,	950.f, 0.f , 38, 0 ,1 };//Xが900まで動く

	//moveinfo[47] = { 1,	 0,  0.f , 48, 62 ,1 };//Xが900で少しの時間停止

	moveinfo[38] = { 1,  0 ,   0.f , 0, 200 ,1 };//Xが900で停止し配列[0]に戻る

}



//デストラクタ
Enemy_03::~Enemy_03()
{

}

//更新
void Enemy_03::Update()
{
	if (land_flg == true && moveinfo[current].enemywaitTime == 0 && moveinfo[current].jumpflg == 0)    //GetRand(30) == 3　のところがジャンプの条件
	{
		g_add = -23.f;    //初期-21.5f,重力加速度をマイナス値に　　下げるほどジャンプ力アップ
		land_flg = false;  //地面についていない

		speed = 2.8f;
	}


	//じゃん撃更新・生成
	Update_Jangeki();

	////属性変更
	if (moveinfo[current].enemywaitTime > 0) {

		e_type = Jan_Type::ROCK;

	}
	//動いているとき属性変更
	else if (moveinfo[current].enemywaitTime < 200) {



		e_type = Jan_Type::SCISSORS;
	}


	//ステ03パターン用関数
	switch (moveinfo[current].moveflg)
	{
	case 0:
		Move_Pattern();

		break;
	case 1:
		//待ち時間カウント
		waitcount++;
		if (moveinfo[current].enemywaitTime <= waitcount) {

			waitcount = 0;
			current = moveinfo[current].next_index;

			//ランダムな動きX方向//
			//moveinfo[current].location_x = GetRand(1150);


		}
		break;
	default:
		break;
	}


	//HPが0以下だったらHPに0を代入
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

	///********************   ジャンプ関係   ********************/


		y_add = (y - old_y) + g_add;  //今回の落下距離を設定

		//落下速度の制限
		if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

		old_y = y;              //1フレーム前のｙ座標
		y += y_add;            //落下距離をｙ座標に加算する
		g_add = _GRAVITY;     //重力加速度を初期化する

}
/********************   横移動   ********************/

//if (land_flg == true && GetRand(30) == 3)    //GetRand(30) == 3　のところがジャンプの条件
//{
//	enemy_x = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ


//	land_flg = false;  //地面についていない

//}

//old_x = (x - old_x) + enemy_x;  //今回の落下距離を設定

////落下速度の制限
//if (enemy_x > static_cast<float>(MAX_LENGTH)) enemy_x = static_cast<float>(MAX_LENGTH);

//old_x = x;                    //1フレーム前のx座標
//x += enemy_x;                   //落下距離をx座標に加算する
//enemy_x = _GRAVITY;              //重力加速度を初期化する

/**********************************************************/

//描画
void Enemy_03::Draw() const

{
	//エネミー停止時
	if (moveinfo[current].enemywaitTime > 0) {

		//ガード時の画像描画							
		DrawRotaGraphF(x, y, 1, 0, enemyimage[1], TRUE, dir == -1 ? 0 : 1);


	}

	else if (moveinfo[current].enemywaitTime < 0) {

		//ジャンプ時の画像描画							
		DrawRotaGraphF(x, y, 1, 0, enemyimage[2], TRUE, dir == -1 ? 0 : 1);

	}





	//そうじゃないとき
	else {
		//攻撃時の画像描画								//向きを変える
		DrawRotaGraphF(x, y, 1, 0, enemyimage[0], TRUE, dir == -1 ? 0 : 1);
	}


	//じゃん撃描画
	Draw_Jangeki();


	//テスト                                                      //赤色
	if (moveinfo[current].enemywaitTime > 0) DrawFormatString((int)(x - 100), (int)(y - 100), GetColor(0, 0, 255), "防御力 UP↑", moveinfo[current].enemywaitTime);

	if (hp <= 40) DrawFormatString((int)(x - 100), (int)(y - 80), GetColor(255, 0, 0), " 攻撃力 UP ↑", hp);

	if (hp <= 0)DrawString((int)(x - 100), (int)(y - 120), "death!", 0xff0000);

}

//じゃん撃生成・更新
void Enemy_03::Update_Jangeki()
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
		float radius = 35.5f;   //半径 //35.5f
		float speed = 4.5f /** dir*/;     //スピード//3.0

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(1));//2 //主に属性時のジャン撃を繰り出す


		//プレイヤー方向へのジャン撃生成

		if (hp >= 41) {
			if (frame_count % 85 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);
		}
		////通常弾生成
		//if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type);

		//攻撃UP時のジャン撃
		else if (hp <= 40) {


			float radius = 50.0f;
			float speed = 4.5f;

			if (frame_count % 90 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);



		}


	}
}

void Enemy_03::Move_Pattern() {

	//移動する量
	float move_x = x;
	float move_y = y;

	//目指している座標とX座標が一致したとき
	if (x == moveinfo[current].location_x) {

		current = moveinfo[current].next_index; //次のパターン

		//speedがup
		speed = 2.8f;
	}


	//x座標が目指している座標と不一致
	if (x != moveinfo[current].location_x) {


		//ジャンプしているとき
		if (moveinfo[current].jumpflg == 0) {

			//speedがup,足場に乗せるための調整
			speed = 4.2f;

		}


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

	//移動を反映する
	x = move_x;
	y = move_y;

}

//enemywaitTime継承
int Enemy_03::GetWaitTime()const {

	return moveinfo[current].enemywaitTime;
}



//プレイヤーの座標を継承
void Enemy_03::ChangeDir(float x)
{
	if (x < 640) dir = -1;
	else dir = 1;
}

