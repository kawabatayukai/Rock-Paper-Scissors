#pragma once
#include <stdio.h>

#define RANKING_DATA 10

/*ランキングデータ（構造体*/
struct RankingData {

	int no;

	char name[11];

	long score;

	int time;
};


class SortSave
{
private:
	FILE* fp;
	RankingData g_Ranking[RANKING_DATA];  // ランキングデータ変数宣言

public:

	/*ランキング並べ替え*/
	void SortRanking(void);

	/*ランキングデータの保存*/
	int  SaveRanking(void);

	/*ランキングデータ読み込み*/
	int ReadRanking(void);

	/*ランキングデータ（構造体*/
	RankingData getRankingData(int i);

	void setName(int i, char name[11]);

	void setScore(int i, int score);

	void setTimer(int i, int time);
};
extern SortSave sortSave;
