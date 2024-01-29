#include "Scene_Stage03.h"
#include"KeyManager.h"
#include"DxLib.h"
#include "Scene_GameClear.h"
#include "Scene_GameOver.h"
#include "Stage_Base.h"
#include "GameData.h"
#include"SoundSystem.h"


//デバッグモード
#include"Debug_Manager.h"

//コンストラクタ
Scene_Stage03::Scene_Stage03(const Player* player)
{
	stage = LoadGraph("images/stage03/stage03back.png");
	GroundImages = LoadGraph("images/stage03/GroundImages.png");
	BlockImages = LoadGraph("images/stage03/BlockImages.png");
	

	//プレイヤー情報が渡されていれば
	if (player != nullptr)
	{
		//情報を引き継いだプレイヤーを生成
		obj_player = new Player(*player);
	}
	else
	{
		//プレイヤーを生成
		obj_player = new Player(100, 640);
	}

	//敵を生成							//敵の属性チョキ
	obj_enemy = new Enemy_03(950, 650, Jan_Type::SCISSORS);//敵の位置

	//床・壁の用意
	Init_Floor(STAGE_03_FLOOR);

	//一つずつ生成  STAGE_03_FLOOR 個分
	obj_floor[0] = new Floor("images/stage03/GroundImages.png", 0, 700, 1280, 20);      //床, GetColor(240, 230, 140)
	obj_floor[1] = new Floor("images/stage03/GroundImagesTate.png", 0, -100, 20, 1260);        //壁（左）, GetColor(240, 230, 140)
	obj_floor[2] = new Floor("images/stage03/GroundImagesTate.png", 1260, -100, 20, 1260);     //壁（右）, GetColor(240, 230, 140)

	//右から順に
	obj_floor[3] = new Floor("images/stage03/BlockImages.png", 1130, 340, 95, 1);//足場1//130,GetColor(193, 107, 68)
	obj_floor[4] = new Floor("images/stage03/BlockImages.png", 1130, 500, 95, 1);//足場2//130,	GetColor(193, 107, 68)
	obj_floor[5] = new Floor("images/stage03/BlockImages.png", 920, 205, 95, 1);//足場3, GetColor(193, 107, 68)
	obj_floor[6] = new Floor("images/stage03/BlockImages.png", 770, 150, 95, 1);//足場4//130, GetColor(193, 107, 68)
	obj_floor[7] = new Floor("images/stage03/BlockImages.png", 575, 205, 95, 1);//足場5//100, GetColor(193, 107, 68)
	obj_floor[8] = new Floor("images/stage03/BlockImages.png", 390, 150, 95, 1);//足場6//130, GetColor(193, 107, 68)
	obj_floor[9] = new Floor("images/stage03/BlockImages.png", 240, 205, 95, 1);//足場7//130, GetColor(193, 107, 68)
	obj_floor[10] = new Floor("images/stage03/BlockImages.png", 60, 340, 95, 1);//足場8//100, GetColor(193, 107, 68)
	obj_floor[11] = new Floor("images/stage03/BlockImages.png", 60, 500, 95, 1);//足場9//130, GetColor(193, 107, 68)


	
	//obj_floor[12] = new Floor("images/stage03/BlockImages.png", 970, 405, 95, 10);//足場3, GetColor(193, 107, 68)
	//obj_floor[12] = new Floor("images/stage03/BlockImages.png", 790, 360, 95, 10);//足場4//130, GetColor(193, 107, 68)
	//obj_floor[13] = new Floor("images/stage03/BlockImages.png", 595, 425, 95, 10);//足場5//100, GetColor(193, 107, 68)
	//obj_floor[14] = new Floor("images/stage03/BlockImages.png", 410, 360, 95, 10);//足場6//130, GetColor(193, 107, 68)
	//obj_floor[16] = new Floor("images/stage03/BlockImages.png", 210, 405, 95, 10);//足場7//130, GetColor(193, 107, 68)

	//制限時間をセット
	GameData::Set_TimeLimit(10860); //3分　//2分 ←　7200 % 3600

	//BGMロード
	st03_bgm = LoadSoundMem("Sound/st03/St03BGM.wav");
}

//デストラクタ
Scene_Stage03::~Scene_Stage03()
{
	StopSoundMem(st03_bgm);
}

//更新
void Scene_Stage03::Update()
{
	//BGMを鳴らす
	if (CheckSoundMem(st03_bgm) == 0) PlaySoundMem(st03_bgm, DX_PLAYTYPE_LOOP);


	//接触じゃんけん開始前
	if (GetJanState()  == Jan_State::BEFORE)
	{
		obj_player->Update();    // プレイヤー更新・操作可能
		obj_enemy->Update();     //敵キャラ更新・内部処理
		obj_enemy->ChangeDir(obj_player->GetX());//プレイヤーがx < 640だったらエネミーの弾の向きを変える
		obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());	//プレイヤーの座標を取得
		
		//時間をカウント
		GameData::Time_Update();
	}

	
	
	//接触じゃんけん処理
	Touch_Janken(obj_enemy, this, 3);

	//走るSE停止
	StopSoundMem(obj_enemy->GetRunSE());
	//歩くSE停止
	StopSoundMem(obj_enemy->GetWalkSE());

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
			case Jan_Type::ROCK:           //敵の属性　グー

				//パーのじゃん撃のみ有効
				if (jangeki_type == Jan_Type::PAPER)
				{

					//HP86以上の時
					if (obj_enemy->GetHP() >= 86) {


						if(obj_enemy->GetWaitTime() > 0 || obj_enemy->GetWaitTime() < 200){

							SheeldEnduranse = 27;				//3 - じゃんけん負けた時 1
							obj_enemy->ReceiveDamage(30 - SheeldEnduranse - EnemyCutDamege); //100 //軽減ダメージが入る

						}

					}

					else if (obj_enemy->GetHP() <= 85 && obj_enemy->GetHP() >= 71) {


						if(obj_enemy->GetWaitTime() > 0 || obj_enemy->GetWaitTime() < 200) {

							SheeldEnduranse = 24;			//6 - じゃんけん負けた時 3
							obj_enemy->ReceiveDamage(30 - SheeldEnduranse- EnemyCutDamege); //軽減ダメージが入る
							
						}

						SoundSystem::PlaySE(SE::ENEMY_SLIGHTLYBROKEN);
					
					}
					else if (obj_enemy->GetHP() <= 70 && obj_enemy->GetHP() >= 56) {
					
						if(obj_enemy->GetWaitTime() > 0 || obj_enemy->GetWaitTime() < 200){

							SheeldEnduranse = 21;			//9 - じゃんけん負けた時 5
							obj_enemy->ReceiveDamage(30 - SheeldEnduranse- EnemyCutDamege); //軽減ダメージが入る

						}

						SoundSystem::PlaySE(SE::ENEMY_SLIGHTLYBROKEN);
						
					}
					else if (obj_enemy->GetHP() <= 55 && obj_enemy->GetHP() >= 46) {

			
						if(obj_enemy->GetWaitTime() > 0 ||  obj_enemy->GetWaitTime() < 200){

							
							SheeldEnduranse = 18;				//12 - じゃんけん負けた時 6
							obj_enemy->ReceiveDamage(30 - SheeldEnduranse - EnemyCutDamege); //軽減ダメージが入る
						
						}

						SoundSystem::PlaySE(SE::ENEMY_SHIELDBROKEN);
					}
					else if (obj_enemy->GetHP() <= 45) {


						if (obj_enemy->GetWaitTime() > 0 || obj_enemy->GetWaitTime() < 200) {

							
							SheeldEnduranse = 15;				//15 - じゃんけん負けた時 8
							obj_enemy->ReceiveDamage(30 - SheeldEnduranse - EnemyCutDamege); //軽減ダメージが入る
						}
						

					}

					else {

						if (obj_enemy->GetWaitTime() < 200 || obj_enemy->GetWaitTime() > 0){
															 

															//1 - じゃんけん負けた時 1

							obj_enemy->ReceiveDamage(1 - EnemyCutDamege); //ダメージが入る


						}
					}


					obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
					i--;

				}

				break;

			//case Jan_Type::SCISSORS:                       //敵の属性　チョキ

			//	//グーのじゃん撃のみ有効
			//	if (jangeki_type == Jan_Type::ROCK)
			//	{

			//		//HPが100以下で85以上の時
			//		if (obj_enemy->GetHP() >= 86 && obj_enemy->GetWaitTime() > 0) {

			//			SheeldEnduranse = 27;
			//			obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //軽減ダメージが入る

			//		}
			//		else if (obj_enemy->GetHP() <= 85 && obj_enemy->GetHP() >= 71 && obj_enemy->GetWaitTime() > 0) {

			//			SheeldEnduranse = 24;
			//			obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //軽減ダメージが入る


			//		}
			//		else if (obj_enemy->GetHP() <= 70 && obj_enemy->GetHP() >= 56 && obj_enemy->GetWaitTime() > 0) {

			//			SheeldEnduranse = 21;
			//			obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //軽減ダメージが入る


			//		}
			//		else if (obj_enemy->GetHP() <= 55 && obj_enemy->GetHP() >= 41 && obj_enemy->GetWaitTime() > 0) {

			//			SheeldEnduranse = 18;
			//			obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //軽減ダメージが入る


			//		}
			//		else if (obj_enemy->GetHP() <= 40 && obj_enemy->GetWaitTime() > 0) {

			//			SheeldEnduranse = 15;
			//			obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //軽減ダメージが入る


			//		}

			//		//}
			//		else {

			//			SheeldEnduranse = 0;
			//			obj_enemy->ReceiveDamage(8 - EnemyCutDamege); //ダメージが入る

			//		}


			//		obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
			//		i--;
			//	}
			//	break;

			//case Jan_Type::PAPER:                          //敵の属性　パー

			//	//チョキのじゃん撃のみ有効
			//	if (jangeki_type == Jan_Type::SCISSORS)
			//	{
			//		//if (obj_enemy->GetWaitTime() > 0) {

			//			//HPに応じて食らうダメージが変化する
			//			
			//			//HPが100以下で85以上の時
			//			if (obj_enemy->GetHP() >= 86 && obj_enemy->GetWaitTime() > 0) {

			//				SheeldEnduranse = 27;
			//				obj_enemy->ReceiveDamage(30 -(SheeldEnduranse)- EnemyCutDamege); //軽減ダメージが入る

			//			}
			//			else if (obj_enemy->GetHP() <= 85 && obj_enemy->GetHP() >= 71 &&obj_enemy->GetWaitTime() > 0) {

			//				SheeldEnduranse = 24;
			//				obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //軽減ダメージが入る


			//			}
			//			else if (obj_enemy->GetHP() <= 70 && obj_enemy->GetHP() >= 56 && obj_enemy->GetWaitTime() > 0) {

			//				SheeldEnduranse = 21;
			//				obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //軽減ダメージが入る


			//			}
			//			else if (obj_enemy->GetHP() <= 55 && obj_enemy->GetHP() >= 41 && obj_enemy->GetWaitTime() > 0) {

			//				SheeldEnduranse = 18;
			//				obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //軽減ダメージが入る


			//			}
			//			else if (obj_enemy->GetHP() <= 40 && obj_enemy->GetWaitTime() > 0) {

			//				SheeldEnduranse = 15;
			//				obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //軽減ダメージが入る


			//			}

			//		//}
			//		else {

			//				SheeldEnduranse = 0;
			//			obj_enemy->ReceiveDamage(8 - EnemyCutDamege); //ダメージが入る

			//		}


			//		obj_player->DeleteJangeki(i);     //当たったじゃん撃を削除
			//		i--;
			//	}
			//	break;

			default:
				break;
			}
		}
	}
	////コメント

	//enemyじゃん撃とplayerの当たり判定
	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		//じゃん撃がない時は処理しない
		if (enemy_jangeki[i] == nullptr) break;

		//じゃん撃との当たり判定
		if (obj_player->Hit_Jangeki(enemy_jangeki[i]) == true)
		{
			///////////
			//ハード///
			///////////
			if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD){

				//エネミーのHPが45以下の場合25ダメージ食らう
				//追尾弾
				if (obj_enemy->GetHP() <= 45) {

					//半径が50.0fの場合のダメージ
					float radius = 50.0f;

					if (radius == 50.0f) {

						obj_player->ReceiveDamage(20 - PlayerCutDamege) ;
					}
				}

				if (obj_enemy->GetHP() <= 85 && obj_enemy->GetHP() >= 45) {
					//反射弾
					//半径が25.5fの場合のダメージ
					float radius = 25.5f;

					if (radius == 25.5f) {

						obj_player->ReceiveDamage(15 - PlayerCutDamege);

					}
				}

				//それ以外
				//通常時のダメージを受ける（プレイヤー）
				else obj_player->ReceiveDamage(15 - PlayerCutDamege);	

				
			}
			///////////
			//ノーマル
			///////////
			else if(GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL){

				//エネミーのHPが45以下の場合25ダメージ食らう
				//バウンド弾
				if (obj_enemy->GetHP() <= 45) {

					//半径が50.0fの場合のダメージ
					float radius = 35.5f;

					if (radius == 35.5f) {

						obj_player->ReceiveDamage(5 - PlayerCutDamege);
					}
				}
				
				if(obj_enemy->GetHP() <= 85 && obj_enemy->GetHP() >= 45 ){

					//半径が25.5fの場合のダメージ
					//反射
					float radius = 25.5f;

					if (radius == 25.5f) {

						obj_player->ReceiveDamage(12 - PlayerCutDamege);
						
					}
				}

				//それ以外
				//通常時のダメージを受ける（プレイヤー）
				else obj_player->ReceiveDamage(15 - PlayerCutDamege);

					
			}
		
		
			//あたったじゃん撃を削除
			obj_enemy->DeleteJangeki(i);
			i--;
		}
	}

	///////////////下ブロックの当たり判定削除///////////////////
	//壁との当たり判定
	if (obj_player->Get_X() <= 50 || obj_player->Get_X() >= 1200)
	{
		HitCtrl_Floor(obj_player, STAGE_03_FLOOR);     // player　床・壁判定
	}

	//プレイヤーのy座標が減少しない時のみ当たり判定を取得
	if (obj_player->Get_Y() >= obj_player->Get_OldY())
	{
		HitCtrl_Floor(obj_player, STAGE_03_FLOOR);     // player　床・壁判定
	}

	//敵のy座標が減少しない時のみ当たり判定を取得
	if (obj_enemy->GetY() >= obj_enemy->Get_OldY())
	{
		HitCtrl_Floor(obj_enemy, STAGE_03_FLOOR);      // 敵　　　床・壁判定
	}


}


//描画
void Scene_Stage03::Draw() const
{
	//ステージ描画
	DrawGraph(0, 0, stage, FALSE);

	//HP描画
	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());
	DrawUI_ON_Enemy(obj_enemy);//HPバー

	//接触じゃんけんでない時
	if (GetJanState() == Jan_State::START || GetJanState() == Jan_State::BEFORE)
	{


		obj_player->Draw();  //プレイヤー描画
		obj_enemy->Draw();   //敵キャラ描画
		

		//床・壁描画
		for (int i = 0; i < STAGE_03_FLOOR; i++)
		{
			if (obj_floor[i] == nullptr) break;
			obj_floor[i]->Draw();
		}

		//じゃんけん負けた時
		if (Player_Janwin == 1)
		{
			float p_x = obj_player->GetX();
			float p_y = obj_player->GetY();

			DrawString(p_x, p_y - 55, "防御力UP↑", 0xfff);
		}
		else {
			int Player_Janwin = 0;
		}

		if (Enemy_Janwin == 1) {

			if (obj_enemy->GetWaitTime() > 0) {
				//エネミー特殊効果テキスト表示

				DrawFormatString((int)(obj_enemy->GetX() - 40), (int)(obj_enemy->GetY() - 90), GetColor(0, 0, 255), "さらに防御UP↑", obj_enemy->GetWaitTime());
			}
			else {

				int Enemy_Janwin = 0;

			}
		}

		//接触した瞬間の演出
		if (GetJanState() == Jan_State::START) Draw_JankenStart();

	}
	else
	{
		//接触時じゃんけん描画
		Draw_Janken();
	}

	//DrawString(640, 360, "Stage03", 0xffff);
	
	//接触じゃんけん時Effect
	Effect_Draw_HitJangeki();

  


}



//じゃんけん描画
void Scene_Stage03::Draw_Janken() const
{
	obj_janken->Draw();
}

//シーンの変更
AbstractScene* Scene_Stage03::ChangeScene()
{
	//"Debug_Manager.h" の #define DEBUG_OFF_03 をコメントアウトすると開発モード
#ifdef DEBUG_OFF_03

	//敵のHP0
	if (IsEnd_DeathEnemy() == true) {


		//走るSE停止
		StopSoundMem(obj_enemy->GetRunSE());
		//歩くSE停止
		StopSoundMem(obj_enemy->GetWalkSE());
		//ゲームクリアシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameClearScene(4));

	}

	//プレイヤーのHPが0以下
					//死亡演出//
	if (obj_player->IsDeathPlayer() == true){
		 

		//走るSE停止
		StopSoundMem(obj_enemy->GetRunSE());
		//歩くSE停止
		StopSoundMem(obj_enemy->GetWalkSE());
		//ゲームオーバーシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameOverScene(3));
	}

#endif // DEBUG_OFF_03

	return this;
}

//じゃんけん終了後の挙動（プレイヤー勝ち）

void Scene_Stage03::AfterJanken_WIN()
{

	//勝ったら1
	Player_Janwin = 1;


	//エネミーのHPが45以下の場合25ダメージ食らう
	if (obj_enemy->GetHP() <= 45) {

		//じゃんけん勝利時
		PlayerCutDamege = 3;


	}
	//じゃんけん勝利時
	else PlayerCutDamege = 10;

	obj_player->SetX(200);
	
	
}

//じゃんけん終了後の挙動（プレイヤー負け）
void Scene_Stage03::AfterJanken_LOSE()
{

	//負けたら1
	Enemy_Janwin = 1;


	if(obj_enemy->GetHP() >= 86){

	    //じゃんけん敗北時
	    EnemyCutDamege = 2;
	}
	else if(obj_enemy->GetHP() <= 85 && obj_enemy->GetHP() >= 71) {

		//じゃんけん敗北時
		EnemyCutDamege = 3;

	}
	else if (obj_enemy->GetHP() <= 70 && obj_enemy->GetHP() >= 56) {

		//じゃんけん敗北時
		EnemyCutDamege = 5;

	}
	else if (obj_enemy->GetHP() <= 55 && obj_enemy->GetHP() >= 46) {

		//じゃんけん敗北時
		EnemyCutDamege = 6;

	}
	else if (obj_enemy->GetHP() <= 45) {


		//じゃんけん敗北時
		EnemyCutDamege = 8;


	}
	else {

		//じゃんけん敗北時
		EnemyCutDamege = 1;

	}

	//Xが200に移動
	obj_player->SetX(200);
	

}


