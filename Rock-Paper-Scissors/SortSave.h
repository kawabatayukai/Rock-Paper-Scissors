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
