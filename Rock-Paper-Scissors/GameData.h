#pragma once

//データを保持する
class GameData
{
public:

	//初期化
	static void Init_Data();

	//スコア加算
	static void Add_Score(unsigned int score);

	static unsigned int Get_Score() ;

private:
	GameData();     //オブジェクトは作れない

	static unsigned int g_score;       //スコア（ゲームプレイ中ずっと保持）
	static unsigned int total_time;    //総合時間
};