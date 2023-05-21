#include "SortSaveTime.h"
#include "GameData.h"

SortSaveTime sortSaveTime;

/*ランキング並べ替え*/
void SortSaveTime::SortRanking(void)
{
	int i, j;
	RankingDataTime work;

	/********
	* 時間  *
	********/
	// 選択法ソート
	for (i = 0; i < 9; i++) {
		for (j = i + 1; j < RANKING_DATA; j++)
		{
			if (g_RankingTime[i].timeMin > 0) //0以上
			{
				if (g_RankingTime[i].timeMin <= g_RankingTime[j].timeMin)
				{
					work = g_RankingTime[i];
					g_RankingTime[i] = g_RankingTime[j];
					g_RankingTime[j] = work;
				}
			}
			else  //0以下
			{
				if (g_RankingTime[i].timeSec <= g_RankingTime[j].timeSec)
				{
					work = g_RankingTime[i];
					g_RankingTime[i] = g_RankingTime[j];
					g_RankingTime[j] = work;
				}
			}
		}
	}

	// 順位付け
	for (i = 0; i < RANKING_DATA; i++)
	{
		g_RankingTime[i].no = 1;
	}

	// 得点が同じ場合は、同じ順位とする
	// 同順位があった場合の次の順位はデータ個数が加算された順位とする
	for (i = 0; i < RANKING_DATA - 1; i++) {
		for (j = i + 1; j < RANKING_DATA; j++)
		{
			if (g_RankingTime[i].timeMin > 0) //0以上
			{
				if (g_RankingTime[i].timeMin > g_RankingTime[j].timeMin)
				{
					g_RankingTime[j].no++;
				}
			}
			else   //0以下
			{
				if (g_RankingTime[i].timeSec > g_RankingTime[j].timeSec)
				{
					g_RankingTime[j].no++;
				}
			}
		}
	}
}

/*ランキングデータの保存*/
int SortSaveTime::SaveRanking(void)
{
	/*通常モード*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL)
	{
		// ファイルオープン
		if ((fopen_s(&fp, "dat/rankingdataTIME.txt", "w")) != 0)
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
		if ((fopen_s(&fp, "dat/rankingdataTIME_HARD.txt", "w")) != 0)
		{
			/* エラー処理 */
			printf("Ranking Data Error\n");
			return -1;
		}
	}

	// ランキングデータ分配列データを書き込む
	for (int i = 0; i < RANKING_DATA; i++)
	{
	/********
	* 時間  *
	********/
		fprintf_s(fp, "%2d %10s %10d %10d %10d\n", g_RankingTime[i].no, g_RankingTime[i].name, g_RankingTime[i].timeMin, g_RankingTime[i].timeSec, g_RankingTime[i].score);
	}

	//ファイルクローズ
	fclose(fp);

	return 0;
}

/*ランキングデータの読み込み*/
int SortSaveTime::ReadRanking(void)
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
	/********
	* 時間  *
	********/
		fscanf_s(fp, "%2d %10s %10d %10d %10d\n", &g_RankingTime[i].no, g_RankingTime[i].name, sizeof(g_RankingTime[i].name), &g_RankingTime[i].timeMin, &g_RankingTime[i].timeSec, &g_RankingTime[i].score);
	}

	//ファイルクローズ
	fclose(fp);

	return 0;
}

/*ランキングデータ（構造体*/
RankingDataTime SortSaveTime::getRankingData(int i)
{
	return g_RankingTime[i];
}

/*名前*/
void SortSaveTime::setName(int i, char name[11])
{
	int j;

	for (j = 0; '\0' != name[j]; j++)
	{
		g_RankingTime[i].name[j] = name[j];
	}
	g_RankingTime[i].name[j] = '\0';
}

/*スコア*/
void SortSaveTime::setScore(int i, int score)
{
	if (0 <= score)
	{
		g_RankingTime[i].score = GameData::Get_Score();
	}
}

/*時間：分*/
void SortSaveTime::setTimerMin(int i, int time)
{
	if (0 < time)
	{
		g_RankingTime[i].timeMin = GameData::Get_Total_Time() / 3600;
	}
}

/*時間：秒*/
void SortSaveTime::setTimerSec(int i, int time)
{
	if (0 < time)
	{
		g_RankingTime[i].timeSec = (GameData::Get_Total_Time() % 3600) / 60;
	}
}