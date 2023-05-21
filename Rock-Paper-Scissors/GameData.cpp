#include"DxLib.h"
#include"GameData.h"



unsigned int GameData::g_score;     //�X�R�A
unsigned int GameData::max_score;   //�X�R�A
int GameData::pierced_count;        //�ђʉ�

int GameData::total_time;        //��������

int GameData::each_stage_time;   //�e�X�e�[�W�̐�������
int GameData::c_time_limit;      //�������ԁi�Œ�j

GAME_DIFFICULTY GameData::game_Diff;

//������
void GameData::Init_Data()
{
	g_score = 0;
	max_score = 0;
	total_time = 0;
}

//�X�R�A���Z
void GameData::Add_Score(unsigned int score)
{
	if (score < 0) return;
	max_score += score;
}

//�X�R�A�擾
unsigned int GameData::Get_Score()
{
	return g_score;
}

//�X�R�A�擾(�{��)
unsigned int GameData::Get_MaxScore()
{
	return max_score;
}

//�ђʉ񐔉��Z �f�t�H���g:2
void GameData::Add_PierceCount(const int& add)
{
	if (add == 0)     pierced_count = 0;    //������0�̎��͏���������
	else if (add > 0) pierced_count += add;
	else return;
}

//�ђʉ񐔎擾
int GameData::Get_PierceCount()
{
	return pierced_count;
}

//�������Ԃ�ݒ�i�e�X�e�[�W�̐������ԁj
void GameData::Set_TimeLimit(const int time_limit)
{
	//����3��

	//0�ȉ��̏ꍇ�͏������Ȃ�
	if (time_limit < 0)
	{
		each_stage_time = 999;
	}

	//each_stage_time = 10800;
	each_stage_time = time_limit;
	c_time_limit = each_stage_time;
}

//���ԃJ�E���^�[
void GameData::Time_Update()
{
	//�������Ԃ͉��Z
	total_time++;

	//�������Ԃ͌��Z
	each_stage_time--;
	if (each_stage_time < 0) each_stage_time = 0;

	if (g_score < max_score) g_score++;
	if (g_score > max_score) g_score = max_score;
}

//�������ԁi�ݒ�l�j�擾
int GameData::Get_ConstTimeLimit()
{
	return c_time_limit;
}

//(�e�X�e�[�W��)�������Ԃ��擾�i�~���b�j
int GameData::Get_Each_Time()
{
	return each_stage_time;
}

//(�e�X�e�[�W��)�������Ԃ��擾�i�b�j
int GameData::Get_Each_Time_Sec()
{
	//��(3600�~���b)�Ŋ������]��
	unsigned int ret = each_stage_time % 3600;

	if (each_stage_time < 1)
	{
		return 0;
	}
	else
	{
		//0���Z�h�~
		if (ret < 60)
			return 0;
		else
			return ret / 60;
	}
}

//(�e�X�e�[�W��)�������Ԃ��擾�i���j
int GameData::Get_Each_Time_Min()
{
	if (each_stage_time < 1)
	{
		return 0;
	}
	else
	{
		//0���Z�h�~
		if (each_stage_time < 3600)
			return 0;
		else
			return each_stage_time / 3600;
	}
}

//�������Ԃ��擾
int GameData::Get_Total_Time()
{
	return total_time;
}

/*��Փx*/
void GameData::Set_DIFFICULTY(GAME_DIFFICULTY game_diff)
{
	game_Diff = game_diff;
}

/*��Փx*/
GAME_DIFFICULTY GameData::Get_DIFFICULTY()
{
	return game_Diff;
}
