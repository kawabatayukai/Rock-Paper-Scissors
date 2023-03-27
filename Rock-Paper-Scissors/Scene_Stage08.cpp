#include "Scene_Stage08.h"
#include"Scene_GameOver.h"
#include"Scene_GameClear.h"
#include"KeyManager.h"
#include"DxLib.h"
#define PI    3.1415926535897932384626433832795f

//デバッグモード
#include"Debug_Manager.h"

//コンストラクタ
Scene_Stage08::Scene_Stage08(const Player* player)
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
	obj_enemy = new Enemy_08(1200, 360, Jan_Type::SCISSORS);

	//床・壁の用意
	Init_Floor(STAGE_08_FLOOR);

	//一つずつ生成  STAGE_08_FLOOR 個分
	obj_floor[0] = new Floor(0, 700, 1280, 20,0x00ff00);        //床
	obj_floor[1] = new Floor(0, -300, 20, 1720);           //壁（左）
	obj_floor[2] = new Floor(1260, -300, 20, 1720);           //壁（右）
	obj_floor[3] = new Floor(211, 590, 100, 5, 0x00ff00);      //足場　下1
	obj_floor[4] = new Floor(465, 590, 105, 5, 0x00ff00);      //足場　下2
	obj_floor[5] = new Floor(717, 590, 107, 5, 0x00ff00);      //足場　下3
	obj_floor[6] = new Floor(973, 590, 110, 5, 0x00ff00);      //足場　下4
	obj_floor[7] = new Floor(307, 470, 160, 5, 0x00ff00);      //足場　右下
	obj_floor[8] = new Floor(565, 470, 153, 5, 0x00ff00);      //足場　右下
	obj_floor[9] = new Floor(820, 470, 153, 5, 0x00ff00);      //足場　右下
	obj_floor[10] = new Floor(465, 470, 5, 120, 0x00ff00);      //足場　右下
	obj_floor[11] = new Floor(306, 470, 5, 120, 0x00ff00);      //足場　右下
	obj_floor[12] = new Floor(717, 470,  5,120, 0x00ff00);      //足場　右下
	obj_floor[13] = new Floor(973, 470,  5,120, 0x00ff00);      //足場　右下
	obj_floor[14] = new Floor(565, 475, 5, 120, 0x00ff00);      //足場　右下
	obj_floor[15] = new Floor(820, 475, 5, 120, 0x00ff00);      //足場　右下

	obj_floor[16] = new Floor(311, 290, 100, 5, 0x00ff00);      //足場　右下
	obj_floor[17] = new Floor(565, 290, 105, 5, 0x00ff00);      //足場　右下
	obj_floor[18] = new Floor(817, 290, 108, 5, 0x00ff00);      //足場　右下
	obj_floor[19] = new Floor(1073, 290, 187, 5,0x00ff00);      //足場　右下
	obj_floor[20] = new Floor(407, 170, 160, 5, 0x00ff00);      //足場　右下
	obj_floor[21] = new Floor(665, 170, 153, 5, 0x00ff00);      //足場　右下
	obj_floor[22] = new Floor(920, 170, 153, 5, 0x00ff00);      //足場　右下
	obj_floor[23] = new Floor(565, 170, 5, 120, 0x00ff00);      //足場　右下
	obj_floor[24] = new Floor(406, 170, 5, 120, 0x00ff00);      //足場　右下
	obj_floor[25] = new Floor(817, 170, 5, 120, 0x00ff00);      //足場　右下
	obj_floor[26] = new Floor(920, 175, 5, 120, 0x00ff00);      //足場　右下
	obj_floor[27] = new Floor(665, 175, 5, 120, 0x00ff00);      //足場　右下
	obj_floor[28] = new Floor(179, 155, 5, 120, 0x00ff00);      //足場　右下
	obj_floor[29] = new Floor(64,  275, 120, 5, 0x00ff00);      //足場　右下

	Back_image = LoadGraph("images/stage08/Stage08_1.jpg",TRUE);
}

//デストラクタ
Scene_Stage08::~Scene_Stage08()
{
}

//更新
void Scene_Stage08::Update()
{
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
					obj_enemy->ReceiveDamage(5);     //ダメージが入る
					obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
					i--;
				}
					
				break;

			case Jan_Type::SCISSORS:                       //敵の属性　チョキ

				//グーのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::ROCK)
				{
					obj_enemy->ReceiveDamage(5);     //ダメージが入る
					obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
					i--;
				}
				break;

			case Jan_Type::PAPER:                          //敵の属性　パー

				//チョキのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::SCISSORS)
				{
					obj_enemy->ReceiveDamage(5);     //ダメージが入る
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
			obj_player->ReceiveDamage(30);

			//あたったじゃん撃を削除
			obj_enemy->DeleteJangeki(i);
			i--;
		}
	}


	HitCtrl_Floor(obj_player, STAGE_08_FLOOR);     // player　床・壁判定
	HitCtrl_Floor(obj_enemy, STAGE_08_FLOOR);      // 敵　　　床・壁判定


}


//描画
void Scene_Stage08::Draw() const
{
	DrawRotaGraph(640, 360, 1.f, 0, Back_image,TRUE);
	//接触じゃんけんでない時
	if (GetJanState() == Jan_State::BEFORE)
	{

		obj_player->Draw();  //プレイヤー描画
		obj_enemy->Draw();   //敵キャラ描画

		//床・壁描画
		for (int i = 0; i < STAGE_08_FLOOR; i++)
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

	//DrawString(640, 360, "Stage08", 0xffffff);
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
	if (obj_enemy->GetHP() < 0)
	{
		//ゲームクリアシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameClearScene(9));
	}

	//プレイヤーのHPが0以下
	if (obj_player->GetHP() < 0)
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
}

//じゃんけん終了後の挙動（プレイヤー負け）
void Scene_Stage08::AfterJanken_LOSE()
{
	obj_player->SetX(100);
}