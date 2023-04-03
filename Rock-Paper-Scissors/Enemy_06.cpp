#include "Enemy_06.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Coming.h"

//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_06::Enemy_06(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 7.0f;
	dir = -1;                 //-1なら左向き  +1なら右向き
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
	//中心から描画
	DrawRotaGraphF(x, y, 1, 0, image, TRUE);

	//じゃん撃描画
	Draw_Jangeki();

	//テスト
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);

	//プレイヤーのx座標とy座標を表示するデバッグ用機能
	DrawFormatString(800, 500, 0xffffff, "player_x : %f", player_x);
	DrawFormatString(800, 530, 0xffffff, "player_y : %f", player_y);

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
		float radius = 35.5f;   //半径
		float speed = 3.0f;     //スピード

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		//プレイヤー方向に向かって発射されるジャン撃の生成
		if (frame_count % 80 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);

		////通常弾生成
		//if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type);
	}
}

//行動ループ1
void Enemy_06::AttackPattern_1()
{
	//4回ジャンプするまでの間以下の処理(ジャンプ)を繰り返す
	if (jump_cnt < 3)         
	{
		if (GetRand(3) == 3)  //乱数でjump_flgをtrueにする
		{
			jump_flg = true;
		}

		//ジャンプ処理
		jump();
	}

	//4回以上ジャンプした際の処理
	if (jump_cnt >= 3 && dir == -1)        //左を向いている時の処理
	{

		x = x - 5;      //1フレームの間に左へ進む距離
		if (x < 100)    //目標座標に到着したかのチェック
		{
			jump_cnt = 0;          //ジャンプ回数のリセット
			dir = 1;  //向いている向きの反転
			ChangeCnt++;
		}
	}
	else if (jump_cnt >= 3 && dir == 1)    //右を向いている時の処理
	{
		x = x + 5;      //1フレームの間に右へ進む距離
		if (x > 1180)   //目標座標に到着したかのチェック
		{
			jump_cnt = 0;           //ジャンプ回数のリセット
			dir = -1;  //向いている向きの反転
			ChangeCnt++;
		}
	}

	//敵の属性変化処理
	if (ChangeCnt > 4)
	{
		SetType(static_cast<Jan_Type>(GetRand(2)));
		ChangeCnt = 0;
	}

	//HPが70以下になると次の行動ループに移行
	if (hp <= 70)
	{
		attack_pattern = 1;    //攻撃パターンを変更
		jump_cnt = 0;          //ジャンプカウント初期化
		jump_flg = false;      //ジャンプフラグ初期化
	}
}

//行動ループ2
void Enemy_06::AttackPattern_2()
{
	if (teleport_Flg == true && dir == -1)
	{
		x = 1180;
		y = 450;
		dir = -1;
		teleport_Flg = false;
		P1_side = false;
		jump_cnt = 0;
	}
	else if (teleport_Flg == true && dir == 1)
	{
		x = 100;
		y = 450;
		dir = 1;
		teleport_Flg = false;
		P1_side = true;
		jump_cnt = 0;
	}



	if (P1_side == false)
	{
		//左の足場へジャンプ
		if (x >= 930 && dir == 1)
		{
			x = x - 6;
		}
		else if (x <= 1180 && dir == 1)
		{
			dir = -1;
			jump_flg = true;
			jump_cnt++;
		}

		//右の足場へジャンプ
		if (x <= 1180 && dir == -1)
		{
			x = x + 6;
		}
		else if (x >= 930 && dir == -1)
		{
			dir = 1;
			jump_flg = true;
			jump_cnt++;
		}

		//瞬間移動
		if (jump_cnt == 5)
		{
			teleport_Flg = true;
			dir = 1;
			ChangeCnt++;
		}

		//ジャンプ処理
		jump();
	}

	else if (P1_side == true)
	{
		//右の足場へジャンプ
		if (x <= 350 && dir == -1)
		{
			x = x + 6;
		}
		else if (x >= 100 && dir == -1)
		{
			dir = 1;
			jump_flg = true;
			jump_cnt++;
		}

		//左の足場へジャンプ
		if (x >= 100 && dir == 1)
		{
			x = x - 5;
		}
		else if (x <= 350 && dir == 1)
		{
			dir = -1;
			jump_flg = true;
			jump_cnt++;
		}

		//瞬間移動
		if (jump_cnt == 5)
		{
			teleport_Flg = true;
			dir = -1;
			ChangeCnt++;
		}

		//ジャンプ処理
		jump();
	}

	//敵の属性変化処理
	if (ChangeCnt > 3)
	{
		SetType(static_cast<Jan_Type>(GetRand(2)));
		ChangeCnt = 0;
	}

	//HPが40以下になると次の行動ループに移行
	if (hp <= 40)
	{
		attack_pattern = 2;
		teleport_Flg = true;
	}
}

//行動ループ3
void Enemy_06::AttackPattern_3()
{
	//攻撃パターン3初期処理
	if (teleport_Flg == true)
	{
		x = 1149;
		y = 450;
		floor = 5;
		dir = -1;
		teleport_Flg = false;
		jump_cnt = 0;
	}


	//床ごとの処理
	switch (floor)
	{
	case 1:
		if (dir == 1)
		{
			x += 7;
		}
		
		if (y == 450 && jump_cnt == 0)
		{
			jump_flg = true;
		}

		//ジャンプ処理
		jump();

		//指定座標に到着したらswitch遷移
		if (x >= 393)
		{
			floor = 2;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 2:
		if (dir == -1)
		{
			x -= 7;
		}
		if (dir == 1)
		{
			x += 7;
		}

		//ジャンプ処理
		jump();

		//指定座標に到着したらswitch遷移
		if (x <= 141)
		{
			floor = 1;
			jump_cnt = 0;
			dir = 1;
			jump_Direction();
		}
		if (x >= 645)
		{
			floor = 3;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 3:
		if (dir == -1)
		{
			x -= 7;
		}
		if (dir == 1)
		{
			x += 7;
		}

		if (y == 450 && jump_cnt == 0)
		{
			jump_flg = true;
		}

		//ジャンプ処理
		jump();

		//指定座標に到着したらswitch遷移
		if (x <= 393)
		{
			floor = 2;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}
		if (x >= 897)
		{
			floor = 4;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 4:
		if (dir == -1)
		{
			x -= 7;
		}
		if (dir == 1)
		{
			x += 7;
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
			x -= 7;
		}

		if (y == 450 && jump_cnt == 0)
		{
			jump_flg = true;
			jump_cnt++;
		}

		//ジャンプ処理
		jump();

		//指定座標に到着したらswitch遷移
		if (x <= 897)
		{
			floor = 4;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}

		break;
	}

	//敵の属性変化処理
	if (ChangeCnt > 5)
	{
		SetType(static_cast<Jan_Type>(GetRand(2)));
		ChangeCnt = 0;
	}
}

//ジャンプ
void Enemy_06::jump()
{
	//ジャンプ処理
	if (jump_flg == true && land_flg == true)
	{
		g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
		land_flg = false;  //地面についていない
		jump_flg = false;  //ジャンプ用フラグのリセット

		if (attack_pattern == 0)
		{
			jump_cnt++;        //ジャンプ回数のカウント
		}

		if (attack_pattern == 2)
		{
			ChangeCnt++;       //属性変化までのカウント
		}
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