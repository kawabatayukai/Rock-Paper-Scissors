#pragma once
#include<iostream>

#define RANKING_DATA_COLUMN 10
#define RANKING_DATA_ROW 5

//��Փx
enum class GAME_DIFFICULTY
{
	NORMAL,/*�ʏ탂�[�h*/
	HARD,/*�������[�h*/
};

//�f�[�^��ێ�����
class GameData
{
public:

	//������
	static void Init_Data();

	//�X�R�A���Z
	static void Add_Score(unsigned int score);

	//�X�R�A�擾(�`��p)
	static unsigned int Get_Score();

	//�X�R�A�擾(�{��)
	static unsigned int Get_MaxScore();

	//�ђʉ񐔉��Z
	static void Add_PierceCount(const int& add = 2);

	//�ђʉ񐔎擾
	static int Get_PierceCount();

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

	//��Փx�擾
	static GAME_DIFFICULTY Get_DIFFICULTY();

	//��Փx�Z�b�g
	static void Set_DIFFICULTY(GAME_DIFFICULTY game_diff);

	//�v���C���[���擾
	static std::string GetPlayerName();

	//�v���C���[���Z�b�g
	static void SetPlayerName(const std::string& name);

private:
	GameData();     //�I�u�W�F�N�g�͍��Ȃ�

	static unsigned int g_score;       //�X�R�A�i�`��p�@1��������)
	static unsigned int max_score;     //�X�R�A
	static int pierced_count;          //�ђʉ� 6�ŉ�

	static int total_time;             //��������

	static GAME_DIFFICULTY game_Diff;  //��Փx

	static int each_stage_time;        //�e�X�e�[�W�̐�������
	static int c_time_limit;           //�������ԁi�ő�j

	static std::string player_name;    //�v���C���[���O
};