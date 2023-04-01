#include "Stage_Base.h"
#include"KeyManager.h"
#include"DxLib.h"


//衝突判定なし時間   5秒
#define NOT_COLLISION_TIME  300

Stage_Base::Stage_Base()
{
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, typeImage);
	hpImage = LoadGraph("images/HitPoint.png");
}

Stage_Base::~Stage_Base()
{

}

//UI描画
void Stage_Base::DrawUI(Jan_Type type, int hp) const
{
	switch (type)
	{
	case Jan_Type::ROCK:
		DrawRotaGraph(810, 60, 0.5, 0, typeImage[0], TRUE);
		break;
	case Jan_Type::SCISSORS:
					
		DrawRotaGraph(810, 60, 0.5, 0, typeImage[1], TRUE);
		break;
	case Jan_Type::PAPER:
		DrawRotaGraph(810, 60, 0.5, 0, typeImage[2], TRUE);
		break;
	default:
		break;
	}

	DrawRotaGraph(1030, 60, 0.5, 0, hpImage, TRUE);			//体力ゲージ枠
	DrawBox(948, 45, 948 + static_cast<int>(hp * 2.54), 75, 0x00ff00, TRUE);	//体力ゲージ
	DrawFormatString(1120, 85, 0x00ff00, "残り:%d", hp);	//残り体力(数値)

	/*if (hp > 0) DrawFormatString(1000, 50, 0xffffff, "HP : %d", hp);
	else DrawString(1100, 50, "death!", 0xffffff);*/
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
			//じゃんけん開始
			j_state = Jan_State::PROGRESS;

			//敵が出す手をランダムに決める　　　（ランダムなint型の値(0～2)を Jan_Type型に変換）
			Jan_Type enemy_janken = static_cast<Jan_Type> (GetRand(2));

			//じゃんけんオブジェクト生成
			obj_janken = new Janken(enemy_janken, my_StageNum);
		}

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

				delete obj_janken;

				//じゃんけん開始
				j_state = Jan_State::PROGRESS;

				//じゃんけんオブジェクト生成
				obj_janken = new Janken(static_cast<Jan_Type> (GetRand(2)));
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