#include"DxLib.h"
#include"GameData.h"



unsigned int GameData::g_score;     //スコア
unsigned int GameData::max_score;   //スコア
int GameData::pierced_count;        //貫通回数

int GameData::total_time;        //総合時間

int GameData::each_stage_time;   //各ステージの制限時間
int GameData::c_time_limit;      //制限時間（固定）

GAME_DIFFICULTY GameData::game_Diff;

//初期化
void GameData::Init_Data()
{
	g_score = 0;
	max_score = 0;
	total_time = 0;
}

//スコア加算
void GameData::Add_Score(unsigned int score)
{
	if (score < 0) return;
	max_score += score;
}

//スコア取得
unsigned int GameData::Get_Score()
{
	return g_score;
}

//スコア取得(本来)
unsigned int GameData::Get_MaxScore()
{
	return max_score;
}

//貫通回数加算 デフォルト:2
void GameData::Add_PierceCount(const int& add)
{
	if (add == 0)     pierced_count = 0;    //引数が0の時は初期化する
	else if (add > 0) pierced_count += add;
	else return;
}

//貫通回数取得
int GameData::Get_PierceCount()
{
	return pierced_count;
}

//制限時間を設定（各ステージの制限時間）
void GameData::Set_TimeLimit(const int time_limit)
{
	//強制3分

	//0以下の場合は処理しない
	if (time_limit < 0)
	{
		each_stage_time = 999;
	}

	//each_stage_time = 10800;
	each_stage_time = time_limit;
	c_time_limit = each_stage_time;
}

//時間カウンター
void GameData::Time_Update()
{
	//総合時間は加算
	total_time++;

	//制限時間は減算
	each_stage_time--;
	if (each_stage_time < 0) each_stage_time = 0;

	if (g_score < max_score) g_score++;
	if (g_score > max_score) g_score = max_score;
}

//制限時間（設定値）取得
int GameData::Get_ConstTimeLimit()
{
	return c_time_limit;
}

//(各ステージの)制限時間を取得（ミリ秒）
int GameData::Get_Each_Time()
{
	return each_stage_time;
}

//(各ステージの)制限時間を取得（秒）
int GameData::Get_Each_Time_Sec()
{
	//分(3600ミリ秒)で割った余り
	unsigned int ret = each_stage_time % 3600;

	if (each_stage_time < 1)
	{
		return 0;
	}
	else
	{
		//0除算防止
		if (ret < 60)
			return 0;
		else
			return ret / 60;
	}
}

//(各ステージの)制限時間を取得（分）
int GameData::Get_Each_Time_Min()
{
	if (each_stage_time < 1)
	{
		return 0;
	}
	else
	{
		//0除算防止
		if (each_stage_time < 3600)
			return 0;
		else
			return each_stage_time / 3600;
	}
}

//総合時間を取得
int GameData::Get_Total_Time()
{
	return total_time;
}

/*難易度*/
void GameData::Set_DIFFICULTY(GAME_DIFFICULTY game_diff)
{
	game_Diff = game_diff;
}

/*難易度*/
GAME_DIFFICULTY GameData::Get_DIFFICULTY()
{
	return game_Diff;
}
