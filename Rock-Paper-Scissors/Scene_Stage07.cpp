#include "Scene_Stage07.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"GameData.h"

#include"Scene_GameOver.h"
#include"Scene_GameClear.h"

//デバッグモード
#include"Debug_Manager.h"

//コンストラクタ
Scene_Stage07::Scene_Stage07(const Player* player)
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
	obj_enemy = new Enemy_07(900, 360, Jan_Type::SCISSORS);

	//床・壁の用意
	Init_Floor(STAGE_07_FLOOR);

	//一つずつ生成  STAGE_07_FLOOR 個分
	obj_floor[0] = new Floor(0, 700, 1280, 20);        //床
	obj_floor[1] = new Floor(0, 0, 20, 1720);          //壁（左）
	obj_floor[2] = new Floor(1260, 0, 20, 1720);       //壁（右）
	obj_floor[3] = new Floor("images/stage07/Ring.png", 220, 590, 840, 110);   //リング
	obj_floor[4] = new Floor(220, 440, 30, 10, 0x007cfe);        //コーナーポスト（当たり判定は少し　　DrawBoxで表現）
	obj_floor[5] = new Floor(1030, 440, 30, 10, 0x007cfe);       //コーナーポスト（当たり判定は少し　　DrawBoxで表現）
	obj_floor[6] = new Floor(20, 230, 150, 20);        //足場      
	obj_floor[7] = new Floor(1110, 230, 150, 20);      //足場
	obj_floor[8] = new Floor(410, 110, 160, 20);       //足場
	obj_floor[9] = new Floor(710, 110, 160, 20);       //足場

	//画像読み込み
	image_back = LoadGraph("images/stage07/back02.png");
	image_spotlight = LoadGraph("images/stage07/soptlight.png");
}

//デストラクタ
Scene_Stage07::~Scene_Stage07()
{
}

//更新
void Scene_Stage07::Update()
{
	//時間をカウント
	GameData::Time_Update();


	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Update();    // プレイヤー更新・操作可能
		obj_enemy->Update();     //敵キャラ更新・内部処理

		//プレイヤーの座標を取得
		obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());

		//プレイヤーがリング上か
		obj_enemy->CheckPlayerState(obj_player);
	}
	
	//接触じゃんけん処理 (敵の行動が"ダイブ"の時は判定なし)
	if (obj_enemy->Is_Diving_TouchJanken() != true)
	{
		Touch_Janken(obj_enemy, this, 7);
	}

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
					obj_enemy->Change_JanType();      //属性が変わる

					obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
					i--;
				}

				break;

			case Jan_Type::SCISSORS:                       //敵の属性　チョキ

				//グーのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::ROCK)
				{
					obj_enemy->ReceiveDamage(10);     //ダメージが入る
					obj_enemy->Change_JanType();      //属性が変わる

					obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
					i--;
				}
				break;

			case Jan_Type::PAPER:                          //敵の属性　パー

				//チョキのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::SCISSORS)
				{
					obj_enemy->ReceiveDamage(10);     //ダメージが入る
					obj_enemy->Change_JanType();      //属性が変わる

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
			obj_player->ReceiveDamage(10);

			//あたったじゃん撃を削除
			obj_enemy->DeleteJangeki(i);
			i--;
		}
	}

	HitCtrl_Floor(obj_player, STAGE_07_FLOOR);     // player　床・壁判定

	//ﾄﾍﾟｺﾝﾋｰﾛ（ダイブ）中の場合、判定をとらない
	if (obj_enemy->Is_Diving_Collision() != true)
	{
		HitCtrl_Floor(obj_enemy, STAGE_07_FLOOR);      // 敵　　　床・壁判定
	}
	
}


//描画
void Scene_Stage07::Draw() const
{
	//背景
	DrawGraph(0, 0, image_back, TRUE);

	//UI
	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());

	//DrawFormatString(300, 300, 0xffffff, "%d", GameData::Get_Score());

	//テスト
	//DrawFormatString(300, 300, 0x00ff00, "p-x : %f   p-y : %f", obj_player->GetX(), obj_player->GetY());

	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::BEFORE)
	{

		obj_player->Draw();  //プレイヤー描画
		obj_enemy->Draw();   //敵キャラ描画

		//床・壁描画
		for (int i = 0; i < STAGE_07_FLOOR; i++)
		{
			if (obj_floor[i] == nullptr) break;
			obj_floor[i]->Draw();
		}

		//コーナーポスト
		DrawBox(220, 440, (220 + 30), (440 + 150), 0x007cfe, TRUE);    //左
		DrawBox(1030, 440, (1030 + 30), (440 + 150), 0x007cfe, TRUE);  //右


		//ロープ
		DrawBox(250, 450, (250 + 780), (450 + 5), 0x000000, TRUE);     //トップロープ
		DrawBox(250, 500, (250 + 780), (500 + 5), 0x000000, TRUE);     //セカンドロープ
		DrawBox(250, 550, (250 + 780), (550 + 5), 0x000000, TRUE);     //サードロープ

		//スポットライト描画
		SetDrawBlendMode(DX_BLENDMODE_ADD_X4, 150);
		DrawGraph(0, 0, image_spotlight, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		//接触時じゃんけん描画
		Draw_Janken();
	}
}

//じゃんけん描画
void Scene_Stage07::Draw_Janken() const
{
	obj_janken->Draw();
}


//じゃんけん終了後の挙動（プレイヤー勝ち）
void Scene_Stage07::AfterJanken_WIN()
{
	//obj_player->SetX(100);
	//obj_enemy->SetX(900);

	obj_enemy->Init_MoveAndAction();

}

//じゃんけん終了後の挙動（プレイヤー負け）
void Scene_Stage07::AfterJanken_LOSE()
{
	obj_player->SetX(100);
	obj_enemy->SetX(900);

	obj_enemy->Init_MoveAndAction();
}


//シーンの変更
AbstractScene* Scene_Stage07::ChangeScene()
{
#ifdef DEBUG_OFF_07

	//敵のHPが0以下
	if (obj_enemy->GetHP() < 0)
	{
		//ゲームクリアシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameClearScene(8));
	}

	//プレイヤーのHPが0以下
	if (obj_player->GetHP() < 0 || GameData::Get_Each_Time() <= 0)
	{
		//ゲームオーバーシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameOverScene(7));
	}

#endif // DEBUG_OFF_07

	return this;
}