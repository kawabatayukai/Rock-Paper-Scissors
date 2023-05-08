#pragma once

//データを保持する
class GameData
{
public:

	//初期化
	static void Init_Data();

	//スコア加算
	static void Add_Score(unsigned int score);

	//スコア取得(描画用)
	static unsigned int Get_Score() ;

	//スコア取得(本来)
	static unsigned int Get_MaxScore();

	//制限時間を設定（各ステージの番号）
	static void Set_TimeLimit(const int time_limit = 10800);

	//時間カウンター
	static void Time_Update();

	//制限時間（設定値）取得
	static int Get_ConstTimeLimit();

	//(各ステージの)制限時間を取得（ミリ秒）
	static int Get_Each_Time();

	//(各ステージの)制限時間を取得（秒）
	static int Get_Each_Time_Sec();

	//(各ステージの)制限時間を取得（分）
	static int Get_Each_Time_Min();

	//総合時間を取得
	static int Get_Total_Time();

private:
	GameData();     //オブジェクトは作れない

	static unsigned int g_score;       //スコア（描画用　1ずつ増える)
	static unsigned int max_score;     //スコア

	static int total_time;    //総合時間


	static int each_stage_time;   //各ステージの制限時間
	static int c_time_limit;      //制限時間（最大）
};