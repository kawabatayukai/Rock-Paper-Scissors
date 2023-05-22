#include "Stage_Base.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"GameData.h"
#include"MobEnemy_05.h"
#include<iostream>
#include<vector>


//衝突判定なし時間   5秒
#define NOT_COLLISION_TIME  300


int Stage_Base::font = 0;         //結果(WIN or LOSE or ONEMORE) 用フォント
int Stage_Base::font_score = 0;   //Score描画用フォント
int Stage_Base::name_font = 0;

namespace _CONSTANTS_SB
{
	//エフェクト最大生成数
	const int EFFECT_MAX = 20;
	//SE Max
	const int SE_MAX = 15;

	//時計座標
	const int CLOCK_X = 640;
	const int CLOCK_Y = 60;

	//敵の名前
	const std::vector<std::string> Enemy_Name =
	{
		"NIWATORI",       //1
		"KAERU",        //2
		"ZAKU",           //3
		"RED EYE",       //4
		"TAMAGO",         //5
		"JAN NINJA",      //6
		"JHO",            //7
		"TWIN AVATAR",     //8
		"SHADOW",        //9
		"Y・Y"            //10
	};
}

Stage_Base::Stage_Base() : blackout_time(0), stage_number(0), Prev_EnemyType(Jan_Type::NONE), obj_effectEnemy(nullptr), obj_death(nullptr)
,bf_result(Jan_Result::_ERROR)
{
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, typeImage);

	if (font == 0)
		font = CreateFontToHandle(NULL, 60, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);

	if (font_score == 0)
		font_score = CreateFontToHandle("メイリオ", 30, 5, DX_FONTTYPE_ANTIALIASING_EDGE, -1, 1);

	//フォントを作成
	if (name_font == 0)
		name_font = CreateFontToHandle("メイリオ", 20, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);

	//エフェクト初期化
	obj_effect = new Effect_Jangeki * [_CONSTANTS_SB::EFFECT_MAX];
	for (int i = 0; i < _CONSTANTS_SB::EFFECT_MAX; i++) obj_effect[i] = nullptr;

	//画像
	LoadDivGraph("images/Clock/color_circles.png", 3, 3, 1, 120, 120, image_circle);
	image_clock = LoadGraph("images/Clock/clockback_wood.png");
	image_clockhand = LoadGraph("images/Clock/clockhand_wood.png");
	image_clockchar = LoadGraph("images/Clock/clock_str.png");

	//SE
	obj_sejan = new Sound_Jangeki * [_CONSTANTS_SB::SE_MAX];
	for (int i = 0; i < _CONSTANTS_SB::SE_MAX; i++) obj_sejan[i] = nullptr;

	//SE Player
	Sound_Player::LoadPlayerSound();

	//SE Janken
	se_Janken = nullptr;
}

Stage_Base::~Stage_Base()
{

}

//UI描画
void Stage_Base::DrawUI(Jan_Type type, int hp) const
{
	using namespace _CONSTANTS_SB;

	//制限時間描画
	//スコア
	DrawFormatStringToHandle(950, 80, 0xffffff, font_score, "Score : %d", GameData::Get_Score(), 0x000000);

	// ------------------------------ 時計 ------------------------------------
	//現在のパーセンテージ(扇形)
	double circle_rate = (100 * static_cast<double>(GameData::Get_Each_Time())) / static_cast<double>(GameData::Get_ConstTimeLimit());
	//針の角度
	double hand_angle = ((360 * circle_rate) / 100) * static_cast<double>(3.14 / 180);

	//色が変わる
	int circle_index = 0;
	if (circle_rate <= 66 && circle_rate > 33) circle_index = 1;
	else if (circle_rate < 33) circle_index = 2;
	else {};


	DrawRotaGraph(CLOCK_X, CLOCK_Y, 1, 0, image_clock, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 250);
	DrawCircleGauge(CLOCK_X, CLOCK_Y, circle_rate, image_circle[circle_index], 0.0, 0.85, 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawRotaGraph(CLOCK_X, CLOCK_Y, 1, 0, image_clockchar, TRUE);
	DrawRotaGraph(CLOCK_X, CLOCK_Y, 1, -hand_angle, image_clockhand, TRUE);
}

//敵の上にUI描画
void Stage_Base::DrawUI_ON_Enemy(const EnemyBase* enemy, const int& notDraw) const
{
	//情報を取得
	Jan_Type type = enemy->GetType();
	int enemy_hp = enemy->GetHP();
	float enemy_x = enemy->GetX();
	float enemy_y = enemy->GetY();
	float enemy_h = enemy->GetH();

	//HPバーの色
	int bar_color = 0xffffff;
	//描画するじゃん撃属性の配列番号
	int index = 0;

	switch (type)
	{
	case Jan_Type::ROCK:

		index = 0;
		bar_color = 0xff0000;    //red
		break;

	case Jan_Type::SCISSORS:

		index = 1;
		bar_color = 0xffd400;    //yellow
		break;

	case Jan_Type::PAPER:

		index = 2;
		bar_color = 0x0000ff;    //blue
		break;

	case Jan_Type::NONE:

		bar_color = 0x8B52A1;    //purple
		break;

	default:
		break;
	}

	float draw_x = enemy_x - 50;  //描画ｘ
	float draw_y = enemy_y - 100; //描画ｙ

	//属性
	if (type != Jan_Type::NONE)DrawRotaGraphF(draw_x - 20, draw_y + 5, 0.3, 1, typeImage[index], TRUE);
	//枠
	DrawBoxAA(draw_x - 3, draw_y - 3, draw_x + 103, draw_y + 13, 0xffffff, TRUE);
	DrawBoxAA(draw_x, draw_y, (draw_x + 100), draw_y + 10, 0x000000, TRUE);
	//HP
	DrawBoxAA(draw_x, draw_y, (draw_x + enemy_hp), draw_y + 10, bar_color, TRUE);

	using namespace _CONSTANTS_SB;

	//名前
	if (notDraw == 0)
	{
		std::string name = Enemy_Name[stage_number > 0 ? stage_number - 1 : 0];
		int str_w = GetDrawStringWidthToHandle(name.c_str(), name.length(), name_font);
		DrawStringToHandle((static_cast<int>(enemy->GetX()) - (str_w / 2)), static_cast<int>(enemy->GetY()) - 80, name.c_str(), 0x00ff00, name_font);
	}
}

//床・壁の準備　　STAGE_XX_FLOOR を引数に
void Stage_Base::Init_Floor(const int floor_MAX)
{
	//床・壁 * floor_MAX個　分のメモリを確保
	obj_floor = new Floor * [floor_MAX];
	for (int i = 0; i < floor_MAX; i++) obj_floor[i] = nullptr;   //nullptrで全て初期化
}


//床・壁とのあたり判定
void Stage_Base::HitCtrl_Floor(CharaBase* character, const int floor_MAX)
{
	for (int i = 0; i < floor_MAX; i++)
	{
		character->Hit_Floor(obj_floor[i]);
	}
}


//"接触時じゃんけん"処理   player(引数１番目　の勝敗結果を返す)
Jan_Result Stage_Base::Get_JankenResult(Jan_Type player, Jan_Type enemy)
{
	// player（引数１番目）が
	switch (player)
	{
	case Jan_Type::ROCK:         //グーの時

		if (enemy == Jan_Type::PAPER)    return Jan_Result::LOSE;    //enemy（引数２番目）がパーの時
		if (enemy == Jan_Type::SCISSORS) return Jan_Result::WIN;     //enemy（引数２番目）がチョキの時
		if (enemy == Jan_Type::ROCK)     return Jan_Result::ONEMORE; //enemy（引数２番目）がグーの時
		break;

	case Jan_Type::SCISSORS:     //チョキの時

		if (enemy == Jan_Type::ROCK)     return Jan_Result::LOSE;    //enemy（引数２番目）がグーの時
		if (enemy == Jan_Type::PAPER)    return Jan_Result::WIN;     //enemy（引数２番目）がパーの時
		if (enemy == Jan_Type::SCISSORS) return Jan_Result::ONEMORE; //enemy（引数２番目）がチョキの時
		break;

	case Jan_Type::PAPER:        //パーの時

		if (enemy == Jan_Type::SCISSORS) return Jan_Result::LOSE;    //enemy（引数２番目）がチョキの時
		if (enemy == Jan_Type::ROCK)     return Jan_Result::WIN;     //enemy（引数２番目）がグーの時
		if (enemy == Jan_Type::PAPER)    return Jan_Result::ONEMORE; //enemy（引数２番目）がパーの時
		break;

	default:
		break;
	}

	//それ以外はエラー
	return Jan_Result::_ERROR;
}



//敵とプレイヤーの当たり判定→接触じゃんけん処理    敵へのポインタ、"this" を引数に
void Stage_Base::Touch_Janken(EnemyBase* enemy, Stage_Base* stage_ptr, int my_StageNum, bool invalidate)
{
	stage_number = my_StageNum;

	//じゃんけん開始前 
	if (j_state == Jan_State::BEFORE)
	{
		//敵とプレイヤーが接触
		if (enemy->Hit_Character(obj_player) == true && nhit_time == 0 && invalidate == false)
		{
			//接触した!
			j_state = Jan_State::START;
			blackout_time = 0;

			//敵が出す手をランダムに決める　　　（ランダムなint型の値(0～2)を Jan_Type型に変換）
			Jan_Type enemy_janken = static_cast<Jan_Type> (GetRand(2));

			//じゃんけんオブジェクト生成
			obj_janken = new Janken(enemy_janken, my_StageNum);

			//SE初期化
			se_Janken = nullptr;
			se_count = 0;
		}

	}
	else if (j_state == Jan_State::START)
	{
		//接触した直後
		blackout_time++;

		//1秒でじゃんけん画面へ
		if (blackout_time > 60) j_state = Jan_State::PROGRESS;
	}
	else if (j_state == Jan_State::PROGRESS)
	{

		//じゃんけん中
		obj_janken->Update();
		obj_janken->Stars_Update();
		//結果を一時格納
		Jan_Result result = obj_janken->GetResult();
		
		// 結果が _ERROR(じゃんけん中)でないとき、じゃんけん終了
		if (result != Jan_Result::_ERROR) j_state = Jan_State::AFTER;
		
	}
	else if (j_state == Jan_State::AFTER)
	{
		obj_janken->Stars_Update();

		if (se_Janken == nullptr && se_count == 0)
		{
			Jan_Result result = obj_janken->GetResult();
			if (result == Jan_Result::WIN)
				se_Janken = new Sound_Janken(SE_JANKEN::JANKEN_WIN);
			else if (result == Jan_Result::LOSE)
				se_Janken = new Sound_Janken(SE_JANKEN::JANKEN_LOSE);
			else if (result == Jan_Result::ONEMORE)
				se_Janken = new Sound_Janken(SE_JANKEN::JANKEN_AIKO);
			else {}
			se_count++;
		}

		//Aボタンが押されたとき 
		if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
		{
			//プレイヤーの座標を初期値に
			obj_player->SetX(640);

			//じゃんけん終了
			switch (obj_janken->GetResult())
			{

			case Jan_Result::LOSE:    //負け

				

				/*難易度が即死モードなら*/
				if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD)
				{
					obj_player->ReceiveDamage(100); //即死
				}
				else /*普通のモード*/
				{
					//オーバーライドされたAfterJanken_LOSE()を呼び出す
					stage_ptr->AfterJanken_LOSE();
				}

				//END演出
				blackout_time = 0;
				j_state = Jan_State::END;

				break;


			case Jan_Result::WIN:     //勝ち

				GameData::Add_Score(500);

				/*難易度が即死モードなら*/
				if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD)
				{
					enemy->ReceiveDamage(100);
					isHard_Win = true;
				}
				else /*普通のモード*/
				{
					//オーバーライドされたAfterJanken_WIN()を呼び出す
					stage_ptr->AfterJanken_WIN();
				}

				//END演出
				blackout_time = 0;  
				j_state = Jan_State::END;

				break;


			case Jan_Result::ONEMORE: //あいこ
			{
				

				//じゃん撃を初期化する
				enemy->Init_Jangeki();

				bf_result = Jan_Result::ONEMORE;
				delete obj_janken;

				//敵が出す手をランダムに決める　　　（ランダムなint型の値(0～2)を Jan_Type型に変換）
				Jan_Type enemy_janken = static_cast<Jan_Type> (GetRand(2));

				//じゃんけんオブジェクト生成
				obj_janken = new Janken(enemy_janken, my_StageNum);

				//じゃんけん開始
				j_state = Jan_State::PROGRESS;

				break;
			}
			default:
				break;
			}



		}
	}
	else if (j_state == Jan_State::END)
    {
		//じゃん撃を初期化する
		enemy->Init_Jangeki();
		//あたり判定なし時間をセット
		nhit_time = NOT_COLLISION_TIME;

		//開始前にリセット
		if(++blackout_time > 60) 
		{
			j_state = Jan_State::BEFORE;
			delete obj_janken;
		}
	}
	else {}

	//SE再生
	if (se_Janken != nullptr)
	{
		se_Janken->Play();
		if (se_Janken->CheckPlayEnd() == true)
		{
			delete se_Janken;
			se_Janken = nullptr;
		}
	}

	//衝突判定なし時間
	if (--nhit_time < 0) nhit_time = 0;

	//Enemyを監視
	if (my_StageNum == 9)
	{
		if (stage09_isclear == true && obj_death == nullptr || enemy->GetHP() <= 0 && obj_death == nullptr)
		{
			enemy->Init_Jangeki();
			//死亡演出用オブジェクト
			obj_death = new Enemy_Death(enemy->GetX(), enemy->GetY(), my_StageNum);

			enemy->SetX(-9999, true);
			enemy->SetY(-9999, true);
		}
	}
	else if (my_StageNum == 10)
	{
	}
	else
	{
		if (enemy->GetHP() <= 0 && obj_death == nullptr)
		{
			enemy->Init_Jangeki();
			//死亡演出用オブジェクト
			obj_death = new Enemy_Death(enemy->GetX(), enemy->GetY(), my_StageNum, enemy->GetType());

			enemy->SetX(-9999, true);
			enemy->SetY(-9999, true);
		}
	}


	Update_DeathEnemy();
};


//じゃん撃ヒット時エフェクト 処理
void Stage_Base::Effect_Update_HitJangeki(const EnemyBase* enemy, const Jangeki_Reflection* ref)
{
	//敵の座標
	float e_x = enemy->GetX();
	float e_y = enemy->GetY();

	//プレイヤーの座標
	float p_x = obj_player->GetX();
	float p_y = obj_player->GetY();

	//エフェクトを生成する配列の要素番号
	int effect_count;

	//エフェクト
	for (effect_count = 0; effect_count < _CONSTANTS_SB::EFFECT_MAX; effect_count++)
	{
		//空なら終了
		if (obj_effect[effect_count] == nullptr) break;
		obj_effect[effect_count]->Update();

		if (obj_effect[effect_count]->GetCharacterType() == _CHAR_TYPE::ENEMY)
			obj_effect[effect_count]->SetCharacterLocation(obj_player->GetX(), obj_player->GetY());
		else if (obj_effect[effect_count]->GetCharacterType() == _CHAR_TYPE::PLAYER)
			obj_effect[effect_count]->SetCharacterLocation(enemy->GetX(), enemy->GetY());
		//削除
		if (obj_effect[effect_count]->Check_PlayEnd() == true)
		{
			delete obj_effect[effect_count];
			obj_effect[effect_count] = nullptr;    //初期化

			//詰める
			for (int j = effect_count; j < (_CONSTANTS_SB::EFFECT_MAX - 1); j++)
			{
				//次の要素が nullptr ならそれ以上は処理しない
				if (obj_effect[j + 1] == nullptr) break;

				obj_effect[j] = obj_effect[j + 1];
				obj_effect[j + 1] = nullptr;
			}
			effect_count--;
		}
	}

	//SEを生成する配列の要素番号
	int se_count;
	for (se_count = 0; se_count < _CONSTANTS_SB::SE_MAX; se_count++)
	{
		if (obj_sejan[se_count] == nullptr) break;
		obj_sejan[se_count]->Play();

		//削除
		if (obj_sejan[se_count]->CheckPlayEnd() == true)
		{
			delete obj_sejan[se_count];
			obj_sejan[se_count] = nullptr;

			//詰める
			for (int j = 0; j < (_CONSTANTS_SB::SE_MAX - 1); j++)
			{
				if (obj_sejan[j + 1] == nullptr) break;
				obj_sejan[j] = obj_sejan[j + 1];
				obj_sejan[j + 1] = nullptr;
			}
			se_count--;
		}

	}

	//playerのじゃん撃をとってくる
	Jangeki_Base** p_jan = obj_player->GetJangeki();
	//enemyのじゃん撃をとってくる
	Jangeki_Base** e_jan = enemy->GetJangeki();

	//--------------------  playerじゃん撃とenemy  -------------------------------------

		//playerじゃん撃とenemyの当たり判定
	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		//空要素なら終了
		if (p_jan[i] == nullptr) break;

		//当たり判定
		if (enemy->Hit_Jangeki(p_jan[i]) == true)
		{
			Jan_Type p_type = p_jan[i]->GetType();  //当たったじゃん撃の属性



			//不利属性のみ
			switch (enemy->GetType())
			{
			case Jan_Type::ROCK:                           //敵の属性　グー

				//パーのみ有効
				if (p_type == Jan_Type::PAPER)
				{
					//エフェクト生成
					if (obj_effect[effect_count] == nullptr && effect_count < _CONSTANTS_SB::EFFECT_MAX)
					{
						obj_effect[effect_count] = new Effect_Jangeki(e_x, e_y, Jan_Type::PAPER, _CHAR_TYPE::PLAYER);
						//effect_count++;

						//SE
						obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::HIT_JAN);
						//se_count++;
					}
				}
				break;

			case Jan_Type::SCISSORS:                       //敵の属性　チョキ

				//グーのみ有効
				if (p_type == Jan_Type::ROCK)
				{
					//エフェクト生成
					if (obj_effect[effect_count] == nullptr && effect_count < _CONSTANTS_SB::EFFECT_MAX)
					{
						obj_effect[effect_count] = new Effect_Jangeki(e_x, e_y, Jan_Type::ROCK, _CHAR_TYPE::PLAYER);
						//effect_count++;

						//SE
						obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::HIT_JAN);
						//se_count++;
					}
				}
				break;

			case Jan_Type::PAPER:                          //敵の属性　パー

				//チョキのみ有効
				if (p_type == Jan_Type::SCISSORS)
				{
					//エフェクト生成
					if (obj_effect[effect_count] == nullptr && effect_count < _CONSTANTS_SB::EFFECT_MAX)
					{
						obj_effect[effect_count] = new Effect_Jangeki(e_x, e_y, Jan_Type::SCISSORS, _CHAR_TYPE::PLAYER);
						//effect_count++;

						//SE
						obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::HIT_JAN);
						//se_count++;
					}
				}
				break;

			case Jan_Type::NONE:                            //属性なし

				//反射じゃん撃に当てることで生成されるホーミングじゃん撃のみ有効
				if (p_jan[i]->IsGetPlayerHoming() == true)
				{
					//エフェクト生成
					if (obj_effect[effect_count] == nullptr && effect_count < _CONSTANTS_SB::EFFECT_MAX)
					{
						obj_effect[effect_count] = new Effect_Jangeki(e_x, e_y, p_type, _CHAR_TYPE::PLAYER);
						//effect_count++;

						//SE
						obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::HIT_JAN);
						//se_count++;
					}
				}
				break;

			default:
				break;
			}
		}
	}

	//----------------------------------------------------------------------------------

	//--------------------  enemyじゃん撃とplayer  -------------------------------------
	{
		//enemyじゃん撃とplayerの当たり判定
		for (int i = 0; i < JANGEKI_MAX; i++)
		{
			//空要素なら終了
			if (e_jan[i] == nullptr) break;

			//当たり判定
			if (obj_player->Hit_Jangeki(e_jan[i]) == true)
			{
				//エフェクト生成
				if (obj_effect[effect_count] == nullptr && effect_count < _CONSTANTS_SB::EFFECT_MAX)
				{
					obj_effect[effect_count] = new Effect_Jangeki(p_x, p_y, e_jan[i]->GetType(), _CHAR_TYPE::ENEMY);
					//effect_count++;

					//SE
					obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::HIT_JAN);
					//se_count++;
				}
			}
		}

		//反射
		if (ref != nullptr)
		{
			Jangeki_Base** r_jan = ref->GetJangeki();

			for (int r = 0; r < JANGEKI_MAX; r++)
			{
				//空要素なら終了
				if (r_jan[r] == nullptr) break;

				//当たり判定
				if (obj_player->Hit_Jangeki(r_jan[r]) == true)
				{
					//エフェクト生成
					if (obj_effect[effect_count] == nullptr && effect_count < _CONSTANTS_SB::EFFECT_MAX)
					{
						obj_effect[effect_count] = new Effect_Jangeki(p_x, p_y, r_jan[r]->GetType(), _CHAR_TYPE::ENEMY);
						//effect_count++;

						//SE
						obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::HIT_JAN);
						//se_count++;
					}
				}
			}
		}
	}
	//----------------------------------------------------------------------------------

	//-------------------  enemyじゃん撃とplayerじゃん撃  ------------------------------

	for (int p = 0; p < JANGEKI_MAX; p++)
	{
		if (p_jan[p] == nullptr) break;                  //なければ抜ける

		//enemy
		for (int e = 0; e < JANGEKI_MAX; e++)
		{
			if (e_jan[e] == nullptr) break;              //なければ抜ける

			if (p_jan[p]->Hit_Jangeki(e_jan[e]) == true) //当たり
			{
				int result = p_jan[p]->CheckAdvantage(e_jan[e]);

				//あいこの場合
				if (result == 2)
				{
					//じゃん撃間の距離
					float dx = e_jan[e]->GetX() - p_jan[p]->GetX();
					float dy = e_jan[e]->GetY() - p_jan[p]->GetY();

					float jan_x = p_jan[p]->GetX() + (dx / 2);
					float jan_y = p_jan[p]->GetY() + (dy / 2);

					obj_effect[effect_count] = new Effect_Jangeki(jan_x, jan_y, e_jan[e]->GetType(), _CHAR_TYPE::NOT_CHARA);
					effect_count++;

					//SE
					obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::ONEMORE);
					//se_count++;
					GameData::Add_PierceCount(1); //貫通回数加算
					GameData::Add_Score(100 / 2); //スコア加算
				}
				else if (result == 1)   //勝ち
				{
					// SE
					obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::PLAYER_WIN);
					//se_count++;
					GameData::Add_PierceCount(2); //貫通回数加算
					GameData::Add_Score(100);     //スコア加算
				}
				else if (result == 0)   //負け
				{
					// SE
					obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::ENEMY_WIN);
					//se_count++;
				}
				else {};
			}

			//ref反射
			if (ref != nullptr)
			{
				Jangeki_Base** r_jan = ref->GetJangeki();
				for (int r = 0; r < JANGEKI_MAX; r++)
				{
					if (r_jan[r] == nullptr) break;              //抜ける
					if (p_jan[p]->Hit_Jangeki(r_jan[r]) == true) //当たり
					{
						int result = p_jan[p]->CheckAdvantage(r_jan[r]);

						//あいこの場合
						if (result == 2)
						{
							//じゃん撃間の距離
							float dx = r_jan[r]->GetX() - p_jan[p]->GetX();
							float dy = r_jan[r]->GetY() - p_jan[p]->GetY();

							float jan_x = p_jan[p]->GetX() + (dx / 2);
							float jan_y = p_jan[p]->GetY() + (dy / 2);

							obj_effect[effect_count] = new Effect_Jangeki(jan_x, jan_y, r_jan[r]->GetType(), _CHAR_TYPE::NOT_CHARA);
							effect_count++;

							//SE
							obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::ONEMORE);
							//se_count++;
							GameData::Add_PierceCount(1); //貫通回数加算
							GameData::Add_Score(100 / 2); //スコア加算
						}
						else if (result == 1)   //勝ち
						{
							// SE
							obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::PLAYER_WIN);
							//se_count++;
							GameData::Add_PierceCount(2); //貫通回数加算
							GameData::Add_Score(100);     //スコア加算
						}
						else if (result == 0)   //負け
						{
							// SE
							obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::ENEMY_WIN);
							//se_count++;
						}
						else {};
					}
				}
			}
		}
	}

	//----------------------------------------------------------------------------------


	//----------------------------------　属性変化　------------------------------------
		//前回の属性と違っていればエフェクト生成
	if (enemy->GetType() != Prev_EnemyType && Prev_EnemyType != Jan_Type::NONE)
	{
		if (obj_effectEnemy == nullptr)
		{
			obj_effectEnemy = new Effect_Enemy(enemy->GetX(), enemy->GetY(), enemy->GetType());
		}
	}
	//敵の属性変化
	Prev_EnemyType = enemy->GetType();

	if (obj_effectEnemy != nullptr)
	{
		obj_effectEnemy->Update();
		obj_effectEnemy->SetEnemyLocation(enemy->GetX(), enemy->GetY());
		if (obj_effectEnemy->IsEffectFinished() == true)
		{
			delete obj_effectEnemy;
			obj_effectEnemy = nullptr;
		}
	}
}

//じゃん撃ヒット時エフェクト 描画
void Stage_Base::Effect_Draw_HitJangeki() const
{
	//エフェクト
	for (int i = 0; i < _CONSTANTS_SB::EFFECT_MAX; i++)
	{
		//空なら終了
		if (obj_effect[i] == nullptr) break;
		obj_effect[i]->Draw();
	}

	if (obj_effectEnemy != nullptr) obj_effectEnemy->Draw();
	Draw_DeathEnemy();
}

//死亡時処理
void Stage_Base::Update_DeathEnemy()
{
	if (obj_death != nullptr)
	{
		obj_death->Update();
	}
}

//死亡時描画
void Stage_Base::Draw_DeathEnemy() const
{
	if (obj_death != nullptr)
	{
		obj_death->Draw();
	}
}

//死亡演出終了チェック
bool Stage_Base::IsEnd_DeathEnemy()
{
	if (obj_death != nullptr)
	{
		if (obj_death->IsDeathEnd() == true)
		{
			return true;
			delete obj_death;

			GameData::Add_Score(1000);
		}
	}
	return false;
}

void Stage_Base::GetStage09IsClear(bool isclear)
{
	stage09_isclear = isclear;
}

//じゃんけん描画
void Stage_Base::Draw_Janken() const
{
	obj_janken->Draw();
}

//じゃんけん開始直後
void Stage_Base::Draw_JankenStart() const
{
	if (j_state == Jan_State::END)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (static_cast<int>(blackout_time * 5)));
		obj_janken->SetAlphaValue(255 - (static_cast<int>(blackout_time * 5)));
		if (blackout_time < 60) obj_janken->Draw();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		for (int i = 0; i < 12; i++)
		{
			DrawBox(0, i * 60, (1280 - (blackout_time * 21)), (i * 60) + 30, 0x000000, TRUE);

			DrawBox(1280, (i * 60) + 30, blackout_time * 21, (i * 60) + 60, 0x000000, TRUE);
		}
	}
	else
	{
		//ポケモンバトル風
		for (int i = 0; i < 12; i++)
		{
			DrawBox(0, i * 60, blackout_time * 21, (i * 60) + 30, 0x000000, TRUE);

			DrawBox(1280, (i * 60) + 30, (1280 - (blackout_time * 21)), (i * 60) + 60, 0x000000, TRUE);
		}
	}
}


//じゃんけん終了後の挙動（プレイヤー勝ち）
void Stage_Base::AfterJanken_WIN()
{
	obj_player->SetX(100);
}

//じゃんけん終了後の挙動（プレイヤー負け）
void Stage_Base::AfterJanken_LOSE()
{
	obj_player->SetX(100);
}


//じゃんけんの状態取得
Jan_State Stage_Base::GetJanState() const
{

	if (j_state == Jan_State::END) return Jan_State::START;

	return j_state;
}
