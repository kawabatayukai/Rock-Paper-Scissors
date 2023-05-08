#pragma once

//�f�[�^��ێ�����
class GameData
{
public:

	//������
	static void Init_Data();

	//�X�R�A���Z
	static void Add_Score(unsigned int score);

	//�X�R�A�擾(�`��p)
	static unsigned int Get_Score() ;

	//�X�R�A�擾(�{��)
	static unsigned int Get_MaxScore();

	//�������Ԃ�ݒ�i�e�X�e�[�W�̔ԍ��j
	static void Set_TimeLimit(const int time_limit = 10800);

	//���ԃJ�E���^�[
	static void Time_Update();

	//�������ԁi�ݒ�l�j�擾
	static int Get_ConstTimeLimit();

	//(�e�X�e�[�W��)�������Ԃ��擾�i�~���b�j
	static int Get_Each_Time();

	//(�e�X�e�[�W��)�������Ԃ��擾�i�b�j
	static int Get_Each_Time_Sec();

	//(�e�X�e�[�W��)�������Ԃ��擾�i���j
	static int Get_Each_Time_Min();

	//�������Ԃ��擾
	static int Get_Total_Time();

private:
	GameData();     //�I�u�W�F�N�g�͍��Ȃ�

	static unsigned int g_score;       //�X�R�A�i�`��p�@1��������)
	static unsigned int max_score;     //�X�R�A

	static int total_time;    //��������


	static int each_stage_time;   //�e�X�e�[�W�̐�������
	static int c_time_limit;      //�������ԁi�ő�j
};