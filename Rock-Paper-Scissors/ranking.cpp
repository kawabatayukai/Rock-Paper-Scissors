#include"ranking.h"
#include"DxLib.h"
#include<fstream>
#include<string>

Rank::Rank(const char* file_path)
{
	using namespace std;
	fstream file;

	//open
	file.open(file_path, ios::in);

	//読み込み失敗
	if (file.fail() == true) cerr << "Error";

	//1行分のデータを格納
	string line_data;
	string str;

	while (getline(file, line_data))
	{
		RankingData data = { 0,"",0,0,0 };
		char name[11];

		int result = sscanf_s(line_data.c_str(), "%d %s %d %d %d",
			 &data.no, name, static_cast<unsigned int>(sizeof(name)),
			 &data.score, &data.timeMin, &data.timeSec);

		name[10] = '\0';
		data.name = string(name);
		rank_data.push_back(data);
	}

	//close
	file.close();
}

Rank::~Rank()
{

}

void Rank::Update()
{
}

void Rank::Draw() const
{
	for (int i = 0; i < 10; i++)
	{

	}
}

AbstractScene* Rank::ChangeScene()
{

	return this;
}
