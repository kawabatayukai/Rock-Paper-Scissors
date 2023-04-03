#include"DxLib.h"
#include"GameData.h"

unsigned int GameData::g_score;       //スコア（ゲームプレイ中ずっと保持）
unsigned int GameData::total_time;    //総合時間

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