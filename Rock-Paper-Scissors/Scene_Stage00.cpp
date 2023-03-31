#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_Stage00.h"
#include"Scene_GameOver.h"
#include"Scene_GameClear.h"
#include"Janken.h"

//デバッグモード
#include"Debug_Manager.h"

//コンストラクタ
Scene_Stage00::Scene_Stage00(const Player* player)
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
	obj_enemy = new Enemy_00(1200, 360, Jan_Type::SCISSORS);

	//床・壁の用意
	Init_Floor(STAGE_00_FLOOR);

	//床、壁を　　　#define 　STAGE_00_FLOOR 　個分生成　　
	//
	// new Floor(ｘ座標,ｙ座標,　幅,　高さ) を設定 
	//
	// new Floor(ｘ座標,ｙ座標,　幅,　高さ,  色(16進数))         色を指定
	//
	// new Floor("images/画像名",  ｘ座標, ｙ座標,　幅,　高さ)　 画像を設定
	//
	// (画像使用の例) new Floor("images/Jangeki_Test.png",200, 200, 100, 50);

	obj_floor[0] = new Floor(50, 700, 1280, 20);        //床
	obj_floor[1] = new Floor(0, 0, 20, 1720);          //壁（左）
	obj_floor[2] = new Floor(1260,0,20,1720);          //壁（右）
	obj_floor[3] = new Floor(1000, 100, 120, 50);      //足場
	obj_floor[4] = new Floor(40, 500, 500, 60);        //足場
	obj_floor[5] = new Floor(100, 300, 100, 50);
	obj_floor[6] = new Floor(200, 100, 50,50);//イメージ追加

	//テスト
	setumei = LoadGraph("images/Setumei.png");

	//画像一覧
	int players[10];
	LoadDivGraph("images/ワンパンマンALL画像腕無し.png", 10, 5, 2, 100, 100, players);

	player_image = players[0];
	player_all = LoadGraph("images/ワンパンマンALL画像腕無し.png");

	enemy_02 = LoadGraph("images/stage02/ex.png");
	enemy_03 = LoadGraph("images/stage03/stage03gard.png");
	enemy_04 = LoadGraph("images/Stage4/ステージ4_ボス.png");
	enemy_05 = LoadGraph("images/stage05/Stage5_Enemy_NoMove_Left.png");
	enemy_06 = LoadGraph("images/tyokitest.png");
	enemy_07 = LoadGraph("images/tyokitest.png");
	enemy_08 = LoadGraph("images/stage08/Stage8_image100.png");
	enemy_09 = LoadGraph("images/stage09/Stage9_100.png");
	enemy_10 = LoadGraph("images/tyokitest.png");
}

//デストラクタ
Scene_Stage00::~Scene_Stage00()
{
}

//更新
void Scene_Stage00::Update()
{
	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::BEFORE)
	{
		//obj_player->Update();    // プレイヤー更新・操作可能
		//obj_enemy->Update();     //敵キャラ更新・内部処理

		////プレイヤーの座標を取得
		//obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());
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
				int result = player_jangeki[p_count]->CheckAdvantage( enemy_jangeki[e_count] );

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


	HitCtrl_Floor(obj_player, STAGE_00_FLOOR);     // player　床・壁判定
	HitCtrl_Floor(obj_enemy, STAGE_00_FLOOR);      // 敵　　　床・壁判定


}

//描画
void Scene_Stage00::Draw() const
{
	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::BEFORE)
	{
		//obj_player->Draw();  //プレイヤー描画
		//obj_enemy->Draw();   //敵キャラ描画

		////床・壁描画
		//for (int i = 0; i < STAGE_00_FLOOR; i++)
		//{
		//	if (obj_floor[i] == nullptr) break;
		//	obj_floor[i]->Draw();
		//}

		DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);

		//すべてのキャラを描画
		DrawGraph(50, 0, player_image, TRUE);
		DrawGraph(200, 0, enemy_02, TRUE);
		DrawGraph(350, 0, enemy_03, TRUE);
		DrawGraph(500, 0, enemy_04, TRUE);
		DrawGraph(650, 0, enemy_05, TRUE);
		DrawGraph(50, 150, enemy_06, TRUE);
		DrawGraph(200, 150, enemy_07, TRUE);
		DrawGraph(350, 150, enemy_08, TRUE);
		DrawGraph(500, 150, enemy_09, TRUE);
		DrawGraph(650, 150, enemy_10, TRUE);

		DrawGraph(50, 350, player_all, TRUE);
	}
	else
	{
		//接触時じゃんけん描画
		Draw_Janken();
	}

	////テスト
	//DrawGraph(20, 0, setumei, TRUE);

}


//じゃんけん描画
void Scene_Stage00::Draw_Janken() const
{
	obj_janken->Draw();
}

//シーンの変更
AbstractScene* Scene_Stage00::ChangeScene()
{
#ifdef DEBUG_OFF_00

	//敵のHPが0以下
	if (obj_enemy->GetHP() < 0)
	{
		//ゲームクリアシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameClearScene(1));
	}

	//プレイヤーのHPが0以下
	if (obj_player->GetHP() < 0)
	{
		//ゲームオーバーシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameOverScene(0));
	}

#endif // _DEBUG_MODE_00




	return this;   //更新なし
}
