#include"GameData.h"
#include"Scene_InputNameRanking.h"
#include "SortSave.h"

SortSave sortSave;

/*ランキング並べ替え*/
void SortSave::SortRanking(void)
{
	int i, j;
	RankingData work;

	// 選択法ソート
	for (i = 0; i < 9; i++) {
		for (j = i + 1; j < RANKING_DATA; j++) {
			if (g_Ranking[i].score <= g_Ranking[j].score)
			{
				work = g_Ranking[i];
				g_Ranking[i] = g_Ranking[j];
				g_Ranking[j] = work;
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
		for (j = i + 1; j < RANKING_DATA; j++) {
			if (g_Ranking[i].score > g_Ranking[j].score)
			{
				g_Ranking[j].no++;
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
		if ((fopen_s(&fp, "dat/rankingdata.txt", "w")) != 0)
		{
			/* エラー処理 */
			printf("Ranking Data Error\n");
			return -1;
		}
	}

	// ランキングデータ分配列データを書き込む
	for (int i = 0; i < RANKING_DATA; i++)
	{
		fprintf_s(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	//ファイルクローズ
	fclose(fp);

	return 0;
}
int  SortSave::ReadRanking(void)
{
	/*通常モード*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL)
	{
		//ファイルオープン
		if ((fopen_s(&fp, "dat/rankingdata_HARD.txt", "r")) != 0)
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
		if ((fopen_s(&fp, "dat/rankingdata_HARD.txt", "w")) != 0)
		{
			/* エラー処理 */
			printf("Ranking Data Error\n");
			return -1;
		}
	}

	//ランキングデータ配分列データを読み込む
	for (int i = 0; i < RANKING_DATA; i++)
	{
		fscanf_s(fp, "%2d %10s %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
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

void SortSave::setName(int i, char name[11])
{
	int j;

	for (j = 0; '\0' != name[j]; j++)
	{
		g_Ranking[i].name[j] = name[j];
	}
	g_Ranking[i].name[j] = '\0';
}

void SortSave::setScore(int i, int score)
{
	if (0 <= score)
	{
		g_Ranking[i].score = GameData::Get_Score();
	}
}

void SortSave::setTimer(int i, int time)
{
	if (0 <= time)
	{
		g_Ranking[i].time = GameData::Get_Total_Time();
	}
}