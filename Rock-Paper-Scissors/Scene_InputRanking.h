<<<<<<<< HEAD:Rock-Paper-Scissors/Scene_InputRanking.h
#pragma once
#include <stdio.h>

#define RANKING_DATA 10

/*�����L���O�f�[�^�i�\����*/
struct RankingData {

	int no;

	char name[11];

	long score;
};


class Scene_InputRanking
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
};
extern Scene_InputRanking inputRanking;
========
//#pragma once
//#include "AbstractScene.h"
//#include <stdio.h>
//
//#define RANKING_DATA 10
//
///*�����L���O�f�[�^�i�\����)*/
//struct RankingData
//{
//	int rank; //���ʔԍ�
//
//	char name[11]; //���O[11]
//
//	long score; //�X�R�A
//
//	//int time;  //����
//};
//
//class SortSave :
//    public AbstractScene
//{
//private:
//	FILE* fp;
//
//	RankingData dataRanking[RANKING_DATA];  // �����L���O�f�[�^�ϐ��錾
//
//public:
//
//	SortSave(const char* name);
//
//	//�X�V
//	void Update()override;
//
//	//�`��
//	void Draw()const override;
//
//	/*�����L���O���בւ�*/
//	void SortRanking(void);
//
//	/*�����L���O�f�[�^�̕ۑ�*/
//	int  SaveRanking(void);
//
//	/*�����L���O�f�[�^�ǂݍ���*/
//	int ReadRanking(void);
//
//	//�X�R�A���Z�b�g
//	void setScore(int i, int score);
//
//	//�V�[���̕ύX����
//	AbstractScene* ChangeScene()override;
//
//};
//
>>>>>>>> parent of bfaa0a9 (ランキング処理の変更追加):Rock-Paper-Scissors/SortSave.h
