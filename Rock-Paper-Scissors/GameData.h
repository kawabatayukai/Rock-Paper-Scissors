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

	//制限時間を設定（各ステージの番号）
	static void Set_TimeLimit(const unsigned int time_limit = 999);

	//時間カウンター
	static void Time_Update();

	//(各ステージの)制限時間を取得
	static unsigned int Get_Each_Time();

	//総合時間を取得
	static unsigned int Get_Total_Time();

private:
	GameData();     //オブジェクトは作れない

	static unsigned int g_score;       //スコア（ゲームプレイ中ずっと保持）
	static unsigned int total_time;    //総合時間


	static unsigned int each_stage_time;   //各ステージの制限時間
};