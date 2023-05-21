#pragma once
#include <stdio.h>

#define RANKING_DATA_COLUMN 10
#define RANKING_DATA_ROW 5

/*ランキングデータ（構造体*/
struct RankingData {

	int no;

	char name[11];

	 int score;

	 int timeMin;

	 int timeSec;
};


class SortSave
{
private:
	FILE* fp;
	RankingData g_Ranking[RANKING_DATA_COLUMN];  // ランキングデータ変数宣言

public:

	/*ランキング並べ替え*/
	void SortRanking(void);

	/*ランキングデータの保存*/
	int  SaveRanking(void);

	/*ランキングデータ読み込み*/
	int ReadRanking(void);

	/*ランキングデータ（構造体*/
	RankingData getRankingData(int i);

	/*名前*/
	void setName(int i, char name[11]);

	/*スコア*/
	void setScore(int i, int score);

	/*時間：分*/
	void setTimerMin(int i, int time);

	/*時間：秒*/
	void setTimerSec(int i, int time);

};
extern SortSave sortSave;
