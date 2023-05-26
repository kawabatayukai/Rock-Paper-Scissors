#include"ranking.h"
#include"DxLib.h"
#include<fstream>
#include<string>
#include<iomanip>
#include"GameData.h"
#include"KeyManager.h"
#include"Scene_Title.h"

Rank::Rank(const char* file_path): now_sort(SORT_TYPE::SCORE)
{
	Load(file_path);

	backimage = LoadGraph("images/Rankingback.png");
	ranking_font = CreateFontToHandle("���C���I", 30, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);
}

//�����L���O��������
Rank::Rank(const char* file_path, const SORT_TYPE& sortType)
{
	Load(file_path);

	//�o�^
	rank_data[9].no = 9;
	rank_data[9].name = GameData::GetPlayerName();
	rank_data[9].score = GameData::Get_MaxScore();
	rank_data[9].timeMin = GameData::Get_Total_Time() / 3600;
	rank_data[9].timeSec = (GameData::Get_Total_Time() % 3600) / 60;

	//���ёւ�
	Sort(sortType);

	//��������
	using namespace std;
	fstream file;
	//open
	file.open(file_path, ios::out);
	//�ǂݍ��ݎ��s
	if (file.fail() == true) cerr << "Error";

	if (sortType == SORT_TYPE::SCORE)
	{
		//10�񏑂�����
		for (int i = 0; i < 10; i++)
		{
			file << setw(2) << right << rank_data[i].no
				<< setw(10) << right << rank_data[i].name
				<< rank_data[i].score << rank_data[i].timeMin << rank_data[i].timeSec << endl;
		}
	}
	else if (sortType == SORT_TYPE::TIME)
	{
		//10�񏑂�����
		for (int i = 0; i < 10; i++)
		{
			file << setw(2) << right << rank_data[i].no
				<< setw(10) << right << rank_data[i].name
				<< rank_data[i].timeMin << rank_data[i].timeSec << rank_data[i].score << endl;
		}
	}
	file << resetiosflags(ios_base::floatfield);

	backimage = LoadGraph("images/Rankingback.png");
	ranking_font = CreateFontToHandle("���C���I", 30, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);
}

Rank::~Rank()
{

}

void Rank::Update()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_B))
	{
		if (now_sort == SORT_TYPE::SCORE) now_sort = SORT_TYPE::TIME;
		else if (now_sort == SORT_TYPE::TIME) now_sort = SORT_TYPE::SCORE;
		else {};

		Sort(now_sort);
	}
}

void Rank::Draw() const
{
	DrawGraph(0, 0, backimage, FALSE);

	if (now_sort == SORT_TYPE::SCORE)
	{
		for (int i = 0; i < 10; i++)
		{
			DrawFormatStringToHandle(0, 170 + i * 50, 0xFFFFFF, ranking_font, "%2d��   %10s  �X�R�A�F%10d  �������ԁF %10d��%10d�b %s",
				rank_data[i].no, rank_data[i].name.c_str(), rank_data[i].score, rank_data[i].timeMin, rank_data[i].timeSec,
				GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL ? "NORMAL" : "HARD");
		}
	}
	else if (now_sort == SORT_TYPE::TIME)
	{
		for (int i = 0; i < 10; i++)
		{
			DrawFormatStringToHandle(0, 170 + i * 50, 0xFFFFFF, ranking_font, "%2d��   %10s  �������ԁF %10d��%10d�b �X�R�A�F%10d %s",
				rank_data[i].no, rank_data[i].name.c_str(), rank_data[i].timeMin, rank_data[i].timeSec, rank_data[i].score, 
				GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL ? "NORMAL" : "HARD");
		}
	}

}

//�t�@�C���ǂݍ���
void Rank::Load(const char* file_path)
{
	using namespace std;
	fstream file;

	//open
	file.open(file_path, ios::in);

	//�ǂݍ��ݎ��s
	if (file.fail() == true) cerr << "Error";

	//1�s���̃f�[�^���i�[
	string line_data;
	int i = 0;
	while (getline(file, line_data))
	{
		RankingData data = RankingData{ 0,"",0,0,0 };
		char name[11];

		int result = sscanf_s(line_data.c_str(), "%d %s %d %d %d",
			&data.no, name, static_cast<unsigned int>(sizeof(name)),
			&data.score, &data.timeMin, &data.timeSec);

		name[10] = '\0';
		data.name = string(name);
		if (i > 10)rank_data[i] = data;
		i++;
	}

	//close
	file.close();
}

void Rank::Sort(const SORT_TYPE& type)
{
	int i, j;
	RankingData work;

	//�X�R�A��
	if (type == SORT_TYPE::SCORE)
	{
		// �I��@�\�[�g
		for (i = 0; i < 9; i++)
		{
			for (j = i + 1; j < 10; j++)
			{
				if (rank_data[i].score <= rank_data[j].score)
				{
					work = rank_data[i];
					rank_data[i] = rank_data[j];
					rank_data[j] = work;
				}
			}
		}
	}
	// ���ԏ�
	else if (type == SORT_TYPE::TIME)
	{
		int atime = 0;
		int btime = 0;

		// �I��@�\�[�g
		for (i = 0; i < 9; i++)
		{
			atime = (rank_data[i].timeMin * 60) + (rank_data[i].timeSec);
			for (j = i + 1; j < 10; j++)
			{
				btime = (rank_data[j].timeMin * 60) + (rank_data[j].timeSec);
				if (atime >= btime)
				{
					work = rank_data[i];
					rank_data[i] = rank_data[j];
					rank_data[j] = work;
				}
			}
		}
	}

	// ���ʕt��
	for (i = 0; i < 10; i++)
	{
		rank_data[i].no = 1;
	}

	// ���_�������ꍇ�́A�������ʂƂ���
	// �����ʂ��������ꍇ�̎��̏��ʂ̓f�[�^�������Z���ꂽ���ʂƂ���
	for (i = 0; i < 10 - 1; i++) 
	{
		for (j = i + 1; j < 10; j++)
		{
			if (rank_data[i].score > rank_data[j].score)
			{
				rank_data[j].no++;
			}
		}
	}
}

AbstractScene* Rank::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)//KEY_INPUT_RETURN
	{

		return dynamic_cast<AbstractScene*> (new TitleScene());

	}

	return this;
}
