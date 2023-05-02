#include "Stage_Base.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"GameData.h"

#include<vector>

//衝突判定なし時間   5秒
#define NOT_COLLISION_TIME  300

namespace _CONSTANTS_SB
{
	//エフェクト最大生成数
	const int EFFECT_MAX = 20;
	
	//時計座標
	const int CLOCK_X = 640;
	const int CLOCK_Y = 60;
}

Stage_Base::Stage_Base() : blackout_time(0)
{
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, typeImage);

	//                           サイズ 幅              外枠
	font = CreateFontToHandle(NULL, 60, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);

	//エフェクト初期化
	obj_effect = new Effect_Jangeki * [_CONSTANTS_SB::EFFECT_MAX];
	for (int i = 0; i < _CONSTANTS_SB::EFFECT_MAX; i++) obj_effect[i] = nullptr;

	//画像
	LoadDivGraph("images/Clock/color_circles.png", 3, 3, 1, 120, 120, image_circle);
	image_clock = LoadGraph("images/Clock/clockback_wood.png");
	image_clockhand = LoadGraph("images/Clock/clockhand_wood.png");
	image_clockchar = LoadGraph("images/Clock/clock_str.png");
}

Stage_Base::~Stage_Base()
{

}

//UI描画
void Stage_Base::DrawUI(Jan_Type type, int hp) const
{
	using namespace _CONSTANTS_SB;

	int color = 0x00ff00;    //HPバーの色

	//制限時間描画
	//DrawFormatStringToHandle(500, 20, 0x00ff00, font, "%d分%d秒", GameData::Get_Each_Time() / 3600, GameData::Get_Each_Time() / 60);
	DrawFormatStringToHandle(500, 20, 0x00ff00, font, "%d : %d", GameData::Get_Each_Time_Min(), GameData::Get_Each_Time_Sec(),0xffffff);

	//スコア表示
	DrawFormatString(20, 220, 0xffffff, "スコア：%d", GameData::Get_Score());

	//スコア
	DrawFormatString(1050, 150, 0x00ff00, "Score : %d", GameData::Get_Score());

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
void Stage_Base::DrawUI_ON_Enemy(const EnemyBase* enemy) const
{
	//情報を取得
	Jan_Type type = enemy->GetType();
	int enemy_hp  = enemy->GetHP();
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

	default:
		break;
	}

	float draw_x = enemy_x - 50;  //描画ｘ
	float draw_y = enemy_y - 100; //描画ｙ

	//属性
	if(type != Jan_Type::NONE)DrawRotaGraph(draw_x - 20, draw_y + 5, 0.3, 1, typeImage[index], TRUE);
	//枠
	DrawBoxAA(draw_x - 3, draw_y - 3, draw_x + 103, draw_y + 13, 0xffffff, TRUE);
	DrawBoxAA(draw_x, draw_y, (draw_x + 100), draw_y + 10, 0x000000, TRUE);
	//HP
	DrawBoxAA(draw_x, draw_y, (draw_x + enemy_hp), draw_y + 10, bar_color, TRUE);
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
void Stage_Base::Touch_Janken(EnemyBase* enemy, Stage_Base* stage_ptr, int my_StageNum)
{
	//じゃんけん開始前 
	if (j_state == Jan_State::BEFORE)
	{
		//敵とプレイヤーが接触
		if (enemy->Hit_Character(obj_player) == true && nhit_time == 0)
		{
			//接触した!
			j_state = Jan_State::START;
			blackout_time = 0;

			//敵が出す手をランダムに決める　　　（ランダムなint型の値(0～2)を Jan_Type型に変換）
			Jan_Type enemy_janken = static_cast<Jan_Type> (GetRand(2));

			//じゃんけんオブジェクト生成
			obj_janken = new Janken(enemy_janken, my_StageNum);
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

		// 結果が _ERROR(じゃんけん中)でないとき、じゃんけん終了
		if (obj_janken->GetResult() != Jan_Result::_ERROR)
		{
			j_state = Jan_State::AFTER;
		}
	}
	else if (j_state == Jan_State::AFTER)
	{
		//Aボタンが押されたとき 
		if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
		{
			//プレイヤーの座標を初期値に
			obj_player->SetX(640);

			//じゃんけん終了
			switch (obj_janken->GetResult())
			{

			case Jan_Result::LOSE:    //負け

				//オーバーライドされたAfterJanken_LOSE()を呼び出す
				stage_ptr->AfterJanken_LOSE();

				//じゃん撃を初期化する
				enemy->Init_Jangeki();

				delete obj_janken;
				//あたり判定なし時間をセット
				nhit_time = NOT_COLLISION_TIME;

				//開始前にリセット
				j_state = Jan_State::BEFORE;
				break;


			case Jan_Result::WIN:     //勝ち

				//オーバーライドされたAfterJanken_WIN()を呼び出す
				stage_ptr->AfterJanken_WIN();

				//じゃん撃を初期化する
				enemy->Init_Jangeki();

				delete obj_janken;
				//あたり判定なし時間をセット
				nhit_time = NOT_COLLISION_TIME;

				//開始前にリセット
				j_state = Jan_State::BEFORE;

				break;


			case Jan_Result::ONEMORE: //あいこ

				//じゃん撃を初期化する
				enemy->Init_Jangeki();

				obj_janken->OneMore_Init();

				//じゃんけん開始
				j_state = Jan_State::PROGRESS;

				break;

			default:

				delete obj_janken;
				break;
			}



		}
	}
	else {}

	//衝突判定なし時間
	if (--nhit_time < 0) nhit_time = 0;
}


//じゃん撃ヒット時エフェクト 処理
void Stage_Base::Effect_Update_HitJangeki(const EnemyBase* enemy)
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


	//--------------------  playerじゃん撃とenemy  -------------------------------------
	{
		//playerのじゃん撃をとってくる
		Jangeki_Base** p_jan = obj_player->GetJangeki();

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
							obj_effect[effect_count] = new Effect_Jangeki(e_x, e_y);
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
							obj_effect[effect_count] = new Effect_Jangeki(e_x, e_y);
						}
					}
					break;

				case Jan_Type::PAPER:                          //敵の属性　パー

					//チョキのみ有効
					if (p_type == Jan_Type::ROCK)
					{
						//エフェクト生成
						if (obj_effect[effect_count] == nullptr && effect_count < _CONSTANTS_SB::EFFECT_MAX)
						{
							obj_effect[effect_count] = new Effect_Jangeki(e_x, e_y);
						}
					}
					break;

				default:
					break;
				}
			}
		}
	}
	//----------------------------------------------------------------------------------

	//--------------------  enemyじゃん撃とplayer  -------------------------------------
	{
		//enemyのじゃん撃をとってくる
		Jangeki_Base** e_jan = enemy->GetJangeki();

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
					obj_effect[effect_count] = new Effect_Jangeki(p_x, p_y);
				}
			}
		}
	}
	//----------------------------------------------------------------------------------
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
}


//じゃんけん描画
void Stage_Base::Draw_Janken() const
{
	obj_janken->Draw();
}

//じゃんけん開始直後
void Stage_Base::Draw_JankenStart() const
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, static_cast<int>(blackout_time * 5));
	DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//DrawBox(0, 0, static_cast<int>(blackout_time), static_cast<int>(blackout_time), 0xffffff, TRUE);
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
	////無理やり
	//if (j_state == Jan_State::START) return Jan_State::BEFORE;
	//else return j_state;

	return j_state;
}
