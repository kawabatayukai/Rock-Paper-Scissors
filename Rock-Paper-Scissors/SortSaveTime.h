#pragma once
#include <stdio.h>

#define RANKING_DATA 10

/*�����L���O�f�[�^�i�\����*/
struct RankingDataTime {

	int no;

	char name[11];

	int score;

	int timeMin;

	int timeSec;
};

class SortSaveTime
{
private:
	FILE* fp;
	RankingDataTime g_RankingTime[RANKING_DATA];  // �����L���O�f�[�^�ϐ��錾

public:

	/*�����L���O���בւ�*/
	void SortRanking(void);

	/*�����L���O�f�[�^�̕ۑ�*/
	int  SaveRanking(void);

	/*�����L���O�f�[�^�ǂݍ���*/
	int ReadRanking(void);

	/*�����L���O�f�[�^�i�\����*/
	RankingDataTime getRankingData(int i);

	/*���O*/
	void setName(int i, char name[11]);

	/*�X�R�A*/
	void setScore(int i, int score);

	/*���ԁF��*/
	void setTimerMin(int i, int time);

	/*���ԁF�b*/
	void setTimerSec(int i, int time);

};
extern SortSaveTime sortSaveTime;
