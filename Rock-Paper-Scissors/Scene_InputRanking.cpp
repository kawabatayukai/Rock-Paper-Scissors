#include "Scene_InputRanking.h"
#include"GameData.h"
#include"Scene_InputName.h"

Scene_InputRanking inputRanking;

/*ランキング並べ替え*/
void Scene_InputRanking::SortRanking(void)
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
int Scene_InputRanking::SaveRanking(void)
{
	//FILE* fp;
//#pragma warning(disable:4996)

	// ファイルオープン
	if ((fopen_s(&fp, "dat/rankingdata.txt", "w")) != 0)
	{
		/* エラー処理 */
		printf("Ranking Data Error\n");
		return -1;
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
int  Scene_InputRanking::ReadRanking(void)
{
	//FILE* fp;
//#pragma warning(disable:4996)

	//ファイルオープン
	if ((fopen_s(&fp, "dat/rankingdata.txt", "r")) != 0)
	{
		//エラー処理
		printf("Ranking Data Error\n");
		return -1;
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
RankingData Scene_InputRanking::getRankingData(int i)
{
	return g_Ranking[i];
}

void Scene_InputRanking::setName(int i, char name[11])
{
	int j;

	for (j = 0; '\0' != name[j]; j++)
	{
		g_Ranking[i].name[j] = name[j];
	}
	g_Ranking[i].name[j] = '\0';
}

void Scene_InputRanking::setScore(int i, int score)
{
	if (0 <= score)
	{
		g_Ranking[i].score = GameData::Get_Score();
	}
}