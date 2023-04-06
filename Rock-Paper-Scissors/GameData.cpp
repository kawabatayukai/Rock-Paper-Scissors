#include"DxLib.h"
#include"GameData.h"

namespace TIME_LIMIT
{
	//�e�X�e�[�W�̐�������

	const int LIMIT_STAGE_02 = 999;
	const int LIMIT_STAGE_03 = 999;
	const int LIMIT_STAGE_04 = 3600;
	const int LIMIT_STAGE_05 = 999;
	const int LIMIT_STAGE_06 = 999;
	const int LIMIT_STAGE_07 = 600;
	const int LIMIT_STAGE_08 = 999;
	const int LIMIT_STAGE_09 = 999;
	const int LIMIT_STAGE_10 = 999;
}

unsigned int GameData::g_score;           //�X�R�A�i�Q�[���v���C�������ƕێ��j
unsigned int GameData::total_time;        //��������

unsigned int GameData::each_stage_time;   //�e�X�e�[�W�̐�������

//������
void GameData::Init_Data()
{
	g_score = 0;
	total_time = 0;
}

//�X�R�A���Z
void GameData::Add_Score(unsigned int score)
{
	if (score < 0) return;
	g_score += score;
}

unsigned int GameData::Get_Score() 
{
	return g_score;
}


//�������Ԃ�ݒ�i�e�X�e�[�W�̔ԍ��j
void GameData::Set_TimeLimit(const unsigned int time_limit)
{
	//0�ȉ��̏ꍇ�͏������Ȃ�
	if (time_limit < 0)
	{
		each_stage_time = 999;
	}

	each_stage_time = time_limit;
}

//���ԃJ�E���^�[
void GameData::Time_Update()
{
	//�������Ԃ͉��Z
	total_time++;

	//�������Ԃ͌��Z
	each_stage_time--;
	if (each_stage_time < 0) each_stage_time = 0;
}

//(�e�X�e�[�W��)�������Ԃ��擾�i�~���b�j
unsigned int GameData::Get_Each_Time()
{
	return each_stage_time;
}

//(�e�X�e�[�W��)�������Ԃ��擾�i�b�j
unsigned int GameData::Get_Each_Time_Sec()
{
	//��(3600�~���b)�Ŋ������]��
	unsigned int ret = each_stage_time % 3600;

	//0���Z�h�~
	if (ret < 60) 
		return 0;
	else          
		return ret / 60;
}

//(�e�X�e�[�W��)�������Ԃ��擾�i���j
unsigned int GameData::Get_Each_Time_Min()
{
	//0���Z�h�~
	if (each_stage_time < 3600) 
		return 0;
	else 
		return each_stage_time / 3600;
}

//�������Ԃ��擾
unsigned int GameData::Get_Total_Time()
{
	return total_time;
}