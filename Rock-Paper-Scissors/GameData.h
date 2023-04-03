#pragma once

//�f�[�^��ێ�����
class GameData
{
public:

	//������
	static void Init_Data();

	//�X�R�A���Z
	static void Add_Score(unsigned int score);

	static unsigned int Get_Score() ;

	//�������Ԃ�ݒ�i�e�X�e�[�W�̔ԍ��j
	static void Set_TimeLimit(const unsigned int time_limit = 999);

	//���ԃJ�E���^�[
	static void Time_Update();

	//(�e�X�e�[�W��)�������Ԃ��擾
	static unsigned int Get_Each_Time();

	//�������Ԃ��擾
	static unsigned int Get_Total_Time();

private:
	GameData();     //�I�u�W�F�N�g�͍��Ȃ�

	static unsigned int g_score;       //�X�R�A�i�Q�[���v���C�������ƕێ��j
	static unsigned int total_time;    //��������


	static unsigned int each_stage_time;   //�e�X�e�[�W�̐�������
};