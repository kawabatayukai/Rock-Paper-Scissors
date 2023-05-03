#include "Enemy_06.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Coming.h"

//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_06::Enemy_06(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 5.0f;             //デフォルト速度は5.0f
	dir = -1;                 //-1なら左向き  +1なら右向き
	hp = 100;                 //HPは100

	old_type = static_cast<Jan_Type>(1);  //チョキ属性で初期化

	//画像読み込み
	images[0] = LoadGraph("images/gu-test.png");     //グー属性
	images[1] = LoadGraph("images/tyokitest.png");   //チョキ属性
	images[2] = LoadGraph("images/pa-test.png");     //パー属性

	////煙エフェクト読み込み
	//LoadDivGraph("images/stage06/pipo-charachip_smoke01a-s..png", 12, 4, 5, 135, 150, smokeImage);

	enemy_images = LoadGraph("images/stage06/NINJA.png");

	Init_Jangeki();       //じゃん撃を用意

}

//デストラクタ
Enemy_06::~Enemy_06()
{

}


//更新
void Enemy_06::Update()
{
	frame_count++;
	TeleportTime++;
	SpeedUpTime++;
	if (smokeCnt < 3)
	{
		smokeCnt++;
	}
	else
	{
		smokeCnt = 0;
	}
	

	//じゃん撃更新・生成
	Update_Jangeki();

	//HP表示がマイナスにならないように調整
	if (hp <= 0)hp = 0;

	if (TeleportFlg == false)   //瞬間移動接触フラグの判定
	{
		//攻撃パターン1
		if (attack_pattern == 0)
		{
			AttackPattern_1();
		}

		//攻撃パターン2
		if (attack_pattern == 1)
		{
			AttackPattern_2();
		}

		//攻撃パターン3
		if (attack_pattern == 2)
		{
			AttackPattern_3();
		}
	}
	else if (TeleportFlg == true && x > 0 && x < 1280)
	{
		//特殊行動2   プレイヤーの後方側に移動し、接近してくる
		if (attack_pattern > 0)  //行動ループ1以外の時
		{
			Teleportation();
		}
		else  //例外処理
		{
			TeleportFlg = false;
			TeleportInit = true;
			speed = 5.0f;
		}
	}
	else  //例外処理
	{
		TeleportFlg = false;
		TeleportInit = true;
		speed = 5.0f;
	}

	//750フレームごとに瞬間移動接触フラグをtrueにする
	if (TeleportTime == 750 && TeleportFlg == false && (player_x - 300) > 0 && (player_x + 300) < 1280 && speed != 8.0f)
	{
		TeleportFlg = true;
	}
	else if(TeleportTime > 750)
	{
		TeleportTime = 0;
	}

	/********************   ジャンプ関係   ********************/

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
	//グー属性の時、赤いキャラ画像を表示
	if (GetType() == static_cast<Jan_Type>(0))
	{
		//中心から描画
		DrawRotaGraphF(x, y, 5, 0, enemy_images, TRUE, dir == -1 ? 0 : 1);
	}

	//チョキ属性の時、黄色いキャラ画像を表示
	if (GetType() == static_cast<Jan_Type>(1))
	{
		//中心から描画
		DrawRotaGraphF(x, y, 5, 0, enemy_images, TRUE, dir == -1 ? 0 : 1);
	}

	//パー属性の時、青いキャラ画像を表示
	if (GetType() == static_cast<Jan_Type>(2))
	{
		//中心から描画
		DrawRotaGraphF(x, y, 5, 0, enemy_images, TRUE, dir == -1 ? 0 : 1);
	}

	//じゃん撃描画
	Draw_Jangeki();

	//テスト
	if (hp > 0) DrawFormatString((int)(x - 50), (int)(y - 125), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 50), (int)(y - 125), "death!", 0xffffff);

	if (speed == 8.0f)
	{
		DrawString((int)(x - 80), (int)(y - 75), "スピードアップ", GetColor(255, 0, 0));
	}

	/*DrawBox((x - (w / 2)), (y - (h / 2)), (x + (w / 2)), (y + (h / 2)), 0xffffff, TRUE);*/
}

//じゃん撃生成・更新
void Enemy_06::Update_Jangeki()
{
	//ジャン撃数のカウント
	int jan_count;

	//じゃん撃配列をひとつずつ
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//配列の jan_count 番目がnullptr（空要素）ならそれ以上処理しない
		if (obj_jangeki[jan_count] == nullptr) break;

		//ジャン撃の更新
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
	

	//配列の空要素
	if (jan_count < JANGEKI_MAX && obj_jangeki[jan_count] == nullptr)
	{
		float radius = 35.5f;   //半径
		float speed = 3.0f;     //スピード

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		//行動パターン1の時の弾(speed = 3.0f  frame_count % 80)
		if (attack_pattern == 0)
		{
			//プレイヤー方向に向かって発射されるジャン撃の生成
			if (frame_count % 90 == 0) obj_jangeki[jan_count] = 
				new Jangeki_Coming(x, y, radius, speed + 1.0f, type, player_x, player_y);
		}

		//行動パターン2の時の弾(speed = 3.0f  frame_count % 80)
		if (attack_pattern == 1)
		{
			//プレイヤー方向に向かって発射されるジャン撃の生成
			if (frame_count % 75 == 0) obj_jangeki[jan_count] =
				new Jangeki_Coming(x, y, radius, speed + 1.5f, type, player_x, player_y);
		}

		//行動パターン3の時の弾(speed = 3.0f  frame_count % 80)
		if (attack_pattern == 2)
		{
			//プレイヤー方向に向かって発射されるジャン撃の生成
			if (frame_count % 65 == 0) obj_jangeki[jan_count] =
				new Jangeki_Coming(x, y, radius, speed + 2.0f, type, player_x, player_y);
		}
	}
}

//行動ループ1
void Enemy_06::AttackPattern_1()
{
	//4回ジャンプするまでの間以下の処理(ジャンプ)を繰り返す
	if (jump_cnt < 2)         
	{
		if (GetRand(3) == 3)  //乱数でjump_flgをtrueにする
		{
			jump_flg = true;
		}

		//ジャンプ処理
		jump();
	}

	//着地してから次の行動を開始
	if (jump_cnt == 2 && land_flg == true)
	{
		jump_cnt++;
	}

	//4回以上ジャンプした際の処理
	if (jump_cnt >= 3 && dir == -1)        //左を向いている時の処理
	{
		x -= speed;      //1フレームの間に左へ進む距離

		/********** 特定座標でジャンプ **********/

		if (x > 380 && x < 386)
		{
			jump_flg = true;
		}
		else if (x > 650 && x < 656)
		{
			jump_flg = true;
		}
		else if (x > 900 && x < 906)
		{
			jump_flg = true;
		}
		else if (x > 1150 && x < 1156)
		{
			jump_flg = true;
		}

		/****************************************/

		low_jump();     //低ジャンプ

		//接地しているかどうかで移動速度を可変   接地時(true)    : speed = 3.0f
		//                                       非接地時(false) : speed = 7.0f
		if (land_flg == true)
		{
			speed = 3.0f;
		}
		else if(land_flg == false)
		{
			speed = 7.0f;
		}

		//目標座標に到着したかのチェック
		if (x < 115)
		{
			jump_cnt = 0;          //ジャンプ回数のリセット
			dir = 1;               //向いている向きの反転
			ChangeCnt++;           //属性変化までのカウント
		}
	}
	else if (jump_cnt >= 3 && dir == 1)    //右を向いている時の処理
	{
		x += speed;      //1フレームの間に右へ進む距離

		/********** 特定座標でジャンプ **********/

		if (x > 124 && x < 130)
		{
			jump_flg = true;
		}
		else if (x > 414 && x < 420)
		{
			jump_flg = true;
		}
		else if (x > 664 && x < 670)
		{
			jump_flg = true;
		}
		else if (x > 904 && x < 910)
		{
			jump_flg = true;
		}

		/****************************************/

		low_jump();     //低ジャンプ

		//接地しているかどうかで移動速度を可変   接地時(true)    : speed = 3.0f
		//                                       非接地時(false) : speed = 7.0f
		if (land_flg == true)
		{
			speed = 3.0f;
		}
		else if (land_flg == false)
		{
			speed = 7.0f;
		}

		if (x > 1180)   //目標座標に到着したかのチェック
		{
			jump_cnt = 0;           //ジャンプ回数のリセット
			dir = -1;               //向いている向きの反転
			ChangeCnt++;            //属性変化までのカウント
		}
	}

	//敵の属性変化処理
	if (ChangeCnt > 4)
	{
		while (GetType() == old_type)
		{
			SetType(static_cast<Jan_Type>(GetRand(2)));
		}
		old_type = GetType();
		ChangeCnt = 0;
	}

	//HPが70以下になると次の行動ループに移行
	if (hp <= 70)
	{
		attack_pattern = 1;    //攻撃パターンを変更
		attack2_Flg = true;    //攻撃パターン2初期処理フラグをtrueにする
	}
}

//行動ループ2
void Enemy_06::AttackPattern_2()
{
	//攻撃パターン2初期処理
	if (attack2_Flg == true)
	{
		x = 1149;                  //瞬間移動後のx座標
		y = 480;                   //瞬間移動後のy座標
		speed = 5.0f;              //スピードの初期化
		floor = 5;                 //現在の床位置の初期化(5)
		dir = -1;                  //向きの初期化(左向き)
		attack2_Flg = false;       //初期化処理フラグをfalseにする
		jump_cnt = 0;              //ジャンプカウントの初期化
	}

	//床ごとの処理
	switch (floor)
	{
	case 1:
		if (dir == 1)
		{
			x += speed;
		}

		if (y == 100)
		{
			jump_flg = false;
		}

		if (y == 500)
		{
			jump_flg = true;
		}

		if (y == 650)
		{
			jump_flg = false;
		}

		//ジャンプ処理
		jump();

		//指定座標に到着したらswitch遷移
		if (x >= 393)
		{
			floor = 2;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 2:
		if (dir == -1)
		{
			x -= speed;
		}
		if (dir == 1)
		{
			x += speed;
		}

		if (y == 650)
		{
			jump_flg = true;
		}

		//ジャンプ処理
		jump();

		//指定座標に到着したらswitch遷移
		if (x <= 141)
		{
			floor = 1;
			dir = 1;
			jump_Direction();
		}
		if (x >= 645)
		{
			floor = 3;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 3:
		if (dir == -1)
		{
			x -= speed;
		}
		if (dir == 1)
		{
			x += speed;
		}

		if (y == 100)
		{
			jump_flg = false;
		}

		if (y == 500)
		{
			jump_flg = true;
		}

		if (y == 650)
		{
			jump_flg = false;
		}

		//ジャンプ処理
		jump();

		//指定座標に到着したらswitch遷移
		if (x <= 393)
		{
			floor = 2;
			decision_Direction();
			jump_Direction();
		}
		if (x >= 897)
		{
			floor = 4;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 4:
		if (dir == -1)
		{
			x -= speed;
		}
		if (dir == 1)
		{
			x += speed;
		}

		if (y == 650)
		{
			jump_flg = true;
		}

		//ジャンプ処理
		jump();

		//指定座標に到着したらswitch遷移
		if (x <= 645)
		{
			floor = 3;
			decision_Direction();
			jump_Direction();
		}
		if (x >= 1149)
		{
			floor = 5;
			dir = -1;
			jump_Direction();
		}

		break;

	case 5:
		if (dir == -1)
		{
			x -= speed;
		}

		if (y == 100)
		{
			jump_flg = false;
		}

		if (y == 500)
		{
			jump_flg = true;
		}

		if (y == 650)
		{
			jump_flg = false;
		}

		//ジャンプ処理
		jump();

		//指定座標に到着したらswitch遷移
		if (x <= 897)
		{
			floor = 4;
			decision_Direction();
			jump_Direction();
		}

		break;
	}



	//敵の属性変化処理
	if (ChangeCnt > 6)
	{
		while (GetType() == old_type)
		{
			SetType(static_cast<Jan_Type>(GetRand(2)));
		}
		old_type = GetType();
		ChangeCnt = 0;
	}

	//HPが40以下になると次の行動ループに移行
	if (hp <= 40)
	{
		attack_pattern = 2;
	}
}

//行動ループ3
void Enemy_06::AttackPattern_3()
{
	//床ごとの処理
	switch (floor)
	{
	case 1:
		if (dir == 1)
		{
			x += speed;
		}

		if (y == 100)
		{
			jump_flg = false;
		}
		
		if (y == 500)
		{
			jump_flg = true;
		}

		if (y == 650)
		{
			jump_flg = false;
		}

		//ジャンプ処理
		jump();

		//指定座標に到着したらswitch遷移
		if (x >= 393)
		{
			floor = 2;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 2:
		if (dir == -1)
		{
			x -= speed;
		}
		if (dir == 1)
		{
			x += speed;
		}

		if (y == 650)
		{
			jump_flg = true;
		}

		//ジャンプ処理
		jump();

		//指定座標に到着したらswitch遷移
		if (x <= 141)
		{
			floor = 1;
			dir = 1;
			jump_Direction();
		}
		if (x >= 645)
		{
			floor = 3;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 3:
		if (dir == -1)
		{
			x -= speed;
		}
		if (dir == 1)
		{
			x += speed;
		}

		if (y == 100)
		{
			jump_flg = false;
		}

		if (y == 500)
		{
			jump_flg = true;
		}

		if (y == 650)
		{
			jump_flg = false;
		}

		//ジャンプ処理
		jump();

		//指定座標に到着したらswitch遷移
		if (x <= 393)
		{
			floor = 2;
			decision_Direction();
			jump_Direction();
		}
		if (x >= 897)
		{
			floor = 4;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 4:
		if (dir == -1)
		{
			x -= speed;
		}
		if (dir == 1)
		{
			x += speed;
		}

		if (y == 650)
		{
			jump_flg = true;
		}

		//ジャンプ処理
		jump();

		//指定座標に到着したらswitch遷移
		if (x <= 645)
		{
			floor = 3;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}
		if (x >= 1149)
		{
			floor = 5;
			jump_cnt = 0;
			dir = -1;
			jump_Direction();
		}

		break;

	case 5:
		if (dir == -1)
		{
			x -= speed;
		}

		if (y == 100)
		{
			jump_flg = false;
		}

		if (y == 500)
		{
			jump_flg = true;
		}

		if (y == 650)
		{
			jump_flg = false;
		}

		//ジャンプ処理
		jump();

		//指定座標に到着したらswitch遷移
		if (x <= 897)
		{
			floor = 4;
			decision_Direction();
			jump_Direction();
		}

		break;
	}



	//敵の属性変化処理
	if (ChangeCnt > 4)
	{
		while (GetType() == old_type)
		{
			SetType(static_cast<Jan_Type>(GetRand(2)));
		}
		old_type = GetType();
		ChangeCnt = 0;
	}

	//数秒経過で元の速度 & 攻撃パターンへ遷移
	if (SpeedUpTime % 600 == 0)
	{
		speed = 5.0f;
		if (hp > 70)
		{
			attack_pattern = 0;
			jump_cnt = 0;
			dir = 1;
			x = 1200;
			y = 360;
		}
		else if (hp > 40)
		{
			attack_pattern = 1;
		}
	}
}

//特殊行動1   speed = 8.0f
void Enemy_06::SpeedUp()
{
	attack_pattern = 2;
	speed = 8.0f;
	SpeedUpTime = 0;
	TeleportFlg = false;
	TeleportInit = true;
}

//特殊行動2   プレイヤーの後方側に移動し、接近してくる
void Enemy_06::Teleportation()
{
	if (TeleportInit == true)
	{
		if (player_dir == 0)
		{
			dir = -1;
			x = player_x + 300;
			y = 650.0f;
		}

		if (player_dir == 1)
		{
			dir = 1;
			x = player_x - 300;
			y = 650.0f;
		}

		speed = 1.5f;
		TeleportInit = false;
	}
	
	speed += 0.2f;

	if (dir == -1)
	{
		x -= speed;
	}
	
	if (dir == 1)
	{
		x += speed;
	}

	if (x < 200)
	{
		TeleportFlg = false;
		TeleportInit = true;
		TeleportTime = 0;
		speed = 5.0f;
	}

	if (x > 1090)
	{
		TeleportFlg = false;
		TeleportInit = true;
		TeleportTime = 0;
		speed = 5.0f;
	}
}


//旧行動ループ2(保存用)
void Enemy_06::AttackPattern_00()
{
	//if (teleport_Flg == true && dir == -1)
	//{
	//	x = 1180;
	//	y = 450;
	//	dir = -1;
	//	teleport_Flg = false;
	//	P1_side = false;
	//	jump_cnt = 0;
	//}
	//else if (teleport_Flg == true && dir == 1)
	//{
	//	x = 100;
	//	y = 450;
	//	dir = 1;
	//	teleport_Flg = false;
	//	P1_side = true;
	//	jump_cnt = 0;
	//}



	//if (P1_side == false)
	//{
	//	//左の足場へジャンプ
	//	if (x >= 930 && dir == 1)
	//	{
	//		x = x - 6;
	//	}
	//	else if (x <= 1180 && dir == 1)
	//	{
	//		dir = -1;
	//		jump_flg = true;
	//		jump_cnt++;
	//	}

	//	//右の足場へジャンプ
	//	if (x <= 1180 && dir == -1)
	//	{
	//		x = x + 6;
	//	}
	//	else if (x >= 930 && dir == -1)
	//	{
	//		dir = 1;
	//		jump_flg = true;
	//		jump_cnt++;
	//	}

	//	//瞬間移動
	//	if (jump_cnt == 5)
	//	{
	//		teleport_Flg = true;
	//		dir = 1;
	//		ChangeCnt++;
	//	}

	//	//ジャンプ処理
	//	jump();
	//}

	//else if (P1_side == true)
	//{
	//	//右の足場へジャンプ
	//	if (x <= 350 && dir == -1)
	//	{
	//		x = x + 6;
	//	}
	//	else if (x >= 100 && dir == -1)
	//	{
	//		dir = 1;
	//		jump_flg = true;
	//		jump_cnt++;
	//	}

	//	//左の足場へジャンプ
	//	if (x >= 100 && dir == 1)
	//	{
	//		x = x - 5;
	//	}
	//	else if (x <= 350 && dir == 1)
	//	{
	//		dir = -1;
	//		jump_flg = true;
	//		jump_cnt++;
	//	}

	//	//瞬間移動
	//	if (jump_cnt == 5)
	//	{
	//		teleport_Flg = true;
	//		dir = -1;
	//		ChangeCnt++;
	//	}

	//	//ジャンプ処理
	//	jump();
	//}
}

//ジャンプ
void Enemy_06::jump()
{
	//ジャンプ処理
	if (jump_flg == true && land_flg == true)
	{
		g_add = -19.8f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
		land_flg = false;  //地面についていない
		jump_flg = false;  //ジャンプ用フラグのリセット

		if (attack_pattern == 0)
		{
			jump_cnt++;        //ジャンプ回数のカウント
		}

		if (attack_pattern >= 1)
		{
			ChangeCnt++;       //属性変化までのカウント
		}
	}
}

//低いジャンプ
void Enemy_06::low_jump()
{
	//ジャンプ処理
	if (jump_flg == true && land_flg == true)
	{
		g_add = -8.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
		land_flg = false;  //地面についていない
		jump_flg = false;  //ジャンプ用フラグのリセット
	}
}

//向きを乱数で決める関数
void Enemy_06::decision_Direction()
{
	if (GetRand(1) == 1)
	{
		dir = -1;
	}
	else
	{
		dir = 1;
	}
}

//ジャンプするかを乱数で決める関数
void Enemy_06::jump_Direction()
{
	if (GetRand(1) == 1)
	{
		jump_flg = true;
	}
}

//old_yの取得関数
float Enemy_06::Get_OldY()
{
	return old_y;
}

//yの取得関数
float Enemy_06::Get_Y()
{
	return y;
}