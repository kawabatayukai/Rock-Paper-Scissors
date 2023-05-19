#include"GameData.h"
#include"Scene_InputNameRanking.h"
#include "SortSave.h"

SortSave sortSave;

/*ランキング並べ替え*/
void SortSave::SortRanking(void)
{
	int i, j;
	RankingData work;

	//g_Ranking[9].timeMin = GameData::Get_Total_Time() / 3600;
	//g_Ranking[9].timeSec = (GameData::Get_Total_Time() % 3600) / 60;

	/*********
	* スコア *
	*********/
	//// 選択法ソート
	//for (i = 0; i < 9; i++) {
	//	for (j = i + 1; j < RANKING_DATA; j++) {
	//		if (g_Ranking[i].score <= g_Ranking[j].score)
	//		{
	//			work = g_Ranking[i];
	//			g_Ranking[i] = g_Ranking[j];
	//			g_Ranking[j] = work;
	//		}
	//	}
	//}
	//// 順位付け
	//for (i = 0; i < RANKING_DATA; i++)
	//{
	//	g_Ranking[i].no = 1;
	//}
	//// 得点が同じ場合は、同じ順位とする
	//// 同順位があった場合の次の順位はデータ個数が加算された順位とする
	//for (i = 0; i < RANKING_DATA - 1; i++) {
	//	for (j = i + 1; j < RANKING_DATA; j++) 
	//	{
	//		if (g_Ranking[i].score > g_Ranking[j].score)
	//		{
	//			g_Ranking[j].no++;
	//		}
	//	}
	//}

	/********
	* 時間  *
	********/
		// 選択法ソート
		for (i = 0; i < 9; i++) {
			for (j = i + 1; j < RANKING_DATA; j++) 
			{
				if (g_Ranking[i].timeMin > 0) //0以上
				{
					if (g_Ranking[i].timeMin <= g_Ranking[j].timeMin)
					{
						work = g_Ranking[i];
						g_Ranking[i] = g_Ranking[j];
						g_Ranking[j] = work;
					}
				}
				else  //0以下
				{
					if (g_Ranking[i].timeSec <= g_Ranking[j].timeSec)
					{
						work = g_Ranking[i];
						g_Ranking[i] = g_Ranking[j];
						g_Ranking[j] = work;
					}
				}
			}
		}

		// 順位付け
		for (i = 0; i < RANKING_DATA; i++)
		{
			g_Ranking[i].no = 1;
		}

		// 得点が同じ場合は、同じ順位とする
		// 同順位があった場合の次の順位はデータ個数が加算された順位とする
		for (i = 0; i < RANKING_DATA - 1; i++) {
			for (j = i + 1; j < RANKING_DATA; j++)
			{
				if (g_Ranking[i].timeMin > 0) //0以上
				{
					if (g_Ranking[i].timeMin > g_Ranking[j].timeMin)
					{
						g_Ranking[j].no++;
					}
				}
				else   //0以下
				{
					if (g_Ranking[i].timeSec > g_Ranking[j].timeSec)
					{
						g_Ranking[j].no++;
					}
				}
			}
		}
}

/*ランキングデータの保存*/
int SortSave::SaveRanking(void)
{
	/*通常モード*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL)
	{
		// ファイルオープン
		if ((fopen_s(&fp, "dat/rankingdata.txt", "w")) != 0)
		{
			/* エラー処理 */
			printf("Ranking Data Error\n");
			return -1;
		}
	}

	/*即死モード*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD)
	{
		// ファイルオープン
		if ((fopen_s(&fp, "dat/rankingdata_HARD.txt", "w")) != 0)
		{
			/* エラー処理 */
			printf("Ranking Data Error\n");
			return -1;
		}
	}

	// ランキングデータ分配列データを書き込む
	for (int i = 0; i < RANKING_DATA; i++)
	{
	/*********
	* スコア *
	*********/
		//fprintf_s(fp, "%2d %10s %10d %10d %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score, g_Ranking[i].timeMin, g_Ranking[i].timeSec);

	/********
	* 時間  *
	********/
		fprintf_s(fp, "%2d %10s %10d %10d %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].timeMin, g_Ranking[i].timeSec, g_Ranking[i].score);
	}

	//ファイルクローズ
	fclose(fp);

	return 0;
}

/*ランキングデータの読み込み*/
int  SortSave::ReadRanking(void)
{
	/*通常モード*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL)
	{
		//ファイルオープン
		if ((fopen_s(&fp, "dat/rankingdata.txt", "r")) != 0)
		{
			//エラー処理
			printf("Ranking Data Error\n");
			return -1;
		}
	}

	/*即死モード*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD)
	{
		// ファイルオープン
		if ((fopen_s(&fp, "dat/rankingdata_HARD.txt", "r")) != 0)
		{
			/* エラー処理 */
			printf("Ranking Data Error\n");
			return -1;
		}
	}

	//ランキングデータ配分列データを読み込む
	for (int i = 0; i < RANKING_DATA; i++)
	{
	/*********
	* スコア *
	*********/
		//fscanf_s(fp, "%2d %10s %10d %10d %10d", &g_Ranking[i].no, g_Ranking[i].name,sizeof(g_Ranking[i].name), &g_Ranking[i].score, &g_Ranking[i].timeMin, &g_Ranking[i].timeSec);

	/********
	* 時間  *
	********/
		fscanf_s(fp, "%2d %10s %10d %10d %10d", &g_Ranking[i].no, g_Ranking[i].name, sizeof(g_Ranking[i].name), &g_Ranking[i].timeMin, &g_Ranking[i].timeSec, &g_Ranking[i].score);
	}

	//ファイルクローズ
	fclose(fp);

	return 0;
}

/*ランキングデータ（構造体*/
RankingData SortSave::getRankingData(int i)
{
	return g_Ranking[i];
}

/*名前*/
void SortSave::setName(int i, char name[11])
{
	int j;

	for (j = 0; '\0' != name[j]; j++)
	{
		g_Ranking[i].name[j] = name[j];
	}
	g_Ranking[i].name[j] = '\0';
}

/*スコア*/
void SortSave::setScore(int i, int score)
{
	if (0 <= score)
	{
		g_Ranking[i].score = GameData::Get_Score();
	}
}

/*時間：分*/
void SortSave::setTimerMin(int i, int time)
{
	if (0 < time)
	{
		g_Ranking[i].timeMin = GameData::Get_Total_Time() / 3600;
	}
}

/*時間：秒*/
void SortSave::setTimerSec(int i, int time)
{
	if (0 < time)
	{
		g_Ranking[i].timeSec = (GameData::Get_Total_Time() % 3600) / 60;
	}
}