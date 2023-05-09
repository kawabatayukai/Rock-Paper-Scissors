#include "Scene_Stage09.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"Scene_GameOver.h"
#include "Scene_GameClear.h"
#include"Scene_Stage10.h"
#include"GameData.h"


//デバッグモード
#include"Debug_Manager.h"

//コンストラクタ
Scene_Stage09::Scene_Stage09(const Player* player)
{

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
	obj_enemy = new Enemy_09(1110, 480, Jan_Type::NONE);

	reflection = new Jangeki_Reflection(0, 0, 0, 0, Jan_Type::ROCK);

	stageimage = LoadGraph("images/stage09/stage09_image.png");



	//床・壁の用意
	Init_Floor(STAGE_09_FLOOR);

	//一つずつ生成  STAGE_09_FLOOR 個分
	obj_floor[0] = new Floor(0, 700, 1280, 20);        //床
	obj_floor[1] = new Floor(0, -200, 20, 1720);           //壁（左）
	obj_floor[2] = new Floor(1260, -200, 20, 1720);           //壁（右）
	//足場   左側
	obj_floor[3] = new Floor(100, 500, 120, 20, 0xd2d2d2);
	obj_floor[4] = new Floor(300, 325, 120, 20, 0xd2d2d2);
	obj_floor[5] = new Floor(100, 150, 120, 20, 0xd2d2d2);
	//足場   右側
	obj_floor[6] = new Floor(1050, 500, 120, 20, 0xd2d2d2);
	obj_floor[7] = new Floor(850, 325, 120, 20, 0xd2d2d2);
	obj_floor[8] = new Floor(1050, 150, 120, 20, 0xd2d2d2);
	//足場   中央
	obj_floor[9] = new Floor(560, 450, 120, 20, 0xd2d2d2);
	obj_floor[10] = new Floor(560, 130, 120, 20, 0xd2d2d2);

}

//デストラクタ
Scene_Stage09::~Scene_Stage09()
{
}

//更新
void Scene_Stage09::Update()
{
	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Update();    // プレイヤー更新・操作可能

		//（playerが）敵の座標を取得
		obj_player->SetEnemyLocation(obj_enemy->GetX(), obj_enemy->GetY());

		obj_enemy->Update();     //敵キャラ更新・内部処理
		obj_enemy->reflection->Update_reflection();
		//プレイヤーの座標を取得
		obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());

		GameData::Time_Update();
	}

	//接触じゃんけん処理
	//特殊行動中とアニメーション再生中はなし
	if (obj_enemy->Spflg == false && obj_enemy->animflg == false)
		Touch_Janken(obj_enemy, this, 9);

	Effect_Update_HitJangeki(obj_enemy);

	//playerのじゃん撃をとってくる
	Jangeki_Base** player_jangeki = obj_player->GetJangeki();

	//enemyのじゃん撃をとってくる
	Jangeki_Base** enemy_jangeki = obj_enemy->GetJangeki();

	//反射されたじゃん撃をとってくる
	Jangeki_Base** reflection_jangeki = obj_enemy->reflection->GetJangeki();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//じゃん撃同士の当たり判定（プレイヤーじゃん撃目線）
	for (int p_count = 0; p_count < JANGEKI_MAX; p_count++)
	{
		if (player_jangeki[p_count] == nullptr) break;         //じゃん撃がない時は処理しない

		bool delete_player = false;       //プレイヤーじゃん撃削除フラグ　true:削除　false:削除しない

		for (int e_count = 0; e_count < JANGEKI_MAX; e_count++)
		{
			if (enemy_jangeki[e_count] == nullptr) break;         //じゃん撃がない時は処理しないuuuuuuuuuuuuuuuuuuuuuuu

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
					if (player_jangeki[p_count]->GetR() != 35.f)
					{
						delete_player = true;
					}

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

		if (obj_enemy->animflg == false) {
			//じゃん撃との当たり判定
			if (obj_enemy->Hit_Jangeki(player_jangeki[i]) == true)
			{

				if (player_jangeki[i]->GetR() == 35.f || obj_enemy->Getflg() == true)
				{
					obj_enemy->ReceiveDamage(20);
					//あたったじゃん撃を削除
					obj_player->DeleteJangeki(i);
					i--;
					if (obj_enemy->Getflg() == true)obj_enemy->Fflg();
				}
				else
				{
					obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
					i--;
					obj_enemy->reflection->trueFlg();
				}
			}
			obj_enemy->HP();

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
			//特殊行動中は10ダメージ
			if (enemy_jangeki[i]->GetR()==40.f)obj_player->ReceiveDamage(10);
			else obj_player->ReceiveDamage(30);
			
			//あたったじゃん撃を削除
			obj_enemy->DeleteJangeki(i);
			i--;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//反射じゃん撃当たり判定

	//反射されたじゃん撃とplayerじゃん撃の当たり判定
	for (int p_count = 0; p_count < JANGEKI_MAX; p_count++)
	{
		if (player_jangeki[p_count] == nullptr) break;         //じゃん撃がない時は処理しない

		bool delete_player = false;       //プレイヤーじゃん撃削除フラグ　true:削除　false:削除しない

		for (int r_count = 0; r_count < JANGEKI_MAX; r_count++)
		{
			if (reflection_jangeki[r_count] == nullptr) break;         //じゃん撃がない時は処理しない

			if (player_jangeki[p_count]->Hit_Jangeki(reflection_jangeki[r_count]) == true)
			{
				//有利属性チェック
				int result = player_jangeki[p_count]->CheckAdvantage(reflection_jangeki[r_count]);

				switch (result)
				{
				case 0:             //playerのじゃん撃が不利

					//player側のじゃん撃を削除
					delete_player = true;

					break;

				case 1:             //playerのじゃん撃が有利

					//enemy側のじゃん撃を削除
					obj_enemy->reflection->Delete_reflectionJangeki(r_count);
					r_count--;

					//ホーミングを特殊生成
					obj_player->Create_Homing(p_count, player_jangeki[p_count]->GetX(), player_jangeki[p_count]->GetY(), 35.f, 10, player_jangeki[p_count]->GetType());

					break;

				case 2:             //あいこ

					//player側のじゃん撃を削除
					delete_player = true;

					//enemy側のじゃん撃を削除
					obj_enemy->reflection->Delete_reflectionJangeki(r_count);
					r_count--;

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


	//反射されたじゃん撃とプレイヤーの当たり判定
	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		//じゃん撃がない時は処理しない
		if (reflection_jangeki[i] == nullptr) break;
		//じゃん撃との当たり判定
		if (obj_player->Hit_Jangeki(reflection_jangeki[i]) == true)
		{
			
			//ダメージを受ける（プレイヤー）
			obj_player->ReceiveDamage(20);

			//あたったじゃん撃を削除
			obj_enemy->reflection->Delete_reflectionJangeki(i);
			i--;
		}
	}


	//壁との当たり判定
	if (obj_player->Get_X() <= 50 || obj_player->Get_X() >= 1200)
	{
		HitCtrl_Floor(obj_player, STAGE_09_FLOOR);     // player　床・壁判定
	}

	//プレイヤーのy座標が減少しない時のみ当たり判定を取得
	if (obj_player->Get_Y() >= obj_player->Get_OldY())
	{
		HitCtrl_Floor(obj_player, STAGE_09_FLOOR);     // player　床・壁判定
	}
	HitCtrl_Floor(obj_enemy, STAGE_09_FLOOR);      // 敵　　　床・壁判定
}


//描画
void Scene_Stage09::Draw() const
{

	DrawGraph(0, 0, stageimage, false);
	
	//HP表示
	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());
	DrawUI_ON_Enemy(obj_enemy);

	//接触じゃんけんでない時
	if (GetJanState() == Jan_State::START || GetJanState() == Jan_State::BEFORE)
	{

		obj_player->Draw();  //プレイヤー描画
		obj_enemy->Draw();   //敵キャラ描画
		obj_enemy->reflection->Draw_reflectionJangeki();


		//床・壁描画
		for (int i = 0; i < STAGE_09_FLOOR; i++)
		{
			if (obj_floor[i] == nullptr) break;
			obj_floor[i]->Draw();
		}
		//接触した瞬間の演出
		if (GetJanState() == Jan_State::START) Draw_JankenStart();

	}

	else
	{
		//接触時じゃんけん描画
		Draw_Janken();
	}

	DrawString(640, 360, "Stage09", 0xffffff);
	Effect_Draw_HitJangeki();
}


//じゃんけん描画
void Scene_Stage09::Draw_Janken() const
{
	obj_janken->Draw();
}

//シーンの変更
AbstractScene* Scene_Stage09::ChangeScene()
{
	//"Debug_Manager.h" の #define DEBUG_OFF_09 をコメントアウトすると開発モード
#ifdef DEBUG_OFF_09

	//敵のHPが0以下
	if (clearFlg == true)
	{
		//ゲームクリアシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameClearScene(10));
	}

	//プレイヤーのHPが0以下
	if (obj_player->IsDeathPlayer() == true)
	{
		//ゲームオーバーシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameOverScene(9));
	}

#endif  DEBUG_OFF_09

	return this;
}

//じゃんけん終了後の挙動（プレイヤー勝ち）
void Scene_Stage09::AfterJanken_WIN()
{
	
	if (obj_enemy->GetHP() == 1)
	{
		clearFlg = true;
	}
	obj_player->SetX(100);
	obj_enemy->SetX(1110);
	obj_enemy->frameDown();
	obj_enemy->Tflg();
}
//じゃんけん終了後の挙動（プレイヤー負け）
void Scene_Stage09::AfterJanken_LOSE()
{

	if (obj_enemy->GetHP() == 1)
	{
		obj_enemy->SetHP(-hp);
		hp = hp / 2;
		if (GameData::Get_Total_Time() <= 3600)
			GameData::Set_TimeLimit(5400);
	}
	
	obj_player->SetX(100);
	obj_enemy->SetX(1110);
	obj_enemy->frameUP();
	obj_enemy->Spflg = true;

}