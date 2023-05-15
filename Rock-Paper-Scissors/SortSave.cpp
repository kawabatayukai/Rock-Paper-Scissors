#include"GameData.h"
#include"Scene_InputNameRanking.h"
#include "SortSave.h"

SortSave sortSave;

/*�����L���O���בւ�*/
void SortSave::SortRanking(void)
{
	int i, j;
	RankingData work;

	// �I��@�\�[�g
	for (i = 0; i < 9; i++) {
		for (j = i + 1; j < RANKING_DATA; j++) {
			if (g_Ranking[i].score <= g_Ranking[j].score)
			{
				work = g_Ranking[i];
				g_Ranking[i] = g_Ranking[j];
				g_Ranking[j] = work;
			}
		}
	}

	// ���ʕt��
	for (i = 0; i < RANKING_DATA; i++)
	{
		g_Ranking[i].no = 1;
	}

	// ���_�������ꍇ�́A�������ʂƂ���
	// �����ʂ��������ꍇ�̎��̏��ʂ̓f�[�^�������Z���ꂽ���ʂƂ���
	for (i = 0; i < RANKING_DATA - 1; i++) {
		for (j = i + 1; j < RANKING_DATA; j++) {
			if (g_Ranking[i].score > g_Ranking[j].score)
			{
				g_Ranking[j].no++;
			}
		}
	}
}

/*�����L���O�f�[�^�̕ۑ�*/
int SortSave::SaveRanking(void)
{
	/*�ʏ탂�[�h*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL)
	{
		// �t�@�C���I�[�v��
		if ((fopen_s(&fp, "dat/rankingdata.txt", "w")) != 0)
		{
			/* �G���[���� */
			printf("Ranking Data Error\n");
			return -1;
		}
	}

	/*�������[�h*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD)
	{
		// �t�@�C���I�[�v��
		if ((fopen_s(&fp, "dat/rankingdata.txt", "w")) != 0)
		{
			/* �G���[���� */
			printf("Ranking Data Error\n");
			return -1;
		}
	}

	// �����L���O�f�[�^���z��f�[�^����������
	for (int i = 0; i < RANKING_DATA; i++)
	{
		fprintf_s(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	//�t�@�C���N���[�Y
	fclose(fp);

	return 0;
}
int  SortSave::ReadRanking(void)
{
	/*�ʏ탂�[�h*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL)
	{
		//�t�@�C���I�[�v��
		if ((fopen_s(&fp, "dat/rankingdata_HARD.txt", "r")) != 0)
		{
			//�G���[����
			printf("Ranking Data Error\n");
			return -1;
		}
	}

	/*�������[�h*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD)
	{
		// �t�@�C���I�[�v��
		if ((fopen_s(&fp, "dat/rankingdata_HARD.txt", "w")) != 0)
		{
			/* �G���[���� */
			printf("Ranking Data Error\n");
			return -1;
		}
	}

	//�����L���O�f�[�^�z����f�[�^��ǂݍ���
	for (int i = 0; i < RANKING_DATA; i++)
	{
		fscanf_s(fp, "%2d %10s %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
	}

	//�t�@�C���N���[�Y
	fclose(fp);

	return 0;
}

/*�����L���O�f�[�^�i�\����*/
RankingData SortSave::getRankingData(int i)
{
	return g_Ranking[i];
}

void SortSave::setName(int i, char name[11])
{
	int j;

	for (j = 0; '\0' != name[j]; j++)
	{
		g_Ranking[i].name[j] = name[j];
	}
	g_Ranking[i].name[j] = '\0';
}

void SortSave::setScore(int i, int score)
{
	if (0 <= score)
	{
		g_Ranking[i].score = GameData::Get_Score();
	}
}

void SortSave::setTimer(int i, int time)
{
	if (0 <= time)
	{
		g_Ranking[i].time = GameData::Get_Total_Time();
	}
}