#pragma once
#include <stdio.h>

#define RANKING_DATA 10

/*�����L���O�f�[�^�i�\����*/
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
	RankingData g_Ranking[RANKING_DATA];  // �����L���O�f�[�^�ϐ��錾

public:

	/*�����L���O���בւ�*/
	void SortRanking(void);

	/*�����L���O�f�[�^�̕ۑ�*/
	int  SaveRanking(void);

	/*�����L���O�f�[�^�ǂݍ���*/
	int ReadRanking(void);

	/*�����L���O�f�[�^�i�\����*/
	RankingData getRankingData(int i);

	void setName(int i, char name[11]);

	void setScore(int i, int score);

	void setTimer(int i, int time);
};
extern SortSave sortSave;
