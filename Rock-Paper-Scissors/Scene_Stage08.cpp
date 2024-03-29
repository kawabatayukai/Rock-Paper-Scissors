#include "Scene_Stage08.h"
#include"Scene_GameOver.h"
#include"Scene_GameClear.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"Enemy_Cannon.h"
#include"GameData.h"
#include"Item_stage08.h"
#include"SoundSystem.h"
#define PI    3.1415926535897932384626433832795f

//デバッグモード
#include"Debug_Manager.h"

//コンストラクタ
Scene_Stage08::Scene_Stage08(const Player* player) : damage(5)
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
	obj_enemy = new Enemy_08(1170, 360, Jan_Type::SCISSORS);
	obj_cannon = new Enemy_Cannon(120, 360, Jan_Type::SCISSORS);
	cannon = new Enemy_Cannon * [2];
	
	for (int a = 0; a < 2; a++)cannon[a] = nullptr;

	cannon[0] = new Enemy_Cannon(1210, 100, Jan_Type::ROCK, 1);
	cannon[1] = new Enemy_Cannon(110, 100, Jan_Type::ROCK, 2);

	//床・壁の用意
	Init_Floor(STAGE_08_FLOOR);
	GameData::Set_TimeLimit();
	//一つずつ生成  STAGE_08_FLOOR 個分
	obj_floor[0] = new Floor(0, 700, 1280, 20,0x00ff00);        //床
	obj_floor[1] = new Floor(0, -300, 20, 1720);           //壁（左）
	obj_floor[2] = new Floor(1260, -300, 20, 1720);           //壁（右）
	obj_floor[3] = new Floor(0, -350 + 20, 1280, 0,0x000000);      //足場　下1
	obj_floor[4] = new Floor(465, 590 , 105, 10,0x00ff00);      //足場　下2
	obj_floor[5] = new Floor(717, 590 , 107, 10,0x00ff00);      //足場　下3
	obj_floor[6] = new Floor(-9999, -9999, 110, 10,0x00ff00);      //足場　下4
	obj_floor[7] = new Floor(307, 470 + 20, 160, 10,0x00ff00);      //足場　右下
	obj_floor[8] = new Floor(565, 470 + 20, 153, 10,0x00ff00);      //足場　右下
	obj_floor[9] = new Floor(820, 470 + 20, 153, 10,0x00ff00);      //足場　右下
	obj_floor[10] = new Floor(465, 470 + 20, 10, 100, 0x00ff00);      //足場　右下
	obj_floor[11] = new Floor(306, 470 + 20, 10, 100, 0x00ff00);      //足場　右下
	obj_floor[12] = new Floor(717, 470 + 20,  10,100, 0x00ff00);      //足場　右下
	obj_floor[13] = new Floor(973, 470 + 20,  10,100, 0x00ff00);      //足場　右下
	obj_floor[14] = new Floor(565, 475 + 20, 10, 100, 0x00ff00);      //足場　右下



	obj_floor[15] = new Floor(820, 475 + 20, 10, 100, 0x00ff00);      //足場　右下
	obj_floor[16] = new Floor(311, 290 + 20, 100, 10,0x00ff00);      //足場　右下
	obj_floor[17] = new Floor(565, 290 + 20, 105, 10,0x00ff00);      //足場　右下
	obj_floor[18] = new Floor(817, 290 + 20, 108, 10,0x00ff00);      //足場　右下
	obj_floor[19] = new Floor(1073, 290 + 20, 187, 10,0x00ff00);      //足場　右下
	obj_floor[20] = new Floor(407, 170 + 20, 160, 10,0x00ff00);      //足場　右下
	obj_floor[21] = new Floor(665, 170 + 20, 153, 10,0x00ff00);      //足場　右下
	obj_floor[22] = new Floor(920, 170 + 20, 153, 10,0x00ff00);      //足場　右下
	obj_floor[23] = new Floor(565, 170 + 20, 10, 120, 0x00ff00);      //足場　右下
	obj_floor[24] = new Floor(406, 170 + 20, 10, 120, 0x00ff00);      //足場　右下
	obj_floor[25] = new Floor(817, 170 + 20, 10, 120, 0x00ff00);      //足場　右下
	obj_floor[26] = new Floor(920, 175 + 20, 10, 120, 0x00ff00);      //足場　右下
	obj_floor[27] = new Floor(665, 175 + 20, 10, 120, 0x00ff00);      //足場　右下
	obj_floor[28] = new Floor(179, 155 + 20, 10, 120, 0x00ff00);      //足場　右下
	obj_floor[29] = new Floor(64,  275+20, 120, 10,0x00ff00);      //足場　右下

	Back_image = LoadGraph("images/stage08/Stage08_1.jpg", TRUE);

	Item = new Jangeki_Base * [5];
	for (int i = 0; i < 5; i++) Item[i] = nullptr;
	//アイテムの位置
	//生成
	Item[0] = new Item_st8(620, 260, 30);
	Item[1] = new Item_st8(60, 200, 30);
	Item[2] = new Item_st8(490, 260, 30);
	Item[3] = new Item_st8(645, 550, 30);
	Item[4] = new Item_st8(1190, 500, 30);
	
	////BGMロード
	bgm = LoadSoundMem("Sound/Stege8/technophobia.mp3");
	ItemSound = LoadSoundMem("Sound/Stege8/stage8_Item.mp3");
}

//デストラクタ
Scene_Stage08::~Scene_Stage08()
{
	StopSoundMem(bgm);
}

//更新
void Scene_Stage08::Update()
{
	//BGM再生
	if (CheckSoundMem(bgm) == 0) PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Update();    // プレイヤー更新・操作可能
		obj_enemy->Update();     //敵キャラ更新・内部処理
		for (int a = 0; a < 2; a++)
		{
			cannon[a]->Update();
			cannon[a]->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());	//プレイヤーの座標を取得
		}	

		if(Player_Janwin==true)
		{
			count++;
			if (count % 120 == 0)Player_Janwin = false;
		}
			
		if (item_ui == true)
		{
			count++;
			if (count % 120 == 0)item_ui = false;
		}

		//cannon[a]->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());	//プレイヤーの座標を取得
		GameData::Time_Update();
	}

	//接触じゃんけん処理
	Touch_Janken(obj_enemy, this, 8);
	Effect_Update_HitJangeki(obj_enemy);

	//playerのじゃん撃をとってくる
	Jangeki_Base** player_jangeki = obj_player->GetJangeki();

	//enemyのじゃん撃をとってくる
	Jangeki_Base** enemy_jangeki = obj_enemy->GetJangeki();
	
	//Jangeki_Base** cannon_jangeki = obj_cannon->GetJangeki();


	Jangeki_Base** cannon_jangeki[2];
	cannon_jangeki[0] = cannon[0]->GetJangeki();
	cannon_jangeki[1] = cannon[1]->GetJangeki();

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
	
	//じゃん撃同士
	for (int a = 0; a < 2; a++)
	{
		Jangeki_Base** enemy_jangeki = cannon_jangeki[a];

		//じゃん撃同士の当たり判定（プレイヤーじゃん撃目線）
		for (int p_count = 0; p_count < JANGEKI_MAX; p_count++)
		{
			if (player_jangeki[p_count] == nullptr) break;         //じゃん撃がない時は処理しない

			bool delete_player = false;       //プレイヤーじゃん撃削除フラグ　true:削除　false:削除しない

			for (int e_count = 0; e_count < JANGEKI_MAX; e_count++)
			{
				if (player_jangeki[e_count] == nullptr) break;         //じゃん撃がない時は処理しない

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
						cannon[a]->DeleteJangeki(e_count); 
						e_count--;


						break;

					case 2:             //あいこ

						//player側のじゃん撃を削除
						delete_player = true;

						//enemy側のじゃん撃を削除
						cannon[a] ->DeleteJangeki(e_count);
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


	for (int i = 0; i < 5; i++)
	{
		if (Item[i] == nullptr) break;

		Item[i]->Update();
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
					obj_enemy->ReceiveDamage(damage);     //元のダメージ
					obj_enemy->Change_JanType();      //属性が変わる
					obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
					i--;
				}
					
				break;

			case Jan_Type::SCISSORS:                       //敵の属性　チョキ

				//グーのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::ROCK)
				{
					obj_enemy->ReceiveDamage(damage);     //元のダメージ
					obj_enemy->Change_JanType();      //属性が変わる
					obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
					i--;
				}
				break;

			case Jan_Type::PAPER:                          //敵の属性　パー

				//チョキのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::SCISSORS)
				{
					obj_enemy->ReceiveDamage(damage);     //元のダメージ
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

	for (int a = 0; a < 2; a++)
	{
		Jangeki_Base** enemy_jangeki = cannon_jangeki[a];

		//enemyじゃん撃とplayerの当たり判定
		for (int i = 0; i < JANGEKI_MAX; i++)
		{
			//じゃん撃がない時は処理しない
			if (enemy_jangeki[i] == nullptr) break;

			//じゃん撃との当たり判定
			if (obj_player->Hit_Jangeki(enemy_jangeki[i]) == true)
			{
				//ダメージを受ける（プレイヤー）
				obj_player->ReceiveDamage(3);

				//あたったじゃん撃を削除
				cannon[a]->DeleteJangeki(i);
				i--;
			}
		}
	}

	//アイテムとプレイヤー当たり判定
	for (int i = 0; i < 5; i++)
	{
		if (Item[i] == nullptr) break;

		if (obj_player->Hit_Jangeki(Item[i]) == true)
		{
			PlaySoundMem(ItemSound,DX_PLAYTYPE_BACK);
			//当たった時
			damage += 5;
			item_ui = true;

			delete Item[i];
			Item[i] = nullptr;

			for (int j = i; j < 5 - 1; j++)
			{
				if (Item[j + 1] == nullptr) break;
				Item[j] = Item[j + 1];
				Item[j + 1] = nullptr;
			}
			i--;
			
		}


	}


	HitCtrl_Floor(obj_player, STAGE_08_FLOOR);     // player　床・壁判定
	HitCtrl_Floor(obj_enemy, STAGE_08_FLOOR);      // 敵　　　床・壁判定


}


//描画
void Scene_Stage08::Draw() const
{	
	
	DrawUI_ON_Enemy(obj_enemy);
	DrawRotaGraph(640, 360, 1.f, 0, Back_image,TRUE);

		//HP表示
	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());
	DrawUI_ON_Enemy(obj_enemy);

	//接触じゃんけんでない時
	if (GetJanState() == Jan_State::START || GetJanState() == Jan_State::BEFORE)
	{

		obj_player->Draw();  //プレイヤー描画
		obj_enemy->Draw();   //敵キャラ描画
		cannon[0]->Draw();
		cannon[1]->Draw();

		//床・壁描画
		for (int i = 0; i < STAGE_08_FLOOR; i++)
		{
			if (obj_floor[i] == nullptr) break;
			obj_floor[i]->Draw();
		}

		//item描画
		for (int i = 0; i < 5; i++)
		{
			if (Item[i] == nullptr) break;

			Item[i]->Draw();
		}

		if (item_ui == true)
		{
			float p_x = obj_player->GetX();
			float p_y = obj_player->GetY();
			//stage8_Item.mp3
			DrawString(p_x, p_y - 55, "攻撃力UP↑", 0xff0000);
		}


		//じゃんけん負けた時
		if (Player_Janwin == true)
		{
			float p_x = obj_player->GetX();
			float p_y = obj_player->GetY();

			DrawString(p_x, p_y - 55, "攻撃力UP↑", 0xff0000);
		}


		//接触した瞬間の演出
		if (GetJanState() == Jan_State::START) Draw_JankenStart();
	}
	else
	{
		//接触時じゃんけん描画
		Draw_Janken();
	}



	//DrawString(640, 360, "Stage08", 0xffffff);
	Effect_Draw_HitJangeki();
}


//じゃんけん描画
void Scene_Stage08::Draw_Janken() const
{
	obj_janken->Draw();
}

//シーンの変更
AbstractScene* Scene_Stage08::ChangeScene()
{
	//"Debug_Manager.h" の #define DEBUG_OFF_08 をコメントアウトすると開発モード
#ifdef DEBUG_OFF_08

	//敵のHPが0以下
	if (IsEnd_DeathEnemy() == true)
	{
		//ゲームクリアシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameClearScene(5));
	}

	//プレイヤーのHPが0以下
	if (obj_player->IsDeathPlayer() == true)
	{
		//ゲームオーバーシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameOverScene(8));
	}

#endif // DEBUG_OFF_08

	return this;
}

//じゃんけん終了後の挙動（プレイヤー勝ち）
void Scene_Stage08::AfterJanken_WIN()
{
	obj_player->SetX(100);
	damage += 2;
	Player_Janwin = true;
}

//じゃんけん終了後の挙動（プレイヤー負け）
void Scene_Stage08::AfterJanken_LOSE()
{
	obj_player->SetX(100);
	obj_enemy->MAX();
	
}