#pragma once
#include<iostream>
#include<vector>
#include"AbstractScene.h"

class Rank : public AbstractScene
{
public:
	Rank(const char* file_path);
	~Rank();

	void Update();
	void Draw() const;

	AbstractScene* ChangeScene();

private:
	
	struct RankingData 
	{
		int no;
		std::string name;
		int score;
		int timeMin;
		int timeSec;
	};
	std::vector<RankingData> rank_data;
};
