#include"DxLib.h"
#include"GameData.h"

namespace TIME_LIMIT
{
	//各ステージの制限時間

	const int LIMIT_STAGE_02 = 999;
	const int LIMIT_STAGE_03 = 999;
	const int LIMIT_STAGE_04 = 999;
	const int LIMIT_STAGE_05 = 999;
	const int LIMIT_STAGE_06 = 999;
	const int LIMIT_STAGE_07 = 600;
	const int LIMIT_STAGE_08 = 999;
	const int LIMIT_STAGE_09 = 999;
	const int LIMIT_STAGE_10 = 999;
}

unsigned int GameData::g_score;           //スコア（ゲームプレイ中ずっと保持）
unsigned int GameData::total_time;        //総合時間

unsigned int GameData::each_stage_time;   //各ステージの制限時間

//初期化
void GameData::Init_Data()
{
	g_score = 0;
	total_time = 0;
}

//スコア加算
void GameData::Add_Score(unsigned int score)
{
	if (score < 0) return;
	g_score += score;
}

unsigned int GameData::Get_Score() 
{
	return g_score;
}


//制限時間を設定（各ステージの番号）
void GameData::Set_TimeLimit(const unsigned int time_limit)
{
	//0以下の場合は処理しない
	if (time_limit < 0)
	{
		each_stage_time = 999;
	}

	each_stage_time = time_limit;
}

//時間カウンター
void GameData::Time_Update()
{
	//総合時間は加算
	total_time++;

	//制限時間は減算
	each_stage_time--;
	if (each_stage_time < 0) each_stage_time = 0;
}

//(各ステージの)制限時間を取得
unsigned int GameData::Get_Each_Time()
{
	return each_stage_time;
}

//総合時間を取得
unsigned int GameData::Get_Total_Time()
{
	return total_time;
}