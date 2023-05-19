#include "Scene_Stage10.h"
#include"Scene_GameOver.h"
#include"Scene_GameClear.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"Scene_GameClear.h"
#include"Scene_GameOver.h"
#include"Jangeki_Homing.h"
#include"GameData.h"
#include"Enemy_10.h"
#include"Jangeki_whole.h"
#include"Scene_InputNameRanking.h"
#include"Scene_Ranking.h"
#include"SortSave.h"

//デバッグモード
#include"Debug_Manager.h"
#include "SoundSystem.h"

//コンストラクタ
Scene_Stage10::Scene_Stage10(const Player* player)
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
	obj_enemy = new Enemy_10(1050, 220, Jan_Type::SCISSORS);

	//床・壁の用意
	Init_Floor(STAGE_10_FLOOR);

	//一つずつ生成  STAGE_10_FLOOR 個分
	obj_floor[0] = new Floor(0, 700, 1280, 20);        //床
	obj_floor[1] = new Floor(0, 0, 20, 1720);           //壁（左）
	obj_floor[2] = new Floor(1260, 0, 20, 1720);           //壁（右）

	reflection = new Jangeki_Reflection(0, 0, 0, 0, Jan_Type::ROCK);

	//BGMロード
	bgm[0] = LoadSoundMem("Sound/VSQPD_0077_Mary_Had_a_Little_Lamb_FC.mp3");
	bgm[1] = LoadSoundMem("Sound/VSQPD_0046_Yankee_Doodle.mp3");
	bgm[2] = LoadSoundMem("Sound/VSQPD_0048_London_Bridge.mp3");
	bgm[3] = LoadSoundMem("Sound/sento.mp3");
}

//デストラクタ
Scene_Stage10::~Scene_Stage10()
{
	for (int i = 0; i < 4; i++)
	{
		StopSoundMem(bgm[i]);
	}
}

//更新
void Scene_Stage10::Update()
{
	switch (obj_enemy->Get_Enemy10Form())
	{
		/***********
		* 第一形態
		***********/
	case 1:

		static int interval;
		interval++;

		//BGM
		if (interval % 10 == 0)
		{
			if (CheckSoundMem(bgm[1]) == 0) PlaySoundMem(bgm[1], DX_PLAYTYPE_LOOP);
		}
		if (interval % 300 == 0)
		{
			if (CheckSoundMem(bgm[0]) == 0) PlaySoundMem(bgm[0], DX_PLAYTYPE_LOOP);
		}
		if (interval % 600 == 0)
		{
			if (CheckSoundMem(bgm[2]) == 0) PlaySoundMem(bgm[2], DX_PLAYTYPE_LOOP);
		}

		/*足場*/
		obj_floor[3] = new Floor(100, 350, 120, 50);      
		obj_floor[4] = new Floor(1000, 350, 120, 50);      

		/*床*/
		obj_floor[5] = new Floor(0, 700, 1280, 20);        
		obj_floor[6] = new Floor(0, 700, 1280, 20);        
		obj_floor[7] = new Floor(0, 700, 1280, 20);        
		obj_floor[8] = new Floor(0, 700, 1280, 20);        
		obj_floor[9] = new Floor(0, 700, 1280, 20);       
		obj_floor[10] = new Floor(0, 700, 1280, 20);        
		obj_floor[11] = new Floor(0, 700, 1280, 20);        
		obj_floor[12] = new Floor(0, 700, 1280, 20);        
		obj_floor[13] = new Floor(0, 700, 1280, 20);       
		obj_floor[14] = new Floor(0, 700, 1280, 20);        
		obj_floor[15] = new Floor(0, 700, 1280, 20);       
		break;

		/***********
		* 第二形態
		***********/
	case 2:

		//BGM STOP
		for (int i = 0; i < 3; i++)
		{
			StopSoundMem(bgm[i]);
		}

		//BGM
		if (CheckSoundMem(bgm[3]) == 0) PlaySoundMem(bgm[3], DX_PLAYTYPE_LOOP);

		/*足場*/  
		obj_floor[3] = new Floor(100, 500, 120, 20, 0xd2d2d2);//テレポート左位置
		obj_floor[4] = new Floor(81, 300, 120, 10, 22822);
		obj_floor[5] = new Floor(0, 700, 1280, 20);
		obj_floor[6] = new Floor(1050, 500, 120, 20, 0xd2d2d2);//テレポート右位置
		obj_floor[7] = new Floor(333, 400, 120, 10, 22822);
		obj_floor[8] = new Floor(585, 100, 120, 10, 22822);
		obj_floor[9] = new Floor(560, 420, 120, 20, 0xd2d2d2);//テレポート真ん中位置
		obj_floor[10] = new Floor(0, 700, 1280, 20);
		obj_floor[11] = new Floor(837, 200, 120, 10, 22822);
		obj_floor[12] = new Floor(800, 500, 120, 10, 22822);
		obj_floor[13] = new Floor(1089, 100, 120, 10, 22822);
		obj_floor[14] = new Floor(1089, 300, 120, 10, 22822);
		obj_floor[15] = new Floor(100, 100, 120, 10, 22822);
		break;
	default:
		break;
	}

	//接触じゃんけんでない時
	//if (janken_flag == false)
	//{
	//	obj_player->Update();    // プレイヤー更新・操作可能
	//	obj_enemy->Update();     //敵キャラ更新・内部処理
	//
	//	/*反射弾*/
	//	//obj_enemy->reflection->Update_reflection();
	//
	//	/*ステージでの属性変化*/
	//	//obj_enemy->SetType(Jan_Type::PAPER);
	//
	//	/*敵がプレイヤーの座標を返す*/
	//	obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());
	//
	//	//敵とプレイヤーの当たり判定  　ここで"接触じゃんけん"
	//	if (obj_enemy->Hit_Character(obj_player) == true)
	//	{
	//		//敵が出す手をランダムに決める　　　（ランダムなint型の値(0〜2)を Jan_Type型に変換）
	//		Jan_Type enemy_janken = static_cast<Jan_Type> (GetRand(2));
	//
	//		//じゃんけん用オブジェクト生成
	//		obj_janken = new Janken(enemy_janken);
	//
	//		//接触じゃんけん開始
	//		janken_flag = true;
	//	}
	//}
	//else
	//{
	//	//接触時じゃんけんの処理を実行
	//	Update_Janken();
	//}

	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Update();    // プレイヤー更新・操作可能
		obj_enemy->Update();     //敵キャラ更新・内部処理

		//プレイヤー座標を取得
		obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());

		//プレイヤー向きを取得
		//obj_enemy->SetPlayerDirection(obj_player->GetDirection());

		//時間をカウント
		GameData::Time_Update();
	}

	//接触じゃんけん処理
	Touch_Janken(obj_enemy, this, 10);

	//playerのじゃん撃をとってくる
	Jangeki_Base** player_jangeki = obj_player->GetJangeki();

	//enemyのじゃん撃をとってくる
	Jangeki_Base** enemy_jangeki = obj_enemy->GetJangeki();

	//反射されたじゃん撃をとってくる
	//Jangeki_Base** reflection_jangeki = obj_enemy->reflection->GetJangeki();

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
					obj_enemy->ReceiveDamage(30);     //ダメージが入る
					obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
					i--;
				}

				break;

			case Jan_Type::SCISSORS:                       //敵の属性　チョキ

				//グーのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::ROCK)
				{
					obj_enemy->ReceiveDamage(30);     //ダメージが入る
					obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
					i--;
				}
				break;

			case Jan_Type::PAPER:                          //敵の属性　パー

				//チョキのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::SCISSORS)
				{
					obj_enemy->ReceiveDamage(30);     //ダメージが入る
					obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
					i--;
				}
				break;

			default:
				break;
			}

			/*反射弾*/
			//if (player_jangeki[i]->GetR() == 35.f || obj_enemy->Getflg() == true)
			//{
			//	obj_enemy->ReceiveDamage(20);
			//
			//	//あたったじゃん撃を削除
			//	obj_player->DeleteJangeki(i);
			//	i--;
			//	if (obj_enemy->Getflg() == true)obj_enemy->Fflg();
			//}
			//else
			//{
			//	obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
			//	i--;
			//	obj_enemy->reflection->trueFlg();
			//}
			//obj_enemy->HP();
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//反射じゃん撃当たり判定

	//反射されたじゃん撃とplayerじゃん撃の当たり判定
	//for (int p_count = 0; p_count < JANGEKI_MAX; p_count++)
	//{
	//	if (player_jangeki[p_count] == nullptr) break;         //じゃん撃がない時は処理しない
	//	bool delete_player = false;       //プレイヤーじゃん撃削除フラグ　true:削除　false:削除しない
	//	for (int r_count = 0; r_count < JANGEKI_MAX; r_count++)
	//	{
	//		if (reflection_jangeki[r_count] == nullptr) break;         //じゃん撃がない時は処理しない
	//		if (player_jangeki[p_count]->Hit_Jangeki(reflection_jangeki[r_count]) == true)
	//		{
	//			//有利属性チェック
	//			int result = player_jangeki[p_count]->CheckAdvantage(reflection_jangeki[r_count]);
	//			switch (result)
	//			{
	//			case 0:             //playerのじゃん撃が不利
	//				//player側のじゃん撃を削除
	//				delete_player = true;
	//				break;
	//			case 1:             //playerのじゃん撃が有利
	//				//enemy側のじゃん撃を削除
	//				obj_enemy->reflection->Delete_reflectionJangeki(r_count);
	//				r_count--;
	//				//ホーミングを特殊生成
	//				obj_player->Create_Homing(p_count, player_jangeki[p_count]->GetX(), player_jangeki[p_count]->GetY(), 35.f, 10, player_jangeki[p_count]->GetType());
	//				break;
	//			case 2:             //あいこ
	//				//player側のじゃん撃を削除
	//				delete_player = true;
	//				//enemy側のじゃん撃を削除(反射弾)
	//				obj_enemy->reflection->Delete_reflectionJangeki(r_count);
	//				r_count--;
	//				break;
	//			default:
	//				break;
	//			}
	//		}
	//	}
	//	//プレイヤーじゃん撃削除フラグがtrue
	//	if (delete_player == true)
	//	{
	//		//player側のじゃん撃を削除
	//		obj_player->DeleteJangeki(p_count);
	//		p_count--;
	//	}
	//}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//enemyじゃん撃とplayerの当たり判定
	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		//じゃん撃がない時は処理しない
		if (enemy_jangeki[i] == nullptr) break;

		//じゃん撃との当たり判定
		if (obj_player->Hit_Jangeki(enemy_jangeki[i]) == true)
		{
			//ダメージを受ける（プレイヤー）
			obj_player->ReceiveDamage(30);

			//あたったじゃん撃を削除
			obj_enemy->DeleteJangeki(i);

			/*あたったじゃん撃を削除(反射弾)*/
			//obj_enemy->reflection->Delete_reflectionJangeki(i);
			i--;
		}
	}
	//HitCtrl_Floor(obj_player, STAGE_10_FLOOR);     // player　床・壁判定
	//HitCtrl_Floor(obj_enemy, STAGE_10_FLOOR);      // 敵　　　床・壁判定

	//壁との当たり判定
	if (obj_player->Get_X() <= 50 || obj_player->Get_X() >= 1220)
	{
		HitCtrl_Floor(obj_player, STAGE_10_FLOOR);     // player　床・壁判定
	}

	//プレイヤーのy座標が減少しない時のみ当たり判定を取得
	if (obj_player->Get_Y() >= obj_player->Get_OldY() || obj_player->Get_Y() <= -200)
	{
		HitCtrl_Floor(obj_player, STAGE_10_FLOOR);     // player　床・壁判定
	}

	//敵のy座標が減少しない時のみ当たり判定を取得
	if (obj_enemy->Get_Y() >= obj_enemy->Get_OldY() || obj_enemy->Get_Y() <= -200)
	{
		HitCtrl_Floor(obj_enemy, STAGE_10_FLOOR);      // 敵　　　床・壁判定
	}
}


//描画
void Scene_Stage10::Draw() const
{
	//背景の描画
	DrawGraph(0, 0, 0, FALSE);

	//UIの描画
	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());
	DrawUI_ON_Enemy(obj_enemy);

	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::START || GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Draw();  //プレイヤー描画
		obj_enemy->Draw();   //敵キャラ描画

		//床・壁描画
		for (int i = 0; i < STAGE_10_FLOOR; i++)
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
}

//じゃんけん更新・内部処理
void Scene_Stage10::Update_Janken()
{
	//　ここは改良したほうがいい

	obj_janken->Update();

	//Aボタンが押されたとき 
	if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	{
		//結果を取得
		switch (obj_janken->GetResult())
		{
		case Jan_Result::LOSE:    //負け

			obj_player->SetX(640);   //ずらす
			janken_flag = false;

			obj_enemy->Init_Jangeki();

			delete obj_janken;
			break;

		case Jan_Result::WIN:     //勝ち

			obj_player->SetX(640);   //ずらす
			janken_flag = false;

			obj_enemy->Init_Jangeki();

			delete obj_janken;
			break;

		case Jan_Result::ONEMORE: //あいこ

			janken_flag = false;

			obj_enemy->Init_Jangeki();

			delete obj_janken;
			break;

		case Jan_Result::_ERROR:  //まだじゃんけん中
			break;

		default:
			break;
		}
	}
}

//じゃんけん描画
void Scene_Stage10::Draw_Janken() const
{
	obj_janken->Draw();
}

/*じゃんけんに勝った時*/
void Scene_Stage10::AfterJanken_WIN()
{
	if(obj_enemy->Get_Enemy10Form() == 1)
	{
		obj_enemy->ReceiveDamage(100);
	}

	if (obj_enemy->Get_Enemy10Form() == 2)
	{
		obj_player->Recover_HP(50);
	}
}

/*じゃんけんに負けた時*/
void Scene_Stage10::AfterJanken_LOSE()
{
	if (obj_enemy->Get_Enemy10Form() == 1)
	{
		obj_player->ReceiveDamage(100);
	}

	if (obj_enemy->Get_Enemy10Form() == 2)
	{
		obj_enemy->Recover_HP(30);
	}
}

//シーンの変更
AbstractScene* Scene_Stage10::ChangeScene()
{
	//"Debug_Manager.h" の #define DEBUG_OFF_10 をコメントアウトすると開発モード
#ifdef DEBUG_OFF_10

	/*敵のHPが0以下*/
	if (obj_enemy->Get_Enemy10Form() == 1 && obj_enemy->IsDeathEnemy10() == true) //第一形態
	{
		StopSoundMem(bgm[0]);
		StopSoundMem(bgm[1]);
		StopSoundMem(bgm[2]);
	}
	if(obj_enemy->Get_Enemy10Form() == 2 && obj_enemy->IsDeathEnemy10() == true) //第二形態
	{
		//ゲームクリアシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameClearScene(11));
	}
	 	   
	/*プレイヤーのHPが0になったら*/
	if (obj_player->IsDeathPlayer() == true)
	{
		//ゲームオーバーシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameOverScene(10));
	}

#endif // DEBUG_OFF_10
	return this;
}