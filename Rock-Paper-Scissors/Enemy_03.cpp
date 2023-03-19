#include "Enemy_03.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include <typeinfo>


//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_03::Enemy_03(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{

	speed = 1.85f;//1.5f
	dir = 1;//エネミーの向き
	hp = 100;

	enemyimage[0] = LoadGraph("images/stage03/stage03attack.png");
	enemyimage[1] = LoadGraph("images/stage03/stage03gard.png");

	Init_Jangeki();       //じゃん撃を用意

	//動きパターン 繰り返し　//0で動き,1で止まる
	moveinfo[0] = { 0, 950.f, 0.f , 1,  0 ,1 };//初期位置のXが950で停止

	moveinfo[1] = { 1,  0 ,   0.f , 2, 125 ,1 };//初期位置のXが950で停止
	//ここから動く
	moveinfo[2] = { 0, 650.f, 0.f , 3,  0 ,1 };//Xが650まで動く

	moveinfo[3] = { 1,  0 ,   0.f , 4, 125 ,1 };//Xが650で停止

	moveinfo[4] = { 0, 325.f, 0.f , 5, 0 ,1 };//Xが325まで動く

	moveinfo[5] = { 1,  0 ,   0.f , 6, 125 ,1 };//Xが325で停止

	//足場に乗る
	moveinfo[6] = { 0, 325.f, 0.f , 7, 0 ,0 };//Xが325で停止

	moveinfo[7] = { 1,  0 ,   0.f , 8, 125 ,1 };//Xが325で停止

	moveinfo[8] = { 0,  70.f , 0.f , 9, 0 ,0 };//Xが325で停止

	moveinfo[9] = { 1,  0 ,   0.f , 10, 125 ,1 };//Xが325で停止

	moveinfo[10] = { 0, 280.f, 0.f , 11,  0 ,0 };//Xが650まで動く

	moveinfo[11] = { 1,  0 ,   0.f , 12, 125,1 };//Xが325で停止

	moveinfo[12] = { 0, 465.f, 0.f , 13,  0 ,0 };//Xが650まで動く

	moveinfo[13] = { 1,  0 ,   0.f , 14, 125,1 };//Xが325で停止

	moveinfo[14] = { 0, 585.f,0.f , 15,  0 ,0 };//Xが650まで動く

	moveinfo[15] = { 1,  0 ,   0.f , 16, 125,1 };//Xが325で停止

	moveinfo[16] = { 0, 780.f, 0.f , 17,  0 ,0 };//Xが650まで動く

	moveinfo[17] = { 1,  0 ,   0.f , 18, 125,1 };//Xが325で停止

	moveinfo[18] = { 0, 970.f, 0.f , 19,  0 ,0 };//Xが650まで動く

	moveinfo[19] = { 1,  0 ,   0.f , 20, 125,1 };//Xが325で停止

	moveinfo[20] = { 0, 1160.f, 0.f , 21,  0 ,0 };//Xが650まで動く

	moveinfo[21] = { 1,  0 ,   0.f , 22, 125,1 };//Xが325で停止

	moveinfo[22] = { 0,  1020.f , 0.f , 23, 0, 1 };//Xが325で停止

	moveinfo[23] = { 1,  0 ,   0.f , 24, 125,1 };//Xが325で停止

	moveinfo[24] = { 0,  930.f , 0.f , 25, 0, 1 };//Xが325で停止

	moveinfo[25] = { 1,  0 , 0.f , 26, 125,1 };//Xが325で停止

	moveinfo[26] = { 0, 1020.f , 0.f , 27, 0, 0 };//Xが325で停止

	moveinfo[27] = { 1,  0 , 0.f , 28, 125,1 };//Xが325で停止

	moveinfo[28] = { 0,  1160.f , 0.f , 29, 0, 0 };//Xが325で停止

	moveinfo[29] = { 1,  0 , 0.f , 30, 125, 1 };//Xが325で停止

	moveinfo[30] = { 0,  970.f , 0.f , 31, 0, 0 };//Xが325で停止

	moveinfo[31] = { 1,  0 , 0.f , 32, 125,1 };//Xが325で停止

	moveinfo[32] = { 0,  780.f , 0.f , 33, 0, 0 };//Xが325で停止

	moveinfo[33] = { 1,  0 , 0.f , 34, 125,1 };//Xが325で停止

	moveinfo[34] = { 0,  585.f , 0.f , 35, 0, 0 };//Xが325で停止

	moveinfo[35] = { 1,  0 ,   0.f , 36, 125,1 };//Xが325で停止

	moveinfo[36] = { 0, 465.f, 0.f , 37,  0 ,0 };//Xが650まで動く

	moveinfo[37] = { 1,  0 ,   0.f , 38, 125,1 };//Xが325で停止

	moveinfo[38] = { 0, 280.f, 0.f , 39,  0 ,0 };//Xが650まで動く

	moveinfo[39] = { 1,  0 ,   0.f , 40, 125,1 };//Xが325で停止

	moveinfo[40] = { 0, 70.f,  0.f , 41,  0 ,0 };//Xが650まで動く

	moveinfo[41] = { 1,  0 ,   0.f , 42, 125,1 };//Xが325で停止
	//ここから動く2
	moveinfo[42] = { 0, 325.f, 0.f , 43,  0 ,1 };//初期位置のXが950で停止

	moveinfo[43] = { 1,  0 ,   0.f , 44, 125 ,1 };//初期位置のXが950で停止
	
	moveinfo[44] = { 0, 650.f, 0.f , 45,  0 ,1 };//Xが650まで動く

	moveinfo[45] = { 1,  0 ,   0.f , 46, 125 ,1 };//Xが650で停止

	moveinfo[46] = { 0,	950.f, 0.f , 47, 0 ,1 };//Xが325まで動く

	moveinfo[47] = { 1,	 0,  0.f , 48, 62 ,1 };//Xが325まで動く

	moveinfo[48] = { 1,  0 ,   0.f , 0, 125 ,1 };//Xが650で停止し配列[0]に戻る

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

	//属性変更
	if (moveinfo[current].enemywaitTime > 0) {

		e_type = Jan_Type::ROCK;

	}
	//上記の属性変更以外
	else e_type = Jan_Type::SCISSORS;

	//ステ03パターン用関数
	switch (moveinfo[current].moveflg)
	{
	case 0:
		Move_Pattern();

		break;
	case 1:
		waitcount++;
		if (moveinfo[current].enemywaitTime <= waitcount) {

			waitcount = 0;
			current = moveinfo[current].next_index;

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

	/********************   ジャンプ関係   ********************/



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
	//そうじゃないとき
	else {
		//攻撃時の画像描画
		DrawRotaGraphF(x, y, 1, 0, enemyimage[0], TRUE, dir == -1 ? 0 : 1);
	}




	//じゃん撃描画
	Draw_Jangeki();




	//テスト                                                      //赤色
	if (moveinfo[current].enemywaitTime > 0) DrawFormatString((int)(x - 100), (int)(y - 100), GetColor(0, 0, 255), "防御力 UP↑", moveinfo[current].enemywaitTime);

	if (hp <= 50) DrawFormatString((int)(x - 100), (int)(y - 80), GetColor(255, 0, 0), "攻撃力 UP↑", hp);

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
		float radius = 40.0f;   //半径 //35.5f
		float speed = 6.0f * dir;     //スピード//3.0

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));//2


		//生成
		if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type);
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

			//speedがup
			speed = 4.0f;

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
