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

	/*enemyimage[0] = LoadGraph("images/stage03/stage03attack.png");
	enemyimage[1] = LoadGraph("images/stage03/stage03gard.png");
	enemyimage[2] = LoadGraph("images/stage03/stage03jump.png");*/

	LoadDivGraph("images/stage03/stage03Anim.png", 6, 6, 1, 100, 100, enemyimage);
	LoadDivGraph("images/stage03/stage03SheeldEnduranse1.png", 6, 6, 1, 100, 100, enemyimage1);
	LoadDivGraph("images/stage03/stage03SheeldEnduranse2.png", 6, 6, 1, 100, 100, enemyimage2);
	LoadDivGraph("images/stage03/stage03SheeldEnduranse3.png", 6, 6, 1, 100, 100, enemyimage3);
	LoadDivGraph("images/stage03/stage03SheeldEnduranse4.png", 6, 6, 1, 100, 100, enemyimage4);

	LoadDivGraph("images/stage03/BreakSheeldAnim.png", 8, 8, 1, 220, 220, SheeldBreakAnim);


	//LoadDivGraph("images/stage03/stage03AnimMirror.png", 6, 6, 1, 100, 100, enemyimageMirror);

	Init_Jangeki();       //じゃん撃を用意

	//動きパターン 繰り返し　//0で動き,1で止まる
	moveinfo[0] = { 0, 950.f, 0.f , 1,  0 ,1 };//初期位置のXが950で停止

	moveinfo[1] = { 1,  0 ,   0.f , 2, 200 ,1 };//初期位置のXが950で停止
	//ここから動く
	moveinfo[2] = { 0, 650.f, 0.f , 3,  0 ,0 };//Xが650まで動く

	moveinfo[3] = { 1,  0 ,   0.f , 4, 0 ,1 };//Xが650で停止

	moveinfo[4] = { 0, 350.f, 0.f , 5, 0 ,1 };//Xが350まで動く

	moveinfo[5] = { 1,  0 ,   0.f , 6, 200 ,1 };//Xが350で停止

	moveinfo[6] = { 0, 350.f, 0.f , 7, 0 ,1 };//Xが350の足場に飛ぶ

	moveinfo[7] = { 1,  0 ,   0.f , 8, 0 ,1 };//Xが350で停止

	//足場に乗る
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

	moveinfo[35] = { 0, 650.f, 0.f , 36,  0 ,0 };//Xが650まで動く

	moveinfo[36] = { 1,  0 ,   0.f , 37, 200 ,1 };//Xが650で停止

	moveinfo[37] = { 0,	950.f, 0.f , 38, 0 ,0 };//Xが900まで動く

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
	if (moveinfo[current].enemywaitTime > 0 || moveinfo[current].enemywaitTime < 200 && moveinfo[current].jumpflg == 0) {

		e_type = Jan_Type::ROCK;


	}
	//動いているとき属性変更
	/*else if (moveinfo[current].enemywaitTime < 200 && moveinfo[current].jumpflg == 0) {



		e_type = Jan_Type::SCISSORS;
	}*/

	if (hp > 40) {//HP40%より多いの間パターンの動きをする


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
			/*case 2:
				MoveRunAway(float enemy_x, float enemy_y, int player_x, int player_y);*/
			break;
		default:
			break;
		}


	}
	else if (hp<=40 && st3_animcount < 8) {



	}
	else {

		//enemyのxが475以下の時
		if (x <= 475) {

			//前回より加速する
			speed = 7.5f;

		}
		//enemyのxが950以下で475以上の時
		else if (x <= 950 && x >= 475) {

			//前回より加速する
			speed = 5.5f;

		}
		//enemyのxが950以上の時
		else if (x >= 950) {

			//前回より加速する
			speed = 7.5f;

		}
		//それ以外は普通の動き
		else
		{

			speed = 1.5f;


		}

		//目標座標
		static float target_x = 0;
		static float target_y = 0;


		//一致回数
		static int count;
		if (count == 0)
		{
			target_x = GetRand(1170) + 70;
			//if (x==1000)
			//{
			//	count = 1;
			//}
			count = 1;
		}
		if (count == 1)
		{

			if (x == target_x)
			{
				count = 0;
			}
		}

		//移動量
		float move_x = x;
		float move_y = y;
		moveinfo[current].jumpflg = 1;

		//x座標が目標と不一致
		if (x != target_x)
		{
			//目標の方が大きい（目標は右方向）
			if (x < target_x)
			{
				move_x += speed;      //右移動（正の値）


				//目標を超えた場合
				if (x <= target_x && target_x <= move_x)
				{
					move_x = target_x;     //目標座標で固定
				}
			}
			else
			{
				move_x -= speed; //左移動（負の値）


				//目標を超えた場合
				if (move_x <= target_x && target_x <= x)
				{
					move_x = target_x;     //目標座標で固定
				}
			}
		}

		////y座標が目標と不一致
		//if (y != target_y)
		//{
		//	//目標の方が大きい（目標は右方向）
		//	if (y < target_y)
		//	{
		//		move_y += speed;      //右移動（正の値）


		//		//目標を超えた場合
		//		if (y <= target_y && target_y <= move_y)
		//		{
		//			move_y = target_y;     //目標座標で固定
		//		}
		//	}
		//	else
		//	{
		//		move_y -= speed; //左移動（負の値）


		//		//目標を超えた場合
		//		if (move_y <= target_y && target_y <= y)
		//		{
		//			move_y = target_y;     //目標座標で固定
		//		}
		//	}
		//}
		//移動を反映
		x = move_x;
		y = move_y;

		if (old_x == x)
		{
			target_x = GetRand(1170) + 70;

		}




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


	//配列0～2番目の画像のループ
	if (++Eframe_count_anim % 40 == 0) {

		Ecurrentindex_st03++;
		if (Ecurrentindex_st03 >= 3)Ecurrentindex_st03 = 0;
		Eframe_count_anim = 0;
	}

	//前回のｘ
	old_x = x;

	//HPが40%以下Animcountが8より小さい時アニメーション実装
	if (hp <= 40 && st3_animcount < 8) {

		++st3_animtimer;
		if (st3_animtimer % 8 == 0) {

			st3_animcount++;
			st3_animtimer = 0;
		}

	}


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
	////////////////////////
	///HPが86以上の時
	///////////////////////

	if (hp >= 86) {

		
		//エネミー停止時
		if (moveinfo[current].enemywaitTime > 0) {


			//ガード時の画像描画							
			DrawRotaGraphF(x, y, 1, 0, enemyimage[5]/*[1]*/, TRUE, dir == -1 ? 0 : 1);


		}

		//ジャンプ時
		else if (moveinfo[current].jumpflg == 0 && moveinfo[current].moveflg == 0 && moveinfo[current].enemywaitTime < 200) {

			//ジャンプ時の画像描画							
			DrawRotaGraphF(x, y, 1, 0, enemyimage[4]/*[2]*/, TRUE, dir == -1 ? 0 : 1);

		}
		//そうじゃないとき
		//動いているとき
		else {

			//エネミーの構造体と一致したときに     エネミーが左または右に動く
			if (enemy_state == ENEMY_STATE::LEFTMOVE || enemy_state == ENEMY_STATE::RIGHTMOVE && moveinfo[current].enemywaitTime < 200) {

				//攻撃時の画像描画								//向きを変える
				DrawRotaGraphF(x, y, 1, 0, enemyimage[Ecurrentindex_st03]/*[0]*/, TRUE, dir == -1 ? 0 : 1);
			}


		}

	}

	//////////////////////
	//HP85以下で70以上のとき
	/////////////////////
	else if (hp <= 85 && hp >= 71) {

		
		if (moveinfo[current].enemywaitTime > 0) {

			DrawRotaGraphF(x, y, 1, 0, enemyimage1[5]/*[1]*/, TRUE, dir == -1 ? 0 : 1);

		}
		else if (moveinfo[current].jumpflg == 0 && moveinfo[current].moveflg == 0 && moveinfo[current].enemywaitTime < 200) {



			//ジャンプ時の画像描画							
			DrawRotaGraphF(x, y, 1, 0, enemyimage1[4]/*[2]*/, TRUE, dir == -1 ? 0 : 1);

		}

		else {

			//エネミーの構造体と一致したときにエネミーが左または右に動く
			if ((enemy_state == ENEMY_STATE::LEFTMOVE || enemy_state == ENEMY_STATE::RIGHTMOVE && moveinfo[current].enemywaitTime < 200)) {
				//攻撃時の画像描画								//向きを変える
				DrawRotaGraphF(x, y, 1, 0, enemyimage1[Ecurrentindex_st03]/*[0]*/, TRUE, dir == -1 ? 0 : 1);
			}


		}



	}
	////////////////////////
	//HP70以下で 55以上のとき
	////////////////////////
	else if (hp <= 70 && hp >= 56) {
		
		if (moveinfo[current].enemywaitTime > 0) {

			DrawRotaGraphF(x, y, 1, 0, enemyimage2[5]/*[1]*/, TRUE, dir == -1 ? 0 : 1);

		}
		else if (moveinfo[current].jumpflg == 0 && moveinfo[current].moveflg == 0 && moveinfo[current].enemywaitTime < 200) {

			//ジャンプ時の画像描画							
			DrawRotaGraphF(x, y, 1, 0, enemyimage2[4]/*[2]*/, TRUE, dir == -1 ? 0 : 1);

		}
		else {

			//エネミーの構造体と一致したときにエネミーが左または右に動く
			if ((enemy_state == ENEMY_STATE::LEFTMOVE || enemy_state == ENEMY_STATE::RIGHTMOVE && moveinfo[current].enemywaitTime < 200)) {
				//攻撃時の画像描画								//向きを変える
				DrawRotaGraphF(x, y, 1, 0, enemyimage2[Ecurrentindex_st03]/*[0]*/, TRUE, dir == -1 ? 0 : 1);
			}
		}

	}

	//////////////////////////
	//HP55以下で41以上のとき
	//////////////////////////
	else if(hp <= 55 && hp >= 41){
		
		if ( moveinfo[current].enemywaitTime > 0) {


			DrawRotaGraphF(x, y, 1, 0, enemyimage3[5]/*[1]*/, TRUE, dir == -1 ? 0 : 1);

		}
		else if (moveinfo[current].jumpflg == 0 && moveinfo[current].moveflg == 0 && moveinfo[current].enemywaitTime < 200) {

			//ジャンプ時の画像描画							
			DrawRotaGraphF(x, y, 1, 0, enemyimage3[4]/*[2]*/, TRUE, dir == -1 ? 0 : 1);

		}
		else {

			//エネミーの構造体と一致したときにエネミーが左または右に動く
			if ((enemy_state == ENEMY_STATE::LEFTMOVE || enemy_state == ENEMY_STATE::RIGHTMOVE && moveinfo[current].enemywaitTime < 200)) {
				//攻撃時の画像描画								//向きを変える
				DrawRotaGraphF(x, y, 1, 0, enemyimage3[Ecurrentindex_st03]/*[0]*/, TRUE, dir == -1 ? 0 : 1);
			}


		}
	}

	//////////////////////////
	//HP40以下のとき
	////////////////////////////
	else {
		
			//エネミーの構造体と一致したときにエネミーが左または右に動く
		if ((hp <= 40 /*&& hp >= 39*/ && enemy_state == ENEMY_STATE::LEFTMOVE || enemy_state == ENEMY_STATE::RIGHTMOVE && moveinfo[current].enemywaitTime < 200)) {
			//攻撃時の画像描画								//向きを変える
			
			DrawRotaGraphF(x, y, 1, 0, enemyimage4[Ecurrentindex_st03]/*[0]*/, TRUE, dir == -1 ? 0 : 1);
			////////////
			//エフェクト
			////////////
			if (st3_animcount < 8) {

				SetDrawBlendMode(DX_BLENDMODE_ADD,155);
				DrawRotaGraphF(x, y, 1, 0, SheeldBreakAnim[st3_animcount],TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			}
		}

	}

	
	

	//じゃん撃描画
	Draw_Jangeki();


	//テスト                                                      //赤色
	if (hp <= 85 && moveinfo[current].enemywaitTime > 0) DrawFormatString((int)(x - 35), (int)(y - 50), GetColor(0, 0, 255), "防御DOWN↓", moveinfo[current].enemywaitTime);

	if (hp <= 40) DrawFormatString((int)(x - 50), (int)(y - 70), GetColor(255, 0, 0), " 攻撃UP↑", hp);

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
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));//2 //主に属性時のジャン撃を繰り出す


		//プレイヤー方向へのジャン撃生成

		if (hp >= 41) {
			if (frame_count % 100 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);
		}
		////通常弾生成
		//if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type);

		//攻撃UP時のジャン撃
		else if (hp <= 40) {

			float radius = 50.0f;
			float speed = 4.5f;

			if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);

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
			speed = 4.3f;

		}


		//目指しているx座標の右方が大きい
		if (x < moveinfo[current].location_x) {

			move_x += speed; //右移動にプラスする

			enemy_state = ENEMY_STATE::RIGHTMOVE;

			//目指していた座標を超えたとき
			if (x <= moveinfo[current].location_x && moveinfo[current].location_x <= move_x)
			{

				move_x = moveinfo[current].location_x; //目指していた座標で固定

			}

		}
		else
		{
			move_x -= speed; //左移動にマイナスする

			enemy_state = ENEMY_STATE::LEFTMOVE;

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



//エネミーの座標を継承
void Enemy_03::ChangeDir(float enemy_x)
{
	if (enemy_x < x) dir = -1;
	else dir = 1;
}

