#include "Scene_Stage04.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"Scene_GameOver.h"
#include"Scene_GameClear.h"

//デバッグモード
#include"Debug_Manager.h"

//コンストラクタ
Scene_Stage04::Scene_Stage04(const Player* player)
{
	back_image = LoadGraph("images/Stage4/Stage_Image2.png");

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
	obj_enemy = new Enemy_04(1100, 550, Jan_Type::SCISSORS);

	//床・壁の用意
	Init_Floor(STAGE_04_FLOOR);

	//一つずつ生成  STAGE_04_FLOOR 個分
	obj_floor[0] = new Floor(0, 700, 1280, 20, 0x493759);		//床
	obj_floor[1] = new Floor(0, 0, 20, 1720, 0x493759);			//壁（左）
	obj_floor[2] = new Floor(1260, 0, 20, 1720, 0x493759);		//壁（右）
	obj_floor[3] = new Floor(300, 500, 200, 15, 0x493759);		//足場(下横)
	obj_floor[4] = new Floor(600, 350, 150, 15, 0x493759);		//足場(真ん中横)
	obj_floor[5] = new Floor(400, 180, 150, 15, 0x493759);		//足場(上横)
	obj_floor[6] = new Floor(390, 425, 15, 170, 0x493759);		//足場(下縦)
	obj_floor[7] = new Floor(667, 295, 15, 130, 0x493759);		//足場(真ん中縦)
	obj_floor[8] = new Floor(467, 125, 15, 130, 0x493759);		//足場(上縦)
	obj_floor[9] = new Floor(0, 320, 100, 10, 0x493759);		//棘?@
	obj_floor[10] = new Floor(0, 540, 70, 10, 0x493759);		//棘?A
	obj_floor[11] = new Floor(300, 0, 10, 80, 0x493759);		//棘?B
	obj_floor[12] = new Floor(900, 0, 10, 130, 0x493759);		//棘?C
	obj_floor[13] = new Floor(1100, 0, 10, 40, 0x493759);		//棘?D
	obj_floor[14] = new Floor(1180, 150, 100, 10, 0x493759);	//棘?E
	obj_floor[15] = new Floor(1230, 400, 30, 10, 0x493759);		//棘?F
	obj_floor[16] = new Floor(1000, 650, 10, 70, 0x493759);		//棘?G
	obj_floor[17] = new Floor(700, 680, 10, 40, 0x493759);		//棘?H
}

//デストラクタ
Scene_Stage04::~Scene_Stage04()
{
}

//更新
void Scene_Stage04::Update()
{
	//接触じゃんけんでない時
	if (janken_flag == false)
	{
		obj_player->Update();    // プレイヤー更新・操作可能
		obj_enemy->Update();     //敵キャラ更新・内部処理



		//敵とプレイヤーの当たり判定  　ここで"接触じゃんけん"
		if (obj_enemy->Hit_Character(obj_player) == true)
		{
			//敵が出す手をランダムに決める　　　（ランダムなint型の値(0〜2)を Jan_Type型に変換）
			Jan_Type enemy_janken = static_cast<Jan_Type> (GetRand(2));

			//じゃんけん用オブジェクト生成
			obj_janken = new Janken(enemy_janken);


			//接触じゃんけん開始
			janken_flag = true;

		}
	}
	else
	{
		//接触時じゃんけんの処理を実行
		Update_Janken();
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


	HitCtrl_Floor(obj_player, STAGE_04_FLOOR);     // player　床・壁判定
	HitCtrl_Floor(obj_enemy, STAGE_04_FLOOR);      // 敵　　　床・壁判定


}


//描画
void Scene_Stage04::Draw() const
{
	//ステージ背景描画
	DrawRotaGraph(640, 360, 1, 0, back_image, FALSE);

	DrawUI(obj_enemy->GetType(),obj_enemy->GetHP());

	//接触じゃんけんでない時
	if (janken_flag == false)
	{

		obj_player->Draw();  //プレイヤー描画
		obj_enemy->Draw();   //敵キャラ描画

		//床・壁描画
		for (int i = 0; i < STAGE_04_FLOOR; i++)
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

	//DrawString(640, 360, "Stage04", 0xffffff);
}

//じゃんけん更新・内部処理
void Scene_Stage04::Update_Janken()
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
void Scene_Stage04::Draw_Janken() const
{
	obj_janken->Draw();
}

//シーンの変更
AbstractScene* Scene_Stage04::ChangeScene()
{
	//"Debug_Manager.h" の #define DEBUG_OFF_04 をコメントアウトすると開発モード
#ifdef DEBUG_OFF_04

	//敵のHPが0以下
	if (obj_enemy->GetHP() < 0)
	{
		//ゲームクリアシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameClearScene(5));
	}

	//プレイヤーのHPが0以下
	if (obj_player->GetHP() < 0)
	{
		//ゲームオーバーシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameOverScene(4));
	}

#endif // DEBUG_OFF_04

	return this;
}