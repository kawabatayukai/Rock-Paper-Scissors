#pragma once
#include<iostream>
#include<vector>
#include"AbstractScene.h"

//�\�[�g���
enum class SORT_TYPE
{
	SCORE,
	TIME
};
//�����L���O����
enum class RANK_TYPE
{
	READ,    // �ǂݍ��݂̂�
	WRITE,   //	��������
};

class Rank : public AbstractScene
{
public:
	Rank(const char* file_path);
	Rank(const char* file_path, const SORT_TYPE& sortType);
	~Rank();

	void Update();
	void Draw() const;
	void Load(const char* file_path);
	void Sort(const SORT_TYPE& type = SORT_TYPE::SCORE);

	AbstractScene* ChangeScene();

private:
	//�����L���O�f�[�^
	struct RankingData 
	{
		int no;
		std::string name;
		int score;
		int timeMin;
		int timeSec;
	};
	RankingData rank_data[10];  //�f�[�^
	SORT_TYPE now_sort;                  //���݂̃\�[�g���@

	int ranking_font;   //�t�H���g
	int backimage;      //�w�i�摜
};
