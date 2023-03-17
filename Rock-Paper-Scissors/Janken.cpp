#include"DxLib.h"
#include"KeyManager.h"
#include"Janken.h"

//コンストラクタ　　　　　　　　　　enemyの出す手が決まる
Janken::Janken(Jan_Type enemy_jan) : enemy_jan(enemy_jan)
{
	//適当に初期化
	player_jan = Jan_Type::ROCK;
	result = Jan_Result::_ERROR;

	//画像読み込み
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, image);

	SetFontSize(50);
}

//デストラクタ
Janken::~Janken()
{

	SetFontSize(20);
}

//更新
void Janken::Update()
{
	//B,Y,Xが押されるまでなにもしない 　押された瞬間if文の中
	if (Check_AnyButton() == true)
	{
		// じゃんけんの結果を取得
		result = Get_JankenResult();
	}
	else
	{
		return;   //何もしない
	}
}

//描画
void Janken::Draw() const
{
	//プレイヤー
	DrawCircle(120, 200, 200, 0xffffff, TRUE);
	DrawString(120, 200, "player", 0x000000);

	//敵
	DrawCircle(1160, 200, 200, 0xffff00, TRUE);
	DrawString(1160, 200, "enemy", 0x000000);

	//どのボタンも押されていないとき
	if (button_B == false && button_Y == false && button_X == false)
	{
		DrawString(280, 400, "じゃ ん け ん....", 0xffffff);
	}
	else
	{
		DrawString(280, 400, "ぽ ん", 0xffffff);

		//プレイヤーの手
		DrawRotaGraph(250, 580, 1.8, 1, image[static_cast<int>(player_jan)], TRUE);

		//敵の手
		DrawRotaGraph(1030, 580, 1.8, 1, image[static_cast<int>(enemy_jan)], TRUE);


		//じゃんけんの結果（プレイヤー目線）
		switch (result)
		{
		case Jan_Result::LOSE:

			DrawString(350, 300, "負けた", 0xffffff);
			break;

		case Jan_Result::WIN:

			DrawString(350, 300, "勝った", 0xffffff);
			break;

		case Jan_Result::ONEMORE:

			DrawString(350, 300, "あいこ", 0xffffff);
			break;

		default:
			break;
		}

		DrawString(300, 600, "Aボタンを押してください", 0xffffff);
	}

	
}


//B（グー）,Y（チョキ）,X（パー）のいずれかが押された瞬間、trueを返す
bool Janken::Check_AnyButton()
{
	//どのボタンも押されていないとき
	if( button_B == false && button_Y == false && button_X == false )
	{
		//どれかが押されると,3つのうち一つに true が入る
		button_B = KeyManager::OnPadClicked(PAD_INPUT_B);  //Bボタンの入力
		button_Y = KeyManager::OnPadClicked(PAD_INPUT_4);  //Yボタンを入力
		button_X = KeyManager::OnPadClicked(PAD_INPUT_3);  //Xボタンを入力
	}
	else
	{
		//playerの出す手が決まる
		if (button_B == true) player_jan = Jan_Type::ROCK;      //Bボタンの時はグー
		if (button_Y == true) player_jan = Jan_Type::SCISSORS;  //Yボタンの時はチョキ
		if (button_X == true) player_jan = Jan_Type::PAPER;     //Xボタンの時はパー

		//どれかが押されたらtrue
		return true;
	}

	//押されるまでfalse
	return false;
}



//"接触時じゃんけん"処理
//   Check_AnyButton() で押されたボタンと enemy（引数）の勝敗結果を返す (押されたボタン目線)
Jan_Result Janken::Get_JankenResult()
{
	// button_type（押されたボタン）が
	switch ( player_jan )
	{
	case Jan_Type::ROCK:         //グーの時

		if (enemy_jan == Jan_Type::PAPER)    return Jan_Result::LOSE;    //enemy（引数２番目）がパーの時
		if (enemy_jan == Jan_Type::SCISSORS) return Jan_Result::WIN;     //enemy（引数２番目）がチョキの時
		if (enemy_jan == Jan_Type::ROCK)     return Jan_Result::ONEMORE; //enemy（引数２番目）がグーの時
		break;

	case Jan_Type::SCISSORS:     //チョキの時

		if (enemy_jan == Jan_Type::ROCK)     return Jan_Result::LOSE;    //enemy（引数２番目）がグーの時
		if (enemy_jan == Jan_Type::PAPER)    return Jan_Result::WIN;     //enemy（引数２番目）がパーの時
		if (enemy_jan == Jan_Type::SCISSORS) return Jan_Result::ONEMORE; //enemy（引数２番目）がチョキの時
		break;

	case Jan_Type::PAPER:        //パーの時

		if (enemy_jan == Jan_Type::SCISSORS) return Jan_Result::LOSE;    //enemy（引数２番目）がチョキの時
		if (enemy_jan == Jan_Type::ROCK)     return Jan_Result::WIN;     //enemy（引数２番目）がグーの時
		if (enemy_jan == Jan_Type::PAPER)    return Jan_Result::ONEMORE; //enemy（引数２番目）がパーの時
		break;

	default:
		break;
	}

	//それ以外はエラー
	return Jan_Result::_ERROR;
}