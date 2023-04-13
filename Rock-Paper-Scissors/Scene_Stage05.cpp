#include "Scene_Stage05.h"
#include "KeyManager.h"
#include "DxLib.h"
#include"Scene_GameOver.h"
#include "Scene_GameClear.h"
#define PI    3.1415926535897932384626433832795f

//デバッグモード
#include"Debug_Manager.h"

//コンストラクタ
Scene_Stage05::Scene_Stage05(const Player* player)
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
		obj_player = new Player(640, 360);
	}

	//敵を生成
	obj_enemy = new Enemy_05(1000, 160, Jan_Type::SCISSORS);

	mob = new MobEnemy_05 * [3];
	for (int i = 0; i < 3; i++) mob[i] = nullptr;


	mob[0] = new MobEnemy_05(640, 100, Jan_Type::PAPER);
	mob[1] = new MobEnemy_05(50, 420, Jan_Type::SCISSORS);
	mob[2] = new MobEnemy_05(1230, 420, Jan_Type::ROCK);

	if (mob[0]->GetHP() <= 0 && mob[1]->GetHP() <= 0 && mob[2]->GetHP() <= 0)
	{
		mob[0] = new MobEnemy_05(640, 100, Jan_Type::PAPER);
		mob[1] = new MobEnemy_05(50, 420, Jan_Type::SCISSORS);
		mob[2] = new MobEnemy_05(1230, 420, Jan_Type::ROCK);
	}


	//床・壁の用意
	Init_Floor(STAGE_05_FLOOR);

	//一つずつ生成  STAGE_05_FLOOR 個分
	obj_floor[0] = new Floor(0, 700, 1280, 20);        //床
	obj_floor[1] = new Floor(0, 0, 20, 1720);           //壁（左）
	obj_floor[2] = new Floor(1260, 0, 20, 1720);           //壁（右）
	obj_floor[3] = new Floor(260, 300, 120, 15);      //足場　(左上)
	obj_floor[4] = new Floor(260, 540, 120, 15);      //足場　(左下)
	obj_floor[5] = new Floor(590, 420, 120, 15);      //足場　(真ん中)
	obj_floor[6] = new Floor(900, 540, 120, 15);      //足場　(右上)
	obj_floor[7] = new Floor(900, 300, 120, 15);      //足場　(右下)

	Back_image = LoadGraph("images/stage05/Stage5_Stageimage.png", TRUE);
}

//デストラクタ
Scene_Stage05::~Scene_Stage05()
{
}

//更新
void Scene_Stage05::Update()
{
	static int timer = 0;
	timer++;

	/*if (timer == 900)
	{
		timer = 0;
	}*/
	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::BEFORE)
	{
		if (obj_enemy->respawn_mobenemy() == true)
		{
			for (int i = 0; i < 3; i++)
			{
				mob[i]->Init_Jangeki();
				mob[i]->Recover_HP(100);
			}
			obj_enemy->SetRespawn(false);
		}

		obj_player->Update();    // プレイヤー更新・操作可能
		obj_enemy->GetMobEnemy(mob);
		obj_enemy->Update();     //敵キャラ更新・内部処理
		


		for (int i = 0; i < 3; i++)
		{
			mob[i]->Update();

			//プレイヤーの座標を取得
			mob[i]->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());
		}



		//プレイヤーの座標を取得
		obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());
	}
	//接触じゃんけん処理
	Touch_Janken(obj_enemy, this);



	//playerのじゃん撃をとってくる
	Jangeki_Base** player_jangeki = obj_player->GetJangeki();

	//enemyのじゃん撃をとってくる
	Jangeki_Base** enemy_jangeki = obj_enemy->GetJangeki();

	Jangeki_Base** mobenemy_jangek[3];
	mobenemy_jangek[0] = mob[0]->GetJangeki();
	mobenemy_jangek[1] = mob[1]->GetJangeki();
	mobenemy_jangek[2] = mob[2]->GetJangeki();

	//for (int j = 0; j < 3; j++)
	//{
	//	//enemyのじゃん撃をとってくる
	//	mobenemy_jangeki[j] = mob[j]->GetJangeki();
	//}

	//enemyのじゃん撃をとってくる
	//Jangeki_Base** mobenemy_jangeki = obj_mobenemy->GetJangeki();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int a = 0; a < 3; a++)
	{
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
						mob[a]->DeleteJangeki(e_count);
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
	}




	for (int a = 0; a < 3; a++)
	{
		Jangeki_Base** enemy_jangeki = mobenemy_jangek[a];
		if (mob[a]->GetHP() >= 0)
		{
			//じゃん撃同士の当たり判定（プレイヤーじゃん撃目線）(mob用)
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
							mob[a]->DeleteJangeki(e_count);
							e_count--;

							break;

						case 2:             //あいこ

							//player側のじゃん撃を削除
							delete_player = true;

							//enemy側のじゃん撃を削除
							mob[a]->DeleteJangeki(e_count);
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
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//playerじゃん撃とenemyの当たり判定
	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (mob[0]->GetHP() <= 0 && mob[1]->GetHP() <= 0 && mob[2]->GetHP() <= 0)
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
					int rand = GetRand(2);
					switch (rand)
					{
					case 0:
						obj_enemy->SetType(Jan_Type::ROCK);
						break;
					case 1:
						obj_enemy->SetType(Jan_Type::SCISSORS);
						break;
					case 2:
						obj_enemy->SetType(Jan_Type::PAPER);
						break;
					}
					
				}
			}

		}
	}

	for (int a = 0; a < 3; a++)
	{
		if (mob[a]->GetHP() >= 0)
		{
			//playerじゃん撃とmobenemyの当たり判定
			for (int i = 0; i < JANGEKI_MAX; i++)
			{
				if (player_jangeki[i] == nullptr) break;         //じゃん撃がない時は処理しない

				//じゃん撃との当たり判定
				if (mob[a]->Hit_Jangeki(player_jangeki[i]) == true)
				{
					Jan_Type mobenemy_type = mob[a]->GetType();            //敵の属性
					Jan_Type jangeki_type = player_jangeki[i]->GetType();  //当たったじゃん撃の属性

					//不利属性のみダメージが入る
					switch (mobenemy_type)
					{
					case Jan_Type::ROCK:                           //敵の属性　グー

						//パーのじゃん撃のみ有効
						if (jangeki_type == Jan_Type::PAPER)
						{
							mob[a]->ReceiveDamage(30);     //ダメージが入る
							obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
							i--;
						}

						break;

					case Jan_Type::SCISSORS:                       //敵の属性　チョキ

						//グーのじゃん撃のみ有効
						if (jangeki_type == Jan_Type::ROCK)
						{
							mob[a]->ReceiveDamage(30);     //ダメージが入る
							obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
							i--;
						}
						break;

					case Jan_Type::PAPER:                          //敵の属性　パー

						//チョキのじゃん撃のみ有効
						if (jangeki_type == Jan_Type::SCISSORS)
						{
							mob[a]->ReceiveDamage(30);     //ダメージが入る
							obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
							i--;
						}
						break;

					default:
						break;
					}
				}
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
			obj_player->ReceiveDamage(30);

			//あたったじゃん撃を削除
			obj_enemy->DeleteJangeki(i);
			i--;
		}
	}

	for (int a = 0; a < 3; a++)
	{
		Jangeki_Base** enemy_jangeki = mobenemy_jangek[a];
		if (mob[a]->GetHP() >= 0)
		{
			//mobenemyじゃん撃とplayerの当たり判定
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
					mob[a]->DeleteJangeki(i);
					i--;
				}
			}
		}
	}



	HitCtrl_Floor(obj_player, STAGE_05_FLOOR);     // player　床・壁判定
	HitCtrl_Floor(obj_enemy, STAGE_05_FLOOR);      // 敵　　　床・壁判定


}


//描画
void Scene_Stage05::Draw() const
{
	DrawRotaGraph(640, 240, 2.0f, 0, Back_image, TRUE);

	//接触じゃんけんでない時
	if (GetJanState() == Jan_State::BEFORE)
	{

		obj_player->Draw();  //プレイヤー描画
		obj_enemy->Draw();   //敵キャラ描画
		
		for (int i = 0; i < 3; i++)
		{
			if (mob[i]->GetHP() >= 0)
			{
				mob[i]->Draw();
			}
		}
		

		//床・壁描画
		for (int i = 0; i < STAGE_05_FLOOR; i++)
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
	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());
	DrawString(640, 360, "Stage05", 0xffffff);
}



//じゃんけん描画
void Scene_Stage05::Draw_Janken() const
{
	obj_janken->Draw();
}

//シーンの変更
AbstractScene* Scene_Stage05::ChangeScene()
{
	//"Debug_Manager.h" の #define DEBUG_OFF_05 をコメントアウトすると開発モード
#ifdef DEBUG_OFF_05

	//敵のHPが0以下
	if (obj_enemy->GetHP() < 0)
	{
		//ゲームクリアシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameClearScene(6));
	}

	//プレイヤーのHPが0以下
	if (obj_player->GetHP() < 0)
	{
		//ゲームオーバーシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameOverScene(5));
	}

#endif // DEBUG_OFF_05

	return this;
}


//じゃんけん終了後の挙動（プレイヤー勝ち）
void Scene_Stage05::AfterJanken_WIN()
{
	obj_player->SetX(100);
}

//じゃんけん終了後の挙動（プレイヤー負け）
void Scene_Stage05::AfterJanken_LOSE()
{
	obj_player->SetX(100);
}