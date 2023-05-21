#include "SortSaveTime.h"
#include "GameData.h"

SortSaveTime sortSaveTime;

/*�����L���O���בւ�*/
void SortSaveTime::SortRanking(void)
{
	int i, j;
	RankingDataTime work;

	/********
	* ����  *
	********/
	// �I��@�\�[�g
	for (i = 0; i < 9; i++) {
		for (j = i + 1; j < RANKING_DATA; j++)
		{
			if (g_RankingTime[i].timeMin > 0) //0�ȏ�
			{
				if (g_RankingTime[i].timeMin <= g_RankingTime[j].timeMin)
				{
					work = g_RankingTime[i];
					g_RankingTime[i] = g_RankingTime[j];
					g_RankingTime[j] = work;
				}
			}
			else  //0�ȉ�
			{
				if (g_RankingTime[i].timeSec <= g_RankingTime[j].timeSec)
				{
					work = g_RankingTime[i];
					g_RankingTime[i] = g_RankingTime[j];
					g_RankingTime[j] = work;
				}
			}
		}
	}

	// ���ʕt��
	for (i = 0; i < RANKING_DATA; i++)
	{
		g_RankingTime[i].no = 1;
	}

	// ���_�������ꍇ�́A�������ʂƂ���
	// �����ʂ��������ꍇ�̎��̏��ʂ̓f�[�^�������Z���ꂽ���ʂƂ���
	for (i = 0; i < RANKING_DATA - 1; i++) {
		for (j = i + 1; j < RANKING_DATA; j++)
		{
			if (g_RankingTime[i].timeMin > 0) //0�ȏ�
			{
				if (g_RankingTime[i].timeMin > g_RankingTime[j].timeMin)
				{
					g_RankingTime[j].no++;
				}
			}
			else   //0�ȉ�
			{
				if (g_RankingTime[i].timeSec > g_RankingTime[j].timeSec)
				{
					g_RankingTime[j].no++;
				}
			}
		}
	}
}

/*�����L���O�f�[�^�̕ۑ�*/
int SortSaveTime::SaveRanking(void)
{
	/*�ʏ탂�[�h*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL)
	{
		// �t�@�C���I�[�v��
		if ((fopen_s(&fp, "dat/rankingdataTIME.txt", "w")) != 0)
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
		if ((fopen_s(&fp, "dat/rankingdataTIME_HARD.txt", "w")) != 0)
		{
			/* �G���[���� */
			printf("Ranking Data Error\n");
			return -1;
		}
	}

	// �����L���O�f�[�^���z��f�[�^����������
	for (int i = 0; i < RANKING_DATA; i++)
	{
	/********
	* ����  *
	********/
		fprintf_s(fp, "%2d %10s %10d %10d %10d\n", g_RankingTime[i].no, g_RankingTime[i].name, g_RankingTime[i].timeMin, g_RankingTime[i].timeSec, g_RankingTime[i].score);
	}

	//�t�@�C���N���[�Y
	fclose(fp);

	return 0;
}

/*�����L���O�f�[�^�̓ǂݍ���*/
int SortSaveTime::ReadRanking(void)
{
	/*�ʏ탂�[�h*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL)
	{
		//�t�@�C���I�[�v��
		if ((fopen_s(&fp, "dat/rankingdata.txt", "r")) != 0)
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
		if ((fopen_s(&fp, "dat/rankingdata_HARD.txt", "r")) != 0)
		{
			/* �G���[���� */
			printf("Ranking Data Error\n");
			return -1;
		}
	}

	//�����L���O�f�[�^�z����f�[�^��ǂݍ���
	for (int i = 0; i < RANKING_DATA; i++)
	{
	/********
	* ����  *
	********/
		fscanf_s(fp, "%2d %10s %10d %10d %10d\n", &g_RankingTime[i].no, g_RankingTime[i].name, sizeof(g_RankingTime[i].name), &g_RankingTime[i].timeMin, &g_RankingTime[i].timeSec, &g_RankingTime[i].score);
	}

	//�t�@�C���N���[�Y
	fclose(fp);

	return 0;
}

/*�����L���O�f�[�^�i�\����*/
RankingDataTime SortSaveTime::getRankingData(int i)
{
	return g_RankingTime[i];
}

/*���O*/
void SortSaveTime::setName(int i, char name[11])
{
	int j;

	for (j = 0; '\0' != name[j]; j++)
	{
		g_RankingTime[i].name[j] = name[j];
	}
	g_RankingTime[i].name[j] = '\0';
}

/*�X�R�A*/
void SortSaveTime::setScore(int i, int score)
{
	if (0 <= score)
	{
		g_RankingTime[i].score = GameData::Get_Score();
	}
}

/*���ԁF��*/
void SortSaveTime::setTimerMin(int i, int time)
{
	if (0 < time)
	{
		g_RankingTime[i].timeMin = GameData::Get_Total_Time() / 3600;
	}
}

/*���ԁF�b*/
void SortSaveTime::setTimerSec(int i, int time)
{
	if (0 < time)
	{
		g_RankingTime[i].timeSec = (GameData::Get_Total_Time() % 3600) / 60;
	}
}