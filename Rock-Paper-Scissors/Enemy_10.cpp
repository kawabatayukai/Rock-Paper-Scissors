#include "Enemy_10.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Homing.h"
#include"Jangeki_Coming.h"

//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_10::Enemy_10(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 7.0f;
	dir = 1;
	hp = 100;

	//image = LoadGraph("images/tyokitest.png");
	if (LoadDivGraph("images/ワンパンマンALL画像.png", 10, 5, 2, 100, 100, image) == -1);

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
			dir = static_cast<int>(DIRECTION::LEFT);   //向きを設定（左）

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
		enemyChange_Image = 2; //switch文の割り当て番号
		break;

	case 1:
		if (x < 1100) //右へ移動
		{
			x++;
			dir = static_cast<int>(DIRECTION::RIGHT);  //向きを設定（右）

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
		enemyChange_Image = 1; //switch文の割り当て番号
		break;
	}

	//画像の選択変更
	EnemySwitch();

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
	DrawRotaGraphF(x, y, 1, 0, image[enemy_Image], TRUE);
	//DrawRotaGraphF(x, y, 1, 0, image, TRUE);

	//じゃん撃描画
	Draw_Jangeki();

	//テスト
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);
	DrawFormatString(500, 200, 0xffffffff, "%f", x);

}

/*画像の変更取得*/
void  Enemy_10::EnemySwitch()
{
	/*プレイヤーの画像変更*/
	switch (enemyChange_Image)
	{
		/*左右移動*/
	case 1: //右移動
	   /*     右向き            接地   */
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true)
		{
			enemyGetMove = 1;      //画像を取得
			enemyCount++;          //フレームカウントを増やす
			EnemyChangeMoveimg();  //画像変更へ

			//pCount = 0;             //動いてないとき用
			//enemyChange_Image = 0; //動いてないとき用
			break;
		}       /*  右向き         非接地     */
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false)
		{
			enemy_Image = 4;     //画像を取得
			break;
		}

	case 2: //左移動の時
	   /*     左向き            接地  */
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true)
		{
			enemyGetMove = 6;      //画像を取得
			enemyCount++;          //フレームカウントを増やす
			EnemyChangeMoveimg();  //画像変更へ

			//pCount = 5;             //動いてないとき用
			//enemyChange_Image = 0; //動いてないとき用
			break;
		}       /*  左向き         非接地     */
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false)
		{
			enemy_Image = 9;     //画像を取得
			break;
		}

		//case 0: //止まっている

		//   /*     左向き            接地                                           押されてない   */
		//	if (dir == 0 && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_RIGHT) == FALSE)
		//	{
		//		pCount = 0;  //動いてないとき用
		//	}
		//	/*     右向き            接地                                           押されてない  */
		//	if (dir == 1 && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_LEFT) == FALSE)
		//	{
		//		pCount = 5;  //動いてないとき用
		//	}
		//	enemyGetMove = pCount; //最後に動いた時の画像
		//	enemyCount++;          //フレームのカウント
		//	EnemyChangeMoveimg();  //画像変更へ
		//	break;

	default:
		break;
	}
}

/*画像の動作変更*/
void  Enemy_10::EnemyChangeMoveimg()
{
	static int std = 0; //画像の基準

	/*画像の保持*/
	switch (enemyGetMove)
	{
		/*右移動*/
	case 1: //1の画像
		if (enemy_Image != 2 && enemy_Image != 3)
		{
			enemy_Image = 1;
			std = 1; //セット処理
		}
		break;
	case 2: //2の画像
		if (enemy_Image != 1 && enemy_Image != 3)
		{
			enemy_Image = 2;
			std = 2; //セット処理
		}
		break;
	case 3: //3の画像
		if (enemy_Image != 1 && enemy_Image != 2)
		{
			enemy_Image = 3;
			std = 3; //セット処理
		}
		break;

		/*左移動*/
	case 6: //6の画像
		if (enemy_Image != 7 && enemy_Image != 8)
		{
			enemy_Image = 6;
			std = 6; //セット処理
		}
		break;
	case 7: //7の画像
		if (enemy_Image != 6 && enemy_Image != 8)
		{
			enemy_Image = 7;
			std = 7; //セット処理
		}
		break;
	case 8: //8の画像
		if (enemy_Image != 6 && enemy_Image != 7)
		{
			enemy_Image = 8;
			std = 8; //セット処理
		}
		break;

		/*ジャンプ*/
	case 4: //4の画像
		enemy_Image = 4;
		std = 0; //セット処理
		break;
	case 9: //9の画像
		enemy_Image = 9;
		std = 0; //セット処理
		break;

		/*止まっている*/
	//case 0: //0の画像
	//	enemy_Image = 0;
	//	std = 0; //セット処理
	//	break;
	//case 5: //5の画像
	//	enemy_Image = 5;
	//	std = 0; //セット処理
	//	break;
	default:
		break;
	}

	/*走っているように画像変更*/
	if (enemyCount % 10 == 0) //5フレーム毎の処理
	{
		/*右移動*/
		if (dir == static_cast<int>(DIRECTION::RIGHT)) {
			if (std == 1 && 2 > enemy_Image) // 画像 1
			{
				enemy_Image = 2;
				std = 2;
			}
			else if (std == 2 && 3 > enemy_Image) // 画像 2
			{
				enemy_Image = 3;
				std = 3;
			}
			else if (std == 3 && 2 < enemy_Image) //画像 3
			{
				enemy_Image = 2;
				std = 4;
			}
			else if (std == 4 && 1 < enemy_Image) // 画像 2
			{
				enemy_Image = 1;
				std = 1;
			}
			enemyCount = 0;
		}
		/*左移動*/
		if (dir == static_cast<int>(DIRECTION::LEFT)) {
			if (std == 6 && 7 > enemy_Image) // 画像 6
			{
				enemy_Image = 7;
				std = 7;
			}
			else if (std == 7 && 8 > enemy_Image) // 画像 7
			{
				enemy_Image = 8;
				std = 8;
			}
			else if (std == 8 && 7 < enemy_Image) // 画像 8
			{
				enemy_Image = 7;
				std = 9;
			}
			else if (std == 9 && 6 < enemy_Image) // 画像 7
			{
				enemy_Image = 6;
				std = 6;
			}
			enemyCount = 0;
		}
	}
	//enemy_Image = enemy_Image + dir * 4;
	//
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
		//if (frame_count % 70 == 0) obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type); //追跡弾 

		/************************************************************************/

		/*********************** ↓↓ 生成( プレイヤー向き通常弾 ) ↓↓ ***********************/

		//            生成速度
		if (frame_count % 70 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);
		
		/************************************************************************/
	}
}