#include"DxLib.h"
#include"KeyManager.h"
#include"Janken.h"


//コンストラクタ　　　　　　　　　　enemyの出す手が決まる
Janken::Janken(Jan_Type enemy_jan, const int stage_num)
	: enemy_jan(enemy_jan), p_image_x(-50), e_image_x(1330), stage_num(stage_num)
{
	//適当に初期化
	player_jan = Jan_Type::ROCK;
	result = Jan_Result::_ERROR;

	//画像読み込み
	LoadDivGraph("images/Janken_Test.png", 3, 3, 1, 200, 200, image);
	image_back = LoadGraph("images/Janken/touch_janBack.png");             //じゃんけん中背景
	image_back_light = LoadGraph("images/Janken/Jan_Lightning_Red.png");

	image_hand = LoadGraph("images/Janken_Hand2.png");

	LoadDivGraph("images/ワンパンマンALL画像.png", 1, 1, 1, 100, 100, &image_player);
	//image_player = LoadGraph("images/sd_body-1.png");     //プレイヤー
	image_enemy = LoadGraph("images/tyokitest.png");

	//敵の画像
	{
		image_all_enemy[0] = LoadGraph("images/tyokitest.png");
		image_all_enemy[1] = LoadGraph("images/tyokitest.png");
		image_all_enemy[2] = LoadGraph("images/stage02/ex.png");
		image_all_enemy[3] = LoadGraph("images/stage03/stage03attack.png");
		image_all_enemy[4] = LoadGraph("images/Stage04/stage_Boss04.png");
		image_all_enemy[5] = LoadGraph("images/stage05/Stage5_Enemy_NoMove_Left.png");
		image_all_enemy[6] = LoadGraph("images/tyokitest.png");
		image_all_enemy[7] = LoadGraph("images/tyokitest.png");
		image_all_enemy[8] = LoadGraph("images/stage08/Stage8_image100.png");
		image_all_enemy[9] = LoadGraph("images/stage09/Stage9_100.png");
		image_all_enemy[10] = LoadGraph("ステージ10敵の画像単体.png");
	}

	//背景
	{
		image_all_back[0] = -1;
		image_all_back[1] = LoadGraph("images/stage01/Tutorial_Back.png");
		image_all_back[2] = LoadGraph("images/stage02/mizuumi01.png");
		image_all_back[3] = LoadGraph("images/stage03/stage03back.png");
		image_all_back[4] = LoadGraph("images/Stage04/Stage_Image2.png");
		image_all_back[5] = LoadGraph("images/stage05/Stage5_Stageimage.png");
		image_all_back[6] = LoadGraph("images/stage06/mori32-.png");
		image_all_back[7] = LoadGraph("images/stage07/back02.png");
		image_all_back[8] = LoadGraph("images/stage08/Stage08_1.jpg");
		image_all_back[9] = LoadGraph("images/stage09/stage09_image.png");
		image_all_back[10] = 0; //LoadGraph("images/stage10/tyokitest.png");
	}

	//フォントデータを作成　　　　　　Windows標準搭載フォントなら大丈夫。多分　　　[候補 "Yu Gothic UI"]
	font_result = CreateFontToHandle("メイリオ", 70, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2);
	font_other = CreateFontToHandle("メイリオ", 40, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);

	//色
	blue      = GetColor(0, 0, 255);    
	red       = GetColor(255, 0, 0);
	brack     = GetColor(0, 0, 0);
	white     = GetColor(255, 255, 255);
	green     = GetColor(0, 255, 0);
}

//デストラクタ
Janken::~Janken()
{
	//フォントデータを削除
	DeleteFontToHandle(font_result);
}

//更新
void Janken::Update()
{
	//40フレーム後
	if (++time > 40)
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
	else
	{
		const int speed = 10;     //移動スピード
		const int p_goal = 200;   //停止点player
		const int e_goal = 1070;  //停止点enemy

		//プレイヤー画像を移動させる
		p_image_x += speed;
		if (p_image_x > p_goal) p_image_x = p_goal;

		//敵画像を移動させる
		e_image_x -= speed;
		if (e_image_x < e_goal) e_image_x = e_goal;
	}
}

//描画
void Janken::Draw() const
{
	//背景
	if (stage_num == 0 || image_all_back[stage_num] == -1)        //画像読み込み失敗
	{
		DrawBox(0, 0, 1280, 720, 0x808080, TRUE);
	}
	else
	{
		DrawGraph(0, 0, image_all_back[stage_num], FALSE);
	}

	//"VS"
	DrawGraph(0, 0, image_back, TRUE);

	//DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
	////SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//DrawGraph(0, 0, image_back_light, TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	//プレイヤー
	DrawRotaGraph(p_image_x, 300, 2, 0, image_player, TRUE);

	//画像読み込みに失敗していなければ
	if (image_all_enemy[stage_num] != -1)
	{
		DrawRotaGraph(e_image_x, 600, 2, 0, image_all_enemy[stage_num], TRUE);
	}
	else
	{
		DrawRotaGraph(e_image_x, 600, 2, 0, image_enemy, TRUE);
	}


	//40フレーム後
	if (time > 40)
	{
		//どのボタンも押されていないとき
		if (button_B == false && button_Y == false && button_X == false)
		{
			DrawStringToHandle(380, 450, "じゃんけん....", white, font_other);

			//ふきだし
			DrawOval(600, 100, 130, 80, 0xffffff, TRUE);
			DrawOval(480, 200, 40, 20, 0xffffff, TRUE);
			DrawOval(400, 230, 20, 10, 0xffffff, TRUE);
			DrawRotaGraph(600, 100, 0.35, 0, image_hand, TRUE);  //手
		}
		else
		{
			DrawStringToHandle(400, 450, "ぽ ん", white, font_other);

			//プレイヤーの手
			DrawRotaGraph(420, 180, 1.0, 0.5, image[static_cast<int>(player_jan)], TRUE);

			//敵の手
			DrawRotaGraph(850, 500, 1.0, 0.5, image[static_cast<int>(enemy_jan)], TRUE);


			//じゃんけんの結果（プレイヤー目線）
			switch (result)
			{
			case Jan_Result::LOSE:

				DrawStringToHandle(50, 50, "LOSE...", blue, font_result, brack);
				DrawStringToHandle(950, 300, "WIN!", red, font_result, brack);
				break;

			case Jan_Result::WIN:

				DrawStringToHandle(50, 50, "WIN!", red, font_result, brack);
				DrawStringToHandle(950, 300, "LOSE...", blue, font_result, brack);
				break;

			case Jan_Result::ONEMORE:

				DrawStringToHandle(50, 50, "AGAIN!", 0xffffff, font_result);
				DrawStringToHandle(850, 300, "AGAIN!", 0xffffff,font_result);
				break;

			default:
				break;
			}

			//点滅
			static int counter;

			if (counter++ < 30)
			{
				DrawStringToHandle(350, 650, "-- Press  A  Button --", white, font_other, green);
			}
			else if (counter > 60)  counter = 0;
			else {}
		}
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


//(あいこの時用) 必要な変数を初期化する
void Janken::OneMore_Init()
{
	button_B = false;   //Bボタンが押されているか
	button_Y = false;   //Yボタンが押されているか
	button_X = false;   //Xボタンが押されているか

	//敵の出す手を再設定
	enemy_jan = static_cast<Jan_Type> (GetRand(2));

	result = Jan_Result::_ERROR;
}