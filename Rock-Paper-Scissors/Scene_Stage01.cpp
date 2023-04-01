#include "Scene_Stage01.h"
#include"KeyManager.h"
#include"Scene_GameOver.h"
#include"Scene_GameClear.h"
#include"DxLib.h"

//デバッグモード
#include"Debug_Manager.h"

//表示する文字列
namespace _STR_TUTORIAL
{
	//char draw_str[][40] =
	//{
	//	"ようこそ。最初に操作説明をします",
	//	"左スティックで左右移動できます",
	//	"LBボタンでジャンプします",
	//	"右スティックで照準を操作できます",
	//	"敵に接触するとじゃんけんが始まります",
	//};
}

//コンストラクタ
Scene_Stage01::Scene_Stage01(const Player* player)
	: frame_count(0), Now_Tut_State(TUTORIAL_STATE::START_TUTORIAL)
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
	obj_enemy = new Enemy_01(1200, 360, Jan_Type::SCISSORS);

	//床・壁の用意
	Init_Floor(STAGE_01_FLOOR);

	//一つずつ生成
	obj_floor[0] = new Floor(0, 700, 1280, 20);        //床
	obj_floor[1] = new Floor(0, 0, 20, 720);           //壁（左）
	obj_floor[2] = new Floor(1260, 0, 20, 720);           //壁（右）
	obj_floor[3] = new Floor(1000, 100, 120, 50);      //壁（右）
	obj_floor[4] = new Floor(400, 300, 500, 20);      //壁（右）


	//色
	blue = GetColor(0, 0, 255);
	red = GetColor(255, 0, 0);
	brack = GetColor(0, 0, 0);
	white = GetColor(255, 255, 255);
	green = GetColor(0, 255, 0);

	//フォントデータを作成　　　　　　Windows標準搭載フォントなら大丈夫。多分　　　[候補 "Yu Gothic UI"]
	font_tut = CreateFontToHandle("メイリオ", 40, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2);
}

//デストラクタ
Scene_Stage01::~Scene_Stage01()
{
}

//更新
void Scene_Stage01::Update()
{
	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Update();    // プレイヤー更新・操作可能
		//obj_enemy->Update();     //敵キャラ更新・内部処理

		//プレイヤーの座標を取得
		//obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());

	}

	//接触じゃんけん処理
	Touch_Janken(obj_enemy, this, 1);


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


	HitCtrl_Floor(obj_player, STAGE_01_FLOOR);     // player　床・壁判定
	HitCtrl_Floor(obj_enemy, STAGE_01_FLOOR);      // 敵　　　床・壁判定



	switch (Now_Tut_State)
	{
	case Scene_Stage01::TUTORIAL_STATE::START_TUTORIAL:
		break;
	case Scene_Stage01::TUTORIAL_STATE::PLAYER_MOVE:
		break;
	case Scene_Stage01::TUTORIAL_STATE::PLAYER_JUMP:
		break;
	case Scene_Stage01::TUTORIAL_STATE::PLAYER_AIMING:
		break;
	case Scene_Stage01::TUTORIAL_STATE::TOUCH_JANKEN:
		break;
	default:
		break;
	}

	NextTutorial();

}

//描画
void Scene_Stage01::Draw() const
{
	//接触じゃんけん開始前
	if (GetJanState() == Jan_State::BEFORE)
	{

		obj_player->Draw();  //プレイヤー描画
		//obj_enemy->Draw();   //敵キャラ描画

		//床・壁描画
		for (int i = 0; i < STAGE_01_FLOOR; i++)
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


	//表示する文字列
	//const char* str = _STR_TUTORIAL::draw_str[static_cast<int>(Now_Tut_State)];

	//DrawStringToHandle(200, 200, str, green, font_tut, white);



	//点滅
	static int counter;

	if (counter++ < 30)
	{
		DrawCircle(1060, 320, 20, white, TRUE);
		DrawCircle(1060, 320, 18, green, TRUE);
		DrawStringToHandle(1030, 310, "A", white, font_tut, brack);

		//DrawStringToHandle(1060, 320, "-- Press  A  Button --", white, font_other, green);
	}
	else if (counter > 60)  counter = 0;
	else {}


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
	if (obj_enemy->GetHP() < 0)
	{
		//ゲームクリアシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameClearScene(2));
	}

	//プレイヤーのHPが0以下
	if (obj_player->GetHP() < 0)
	{
		//ゲームオーバーシーンへ切り替え
		return dynamic_cast<AbstractScene*> (new GameOverScene(1));
	}

#endif 

	return this;   //更新なし
}

//次の操作へ
void Scene_Stage01::NextTutorial()
{
	//チュートリアル
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		switch (Now_Tut_State)
		{
		case Scene_Stage01::TUTORIAL_STATE::START_TUTORIAL:

			//左右移動へ
			Now_Tut_State = TUTORIAL_STATE::PLAYER_MOVE;
			break;

		case Scene_Stage01::TUTORIAL_STATE::PLAYER_MOVE:

			//ジャンプへ
			Now_Tut_State = TUTORIAL_STATE::PLAYER_JUMP;
			break;

		case Scene_Stage01::TUTORIAL_STATE::PLAYER_JUMP:

			//照準へ
			Now_Tut_State = TUTORIAL_STATE::PLAYER_AIMING;
			break;

		case Scene_Stage01::TUTORIAL_STATE::PLAYER_AIMING:

			//接触じゃんけんへ
			Now_Tut_State = TUTORIAL_STATE::TOUCH_JANKEN;
			break;

		case Scene_Stage01::TUTORIAL_STATE::TOUCH_JANKEN:

			break;

		default:
			break;
		}
	}
}

//左右移動を確認する
bool Scene_Stage01::CheckMoveLR()
{
	static bool move_left;    //左移動したか
	static bool move_right;   //右移動したか

	//前回の座標と一致していた場合、移動していない
	if (obj_player->Get_OldX() == obj_player->GetX()) return false;

	

	//どちらも移動した
	if (move_left == true && move_right == true) return true;
}