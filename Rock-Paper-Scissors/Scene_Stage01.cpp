#include "Scene_Stage01.h"
#include"KeyManager.h"
#include"Scene_GameOver.h"
#include"Scene_GameClear.h"
#include"DxLib.h"
#include"GameData.h"
#include"SoundSystem.h"
#include"Scene_Ranking.h"

//デバッグモード
#include"Debug_Manager.h"

//コンストラクタ
Scene_Stage01::Scene_Stage01(const Player* player)
	: Now_Tut_State(TUTORIAL_STATE::START_TUTORIAL)
{
	//制限時間をセット
	GameData::Set_TimeLimit(10800);

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
	obj_enemy = new Enemy_01(1110, 680, Jan_Type::SCISSORS);

	//床・壁の用意
	Init_Floor(STAGE_01_FLOOR);

	//一つずつ生成
	obj_floor[0] = new Floor(0, 700, 1280, 20);        //床
	obj_floor[1] = new Floor(0, 0, 20, 720);           //壁（左）
	obj_floor[2] = new Floor(1260, 0, 20, 720);        //壁（右）

	obj_floor[3] = new Floor(1100, 500, 120, 20, 0x006400);      //足場No.01
	obj_floor[4] = new Floor(900, 290, 120, 20, 0x006400);       //足場No.02
	obj_floor[5] = new Floor(330, 140, 460, 20, 0x006400);       //足場No.03
	obj_floor[6] = new Floor(50, 290, 120, 20, 0x006400);        //足場No.04
	obj_floor[7] = new Floor(250, 500, 120, 20, 0x006400);       //足場No.05

	//画像読み込み
	image_back = LoadGraph("images/stage01/Tutorial_Back.png");

	//BGMロード
	bgm = LoadSoundMem("Sound/stage01/maou_game_battle37.mp3");
	
}

//デストラクタ
Scene_Stage01::~Scene_Stage01()
{
	delete obj_enemy;
	DeleteSoundMem(bgm);
}

//更新
void Scene_Stage01::Update()
{
	//BGM再生
	
	if (CheckSoundMem(bgm) == 0) PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Update();    // プレイヤー更新・操作可能
		obj_enemy->Update();     //敵キャラ更新・内部処理

		//時間をカウント
		GameData::Time_Update();


		//プレイヤーの座標を取得
		obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());

	}

	//接触じゃんけん処理
	Touch_Janken(obj_enemy, this, 1);
	Effect_Update_HitJangeki(obj_enemy);

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
					//エフェクト発動
					//Play_Effect(player_jangeki[p_count]->GetX(), player_jangeki[p_count]->GetY(), 0);
					break;

				case 1:             //playerのじゃん撃が有利

					//enemy側のじゃん撃を削除
					obj_enemy->DeleteJangeki(e_count);
					e_count--;

					//エフェクト発動
					//Play_Effect(player_jangeki[p_count]->GetX(), player_jangeki[p_count]->GetY(),1);
					break;

				case 2:             //あいこ

					//player側のじゃん撃を削除
					delete_player = true;

					//enemy側のじゃん撃を削除
					obj_enemy->DeleteJangeki(e_count);
					e_count--;

					//エフェクト発動
					//Play_Effect(player_jangeki[p_count]->GetX(), player_jangeki[p_count]->GetY(),2);
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

			int jan_damage = 10;    //ダメージ

			//不利属性のみダメージが入る
			switch (enemy_type)
			{
			case Jan_Type::ROCK:                           //敵の属性　グー

				//パーのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::PAPER)
				{
					obj_enemy->ReceiveDamage(jan_damage);  //ダメージが入る
					obj_player->DeleteJangeki(i);          //当たったじゃん撃を削除
					i--;
				}

				break;

			case Jan_Type::SCISSORS:                       //敵の属性　チョキ

				//グーのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::ROCK)
				{
					obj_enemy->ReceiveDamage(jan_damage);  //ダメージが入る
					obj_player->DeleteJangeki(i);          //当たったじゃん撃を削除
					i--;
				}
				break;

			case Jan_Type::PAPER:                          //敵の属性　パー

				//チョキのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::SCISSORS)
				{
					obj_enemy->ReceiveDamage(jan_damage);  //ダメージが入る
					obj_player->DeleteJangeki(i);          //当たったじゃん撃を削除
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
			obj_player->ReceiveDamage(5);

			//あたったじゃん撃を削除
			obj_enemy->DeleteJangeki(i);
			i--;
		}
	}


	//壁との当たり判定
	if (obj_player->Get_X() <= 50 || obj_player->Get_X() >= 1220)
	{
		HitCtrl_Floor(obj_player, STAGE_01_FLOOR);     // player　床・壁判定
	}

	//プレイヤーのy座標が減少しない時のみ当たり判定を取得
	if (obj_player->Get_Y() >= obj_player->Get_OldY() || obj_player->Get_Y() <= -200)
	{
		HitCtrl_Floor(obj_player, STAGE_01_FLOOR);     // player　床・壁判定
	}

	//敵のy座標が減少しない時のみ当たり判定を取得
	if (obj_enemy->Get_Y() >= obj_enemy->Get_OldY() || obj_enemy->Get_Y() <= -200)
	{
		HitCtrl_Floor(obj_enemy, STAGE_01_FLOOR);      // 敵　　　床・壁判定

		//(x - (w / 2))
		//(y - (h / 2))
		//(x + (w / 2))
		//(y + (h / 2))
	}
}

//描画
void Scene_Stage01::Draw() const
{
	//背景
	DrawGraph(0, 0, image_back, FALSE);

	//UI
	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());
	DrawUI_ON_Enemy(obj_enemy);

	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::START || GetJanState() == Jan_State::BEFORE)
	{
		//床・壁描画
		for (int i = 0; i < STAGE_01_FLOOR; i++)
		{
			if (obj_floor[i] == nullptr) break;
			obj_floor[i]->Draw();
		}
		obj_player->Draw();  //プレイヤー描画
		obj_enemy->Draw();   //敵キャラ描画

		//接触した瞬間の演出
		if (GetJanState() == Jan_State::START) Draw_JankenStart();
	}
	else
	{
		//接触時じゃんけん描画
		Draw_Janken();
	}
			
	//Effect
	Effect_Draw_HitJangeki();
}

//じゃんけん描画
void Scene_Stage01::Draw_Janken() const
{
	obj_janken->Draw();
}

//シーンの変更
AbstractScene* Scene_Stage01::ChangeScene()
{
#ifdef DEBUG_OFF_01

	//敵のHPが0以下
	if (IsEnd_DeathEnemy() == true)
	{

		//ゲームクリアシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameClearScene(2));
		//sortSave.setScore(9, 10);	// ランキングデータの１０番目にスコアを登録
		//sortSave.SortRanking();		// ランキング並べ替え
		//sortSave.SaveRanking();		// ランキングデータの保存
		//return new Scene_Ranking();
	}

	//プレイヤーのHPが0以下
	if (obj_player->IsDeathPlayer() == true)
	{
		//ゲームオーバーシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameOverScene(1));
	}

#endif 

	return this;   //更新なし
}

//じゃんけん終了後の挙動（プレイヤー勝ち）
void Scene_Stage01::AfterJanken_WIN()
{
	obj_player->SetX(1280 / 2);
	//obj_player->SetY(500);

	//HPを全回復
	obj_player->Recover_HP(100);
}

//じゃんけん終了後の挙動（プレイヤー負け）
void Scene_Stage01::AfterJanken_LOSE()
{
	obj_player->SetX(1280 / 2);
	//obj_player->SetY(500);
}