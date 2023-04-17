#include "Scene_Stage06.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"Scene_GameOver.h"
#include "Scene_GameClear.h"
#include "Enemy_02.h"
#include"GameData.h"

//デバッグモード
#include"Debug_Manager.h"

//コンストラクタ
Scene_Stage06::Scene_Stage06(const Player* player)
{
	//プレイヤー情報が渡されていれば
	if (player != nullptr)
	{
		//情報を引き継いだプレイヤーを生成
		obj_player = new Player(*player);
	}
	else
	{
		//プレイヤーを生成
		obj_player = new Player(100, 600);
	}

	//敵を生成
	obj_enemy = new Enemy_06(1200, 360, Jan_Type::SCISSORS);

	//背景画像の読み込み
	stage6_BackImage = LoadGraph("images/stage6/mori32-.png");

	//床・壁の用意
	Init_Floor(STAGE_06_FLOOR);

	//一つずつ生成  STAGE_06_FLOOR 個分
	obj_floor[0] = new Floor(0, 700, 1280, 20, 22822);        //床
	obj_floor[1] = new Floor(0, 0 - 400, 20, 1720 + 400);           //壁（左）
	obj_floor[2] = new Floor(1260, 0 - 400, 20, 1720 + 400);           //壁（右）

	obj_floor[3] = new Floor(81, 150, 120, 10, 22822);          //足場[3]～[15]
	obj_floor[4] = new Floor(81, 350, 120, 10, 22822);
	obj_floor[5] = new Floor(81, 550, 120, 10, 22822);

	obj_floor[6] = new Floor(333, 250, 120, 10, 22822);
	obj_floor[7] = new Floor(333, 450, 120, 10, 22822);

	obj_floor[8] = new Floor(585, 150, 120, 10, 22822);
	obj_floor[9] = new Floor(585, 350, 120, 10, 22822);
	obj_floor[10] = new Floor(585, 550, 120, 10, 22822);

	obj_floor[11] = new Floor(837, 250, 120, 10, 22822);
	obj_floor[12] = new Floor(837, 450, 120, 10, 22822);

	obj_floor[13] = new Floor(1089, 150, 120, 10, 22822);
	obj_floor[14] = new Floor(1089, 350, 120, 10, 22822);
	obj_floor[15] = new Floor(1089, 550, 120, 10, 22822);

	obj_floor[16] = new Floor(0, -220, 1280, 20, 22822);        //天井

	//制限時間をセット
	GameData::Set_TimeLimit(5460);
}

//デストラクタ
Scene_Stage06::~Scene_Stage06()
{
}

//更新
void Scene_Stage06::Update()
{
	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Update();    // プレイヤー更新・操作可能
		obj_enemy->Update();     //敵キャラ更新・内部処理

		//プレイヤー座標を取得
		obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());

		//プレイヤー向きを取得
		obj_enemy->SetPlayerDirection(obj_player->GetDirection());

		//時間をカウント
		GameData::Time_Update();
	}

	//接触じゃんけん処理
	Touch_Janken(obj_enemy, this, 6);

	//playerのじゃん撃をとってくる
	Jangeki_Base** player_jangeki = obj_player->GetJangeki();

	//enemyのじゃん撃をとってくる
	Jangeki_Base** enemy_jangeki = obj_enemy->GetJangeki();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//じゃん撃同士の当たり判定（プレイヤーじゃん撃目線）
	for (int p_count = 0; p_count < JANGEKI_MAX; p_count++)
	{
		if (player_jangeki[p_count] == nullptr) break;         //じゃん撃がない時は処理しない

		bool delete_player = false;       //プレイヤーじゃん撃削除フラグ　true:削除　false:削除しない

		for (int e_count = 0; e_count < JANGEKI_MAX; e_count++)
		{
			if (enemy_jangeki[e_count] == nullptr) break;         //じゃん撃がない時は処理しない

			if (player_jangeki[p_count]->Hit_Jangeki(enemy_jangeki[e_count]) == true)
			{
				//有利属性チェック
				int result = player_jangeki[p_count]->CheckAdvantage(enemy_jangeki[e_count]);

				switch (result)
				{
				case 0:             //playerのじゃん撃が不利

					//player側のじゃん撃を削除
					delete_player = true;

					break;

				case 1:             //playerのじゃん撃が有利

					//enemy側のじゃん撃を削除
					obj_enemy->DeleteJangeki(e_count);
					e_count--;

					break;

				case 2:             //あいこ

					//player側のじゃん撃を削除
					delete_player = true;

					//enemy側のじゃん撃を削除
					obj_enemy->DeleteJangeki(e_count);
					e_count--;

					break;

				default:
					break;
				}
			}
		}

		//プレイヤーじゃん撃削除フラグがtrue
		if (delete_player == true)
		{
			//player側のじゃん撃を削除
			obj_player->DeleteJangeki(p_count);
			p_count--;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//playerじゃん撃とenemyの当たり判定
	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		if (player_jangeki[i] == nullptr) break;         //じゃん撃がない時は処理しない

		//じゃん撃との当たり判定
		if (obj_enemy->Hit_Jangeki(player_jangeki[i]) == true)
		{
			Jan_Type enemy_type = obj_enemy->GetType();            //敵の属性
			Jan_Type jangeki_type = player_jangeki[i]->GetType();  //当たったじゃん撃の属性

			//不利属性のみダメージが入る
			switch (enemy_type)
			{
			case Jan_Type::ROCK:                           //敵の属性　グー

				//パーのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::PAPER)
				{
					obj_enemy->ReceiveDamage(10);     //ダメージが入る
					obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
					i--;
				}

				break;

			case Jan_Type::SCISSORS:                       //敵の属性　チョキ

				//グーのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::ROCK)
				{
					obj_enemy->ReceiveDamage(10);     //ダメージが入る
					obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
					i--;
				}
				break;

			case Jan_Type::PAPER:                          //敵の属性　パー

				//チョキのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::SCISSORS)
				{
					obj_enemy->ReceiveDamage(10);     //ダメージが入る
					obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
					i--;
				}
				break;

			default:
				break;
			}
		}
	}


	//enemyじゃん撃とplayerの当たり判定
	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		//じゃん撃がない時は処理しない
		if (enemy_jangeki[i] == nullptr) break;

		//じゃん撃との当たり判定
		if (obj_player->Hit_Jangeki(enemy_jangeki[i]) == true)
		{
			//ダメージを受ける（プレイヤー）
			obj_player->ReceiveDamage(20);

			//あたったじゃん撃を削除
			obj_enemy->DeleteJangeki(i);
			i--;
		}
	}

	//壁との当たり判定
	if (obj_player->Get_X() <= 50 || obj_player->Get_X() >= 1220)
	{
		HitCtrl_Floor(obj_player, STAGE_06_FLOOR);     // player　床・壁判定
	}

	//プレイヤーのy座標が減少しない時のみ当たり判定を取得
	if (obj_player->Get_Y() >= obj_player->Get_OldY() || obj_player->Get_Y() <= -200)
	{
		HitCtrl_Floor(obj_player, STAGE_06_FLOOR);     // player　床・壁判定
	}

	//敵のy座標が減少しない時のみ当たり判定を取得
	if (obj_enemy->Get_Y() >= obj_enemy->Get_OldY() || obj_enemy->Get_Y() <= -200)
	{
		HitCtrl_Floor(obj_enemy, STAGE_06_FLOOR);      // 敵　　　床・壁判定
	}
}


//描画
void Scene_Stage06::Draw() const
{
	//背景の描画
	DrawGraph(0, 0, stage6_BackImage, TRUE);

	//UIの描画
	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());
	DrawUI_ON_Enemy(obj_enemy);

	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::START || GetJanState() == Jan_State::BEFORE)
	{

		obj_player->Draw();  //プレイヤー描画
		obj_enemy->Draw();   //敵キャラ描画

		//床・壁描画
		for (int i = 0; i < STAGE_06_FLOOR; i++)
		{
			if (obj_floor[i] == nullptr) break;
			obj_floor[i]->Draw();
		}

		// 接触した瞬間の演出
		if (GetJanState() == Jan_State::START) Draw_JankenStart();
	}
	else
	{
		//接触時じゃんけん描画
		Draw_Janken();
	}

	DrawString(640, 360, "Stage06", 0xffffff);
}

//じゃんけん描画
void Scene_Stage06::Draw_Janken() const
{
	obj_janken->Draw();
}

void Scene_Stage06::AfterJanken_WIN()
{
	obj_player = new Player(100, 600);     //プレイヤーを指定座標に生成
}

void Scene_Stage06::AfterJanken_LOSE()
{
	obj_player = new Player(100, 600);                            //プレイヤーを指定座標に生成
	//obj_enemy  = new Enemy_06(1149, 480, obj_enemy->GetType());   //敵を指定座標に生成
	obj_enemy->SpeedUp();                                         //敵の特殊行動1
}

//シーンの変更
AbstractScene* Scene_Stage06::ChangeScene()
{
	//"Debug_Manager.h" の #define DEBUG_OFF_06 をコメントアウトすると開発モード
#ifdef DEBUG_OFF_06

	//敵のHPが0以下
	if (obj_enemy->GetHP() <= 0)
	{
		//ゲームクリアシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameClearScene(7));
	}

	//プレイヤーのHPが0以下
	if (obj_player->GetHP() <= 0  || GameData::Get_Each_Time() <= 0 )
	{
		//ゲームオーバーシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameOverScene(6));
	}

#endif // DEBUG_OFF_06

	return this;
}