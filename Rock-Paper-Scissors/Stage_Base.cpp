#include "Stage_Base.h"
#include"DxLib.h"

Stage_Base::Stage_Base()
{
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, typeImage);
	hpImage = LoadGraph("images/HitPoint.png");
}

Stage_Base::~Stage_Base()
{

}

void Stage_Base::DrawUI(Jan_Type type ,int hp) const
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
		DrawRotaGraph(950, 60, 0.5, 0, typeImage[2], TRUE);
		break;
	default:
		break;
	}

	DrawRotaGraph(1030, 60, 0.5, 0, hpImage, TRUE);			//体力ゲージ枠
	DrawBox(948, 45, 948 + hp * 2.54, 75, 0x00ff00, TRUE);	//体力ゲージ
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