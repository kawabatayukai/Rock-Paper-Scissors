#pragma once
#include<iostream>
#include<vector>
#include"AbstractScene.h"

//ソート種類
enum class SORT_TYPE
{
	SCORE,
	TIME
};
//ランキング操作
enum class RANK_TYPE
{
	READ,    // 読み込みのみ
	WRITE,   //	書き込み
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
	//ランキングデータ
	struct RankingData 
	{
		int no;
		std::string name;
		int score;
		int timeMin;
		int timeSec;
	};
	RankingData rank_data[10];  //データ
	SORT_TYPE now_sort;                  //現在のソート方法

	int ranking_font;   //フォント
	int backimage;      //背景画像
};
