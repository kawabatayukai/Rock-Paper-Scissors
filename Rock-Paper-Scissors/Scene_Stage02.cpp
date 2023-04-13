#include "Scene_Stage02.h"
#include"KeyManager.h"
#include"DxLib.h"
#include "Scene_Stage03.h"
#include"Scene_GameOver.h"
#include "Scene_GameClear.h"
#include "GameData.h"
#include "Enemy_02.h"
//デバッグモード
#include"Debug_Manager.h"

//コンストラクタ
Scene_Stage02::Scene_Stage02(const Player* player)
{
	//制限時間をセット
	GameData::Set_TimeLimit(6000);

	//プレイヤー情報が渡されていれば
	if (player != nullptr)
	{
		//情報を引き継いだプレイヤーを生成
		obj_player = new Player(*player);
	}
	else
	{
		//プレイヤーを生成
		obj_player = new Player(640, 360);
	}

	//敵を生成
	obj_enemy = new Enemy_02(1200, 680, Jan_Type::SCISSORS);

	//床・壁の用意
	Init_Floor(STAGE_02_FLOOR);

	//一つずつ生成  STAGE_02_FLOOR 個分
	obj_floor[0] = new Floor(0, 700, 1280, 20, 0x006400);        //床
	obj_floor[1] = new Floor(0, 0, 20, 1720);           //壁（左）
	obj_floor[2] = new Floor(1260, 0, 20, 1720);           //壁（右）
	//obj_floor[3] = new Floor(0, 200, 120, 20);      //足場

	image_back = LoadGraph("images/stage02/mizuumi01.png");
}

//デストラクタ
Scene_Stage02::~Scene_Stage02()
{
}

//更新
void Scene_Stage02::Update()
{

	//時間をカウント
	GameData::Time_Update();

	obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());

	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Update();    // プレイヤー更新・操作可能
		obj_enemy->Update();     //敵キャラ更新・内部処理
	}

	//接触じゃんけん処理
	Touch_Janken(obj_enemy, this);


	


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

					GameData::Add_Score(100);    //スコア加算

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
					obj_enemy->ReceiveDamage(25);     //ダメージが入る
					obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
					i--;
				}

				break;

			case Jan_Type::SCISSORS:                       //敵の属性　チョキ

				//グーのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::ROCK)
				{
					obj_enemy->ReceiveDamage(25);     //ダメージが入る
					obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
					i--;
				}
				break;

			case Jan_Type::PAPER:                          //敵の属性　パー

				//チョキのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::SCISSORS)
				{
					obj_enemy->ReceiveDamage(25);     //ダメージが入る
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
			obj_player->ReceiveDamage(25);

			//あたったじゃん撃を削除
			obj_enemy->DeleteJangeki(i);
			i--;
		}
	}


	HitCtrl_Floor(obj_player, STAGE_02_FLOOR);     // player　床・壁判定
	HitCtrl_Floor(obj_enemy, STAGE_02_FLOOR);      // 敵　　　床・壁判定


}


//描画
void Scene_Stage02::Draw() const
{
	//背景
	DrawGraph(0, 0, image_back, TRUE);

	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());
	DrawUI_ON_Enemy(obj_enemy);

	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::BEFORE)
	{

		obj_player->Draw();  //プレイヤー描画
		obj_enemy->Draw();   //敵キャラ描画

		//床・壁描画
		for (int i = 0; i < STAGE_02_FLOOR; i++)
		{
			if (obj_floor[i] == nullptr) break;
			obj_floor[i]->Draw();
		}

	}
	else
	{
		//接触時じゃんけん描画
		Draw_Janken();
	}

	DrawString(640, 360, "Stage02", 0xffffff);
}

//じゃんけん描画
void Scene_Stage02::Draw_Janken() const
{
	obj_janken->Draw();
}

//シーンの変更
AbstractScene* Scene_Stage02::ChangeScene()
{
	//"Debug_Manager.h" の #define DEBUG_OFF_02 をコメントアウトすると開発モード
#ifdef DEBUG_OFF_02

	//敵のHPが0以下
	if (obj_enemy->GetHP() < 0)
	{
		//ゲームクリアシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameClearScene(3));
	}

	//プレイヤーのHPが0以下
	if (obj_player->GetHP() < 0 || GameData::Get_Each_Time() <= 0)
	{
		//ゲームオーバーシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameOverScene(2));
		
	}

#endif // DEBUG_OFF_02

	return this;
}
//じゃんけん終了後の挙動（プレイヤー勝ち）
void Scene_Stage02::AfterJanken_WIN()
{
	obj_enemy->frameDown();
	obj_player->SetX(100);
	obj_enemy->SetX(1100);
}

//じゃんけん終了後の挙動（プレイヤー負け）
void Scene_Stage02::AfterJanken_LOSE()
{
	//特殊行動の時間制限の秒数を変えれる
	obj_enemy->SetSpecialTime(600);
	obj_enemy->frameUP();
	obj_player->SetX(100);
	obj_enemy->SetX(1100);
	obj_enemy->Spflg = true;
}